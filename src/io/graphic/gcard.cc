/*
 *	PearPC
 *	gcard.cc
 *
 *	Copyright (C) 2003, 2004 Sebastian Biallas (sb@biallas.net)
 *
 *	This program is free software; you can redistribute it and/or modify
 *	it under the terms of the GNU General Public License version 2 as
 *	published by the Free Software Foundation.
 *
 *	This program is distributed in the hope that it will be useful,
 *	but WITHOUT ANY WARRANTY; without even the implied warranty of
 *	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *	GNU General Public License for more details.
 *
 *	You should have received a copy of the GNU General Public License
 *	along with this program; if not, write to the Free Software
 *	Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
 */

#include <cstdlib>
#include <cstring>

#include "debug/tracers.h"
#include "system/display.h"
#include "tools/snprintf.h"
#include "cpu_generic/ppc_tools.h"
#include "io/pic/pic.h"
#include "gcard.h"

DisplayCharacteristics gGraphicModes[MAX_GRAPHIC_MODES] = {
	{width: 640, height: 480, bytesPerPixel: 2, scanLineLength: 1280, vsyncFrequency: 60,
	 redShift: 10, redSize: 5, greenShift: 5, greenSize: 5, blueShift: 0, blueSize: 5},
};

/*
DisplayCharacteristics gGraphicModes[MAX_GRAPHIC_MODES] = {
	{width: 640, height: 480, bytesPerPixel: 2,
	 redShift: 10, redSize: 5, greenShift: 5, greenSize: 5, blueShift: 0, blueSize: 5},
	{width: 640, height: 480, bytesPerPixel: 4,
	 redShift: 16, redSize: 8, greenShift: 8, greenSize: 8, blueShift: 0, blueSize: 8},
	{width: 800, height: 600, bytesPerPixel: 2,
	 redShift: 10, redSize: 5, greenShift: 5, greenSize: 5, blueShift: 0, blueSize: 5},
	{width: 800, height: 600, bytesPerPixel: 4,
	 redShift: 16, redSize: 8, greenShift: 8, greenSize: 8, blueShift: 0, blueSize: 8},
	{width: 1024, height: 768, bytesPerPixel: 2,
	 redShift: 10, redSize: 5, greenShift: 5, greenSize: 5, blueShift: 0, blueSize: 5},
	{width: 1024, height: 768, bytesPerPixel: 4,
	 redShift: 16, redSize: 8, greenShift: 8, greenSize: 8, blueShift: 0, blueSize: 8},
	{width: 1152, height: 864, bytesPerPixel: 2,
	 redShift: 10, redSize: 5, greenShift: 5, greenSize: 5, blueShift: 0, blueSize: 5},
	{width: 1152, height: 864, bytesPerPixel: 4,
	 redShift: 16, redSize: 8, greenShift: 8, greenSize: 8, blueShift: 0, blueSize: 8},
	{width: 1280, height: 720, bytesPerPixel: 2,
	 redShift: 10, redSize: 5, greenShift: 5, greenSize: 5, blueShift: 0, blueSize: 5},
	{width: 1280, height: 720, bytesPerPixel: 4,
	 redShift: 16, redSize: 8, greenShift: 8, greenSize: 8, blueShift: 0, blueSize: 8},
	{width: 1280, height: 768, bytesPerPixel: 2,
	 redShift: 10, redSize: 5, greenShift: 5, greenSize: 5, blueShift: 0, blueSize: 5},
	{width: 1280, height: 768, bytesPerPixel: 4,
	 redShift: 16, redSize: 8, greenShift: 8, greenSize: 8, blueShift: 0, blueSize: 8},
	{width: 1280, height: 960, bytesPerPixel: 2,
	 redShift: 10, redSize: 5, greenShift: 5, greenSize: 5, blueShift: 0, blueSize: 5},
	{width: 1280, height: 960, bytesPerPixel: 4,
	 redShift: 16, redSize: 8, greenShift: 8, greenSize: 8, blueShift: 0, blueSize: 8},
	{width: 1280, height: 1024, bytesPerPixel: 2,
	 redShift: 10, redSize: 5, greenShift: 5, greenSize: 5, blueShift: 0, blueSize: 5},
	{width: 1280, height: 1024, bytesPerPixel: 4,
	 redShift: 16, redSize: 8, greenShift: 8, greenSize: 8, blueShift: 0, blueSize: 8},
	{width: 1360, height: 768, bytesPerPixel: 2,
	 redShift: 10, redSize: 5, greenShift: 5, greenSize: 5, blueShift: 0, blueSize: 5},
	{width: 1360, height: 768, bytesPerPixel: 4,
	 redShift: 16, redSize: 8, greenShift: 8, greenSize: 8, blueShift: 0, blueSize: 8},
	{width: 1600, height: 900, bytesPerPixel: 2,
	 redShift: 10, redSize: 5, greenShift: 5, greenSize: 5, blueShift: 0, blueSize: 5},
	{width: 1600, height: 900, bytesPerPixel: 4,
	 redShift: 16, redSize: 8, greenShift: 8, greenSize: 8, blueShift: 0, blueSize: 8},
	{width: 1600, height: 1024, bytesPerPixel: 2,
	 redShift: 10, redSize: 5, greenShift: 5, greenSize: 5, blueShift: 0, blueSize: 5},
	{width: 1600, height: 1024, bytesPerPixel: 4,
	 redShift: 16, redSize: 8, greenShift: 8, greenSize: 8, blueShift: 0, blueSize: 8},
	{width: 1600, height: 1200, bytesPerPixel: 2,
	 redShift: 10, redSize: 5, greenShift: 5, greenSize: 5, blueShift: 0, blueSize: 5},
	{width: 1600, height: 1200, bytesPerPixel: 4,
	 redShift: 16, redSize: 8, greenShift: 8, greenSize: 8, blueShift: 0, blueSize: 8},
};*/

