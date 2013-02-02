#ifndef __GENERIX_SCREENIO_HPP__
#define __GENERIX_SCREENIO_HPP__

#include <Types.hpp>
#include <Macros.hpp>
#include <ColorCode.hpp>

namespace Console {

EXTERN "C" INT Write(CSTRING str, ...)
		__attribute__((format(printf, 1, 2)));
EXTERN "C" INT Writeln(CSTRING str, ...)
		__attribute__((format(printf, 1, 2)));
EXTERN "C" VOID Putch(CCHAR ch);
EXTERN "C" VOID Clear();
EXTERN "C" VOID SetColor(Color fgColor, Color bgColor);
EXTERN "C" VOID SetFontColor(Color fgColor);
EXTERN "C" VOID SetBackColor(Color bgColor);
EXTERN "C" Color GetFontColor();
EXTERN "C" Color GetBackColor();
EXTERN "C" UINT GetX();
EXTERN "C" UINT GetY();
EXTERN "C" VOID SetX(UINT X);
EXTERN "C" VOID SetY(UINT Y);
EXTERN "C" UINT GetWidth();
EXTERN "C" UINT GetHeight();
//EXTERN "C" VOID  SetWidth(UINT width);
//EXTERN "C" VOID  SetHeight(UINT height);
EXTERN "C" VOID Refresh();

}

EXTERN "C" INT printk(CSTRING format, ...)
		__attribute__((format(printf, 1, 2)));
EXTERN "C" INT dprintk(INT flag, CSTRING file, const INT line,
		const CHAR* format, ...) __attribute__((format(printf, 4, 5)));
#define DEBUG_PRINT(flag, ...)  dprintk(flag, __FILE__, __LINE__, __VA_ARGS__)

#endif //__GENERIX_SCREENIO_HPP__
