#ifndef __GENERIX_SCREENIO_HPP__
#define __GENERIX_SCREENIO_HPP__

#include <Types.hpp>
#include <Macros.hpp>
#include <ColorCode.hpp>

namespace Console {

EXTERN "C" INT Write(const CHAR *str);
EXTERN "C" INT Writeln(const CHAR *str);
EXTERN "C" VOID Putch(const CHAR ch);
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

EXTERN "C" INT printk(const CHAR* format, ...) __attribute__((format(printf,1,2)));
EXTERN "C" INT dprintk(const CHAR* format, ...) __attribute__((format(printf,1,2)));

#endif //__GENERIX_SCREENIO_HPP__
