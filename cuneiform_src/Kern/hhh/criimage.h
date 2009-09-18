/*
Copyright (c) 1993-2008, Cognitive Technologies
All rights reserved.

Разрешается повторное распространение и использование как в виде исходного кода,
так и в двоичной форме, с изменениями или без, при соблюдении следующих условий:

      * При повторном распространении исходного кода должны оставаться указанное
        выше уведомление об авторском праве, этот список условий и последующий
        отказ от гарантий.
      * При повторном распространении двоичного кода в документации и/или в
        других материалах, поставляемых при распространении, должны сохраняться
        указанная выше информация об авторском праве, этот список условий и
        последующий отказ от гарантий.
      * Ни название Cognitive Technologies, ни имена ее сотрудников не могут
        быть использованы в качестве средства поддержки и/или продвижения
        продуктов, основанных на этом ПО, без предварительного письменного
        разрешения.

ЭТА ПРОГРАММА ПРЕДОСТАВЛЕНА ВЛАДЕЛЬЦАМИ АВТОРСКИХ ПРАВ И/ИЛИ ДРУГИМИ ЛИЦАМИ "КАК
ОНА ЕСТЬ" БЕЗ КАКОГО-ЛИБО ВИДА ГАРАНТИЙ, ВЫРАЖЕННЫХ ЯВНО ИЛИ ПОДРАЗУМЕВАЕМЫХ,
ВКЛЮЧАЯ ГАРАНТИИ КОММЕРЧЕСКОЙ ЦЕННОСТИ И ПРИГОДНОСТИ ДЛЯ КОНКРЕТНОЙ ЦЕЛИ, НО НЕ
ОГРАНИЧИВАЯСЬ ИМИ. НИ ВЛАДЕЛЕЦ АВТОРСКИХ ПРАВ И НИ ОДНО ДРУГОЕ ЛИЦО, КОТОРОЕ
МОЖЕТ ИЗМЕНЯТЬ И/ИЛИ ПОВТОРНО РАСПРОСТРАНЯТЬ ПРОГРАММУ, НИ В КОЕМ СЛУЧАЕ НЕ
НЕСЁТ ОТВЕТСТВЕННОСТИ, ВКЛЮЧАЯ ЛЮБЫЕ ОБЩИЕ, СЛУЧАЙНЫЕ, СПЕЦИАЛЬНЫЕ ИЛИ
ПОСЛЕДОВАВШИЕ УБЫТКИ, СВЯЗАННЫЕ С ИСПОЛЬЗОВАНИЕМ ИЛИ ПОНЕСЕННЫЕ ВСЛЕДСТВИЕ
НЕВОЗМОЖНОСТИ ИСПОЛЬЗОВАНИЯ ПРОГРАММЫ (ВКЛЮЧАЯ ПОТЕРИ ДАННЫХ, ИЛИ ДАННЫЕ,
СТАВШИЕ НЕГОДНЫМИ, ИЛИ УБЫТКИ И/ИЛИ ПОТЕРИ ДОХОДОВ, ПОНЕСЕННЫЕ ИЗ-ЗА ДЕЙСТВИЙ
ТРЕТЬИХ ЛИЦ И/ИЛИ ОТКАЗА ПРОГРАММЫ РАБОТАТЬ СОВМЕСТНО С ДРУГИМИ ПРОГРАММАМИ,
НО НЕ ОГРАНИЧИВАЯСЬ ЭТИМИ СЛУЧАЯМИ), НО НЕ ОГРАНИЧИВАЯСЬ ИМИ, ДАЖЕ ЕСЛИ ТАКОЙ
ВЛАДЕЛЕЦ ИЛИ ДРУГОЕ ЛИЦО БЫЛИ ИЗВЕЩЕНЫ О ВОЗМОЖНОСТИ ТАКИХ УБЫТКОВ И ПОТЕРЬ.

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

#ifndef __CRIMAGE_HEADER_
#define __CRIMAGE_HEADER_

#ifndef __GLOBUS_H
 #include "globus.h"
#endif
 #include "cttypext.h"
///////////////////////////////////////////////////////////////////////////////////////////////
//#include"CTIDefines.h"
/*
#ifndef __RECDEFS_H
   #include "recdefs.h"
#endif
   #include "memfunc.h"
*/
///////////////////////////////////////////////////////////////////////////////////////////////
#ifdef __RIMAGE__
  #define RIMAGE_FUNC(a)  FUN_EXPO(a)
#else
  #define RIMAGE_FUNC(a)  FUN_IMPO(a)
