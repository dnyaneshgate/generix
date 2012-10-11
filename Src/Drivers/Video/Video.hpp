#ifndef __GENERIX_DRIVER_VIDEO_HPP__
#define __GENERIX_DRIVER_VIDEO_HPP__

#include <Driver.hpp>
#include <Macros.hpp>
#include "Text/TextMode.hpp"

namespace Generix {

	class GVideo : public GDriver {
	public:

		STATIC GVideo* Instance() {
			return &m_GVideo;
		}
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
		INT Write(CHAR *buffer, UINT size, ULLONG offset);
		INT Read(CHAR *buffer, UINT size, ULLONG offset);
		GVideo();
		virtual ~GVideo();
	protected:

	private:
		//	GVideo();
		//	virtual ~GVideo();
		STATIC GVideo m_GVideo;
		GTextMode m_textMode;
	};
}
#endif //__GENERIX_DRIVER_VIDEO_HPP__
