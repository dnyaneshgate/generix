#include <Types.hpp>
#include <Macros.hpp>
#include <Processor/Processor.hpp>
#include <string.h>
#include <stdarg.h>
#include <ScreenIo.hpp>

using namespace Generix;

EXTERN "C" INT vsprintf(char * buf, const char * fmt, va_list args);
STATIC CHAR BUFF[BUFFSIZE];

namespace Console {
#define ATTRIBUTE(F,B) ( SHL(B,4) OR (F AND 0xF) )
#define TEXT_MODE 0
PRIVATE UINT WIDTH = 80, HEIGHT = 25;
#define BUFFERSIZE WIDTH * HEIGHT
PRIVATE UINT Xpos = 0, Ypos = 0;
PRIVATE USHORT *TEXTBUFFER = (USHORT*) 0xB8000;
PRIVATE Color FontColor = LIGHTGRAY;
PRIVATE Color BackColor = BLUE;
PRIVATE INT GraphicsMode = 0;
PRIVATE CCHAR __GETCHAR(INT X, INT Y, Color *fontColor, Color *backColor);
PRIVATE VOID __PUTCHAR(INT X, INT Y, CCHAR CH, Color fontColor, Color backColor);

PRIVATE VOID UpdateCursor() {
	unsigned temp;
	temp = Xpos + Ypos * WIDTH;
	OUTB(0x3D4 + 0, 14);
	OUTB(0x3D4 + 1, SHR(temp, 8));
	OUTB(0x3D4 + 0, 15);
	OUTB(0x3D4 + 1, temp);
}

PRIVATE VOID ScrollUp() {
	if (GraphicsMode == TEXT_MODE) {
		USHORT *buffer = (USHORT*) TEXTBUFFER;
		for (UINT i = 0; i LT HEIGHT; ++i) {
			memmove_w(buffer, buffer + WIDTH, WIDTH);
			buffer += WIDTH;
		}
		memset_w(buffer - WIDTH, (USHORT)(' ' | SHL(ATTRIBUTE(FontColor, BackColor), 8)), WIDTH);
		--Ypos;
		UpdateCursor();
	}
}

VOID Clear() {
	if (GraphicsMode == TEXT_MODE) {
		memset_w(TEXTBUFFER, (' ' | SHL(ATTRIBUTE(FontColor, BackColor), 8)),
		BUFFERSIZE);
		Xpos = Ypos = ZERO;
		UpdateCursor();
	}
}

VOID SetColor(Color fgColor, Color bgColor) {
	FontColor = fgColor;
	BackColor = bgColor;
}

VOID SetFontColor(Color fgColor) {
	FontColor = fgColor;
}

VOID SetBackColor(Color bgColor) {
	BackColor = bgColor;
}

Color GetFontColor() {
	return FontColor;
}

Color GetBackColor() {
	return BackColor;
}

UINT GetX() {
	return Xpos;
}

UINT GetY() {
	return Ypos;
}

VOID SetX(UINT X) {
	Xpos = X;
}

VOID SetY(UINT Y) {
	Ypos = Y;
}

UINT GetWidth() {
	return WIDTH;
}

UINT GetHeight() {
	return HEIGHT;
}

INT Write(CSTRING format, ...) {
	va_list args;
	va_start(args, format);
	vsprintf(BUFF, format, args);
	va_end(args);

	CSTRING str = BUFF;
	while (*str)
		Putch(*str++);
	return BUFF - str;
}

INT Writeln(CSTRING format, ...) {
	va_list args;
	va_start(args, format);
	vsprintf(BUFF, format, args);
	va_end(args);
	INT n = Write("%s\n", BUFF);
	return n;
}

VOID Putch(CCHAR ch) {
	switch (ch) {
	case '\n':
		Xpos = 0;
		++Ypos;
		if (Ypos >= HEIGHT)
			ScrollUp();
		break;
	case '\t':
		Xpos += 4;
		if (Xpos >= WIDTH) {
			Xpos = 0;
			++Ypos;
		}
		if (Ypos >= HEIGHT)
			ScrollUp();
		break;
	case '\r':
		Xpos = 0;
		break;
	case '\b':
		if (Xpos > 0) {
			--Xpos;
			__PUTCHAR(Xpos, Ypos, ' ', FontColor, BackColor);
		}
		break;
	default:
		if (Xpos >= WIDTH) {
			Xpos = 0;
			++Ypos;
		}

		if (Ypos >= HEIGHT)
			ScrollUp();

		__PUTCHAR(Xpos, Ypos, ch, FontColor, BackColor);

		++Xpos;
		break;
	}
	UpdateCursor();
}

PRIVATE VOID __PUTCHAR(INT X, INT Y, CCHAR CH, Color fontColor, Color backColor) {
	if (GraphicsMode == TEXT_MODE) {
		TEXTBUFFER[X + WIDTH * Y] = (USHORT) (CH
				| SHL(ATTRIBUTE(fontColor, backColor), 8));
	}
}

PRIVATE CCHAR __GETCHAR(INT X, INT Y, Color *fontColor, Color *backColor) {
	if (GraphicsMode == TEXT_MODE) {
		USHORT ch = TEXTBUFFER[X + WIDTH * Y];
		*fontColor = (Color)(SHR(ch, 8) AND 0x0f);
		*backColor = (Color)(SHR(ch, 12) AND 0x0f);
		return (CCHAR)(ch AND 0xff);
	}
	return (CCHAR)ZERO;
}

}

INT printk(CSTRING format, ...) {
	va_list args;
	va_start(args, format);
	vsprintf(BUFF, format, args);
	va_end(args);
	return Console::Write("%s", BUFF);
}

INT dprintk(INT flag, CSTRING file, const INT line, const CHAR* format, ...) {
	INT n = 0;

	va_list args;
	va_start(args, format);
	n = vsprintf(BUFF, format, args);
	va_end(args);

	Console::Color col = Console::GetFontColor();
	Console::SetFontColor(Console::DARKGRAY);
	n = Console::Writeln("[%s] %s:%d: %s",
			(flag EQU 0) ? "INFO" : (flag EQU 1) ? "WARN" :
			(flag EQU 2) ? "ERROR" : "", file, line, BUFF);
	Console::SetFontColor(col);

	return n;
}
