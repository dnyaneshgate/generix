#include <Types.hpp>
#include <Macros.hpp>
#include <Processor/Processor.hpp>
#include <string.h>
#include "TextMode.hpp"

namespace Generix {
#define ATTRIBUTE(F,B) ( SHL(B,4) | (F & 0xF) )

GTextMode::GTextMode() {
	m_u_X = m_u_Y = ZERO;
	m_u_Width = SCR_WIDTH;
	m_u_Height = SCR_HEIGHT;
	m_FontColor = Console::LIGHTGRAY;
	m_BackColor = Console::BLUE;
	bzero(m_ScreenBuffer, SCR_BUFFER_SIZE);

	CHAR c = (*(USHORT*) 0x410 & 0x30);
	if (c == 0x30) {
		m_ScrHardwareBuffer = (USHORT*) 0xB0000;
		m_CrtcMem = 0x3B4; // mono
	} else {
		m_ScrHardwareBuffer = (USHORT*) 0xB8000;
		m_CrtcMem = 0x3D4; // colour
	}
}

GTextMode::~GTextMode() {
}

VOID GTextMode::ScrollUp() {
	INT last = m_u_Width * (m_u_Height - 1);

	for (INT i = 0; i < last; i++) {
		m_ScreenBuffer[i] = m_ScreenBuffer[i + m_u_Width];
	}

	m_u_X = 0;
	m_u_Y = m_u_Height - 1;

	Refresh();
}

VOID GTextMode::ScrollDown() {

}

VOID GTextMode::UpdateCursor() {
	unsigned temp;
	temp = m_u_X + m_u_Y * m_u_Width;
	OUTB(m_CrtcMem + 0, 14);
	OUTB(m_CrtcMem + 1, SHR(temp, 8));
	OUTB(m_CrtcMem + 0, 15);
	OUTB(m_CrtcMem + 1, temp);
}

VOID GTextMode::Clear() {
	for (UINT i = 0; i < m_u_Height; i++) {
		ClearLine(i);
	}
	Refresh();
	m_u_X = m_u_Y = 0;
	UpdateCursor();
}

VOID GTextMode::ClearLine(UINT line) {
	if (line >= m_u_Height)
		return;

	for (UINT i = 0; i < m_u_Width; i++) {
		m_ScreenBuffer[line * m_u_Width + i] = (USHORT) (' '
				| SHL(ATTRIBUTE(m_FontColor, m_BackColor), 8));
	}
}

VOID GTextMode::Refresh() {
	memmove(m_ScrHardwareBuffer, m_ScreenBuffer,
			SCR_BUFFER_SIZE * sizeof(USHORT));
}

VOID GTextMode::PartialRefresh() {
	m_ScrHardwareBuffer[m_u_X + m_u_Width * m_u_Y] = m_ScreenBuffer[m_u_X
			+ m_u_Width * m_u_Y];
}

VOID GTextMode::SetFontColor(Console::Color fColor) {
	m_FontColor = fColor;
}

VOID GTextMode::SetBackColor(Console::Color bColor) {
	m_BackColor = bColor;
}

INT GTextMode::WriteString(const CHAR *S) {
	const CHAR *str = S;
	while (*str)
		WriteChar(*str++);

	return str - S;
}

VOID GTextMode::WriteChar(const CHAR ch) {
	switch (ch) {
	case '\n':
		m_u_X = 0;
		++m_u_Y;
		if (m_u_Y >= m_u_Height)
			ScrollUp();
		break;
	case '\t':
		m_u_X += 4;
		if (m_u_X >= m_u_Width) {
			m_u_X = 0;
			++m_u_Y;
		}
		break;
	case '\r':
		m_u_X = 0;
		break;
	case '\b':
		--m_u_X;
		m_ScreenBuffer[m_u_X + m_u_Width * m_u_Y] = (USHORT) (' '
				| SHL(ATTRIBUTE(m_FontColor, m_BackColor), 8));
		PartialRefresh();
		break;
	case '\a':
		break;
	default:
		if (m_u_X >= m_u_Width) {
			m_u_X = 0;
			++m_u_Y;
		}

		if (m_u_Y >= m_u_Height)
			ScrollUp();

		m_ScreenBuffer[m_u_X + m_u_Width * m_u_Y] = (USHORT) (ch
				| SHL(ATTRIBUTE(m_FontColor, m_BackColor), 8));
		PartialRefresh();
		++m_u_X;
		break;
	}
	UpdateCursor();
}

}
