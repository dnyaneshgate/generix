#include <Processor/Processor.hpp>
#include <string.h>
#include <stdarg.h>
#include "ScreenIo.hpp"

EXTERN "C" INT vsprintf(char * buf, const char * fmt, va_list args);

#define BUFFSIZE 512
STATIC CHAR BUFF[BUFFSIZE];

namespace Console {

#define ATTRIBUTE(F,B) ( SHL(B,4) | (F & 0xF) )

	const PRIVATE UINT WIDTH = 80, HEIGHT = 25;
	const PRIVATE UINT BUFFERSIZE = WIDTH * HEIGHT;
	PRIVATE USHORT DBUFFER[ BUFFERSIZE ] = {ZERO};
	PRIVATE UINT Xpos = 0, Ypos = 0;
	PRIVATE USHORT *TEXTBUFFER = (USHORT*) 0xB8000;
	PRIVATE Color FontColor = LIGHTGRAY;
	PRIVATE Color BackColor = BLUE;

	PRIVATE VOID ScrollUp() {
		memmove(TEXTBUFFER, DBUFFER + WIDTH, sizeof (USHORT) * WIDTH * (HEIGHT - 1));
	}

	PRIVATE VOID UpdateCursor() {
		unsigned temp;
		temp = Xpos + Ypos * WIDTH;
		OUTB(0x3D4 + 0, 14);
		OUTB(0x3D4 + 1, SHR(temp, 8));
		OUTB(0x3D4 + 0, 15);
		OUTB(0x3D4 + 1, temp);
	}

	PRIVATE VOID PartRefresh() {
		TEXTBUFFER[ Xpos + Ypos * WIDTH ] = DBUFFER[ Xpos + Ypos * WIDTH ];
	}

	VOID Refresh() {
		memmove(TEXTBUFFER, DBUFFER, sizeof (USHORT) * BUFFERSIZE);
	}

	VOID Clear() {
		for (UINT i = 0; i < BUFFERSIZE; i++)
			DBUFFER[i] = (USHORT) (' ' | SHL(ATTRIBUTE(FontColor, BackColor), 8));
		Refresh();
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

	/*INT Write(const CHAR *S) {
		const CHAR* str = S;
		while (*str)
			Putch(*str++);
		return S - str;
	}

	INT Writeln(const CHAR *S) {
		INT n = Write(S);
		Putch('\n');
		return ++n;
	}*/

	INT Write(const CHAR *format, ...) {
		va_list args;
		va_start(args, format);
		vsprintf(BUFF, format, args);
		va_end(args);

		const CHAR* str = BUFF;
		while (*str)
			Putch(*str++);
		return BUFF - str;
	}

	INT Writeln(const CHAR *format, ...) {
		va_list args;
		va_start(args, format);
		vsprintf(BUFF, format, args);
		va_end(args);
		INT n = Write(BUFF);
		Putch('\n');
		return ++n;
	}

	VOID Putch(const CHAR ch) {
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
				break;
			case '\r':
				Xpos = 0;
				break;
			case '\b':
				--Xpos;
				DBUFFER[Xpos + WIDTH * Ypos] = (USHORT) (' '
						| SHL(ATTRIBUTE(FontColor, BackColor), 8));
				PartRefresh();
				break;
			case '\a':
				break;
			default:
				if (Xpos >= WIDTH) {
					Xpos = 0;
					++Ypos;
				}

				if (Ypos >= HEIGHT)
					ScrollUp();

				DBUFFER[Xpos + WIDTH * Ypos] = (USHORT) (ch
						| SHL(ATTRIBUTE(FontColor, BackColor), 8));
				PartRefresh();
				++Xpos;
				break;
		}
		UpdateCursor();
	}

}

INT printk(const CHAR* format, ...) {
	va_list args;
	va_start(args, format);
	vsprintf(BUFF, format, args);
	va_end(args);
	return Console::Write(BUFF);
}

INT dprintk(const CHAR* format, ...) {
	INT n = 0;
#ifdef __DEBUG__
	va_list args;
	va_start(args, format);
	n = vsprintf(BUFF, format, args);
	va_end(args);
	
	Console::Color col = Console::GetFontColor();
	Console::SetFontColor(Console::DARKGRAY);
	n = Console::Write(BUFF);
	Console::SetFontColor(col);
#endif
	return n;
}
