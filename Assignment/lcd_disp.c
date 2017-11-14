#include <usbstk5515.h>

#include "LCD_FCN.h"
#define offset (int) 5

char *band_gain_display[9] = {"-12dB", " -9dB", " -6dB", " -3dB", "  0dB", "  3dB", "  6dB", "  9dB", " 12dB"};

void LCD_Clear(){
	Uint16 i;
 	 /* clear top plane */
	set_plane(0);
  	for (i=0; i<128; i++) {
    	OSD9616_send(0x40,0x00);
  	}
  	/* clear bottom plane */
  	set_plane(1);
  	for (i=0; i<128; i++) {
    	OSD9616_send(0x40,0x00);
  	}
}

void LCD_disp_init(){
	Uint16 i;
	set_plane(0);
	printstring("       MODE  LBG  MBG  HBG  ");
}

void LCD_disp_update(Int16 mode, Int16 b1, Int16 b2, Int16 b3){
	Uint16 i;
	set_plane(1);
//	OSD9616_send(0x00,0x2F);
	if (mode == 0){	
printstring("       BP  ");
	} else if(mode == 1) {
printstring("       LGE ");
	}else if(mode == 2) {
printstring("       MGE ");
	}else{
	printstring("       HGE ");
	}
printstring(band_gain_display[b1]);
printstring(band_gain_display[b2]);
printstring(band_gain_display[b3]);			
}


