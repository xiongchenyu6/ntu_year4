#include <usbstk5515.h>
#include "LCD_FCN.h"
#include "font.h"

#define offset (int) 5

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
	for (i=0; i<7; i++){
		printLetter(tiny_font[5-offset]);
	}
	printLetter(tiny_font[50-offset]);
	printLetter(tiny_font[52-offset]);
	printLetter(tiny_font[41-offset]);
	printLetter(tiny_font[42-offset]);
	
	for (i=0; i<2; i++){
		printLetter(tiny_font[5-offset]);
	}
	printLetter(tiny_font[39-offset]);
	printLetter(tiny_font[41-offset]);
	printLetter(tiny_font[22-offset]);
	
	for (i=0; i<2; i++){
		printLetter(tiny_font[5-offset]);
	}
	printLetter(tiny_font[39-offset]);
	printLetter(tiny_font[41-offset]);
	printLetter(tiny_font[23-offset]);
	
	for (i=0; i<2; i++){
		printLetter(tiny_font[5-offset]);
	}
	printLetter(tiny_font[39-offset]);
	printLetter(tiny_font[41-offset]);
	printLetter(tiny_font[24-offset]);
	
}

void LCD_disp_update(Int16 mode, Int16 b1, Int16 b2, Int16 b3){
	Uint16 i;
	set_plane(1);
	for (i=0; i<128; i++) {
    	OSD9616_send(0x40,0x00);
  	}
  	// spaceholder
  	for (i=0; i<7; i++){
		printLetter(tiny_font[5-offset]);
	}
	if (mode == 0){	
	  	printLetter(tiny_font[39-offset]);
		printLetter(tiny_font[62-offset]);
		printLetter(tiny_font[53-offset]);
	} else {
		printLetter(tiny_font[44-offset]);
		printLetter(tiny_font[42-offset]);
		printLetter(tiny_font[54-offset]);
	}
	
	for (i=0; i<3; i++){
		printLetter(tiny_font[5-offset]);
	}
	if (b1 < 4){
		printLetter(tiny_font[18-offset]);
	} else if (b1 > 4){
		printLetter(tiny_font[16-offset]);
	} else if (b1 == 4){
		printLetter(tiny_font[5-offset]);
	}
	switch(b1){
		case 0:
			printLetter(tiny_font[22-offset]);
			printLetter(tiny_font[23-offset]);
			break;
		case 1:
			printLetter(tiny_font[21-offset]);
			printLetter(tiny_font[30-offset]);
			break;
		case 2:
			printLetter(tiny_font[21-offset]);
			printLetter(tiny_font[27-offset]);
			break;
		case 3:
			printLetter(tiny_font[21-offset]);
			printLetter(tiny_font[24-offset]);
			break;
		case 4:
			printLetter(tiny_font[21-offset]);
			printLetter(tiny_font[21-offset]);
			break;
		case 5:
			printLetter(tiny_font[21-offset]);
			printLetter(tiny_font[24-offset]);
			break;
		case 6:
			printLetter(tiny_font[21-offset]);
			printLetter(tiny_font[27-offset]);
			break;
		case 7:
			printLetter(tiny_font[21-offset]);
			printLetter(tiny_font[30-offset]);
			break;
		case 8:
			printLetter(tiny_font[22-offset]);
			printLetter(tiny_font[23-offset]);
			break;		
	}
	
	for (i=0; i<2; i++){
		printLetter(tiny_font[5-offset]);
	}
	if (b2 < 4){
		printLetter(tiny_font[18-offset]);
	} else if (b2 > 4){
		printLetter(tiny_font[16-offset]);
	} else if (b2 == 4){
		printLetter(tiny_font[5-offset]);
	}
	switch(b2){
		case 0:
			printLetter(tiny_font[22-offset]);
			printLetter(tiny_font[23-offset]);
			break;
		case 1:
			printLetter(tiny_font[21-offset]);
			printLetter(tiny_font[30-offset]);
			break;
		case 2:
			printLetter(tiny_font[21-offset]);
			printLetter(tiny_font[27-offset]);
			break;
		case 3:
			printLetter(tiny_font[21-offset]);
			printLetter(tiny_font[24-offset]);
			break;
		case 4:
			printLetter(tiny_font[21-offset]);
			printLetter(tiny_font[21-offset]);
			break;
		case 5:
			printLetter(tiny_font[21-offset]);
			printLetter(tiny_font[24-offset]);
			break;
		case 6:
			printLetter(tiny_font[21-offset]);
			printLetter(tiny_font[27-offset]);
			break;
		case 7:
			printLetter(tiny_font[21-offset]);
			printLetter(tiny_font[30-offset]);
			break;
		case 8:
			printLetter(tiny_font[22-offset]);
			printLetter(tiny_font[23-offset]);
			break;		
	}
	
	for (i=0; i<2; i++){
		printLetter(tiny_font[5-offset]);
	}
	if (b3 < 4){
		printLetter(tiny_font[18-offset]);
	} else if (b3 > 4){
		printLetter(tiny_font[16-offset]);
	} else if (b3 == 4){
		printLetter(tiny_font[5-offset]);
	}
	switch(b3){
		case 0:
			printLetter(tiny_font[22-offset]);
			printLetter(tiny_font[23-offset]);
			break;
		case 1:
			printLetter(tiny_font[21-offset]);
			printLetter(tiny_font[30-offset]);
			break;
		case 2:
			printLetter(tiny_font[21-offset]);
			printLetter(tiny_font[27-offset]);
			break;
		case 3:
			printLetter(tiny_font[21-offset]);
			printLetter(tiny_font[24-offset]);
			break;
		case 4:
			printLetter(tiny_font[21-offset]);
			printLetter(tiny_font[21-offset]);
			break;
		case 5:
			printLetter(tiny_font[21-offset]);
			printLetter(tiny_font[24-offset]);
			break;
		case 6:
			printLetter(tiny_font[21-offset]);
			printLetter(tiny_font[27-offset]);
			break;
		case 7:
			printLetter(tiny_font[21-offset]);
			printLetter(tiny_font[30-offset]);
			break;
		case 8:
			printLetter(tiny_font[22-offset]);
			printLetter(tiny_font[23-offset]);
			break;		
	}
		
	
}


