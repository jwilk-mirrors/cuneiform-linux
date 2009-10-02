/*
Copyright (c) 1993-2008, Cognitive Technologies
All rights reserved.

����������� ��������� ��������������� � ������������� ��� � ���� ��������� ����,
��� � � �������� �����, � ����������� ��� ���, ��� ���������� ��������� �������:

      * ��� ��������� ��������������� ��������� ���� ������ ���������� ���������
        ���� ����������� �� ��������� �����, ���� ������ ������� � �����������
        ����� �� ��������.
      * ��� ��������� ��������������� ��������� ���� � ������������ �/��� �
        ������ ����������, ������������ ��� ���������������, ������ �����������
        ��������� ���� ���������� �� ��������� �����, ���� ������ ������� �
        ����������� ����� �� ��������.
      * �� �������� Cognitive Technologies, �� ����� �� ����������� �� �����
        ���� ������������ � �������� �������� ��������� �/��� �����������
        ���������, ���������� �� ���� ��, ��� ���������������� �����������
        ����������.

��� ��������� ������������� ����������� ��������� ���� �/��� ������� ������ "���
��� ����" ��� ������-���� ���� ��������, ���������� ���� ��� ���������������,
������� �������� ������������ �������� � ����������� ��� ���������� ����, �� ��
������������� ���. �� �������� ��������� ���� � �� ���� ������ ����, �������
����� �������� �/��� �������� �������������� ���������, �� � ���� ������ ��
��Ѩ� ���������������, ������� ����� �����, ���������, ����������� ���
������������� ������, ��������� � �������������� ��� ���������� ����������
������������� ������������� ��������� (������� ������ ������, ��� ������,
������� ���������, ��� ������ �/��� ������ �������, ���������� ��-�� ��������
������� ��� �/��� ������ ��������� �������� ��������� � ������� �����������,
�� �� ������������� ����� ��������), �� �� ������������� ���, ���� ���� �����
�������� ��� ������ ���� ���� �������� � ����������� ����� ������� � ������.

Redistribution and use in source and binary forms, with or without modification,
are permitted provided that the following conditions are met:

    * Redistributions of source code must retain the above copyright notice,
      this list of conditions and the following disclaimer.
    * Redistributions in binary form must reproduce the above copyright notice,
      this list of conditions and the following disclaimer in the documentation
      and/or other materials provided with the distribution.
    * Neither the name of the Cognitive Technologies nor the names of its
      contributors may be used to endorse or promote products derived from this
      software without specific prior written permission.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE
FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/


// HTML.cpp

//********************************************************************
//
// HTML.cpp - ������ HTML
//
// This file creation date: 27.05.99
// By Eugene Pliskin pliskin@cs.isa.ac.ru
//
// Changes by julien:
//   * added ocr_cinfo element (placed inside ocr_line element)
//   * moved <br> to be inside the ocr_line element (according to hocr spec)
//********************************************************************

#include <string.h>
#include "stdafx.h"
#include "rout_own.h"
#include "compat_defs.h"

#include <string>
#include <sstream>

#include <vector>

using namespace std;

static BOOL Static_MakeHTML(Handle hObject, long reason);

static BOOL FontStyle(ULONG newStyle);
static BOOL BeginParagraph(Handle hObject);
static BOOL CellStart();
static BOOL CalcCellSpan();
static BOOL OptimizeTags();
static BOOL Picture();
static BOOL CreatePageFilesFolder();

static ULONG sFontStyle = 0;		// ����� ������
static long rowspan = 0, colspan = 0;
static BOOL hocrmode = FALSE; // If true, print hOCR tags to output.

//********************************************************************
BOOL MakeHTML()
{
/* ������ HTML.

   ���������� �������.
   ����� ����� �����������, ���� gPreserveLineBreaks = TRUE.
*/
	sFontStyle = 0;			// ����� ������
	hocrmode = FALSE;

	return BrowsePage(Static_MakeHTML,
				FALSE,		// wantSkipTableCells
				FALSE);		// wantSkipParagraphs

}
//********************************************************************
BOOL MakeHOCR() {
    sFontStyle = 0;
    hocrmode = TRUE;
    return BrowsePage(Static_MakeHTML, FALSE, FALSE);
}

