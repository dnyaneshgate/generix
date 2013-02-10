#include <Types.hpp>
#include <Macros.hpp>
#include <Processor/Arch/IOPort.hpp>

using namespace Generix;
#define SZ(x) (sizeof(x)/sizeof(x[0]))
// misc out (3c2h) value for various modes
#define R_COM  0x63 // "common" bits
#define R_W256 0x00
#define R_W320 0x00
#define R_W360 0x04
#define R_W376 0x04
#define R_W400 0x04
#define R_H200 0x00
#define R_H224 0x80
#define R_H240 0x80
#define R_H256 0x80
#define R_H270 0x80
#define R_H300 0x80
#define R_H360 0x00
#define R_H400 0x00
#define R_H480 0x80
#define R_H564 0x80
#define R_H600 0x80
STATIC CONST BYTE hor_regs[] = { 0x0, 0x1, 0x2, 0x3, 0x4, 0x5, 0x13 };
STATIC CONST BYTE width_256[] = { 0x5f, 0x3f, 0x40, 0x82, 0x4a, 0x9a, 0x20 };
STATIC CONST BYTE width_320[] = { 0x5f, 0x4f, 0x50, 0x82, 0x54, 0x80, 0x28 };
STATIC CONST BYTE width_360[] = { 0x6b, 0x59, 0x5a, 0x8e, 0x5e, 0x8a, 0x2d };
STATIC CONST BYTE width_376[] = { 0x6e, 0x5d, 0x5e, 0x91, 0x62, 0x8f, 0x2f };
STATIC CONST BYTE width_400[] = { 0x70, 0x63, 0x64, 0x92, 0x65, 0x82, 0x32 };
STATIC CONST BYTE ver_regs[] = { 0x6, 0x7, 0x9, 0x10, 0x11, 0x12, 0x15, 0x16 };
STATIC CONST BYTE height_200[] = { 0xbf, 0x1f, 0x41, 0x9c, 0x8e, 0x8f, 0x96,
		0xb9 };
STATIC CONST BYTE height_224[] = { 0x0b, 0x3e, 0x41, 0xda, 0x9c, 0xbf, 0xc7,
		0x04 };
STATIC CONST BYTE height_240[] = { 0x0d, 0x3e, 0x41, 0xea, 0xac, 0xdf, 0xe7,
		0x06 };
STATIC CONST BYTE height_256[] = { 0x23, 0xb2, 0x61, 0x0a, 0xac, 0xff, 0x07,
		0x1a };
STATIC CONST BYTE height_270[] = { 0x30, 0xf0, 0x61, 0x20, 0xa9, 0x1b, 0x1f,
		0x2f };
STATIC CONST BYTE height_300[] = { 0x70, 0xf0, 0x61, 0x5b, 0x8c, 0x57, 0x58,
		0x70 };
STATIC CONST BYTE height_360[] = { 0xbf, 0x1f, 0x40, 0x88, 0x85, 0x67, 0x6d,
		0xba };
STATIC CONST BYTE height_400[] = { 0xbf, 0x1f, 0x40, 0x9c, 0x8e, 0x8f, 0x96,
		0xb9 };
STATIC CONST BYTE height_480[] = { 0x0d, 0x3e, 0x40, 0xea, 0xac, 0xdf, 0xe7,
		0x06 };
STATIC CONST BYTE height_564[] = { 0x62, 0xf0, 0x60, 0x37, 0x89, 0x33, 0x3c,
		0x5c };
STATIC CONST BYTE height_600[] = { 0x70, 0xf0, 0x60, 0x5b, 0x8c, 0x57, 0x58,
		0x70 };

// the chain4 parameter should be 1 for normal 13h-type mode, but
//only allows 320x200 256x200, 256x240 and 256x256 because you
// can only access the first 64kb

// if chain4 is 0, then plane mode is used (tweaked modes), and
// you'll need to switch planes to access the whole screen but
// that allows you using any resolution, up to 400x600

int init_graph_vga(int width, int height, int chain4)
// returns 1=ok, 0=fail
		{
	CONST BYTE *w, *h;
	BYTE val;
	UINT a;

	switch (width) {
	case 256:
		w = width_256;
		val = R_COM + R_W256;
		break;
	case 320:
		w = width_320;
		val = R_COM + R_W320;
		break;
	case 360:
		w = width_360;
		val = R_COM + R_W360;
		break;
	case 376:
		w = width_376;
		val = R_COM + R_W376;
		break;
	case 400:
		w = width_400;
		val = R_COM + R_W400;
		break;
	default:
		return 0; // fail
	}
	switch (height) {
	case 200:
		h = height_200;
		val |= R_H200;
		break;
	case 224:
		h = height_224;
		val |= R_H224;
		break;
	case 240:
		h = height_240;
		val |= R_H240;
		break;
	case 256:
		h = height_256;
		val |= R_H256;
		break;
	case 270:
		h = height_270;
		val |= R_H270;
		break;
	case 300:
		h = height_300;
		val |= R_H300;
		break;
	case 360:
		h = height_360;
		val |= R_H360;
		break;
	case 400:
		h = height_400;
		val |= R_H400;
		break;
	case 480:
		h = height_480;
		val |= R_H480;
		break;
	case 564:
		h = height_564;
		val |= R_H564;
		break;
	case 600:
		h = height_600;
		val |= R_H600;
		break;
	default:
		return 0; // fail
	}

	// chain4 not available if mode takes over 64k

	if (chain4 && (long) width * (long) height > 65536L)
		return 0;

	// here goes the actual modeswitch

	OUTB(0x3c2, val);
	OUTW(0x3d4, 0x0e11);
	// enable regs 0-7

	for (a = 0; a < SZ(hor_regs); ++a)
		OUTW(0x3d4, (WORD) ((w[a] << 8) + hor_regs[a]));
	for (a = 0; a < SZ(ver_regs); ++a)
		OUTW(0x3d4, (WORD) ((h[a] << 8) + ver_regs[a]));

	OUTW(0x3d4, 0x0008);
	// vert.panning = 0

	if (chain4) {
		OUTW(0x3d4, 0x4014);
		OUTW(0x3d4, 0xa317);
		OUTW(0x3c4, 0x0e04);
	} else {
		OUTW(0x3d4, 0x0014);
		OUTW(0x3d4, 0xe317);
		OUTW(0x3c4, 0x0604);
	}

	OUTW(0x3c4, 0x0101);
	OUTW(0x3c4, 0x0f02);
	// enable writing to all planes
	OUTW(0x3ce, 0x4005);
	// 256color mode
	OUTW(0x3ce, 0x0506);
	// graph mode & A000-AFFF

	UCHAR unused;
	INB(0x3da, &unused);
	OUTB(0x3c0, 0x30);
	OUTB(0x3c0, 0x41);
	OUTB(0x3c0, 0x33);
	OUTB(0x3c0, 0x00);

	for (a = 0; a < 16; a++) { // ega pal
		OUTB(0x3c0, (BYTE) a);
		OUTB(0x3c0, (BYTE) a);
	}

	OUTB(0x3c0, 0x20);
	// enable video

	return 1;
}