#endif
///////////////////////////////////////////////////////////////////////////////////////////////
//#define     CIMAGE_CALLBACK_FUNC(a)         CIMAGE_FUNC(a)
#define     RIMAGE_CALLBACK_FUNC(a)         a
///////////////////////////////////////////////////////////////////////////////////////////////
#ifdef __cplusplus
	extern "C" {
#endif
///////////////////////////////////////////////////////////////////////////////////////////////
#pragma pack (push,8)
///////////////////////////////////////////////////////////////////////////////////////////////
# define	RIMAGE_MAXNAME 260
# define	RIMAGE_TURN_90        1
# define	RIMAGE_TURN_270       2
# define    RIMAGE_TURN_180       3
///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
# define    RIMAGEBOOL16          Bool16
# define    RIMAGEWORD            Word16
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
typedef struct tag_RIMAGE_MARGINS
{
	Word32    rmLeftMarg;
	Word32    rmTopMarg;
	Word32    rmRightMarg;
	Word32    rmBottomMarg;
}   RIMAGEMARGINS, *PRIMAGEMARGINS, **PPRIMAGEMARGINS;
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
RIMAGE_FUNC(Bool32) RIMAGE_Init(Word16 wHeightCode,Handle hStorage);
RIMAGE_FUNC(Bool32) RIMAGE_Done();
RIMAGE_FUNC(Bool32) RIMAGE_Reset();
RIMAGE_FUNC(Word32) RIMAGE_GetReturnCode();
RIMAGE_FUNC(Int8 *) RIMAGE_GetReturnString(Word32 dwError);
RIMAGE_FUNC(Bool32) RIMAGE_GetExportData(Word32 dwType, void * pData);
RIMAGE_FUNC(Bool32) RIMAGE_SetImportData(Word32 dwType, void * pData);
/////////////////////////////////////////////////////////////
typedef enum
{
		RIMAGE_FN_SetMargins = 1,
		RIMAGE_FN_Binarise,
		RIMAGE_FN_Rotate,
		RIMAGE_FN_Roll,
		RIMAGE_FN_Turn,
		RIMAGE_FN_Inverse,
		RIMAGE_FN_Flip,
		RIMAGE_FN_SetProgressCB,
		RIMAGE_FN_RotatePoint
} RIMAGE_EXPORT_ENTRIES;
//////////////////////////////////////////////////////////////////////////////////////////////
typedef void   (*PRIMAGECBPRogressStart)(void);
typedef Bool32 (*PRIMAGECBPRogressStep)(Word32);
typedef void   (*PRIMAGECBPRogressFinish)(void);
//////////////////////////////////////////////////////////////////////////////////////////////
typedef enum
{
		RIMAGE_FN_SetProgressStart = 32,
		RIMAGE_FN_SetProgressStep,
		RIMAGE_FN_SetProgressFinish
} RIMAGE_IMPORT_ENTRIES;
/////////////////////////////////////////////////////////////////////////////////////////
#define DEC_FUN(a,b,c) typedef a (*FNRIMAGE##b)c; RIMAGE_FUNC(a) RIMAGE_##b c
//////////////////////////////////////////////////////////////////////////////////////////
//
#define       RIMAGE_USE_MARGINS       TRUE
#define       RIMAGE_WITHOUT_MARGINS   FALSE
DEC_FUN(Bool32,  SetMargins,           (PRIMAGEMARGINS));
DEC_FUN(Bool32,  Binarise,             (PWord8 , PWord8 , Word32, Word32));
DEC_FUN(Bool32,  Rotate,               (PWord8 , PWord8 , Int32, Int32, Word32));
DEC_FUN(Bool32,  Roll,                 (PWord8 , PWord8 , Int32, Int32, Word32));
DEC_FUN(Bool32,  Turn,                 (PWord8 , PWord8 , Word32, Word32));
DEC_FUN(Bool32,  Inverse,              (PWord8 , PWord8 , Word32));
DEC_FUN(Bool32,  SetProgressCB,        (PRIMAGECBPRogressStart, PRIMAGECBPRogressStep , PRIMAGECBPRogressFinish));
DEC_FUN(Bool32,  RotatePoint,          (PWord8 , Int32, Int32, PInt32, PInt32));
//////////////////////////////////////////////////////////////////////////////////////////
//
#undef DEC_FUN
//////////////////////////////////////////////////////////////////////////////////////////
//
#pragma pack (pop)

#ifdef __cplusplus
            }
#endif
//////////////////////////////////////////////////////////////////////////////////////////
//
#endif //__CRIMAGE_HEADER_
//////////////////////////////////////////////////////////////////////////////////////////////////////////
// end of file