/*!
\brief \~english Put stream bufer into buffer for OCR results.
       \~russian ��������� ���������� ���������� ������ � �����
                 ����������� �������������.
*/
static BOOL
strm2buf(const ostringstream& outStrm)
{
	unsigned long sizeMem = outStrm.str().size();
	// �������� ������������� ������
	CHECK_MEMORY(sizeMem + 10);

	::memcpy(gMemCur, outStrm.str().c_str(), sizeMem);
	gMemCur += sizeMem;

	return TRUE;
}



/*!
\brief \~english Put info about hOCR text line into buffer for OCR results.
       \~russian ��������� ��������� ������ hOCR � ����� ����������� �������������.
*/
static BOOL
writeHocrLineStartTag(Byte* pLineStart, const edRect& rcLine, const unsigned int iLine)
{
	ASSERT(pLineStart);
	ostringstream outStrm;
	outStrm << "<span class='ocr_line' id='line_" << iLine << "' "
		<< "title=\"bbox "
		<< rcLine.left << " "
		<< rcLine.top << " "
		<< rcLine.right << " "
		<< rcLine.bottom << "\">";
	outStrm.write(reinterpret_cast<const char*>(pLineStart), gMemCur - pLineStart);

	unsigned long sizeMem = outStrm.str().size();
	// �������� ������������� ������
	CHECK_MEMORY(sizeMem + 10);

	::memcpy(pLineStart, outStrm.str().c_str(), sizeMem);
	gMemCur = pLineStart + sizeMem;

	return TRUE;
}



static bool
isGoodCharRect(const edRect& rc)
{
	bool goodCharRect = true;
	goodCharRect = goodCharRect && (rc.left != -1);
	goodCharRect = goodCharRect && (rc.left != 65535);
	goodCharRect = goodCharRect && (rc.right != 65535);
	goodCharRect = goodCharRect && (rc.top != 65535);
	goodCharRect = goodCharRect && (rc.bottom != 65535);
	return goodCharRect;
}

// decided to use CHECK_MEMORY macro in case it becomes a function which does more things than check if gMemCur+a>gMemEnd
// as a consequence, this function always returns true unless there is a memory issue.
static BOOL
writeHocrCharBBoxesInfo(const std::vector<edRect > &charBboxes, const unsigned int iLine)
{
	ostringstream outStrm;
	outStrm << "<span class='ocr_cinfo' id='line_" << iLine << "' " << "title=\"x_bboxes ";

	for (unsigned int i = 0; i < charBboxes.size(); i++) {

		outStrm << charBboxes[i].left << " " << charBboxes[i].top << " "
				<< charBboxes[i].right << " " << charBboxes[i].bottom;
	}

	outStrm << "\"></span>";

	unsigned long sizeMem = outStrm.str().size();

	// (check memory assures gMemCur can store and has 10 bytes extra).
	// the comment below was copied from writeHocrLine
	// �������� ������������� ������
	CHECK_MEMORY(sizeMem + 10);

	::memcpy(gMemCur, outStrm.str().c_str(), sizeMem);
	gMemCur += sizeMem;

	return TRUE;
}


