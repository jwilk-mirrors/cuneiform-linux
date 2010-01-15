/*
 Copyright (c) 1993-2008, Cognitive Technologies
 Copyright (c) 2010  Cuneiform development team

 All rights reserved.
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

#ifndef CUNEIFORM_H
#define CUNEIFORM_H

#ifdef MSVC
#error "This header will not work with MSVC."
#endif

#include<stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

// Format codes
enum PUMA_FORMATS {
    PUMA_TOEDNATIVE = 0,
    PUMA_TOTEXT = 0x02,
    PUMA_TOSMARTTEXT = 0x04,
    PUMA_TORTF = 0x08,
    PUMA_TOTABLETXT = 0x0100,
    PUMA_TOTABLECSV = 0x0200,
    PUMA_TOTABLEDBF = 0x0400,
    PUMA_TOTABLEODBC = 0x0800,
    PUMA_TOTABLEWKS = 0x1000,
    PUMA_TOHTML = 0x2000,
    PUMA_TOHOCR = 0x4000,
};

enum Languages {
    LANG_ENGLISH    = 0,
    LANG_GERMAN     = 1,
    LANG_FRENCH     = 2,
    LANG_RUSSIAN    = 3,
    LANG_SWEDISH    = 4,
    LANG_SPANISH    = 5,
    LANG_ITALIAN    = 6,
    LANG_RUSENG     = 7,
    LANG_UKRAINIAN  = 8,
    LANG_SERBIAN    = 9,
    LANG_CROATIAN   = 10,
    LANG_POLISH     = 11,
    LANG_DANISH     = 12,
    LANG_PORTUGUESE = 13,
    LANG_DUTCH      = 14,
    LANG_DIG        = 15,
    LANG_UZBEK      = 16,
    LANG_KAZ        = 17,
    LANG_KAZ_ENG    = 18,
    LANG_CZECH      = 19,
    LANG_ROMAN      = 20,
    LANG_HUNGAR     = 21,
    LANG_BULGAR     = 22,
    LANG_SLOVENIAN  = 23,
    LANG_LATVIAN    = 24,
    LANG_LITHUANIAN = 25,
    LANG_ESTONIAN   = 26,
    LANG_TURKISH    = 27,
    LANG_TOTAL      = 28,
    LG_LAT          =  1,
    LG_CYR          =  2,
};


# define PUMA_CODE_UNKNOWN    0x0000
# define PUMA_CODE_ASCII      0x0001
# define PUMA_CODE_ANSI       0x0002
# define PUMA_CODE_KOI8       0x0004
# define PUMA_CODE_ISO        0x0008
# define PUMA_CODE_UTF8       0x0010

# define PUMA_FORMAT_NONE 0x0040
# define PUMA_FORMAT_ALL  0x0001
# define PUMA_FORMAT_ONLY_FRAME 0x0002

# define PUMA_TABLE_NONE 0
# define PUMA_TABLE_DEFAULT 1
# define PUMA_TABLE_ONLY_LINE 2
# define PUMA_TABLE_ONLY_TEXT 3
# define PUMA_TABLE_LINE_TEXT 4

# define PUMA_PICTURE_NONE 0
# define PUMA_PICTURE_ALL 1

enum PUMA_EXPORT_ENTRIES {
    PUMA_FNPUMA_XOpen = 1,
    PUMA_FNPUMA_XClose,
    PUMA_FNPUMA_XPageAnalysis,
    PUMA_FNPUMA_XFinalRecognition,
    PUMA_FNPUMA_XSave,
    PUMA_FNPUMA_EnumLanguages,
    PUMA_FNPUMA_EnumFormats,
    PUMA_FNPUMA_EnumCodes,
    PUMA_Word32_Language,
    PUMA_Bool32_Speller,
    PUMA_Bool32_OneColumn,
    PUMA_Bool32_Fax100,
    PUMA_Bool32_DotMatrix,
    PUMA_pchar_UserDictName,
    PUMA_Bool32_Bold,
    PUMA_Bool32_Italic,
    PUMA_Bool32_Size,
    PUMA_Bool32_Format,
    PUMA_pchar_SerifName,
    PUMA_pchar_SansSerifName,
    PUMA_pchar_CourierName,
    PUMA_Word32_Pictures,
    PUMA_Word32_Tables,
    PUMA_pchar_Version,
    PUMA_Word32_Format,
    PUMA_FNPUMA_EnumFormatMode,
    PUMA_FNPUMA_EnumTable,
    PUMA_FNPUMA_EnumPicture,
    PUMA_Word8_Format,
    PUMA_FNPUMA_XGetRotateDIB,
    PUMA_FNPUMA_ProgressStart,
    PUMA_FNPUMA_ProgressFinish,
    PUMA_FNPUMA_ProgressStep,
    PUMA_Bool32_AutoRotate,
    PUMA_Point32_PageSize,
    PUMA_FNPUMA_RenameImageName,
    PUMA_FNPUMA_XSetTemplate,
    PUMA_Handle_CurrentEdPage,
    PUMA_FNPUMA_Save,
    PUMA_Bool32_PreserveLineBreaks,
    PUMA_FNPUMA_XOpenClbk,
    PUMA_LPPUMAENTRY_CED,
    PUMA_LPPUMAENTRY_ROUT,
    PUMA_FNPUMA_SaveToMemory,
    PUMA_FNPUMA_GetSpecialBuffer,
    PUMA_FNPUMA_SetSpecialProject,
    PUMA_FNPUMA_XGetTemplate
};

typedef int Bool;

Bool PUMA_Init(uint16_t wHeightCode, void* hStorage);
Bool PUMA_Done();
uint32_t PUMA_GetReturnCode();
char * PUMA_GetReturnString(uint32_t dwError);
Bool PUMA_GetExportData(uint32_t dwType, void * pData);
Bool PUMA_SetImportData(uint32_t dwType, void * pData);

Bool PUMA_XOpen(void * DIB_image, const char *identifier);
Bool PUMA_XClose(void);
Bool PUMA_XFinalRecognition(void);
Bool PUMA_XSave(const char * lpOutFileName, int32_t lnFormat, int32_t lnCode );
/*
Bool32 PUMA_XPageAnalysis(void);
int32_t PUMA_EnumLanguages(int32_t nPrev );
int32_t PUMA_EnumFormats(int32_t nPrev );
int32_t PUMA_EnumCodes(int32_t format, int32_t nPrev );
int32_t PUMA_EnumFormatMode(int32_t nPrev );
int32_t PUMA_EnumTable(int32_t nPrev );
int32_t PUMA_EnumPicture(int32_t nPrev );
Bool32 PUMA_XGetRotateDIB(void ** lpDIB, Point32 * p);
void  PUMA_RenameImageName(char * name);
Bool32 PUMA_XSetTemplate(Rect32 rect);
Bool32 PUMA_XGetTemplate(Rect32 *pRect);
Bool32 PUMA_Save(Handle hEdPage, const char * lpOutFileName, int32_t lnFormat, int32_t lnCode, Bool32 bAppend );
Bool32 PUMA_XOpenClbk,(PUMAIMAGECALLBACK CallBack,const char * lpFileName);
uint32_t PUMA_SaveToMemory(Handle hEdPage, int32_t lnFormat, int32_t lnCode, char * lpMem, uint32_t size );
void PUMA_GetSpecialBuffer(char * szResult,int32_t *nResultLength);
Bool32 PUMA_SetSpecialProject(uint8_t nSpecPrj);
*/
#ifdef __cplusplus
}
#endif

#endif
