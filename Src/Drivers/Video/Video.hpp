#ifndef __GENERIX_DRIVER_VIDEO_HPP__
#define __GENERIX_DRIVER_VIDEO_HPP__

#include <Driver.hpp>
#include <Macros.hpp>
#include "Text/TextMode.hpp"
#include <Singleton.hpp>

namespace Generix {

class GVideo: public GDriver, public GSingleton<GVideo> {
	friend class GSingleton<GVideo> ;
public:
	INT Write(const CHAR *buffer);
	VOID Put(const CHAR ch);
	VOID ClrScr();
	VOID SetFontColor(Console::Color fColor);
	VOID SetBackColor(Console::Color bColor);
	Console::Color GetFontColor();
	Console::Color GetBackColor();
	VOID SetX(UINT X);
	VOID SetY(UINT Y);
	UINT GetX();
	UINT GetY();
	UINT GetWidth();
	UINT GetHeight();
	VOID Refresh();
	INT Write(CHAR *buffer, UINT size, ULONG64 offset);
	INT Read(CHAR *buffer, UINT size, ULONG64 offset);
	//GVideo();
	//~GVideo();
protected:

private:
	GVideo();
	~GVideo();
	GTextMode m_textMode;
};
}
#endif //__GENERIX_DRIVER_VIDEO_HPP__