//********************************************************************
BOOL Static_MakeHTML(
			Handle hObject,
			long reason	// ��. enum BROWSE_REASON
			)
{
	static char buf[256] = {0};
    //! \~russian ������������� �������
	edRect r = {0};

	static unsigned int iPage(1);
    //! \~russian ������������� ������
	//! \~english rectangle state variable, for the current line, is expanded per incoming char.
	static edRect rcLine = {0};
    //! \~russian ������������� ������
	//! \~english true if last none-space character was in line (i.e had a valid bbox).
	static bool isInLine(false);
    //! \~russian ����� ������� ������
	//! \~english state flag for current line nr.
	static unsigned int iLine(1);
    //! \~russian ������� ������ ������ � ��������� ������ ������
	static Byte* pLineStart = 0;
	//! \~english is the ptr to the location that gMemCur pointed to when reason was BROWSE_LINE_START

	static std::vector<edRect >	currentLineCharBBoxes;
	currentLineCharBBoxes.reserve(200);


	// � ����� ���������� WordControl

	switch(reason)
	{
		case BROWSE_CHAR: // ������
		{
			// ���������� ����
			long lang = CED_GetCharFontLang(hObject);
			if (lang != gLanguage)
				SetLanguage(lang);
			// ����� ������
			FontStyle(CED_GetCharFontAttribs(hObject));

			r = CED_GetCharLayout(hObject);
            currentLineCharBBoxes.push_back(r);

			// �������� ������
            if(isGoodCharRect(r) && hocrmode)
			{
                if (0 == isInLine)
				// ������ ����������� ������ ������
				{
					if (isGoodCharRect(r))
					{
						rcLine = r;
						isInLine = true;
					}
				}
				else
				{
					if (isGoodCharRect(r))
					{
						rcLine.left = min(rcLine.left, r.left);
						rcLine.top = min(rcLine.top, r.top);
						rcLine.right = max(rcLine.right, r.right);
						rcLine.bottom = max(rcLine.bottom, r.bottom);
					}
					else
					{
					}
				}
            }
            ONE_CHAR(hObject);

			break;
		}
		case BROWSE_LINE_START:
			// ������ ������ ������
			pLineStart = gMemCur;
			::memset(&rcLine, 0, sizeof(rcLine));
			break;

		case BROWSE_LINE_END:
			// ����� ������ ������
			writeHocrLineStartTag(pLineStart, rcLine, iLine);

			// write character bounding boxes info
			if (currentLineCharBBoxes.size())
				writeHocrCharBBoxesInfo(currentLineCharBBoxes, iLine);
			currentLineCharBBoxes.resize(0);


			isInLine = false;
			if ( gPreserveLineBreaks || gEdLineHardBreak )
			{
				PUT_STRING("<br>");
			}

			iLine++;
			// close HocrLine tag
			PUT_STRING("</span>");

			NEW_LINE;
			break;

		case BROWSE_PARAGRAPH_START:
			// ������ ������
			FontStyle(0);
			BeginParagraph(hObject);
			break;

		case BROWSE_PARAGRAPH_END:
			// ����� ������
			FontStyle(0);
			PUT_STRING("</p>");
			NEW_LINE;
			break;

		case BROWSE_PAGE_START:
			// Start of page.
			FontStyle(0);
			{
				ostringstream outStrm;
				outStrm << "<!DOCTYPE html PUBLIC \"-//W3C//DTD HTML 4.01 "
					       "Transitional//EN\""
						   " \"http://www.w3.org/TR/html4/loose.dtd\">" << endl;
				outStrm << "<html><head><title></title>" << endl;
				if (gActiveCode==ROUT_CODE_UTF8)
				{
					outStrm << "<meta http-equiv=\"Content-Type\""
						       " content=\"text/html;charset=utf-8\" >" << endl;
				}
				outStrm << "<meta name='ocr-system' content='openocr'>" << endl;
				outStrm << "</head>" << endl << "<body>";
				strm2buf(outStrm);
			}
			{
				ostringstream outStrm;
				EDSIZE sizeImage(CED_GetPageImageSize(hObject));
				const char* pImageName = CED_GetPageImageName(hObject);
				assert(pImageName);
				//������ <div class='ocr_page' title='image "page-000.pbm"; bbox 0 0 4306 6064'>
				outStrm << "<div class='ocr_page' id='page_" << iPage << "' ";
				outStrm << "title='image \"" << pImageName << "\"; bbox 0 0 "
					<< sizeImage.cx << " " << sizeImage.cy << "'>" << endl;
				strm2buf(outStrm);
				++iPage;
			}
			break;

		case BROWSE_PAGE_END:
			// ����� ��������
			PUT_STRING("</div>");
			// ����� ���������
			PUT_STRING("</body></html>");
			iLine = 1;
			break;

		case BROWSE_TABLE_START:
			// ������ �������
			FontStyle(0);
			PUT_STRING("<table border>");
			break;

		case BROWSE_TABLE_END:
			// ����� �������
			FontStyle(0);
			PUT_STRING("</table>");
			break;

		case BROWSE_ROW_START:
			// ������ ������ �������
			PUT_STRING("<tr>");
			break;

		case BROWSE_CELL_START:
			// ������ ������ �������
			CellStart();
			break;

		case BROWSE_PICTURE:
			// ��������
			Picture();
			break;

		}

	// �������� �� ������� � ��������
	WORDS_CONTROL(reason);

	// ���������� ���������� �����
	OptimizeTags();

	return TRUE;	// ���������� ��������
}
//********************************************************************
static BOOL FontStyle(ULONG newStyle)
{

if ((newStyle & FONT_BOLD) &&
				(!(sFontStyle & FONT_BOLD) ||
				  (sFontStyle & FONT_LIGHT)))
	{PUT_STRING("<b>");}

else if ((sFontStyle & FONT_BOLD) &&
				(!(newStyle & FONT_BOLD) ||
				  (newStyle & FONT_LIGHT)))
	{PUT_STRING("</b>");}

if ((newStyle & FONT_ITALIC) &&
				(!(sFontStyle & FONT_ITALIC) ))
	{PUT_STRING("<i>");}

else if ((sFontStyle & FONT_ITALIC) &&
				(!(newStyle & FONT_ITALIC) ))
	{PUT_STRING("</i>");}

if ((newStyle & FONT_UNDERLINE) &&
	!(sFontStyle & FONT_UNDERLINE))
	{PUT_STRING("<u>");}

else if ((sFontStyle & FONT_UNDERLINE) &&
		 !(newStyle & FONT_UNDERLINE))
	{PUT_STRING("</u>");}

// ��������� �����
sFontStyle = newStyle;
return TRUE;
}
//********************************************************************
static BOOL BeginParagraph(Handle hObject)
{
	const char *p = NULL;
	char buf[80] = "";
        edBox b = CED_GetLayout(hObject);
        ULONG alignment = CED_GetAlignment(hObject);

        switch (alignment & ALIGN_MASK)	{
	case ALIGN_CENTER:
		p = "center";
		break;

	case (ALIGN_LEFT | ALIGN_RIGHT):
		p = "justify";
		break;

	case ALIGN_LEFT:
	default:
		// "left" by default
	    ;
    }

    PUT_STRING("<p");
    if (p) {
        sprintf(buf, " align=%s", p);
        PUT_STRING(buf);
    }

    if (b.x != -1 && hocrmode) {
        sprintf(buf, " title=\"bbox %d %d %d %d\"", b.x, b.y, b.x + b.w, b.y
                + b.h);
        PUT_STRING(buf);
    }
    PUT_STRING(">");

    return TRUE;
}
//********************************************************************
static BOOL CellStart()
{
// ������ �������
	char buf[80] = "";

	// ��������� ������ ������
	CalcCellSpan();

	if ( rowspan == 1 && colspan == 1 )
		strcpy(buf,"<td>");

	else if ( rowspan > 1 && colspan == 1 )
		sprintf(buf,"<td rowspan=%d>",rowspan);

	else if ( rowspan == 1 && colspan > 1 )
		sprintf(buf,"<td colspan=%d>",colspan);

	else // ( rowspan > 1 && colspan > 1 )
		sprintf(buf,"<td rowspan=%d colspan=%d>",rowspan,colspan);

	PUT_STRING(buf);
	return TRUE;
}
//********************************************************************
static BOOL CalcCellSpan()
{
// ��������� ������ ������
	long row,col;

	rowspan = 0;
	colspan = 0;

	// �������� ���� �� ������� ������
	row = gIndexTableRow;
	col = gIndexTableCol;

	while ( row < gTableRows &&
			gIndexTableCell == gLogicalCells[row*gTableCols+col]
		  )
		{
		rowspan++;
		row++;
		}

	// �������� ������ �� ������� ������
	row = gIndexTableRow;
	col = gIndexTableCol;

	while ( col < gTableCols &&
			gIndexTableCell == gLogicalCells[row*gTableCols+col]
		  )
		{
		colspan++;
		col++;
		}

	ASSERT(rowspan>0 && colspan>0);
	return TRUE;
}
//********************************************************************
static BOOL OptimizeTags()
{
	// ���������� ���������� �����
	long l1 = 0, l2 = 0;
	char *p;

#define SUBST(a,b) {\
		l1 = strlen(a);\
		l2 = strlen(b);\
		p = (char*)gMemCur - l1;\
		if (!memcmp(a,p,l1))\
			{\
			strcpy(p,b);\
			gMemCur -= l1 - l2;\
			}\
		}

	SUBST("<td><p>","<td>");
	SUBST("</p><td>","<td>");
	SUBST("</p></table>","</table>");
	SUBST("<p></p>","");
	SUBST("<br></p>","</p>");

	return TRUE;
}
//********************************************************************
static BOOL Picture()
{
/* ��������.

	gPictureNumber - img number 1
	gPictureData   - DIB address, wiith header
	gPictureLength - DIB length, with header

	1. ������� �������� ��� �������� "<page>_files"
	2. �������� �������� � BMP-���� <�����>.bmp.
	3. �������� ��� "img" �� ������� �� ���� ��������.
*/
	char buf[256] = "";
	char absPicFileName[256] = "";
	char relPicFileName[256] = "";
	char dir[_MAX_PATH], name[_MAX_PATH], ext[_MAX_EXT];

	// create folder for images gPageFilesFolder.
	if ( !CreatePageFilesFolder() )
		return FALSE;

	// create file name
	split_path(gPageName, dir, name, ext);

	// write picture to bmp file
	if(dir[0])
	    sprintf(absPicFileName,"%s/%s/%d.bmp", dir,
	            gPageFilesFolder, gPictureNumber);
	else
	    sprintf(absPicFileName,"%s/%d.bmp",
	            gPageFilesFolder, gPictureNumber);

	sprintf (relPicFileName,"%s/%d.bmp",
		gPageFilesFolder, gPictureNumber);

	if ( !WritePictureToBMP_File(
					gPictureData,
					gPictureLength,
					absPicFileName)
		)
		return FALSE;

	// write img html tag.
	sprintf (buf,"<img src=%s "
"width=%d height=%d "
"alt=\"%s\">",
		relPicFileName,
		gPictureGoal.cx * 72L / 1440L,
		gPictureGoal.cy * 72L / 1440L,
		relPicFileName
		);

	PUT_STRING(buf);
	return TRUE;
}
//********************************************************************

/**
 * Create a subdirectory to hold image files for html document.
 */
static BOOL CreatePageFilesFolder() {
    // ������� �������� ��� �������� gPageFilesFolder.
    char dir[_MAX_PATH], name[_MAX_PATH], ext[_MAX_EXT], path[_MAX_PATH];

    // ������ �� ��� ��������?
    if (!gPageName[0])
        return FALSE;

    // ���������� ��� ��������
    split_path(gPageName, dir, name, ext);
    memset(gPageFilesFolder, 0, sizeof(gPageFilesFolder));
    sprintf(gPageFilesFolder, "%s_files", name);

    // ������� ��������
    if(dir[0])
        sprintf(path, "%s/%s", dir, gPageFilesFolder);
    else
        sprintf(path, "%s", gPageFilesFolder);
    if (CreateDirectory(&path[0], 0) == FALSE) {
        DWORD err = GetLastError();
        if (err != ERROR_ALREADY_EXISTS) {
            DEBUG_PRINT("CreatePageFilesFolder error = %d",err);
            return FALSE;
        }
    }

    return TRUE;
}
//********************************************************************
