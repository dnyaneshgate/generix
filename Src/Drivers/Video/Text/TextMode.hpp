#ifndef __GENERIX_DRIVER_VIDEO_TEXTMODE_HPP__
#define __GENERIX_DRIVER_VIDEO_TEXTMODE_HPP__

#include <ColorCode.hpp>

#define SCR_HEIGHT          25
#define SCR_WIDTH           80
#define SCR_PAGES           3
#define SCR_BUFFER_SIZE     SCR_HEIGHT * SCR_WIDTH
namespace Generix {

class GTextMode {
	friend class GVideo;

public:
	INT WriteString(const CHAR *str);
	VOID WriteChar(const CHAR ch);
	VOID Clear();
	VOID ClearLine(UINT line);
	VOID SetFontColor(Console::Color fColor);
	VOID SetBackColor(Console::Color bColor);
protected:
	VOID ScrollUp();
	VOID ScrollDown();
	VOID Refresh();
	VOID PartialRefresh();
	VOID UpdateCursor();
private:
	GTextMode();
	virtual ~GTextMode();
	//GTextMode(const GTextMode&){};
	USHORT *m_ScrHardwareBuffer;
	USHORT m_CrtcMem;
	UINT m_u_X;
	UINT m_u_Y;
	UINT m_u_Width;
	UINT m_u_Height;
	Console::Color m_FontColor;
	Console::Color m_BackColor;

	USHORT m_ScreenBuffer[ SCR_BUFFER_SIZE];
};

}
#endif //__GENERIX_DRIVER_VIDEO_TEXTMODE_HPP__