PCI_GCard::PCI_GCard()
	:PCI_Device("pci-graphic", 0x00, 0x07)
{
	mIORegSize[0] = 0x400000;
	mIORegType[0] = PCI_ADDRESS_SPACE_MEM_PREFETCH;
/*	mIORegSize[1] = 0x20000;
	mIORegType[1] = PCI_ADDRESS_SPACE_MEM;
	mIORegSize[2] = 0x4000;
	mIORegType[2] = PCI_ADDRESS_SPACE_MEM;*/

//	mConfig[0x00] = 0x02;	// vendor ID
//	mConfig[0x01] = 0x10;
//	mConfig[0x02] = 0x45;	// unit ID
//	mConfig[0x03] = 0x52;
	mConfig[0x00] = 0x66;	// vendor ID
	mConfig[0x01] = 0x66;
	mConfig[0x02] = 0x66;	// unit ID
	mConfig[0x03] = 0x66;

	mConfig[0x08] = 0x00;	// revision
	mConfig[0x09] = 0x00;
	mConfig[0x0a] = 0x00;
	mConfig[0x0b] = 0x03;

	mConfig[0x0e] = 0x00;	// header-type
	
	assignMemAddress(0, IO_GCARD_FRAMEBUFFER_PA_START);
//	assignMemAddress(1, 0x80a20000);
//	assignMemAddress(2, 0x80a00000);
	
	mConfig[0x3c] = IO_PIC_IRQ_GCARD;
	mConfig[0x3d] = 1;
	mConfig[0x3e] = 0;
	mConfig[0x3f] = 0;
}

bool PCI_GCard::readDeviceMem(uint r, uint32 address, uint32 &data, uint size)
{
	IO_GRAPHIC_TRACE("read %d, %08x, %d\n", r, address, size);
	data = 0;
	return true;
}

bool PCI_GCard::writeDeviceMem(uint r, uint32 address, uint32 data, uint size)
{
	IO_GRAPHIC_TRACE("write %d, %08x, %08x, %d\n", r, address, data, size);
	return true;
}

#define MAYBE_PPC_HALF_TO_BE(a) ppc_half_to_BE(a)
#define MAYBE_PPC_WORD_TO_BE(a) ppc_word_to_BE(a)
#define MAYBE_PPC_DWORD_TO_BE(a) ppc_dword_to_BE(a)

void FASTCALL gcard_write_1(uint32 addr, uint32 data)
{
	addr -= IO_GCARD_FRAMEBUFFER_PA_START;
	*(uint8*)(gFrameBuffer+addr) = data;
	damageFrameBuffer(addr);
}

void FASTCALL gcard_write_2(uint32 addr, uint32 data)
{
	addr -= IO_GCARD_FRAMEBUFFER_PA_START;
	*(uint16*)(gFrameBuffer+addr) = MAYBE_PPC_HALF_TO_BE(data);
	damageFrameBuffer(addr);
}

void FASTCALL gcard_write_4(uint32 addr, uint32 data)
{
	addr -= IO_GCARD_FRAMEBUFFER_PA_START;
	*(uint32*)(gFrameBuffer+addr) = MAYBE_PPC_WORD_TO_BE(data);
	damageFrameBuffer(addr);
}

void FASTCALL gcard_write_8(uint32 addr, uint64 data)
{
	addr -= IO_GCARD_FRAMEBUFFER_PA_START;
	*(uint64*)(gFrameBuffer+addr) = MAYBE_PPC_DWORD_TO_BE(data);
	damageFrameBuffer(addr);
}

void FASTCALL gcard_read_1(uint32 addr, uint32 &data)
{
	addr-= IO_GCARD_FRAMEBUFFER_PA_START;
	data = (*(uint8*)(gFrameBuffer+addr));
}

void FASTCALL gcard_read_2(uint32 addr, uint32 &data)
{
	addr-= IO_GCARD_FRAMEBUFFER_PA_START;
	data = MAYBE_PPC_HALF_TO_BE(*(uint16*)(gFrameBuffer+addr));
}

