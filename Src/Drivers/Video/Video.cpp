#include "Video.hpp"

GVideo GVideo::m_GVideo;

GVideo::GVideo() : GDriver(1, "Video")
{
	USHORT *vidm = (USHORT*)0xb8000;
	vidm[3] = (USHORT)('A'|(4 << 8));
}

GVideo::~GVideo()
{

}

INT
GVideo::Write(const CHAR *buffer)
{
	return m_textMode.WriteString(buffer);
}

VOID
GVideo::Put(const CHAR ch)
{
	m_textMode.WriteChar(ch);
}

VOID
GVideo::ClrScr()
{
	m_textMode.Clear();
}

VOID
GVideo::SetFontColor(Console::Color fColor)
{
	m_textMode.SetFontColor(fColor);
}

VOID
GVideo::SetBackColor(Console::Color bColor)
{
	m_textMode.SetBackColor(bColor);
}

Console::Color
GVideo::GetFontColor()
{
	return m_textMode.m_FontColor;
}

Console::Color
GVideo::GetBackColor()
{
	return m_textMode.m_BackColor;
}

VOID
GVideo::SetX(UINT X)
{
	m_textMode.m_u_X = X;
}

VOID
GVideo::SetY(UINT Y)
{
	m_textMode.m_u_Y = Y;
}

UINT
GVideo::GetX()
{
	return m_textMode.m_u_X;
}

UINT
GVideo::GetY()
{
	return m_textMode.m_u_Y;
}

UINT
GVideo::GetWidth()
{
	return m_textMode.m_u_Width;
}

UINT
GVideo::GetHeight()
{
	return m_textMode.m_u_Height;
}

VOID
GVideo::Refresh()
{
	m_textMode.Refresh();
}

INT 
GVideo::Write(CHAR *buffer, UINT size, ULLONG offset)
{
	return 0;
}

INT 
GVideo::Read(CHAR *buffer, UINT size, ULLONG offset)
{
	return 0;
}