void FASTCALL gcard_read_4(uint32 addr, uint32 &data)
{
	addr-= IO_GCARD_FRAMEBUFFER_PA_START;
	data = MAYBE_PPC_WORD_TO_BE(*(uint32*)(gFrameBuffer+addr));
}

void FASTCALL gcard_read_8(uint32 addr, uint64 &data)
{
	addr-= IO_GCARD_FRAMEBUFFER_PA_START;
	data = MAYBE_PPC_DWORD_TO_BE(*(uint64*)(gFrameBuffer+addr));
}

static bool gVBLon = false;
static int gCurrentGraphicMode;

void gcard_raise_interrupt()
{
	if (gVBLon) pic_raise_interrupt(IO_PIC_IRQ_GCARD);
}

void gcard_set_mode(int mode)
{
	gCurrentGraphicMode = mode;
}

#include "cpu_generic/ppc_cpu.h"
void gcard_osi()
{
	IO_GRAPHIC_TRACE("osi: %d\n", gCPU.gpr[5]);
	switch (gCPU.gpr[5]) {
	case 4:
		// cmount
//		SINGLESTEP("");
		return;
	case 28: {
		// set_vmode
		uint vmode = gCPU.gpr[6]-1;
		if (vmode > MAX_GRAPHIC_MODES || gCPU.gpr[7]) {
			gCPU.gpr[3] = 1;
			return;
		}
		IO_GRAPHIC_TRACE("set mode %d\n", vmode);
		gCPU.gpr[3] = gDisplay->changeResolution(gGraphicModes[vmode]) ? 0 : 1;
		return;
	}
	case 29: {
/*		
typedef struct osi_get_vmode_info {
	short		num_vmodes;
	short		cur_vmode;		// 1,2,... 
	short		num_depths;
	short		cur_depth_mode;		// 0,1,2,... 
	short		w,h;
	int		refresh;		// Hz/65536 

	int		depth;
	short		row_bytes;
	short		offset;
} osi_get_vmode_info_t;
*/
		// get_vmode_info
		int vmode = gCPU.gpr[6]-1;
		int depth_mode = gCPU.gpr[7];
		if (vmode == -1) {
			vmode = gCurrentGraphicMode;
			depth_mode = gGraphicModes[vmode].bytesPerPixel*8;
		}
		if (vmode > MAX_GRAPHIC_MODES || vmode < 0) {
			gCPU.gpr[3] = 1;
			return;
		}
		gCPU.gpr[3] = 0;
		gCPU.gpr[4] = (MAX_GRAPHIC_MODES<<16) | (vmode+1);
		gCPU.gpr[5] = (1<<16) | 0;
		gCPU.gpr[6] = (gGraphicModes[vmode].width << 16) | gGraphicModes[vmode].height;
		gCPU.gpr[7] = 85 << 16;
		gCPU.gpr[8] = gGraphicModes[vmode].bytesPerPixel*8;
		gCPU.gpr[9] = ((gGraphicModes[vmode].width * gGraphicModes[vmode].bytesPerPixel)<<16)
		              | 0;
		return;
	}
	case 31:
		// set_video_power
		gCPU.gpr[3] = 0;
		return;
	case 39:
		IO_GRAPHIC_TRACE("video_ctrl: %d\n", gCPU.gpr[6]);
		// video_ctrl
		switch (gCPU.gpr[6]) {
		case 0:
			gVBLon = false;
			break;
		case 1:
			gVBLon = true;
			break;
		default:
			IO_GRAPHIC_ERR("39\n");
		}
		gCPU.gpr[3] = 0;
		return;
	case 47:
//		printf("%c\n", gCPU.gpr[6]);
		return;
	case 59:
		// set_color
		gDisplay->setColor(gCPU.gpr[6], MK_RGB((gCPU.gpr[7]>>16)&0xff, (gCPU.gpr[7]>>8)&0xff, gCPU.gpr[7]&0xff));
		gCPU.gpr[3] = 0;
		return;
	case 64: {
		// get_color
		RGB c = gDisplay->getColor(gCPU.gpr[6]);
		gCPU.gpr[3] = (RGB_R(c) << 16) | (RGB_G(c) << 8) | (RGB_B(c));
		return;
	}
	case 116:
		// hardware_cursor_bla
//		SINGLESTEP("hw cursor!! %d, %d, %d\n", gCPU.gpr[6], gCPU.gpr[7], gCPU.gpr[8]);
		IO_GRAPHIC_TRACE("hw cursor!! %d, %d, %d\n", gCPU.gpr[6], gCPU.gpr[7], gCPU.gpr[8]);
		gDisplay->setHWCursor(gCPU.gpr[6], gCPU.gpr[7], gCPU.gpr[8], NULL);
		return;
	}
	IO_GRAPHIC_ERR("unknown osi function\n");
}

void gcard_init()
{
	gPCI_Devices->insert(new PCI_GCard());
}

void gcard_init_config()
{
}
