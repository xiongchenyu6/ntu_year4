///*
// * main.c
// *      Toggle LEDs: Blue, Yellow, Red, Green
// * 		TI C5515 eZDSP
// * 		EE4413 - NTU Singapore - EEE
// * 		7/7/2017 
// */
//
//#include <usbstk5515.h>
//#include <usbstk5515_i2c.h>
//#include <stdio.h>
//#include <sar.h>
//#include <AIC_func.h>
//#include <firc.h>
//
////Addresses of the MMIO for the GPIO out registers: 1,2 
//#define LED_OUT1 SYS_GPIO_DATAOUT0
//#define LED_OUT2 SYS_GPIO_DATAOUT1
////Addresses of the MMIO for the GPIO direction registers: 1,2
//#define LED_DIR1 SYS_GPIO_DIR0    
//#define LED_DIR2 SYS_GPIO_DIR1
//
//#define bitGpio14 14
//#define bitGpio15 15
//#define bitGpio16 0
//#define bitGpio17 1
////Toggles LED specified by index Range 0 to 3
//void toggle_LED(int index)
//{
//	if(index == 3)  //Blue
//		LED_OUT1 = LED_OUT1 ^ (Uint16)(1<<(bitGpio14));
//	else if(index == 2)  //Yellow(ish)
//		LED_OUT1 = LED_OUT1 ^ (Uint16)(1<<(bitGpio15));
//	else if(index == 1)  //Red
//		LED_OUT2 = LED_OUT2 ^ (Uint16)(1<<(bitGpio16));
//	else if(index == 0)  //Green
//		LED_OUT2 = LED_OUT2 ^ (Uint16)(1<<(bitGpio17));
//}
//
////Makes the GPIO associated with the LEDs the correct direction; turns them off
//void My_LED_init()
//{
//	Uint16 temp=0x00;
//	Uint16 temp2=0x01;
//	temp |=(1<<14);
//	temp |=(Uint16)(1<<15);
//	LED_DIR1 |= temp; // set Yellow, Blue (14,15) as OUTPUT
//	temp2 |=(1<<1);
//	LED_DIR2 |= temp2; // set Red, Green (0,1) as OUTPUT
//
//	LED_OUT1 |= temp;  //Set LEDs 0, 1 to off
//	LED_OUT2 |= temp2;  //Set LEDs 2, 3 to off
//}
//Int16 i[TAPS] = {0};
//void main(void)
//{
//	//Uint16 value;
//	Int16 x_right[TAPS], x_left[TAPS];
//	Int16 r_right[TAPS], r_left[TAPS];
//	//USBSTK5515_init(); //Initializing the Processor
////	My_LED_init();
////	Init_SAR();
////	AIC_init();
//	Uint16 i=0;
//		Uint16 j=0;
//	Int16 right, left; //AIC inputs
//
//	USBSTK5515_init(); 	//Initializing the Processor
//	AIC_init(); 		//Initializing the Audio Codec
//	while(1)
//	{
////		printf("Which LED shall we toggle(0, 1, 2, or 3)?\n");
////		scanf("%d",&value);
////        value = Get_Sar_Key();
////        if ( value == SW1){
////        toggle_LED(1);
////        }
////        else if (value == SW2){
////        	toggle_LED(2);
////        }
////        else if (value == SW12){
////        	toggle_LED(3);
////        }
////		AIC_read2(x_right, x_left);
////		r_right[0]=x_right[0];
////		r_left[0]=x_left[0];
////		AIC_write2(r_right[0], r_left[0]);
//	if(i>=TAPS) {i=0;}
//	else{
//		AIC_read2(&right, &left);
//		x_right[i]=right;
//		x_left[i]=left;
//
//		i++;
//		}
//		if(j>=TAPS) {j=0;}else{
////			r_right[j] = x_right[j];
////			r_left[j] = x_left[j];
//		    r_right[j] = firc(j,x_right);
//		    r_left[j] = firc(j,x_left);
//			AIC_write2(r_right[j],r_left[j]);
//				j++;
//		}
//		
//		//r_right[0]=x_right[0]; //Audio Bypass
//		// POSTFILTER:
//	
//	}
//}
#include <usbstk5515.h>
#include <usbstk5515_i2c.h>
#include <AIC_func.h>
#include <stdio.h>
#include <Dsplib.h>
#include <LCD_FCN.h>

#define TAPS	49
//#define BLOCK_SIZE	32

Int16 LP[TAPS] = {
	#include "lpf.dat"
};
Int16 LP2[TAPS] = {
	#include "lpf.dat"
};
Int16 dbuffer_left[TAPS+2] = {0};
Int16 dbuffer_right[TAPS+2] = {0};
 
void main(void)
{
	Int16 x_right[1], x_left[1]; //AIC inputs
	Int16 r_right[1], r_left[1]; //AIC outputs
	
	Int8 message[128] = {134,1234,1234,1234,143};
	
	Int16 f = 0;
	Uint16 i=0;
	Uint16 j=0;
	char ti[23]; 

	USBSTK5515_init(); 	//Initializing the Processor
	AIC_init(); 		//Initializing the Audio Codec
	LCD_init();
//	OSD9616_multiSend(message,f);
 //   print_ti();
    clear_lcd();
  //	sprintf(ti,"ABCDEFG");
	//printstring(ti);
	printLetter(0xff,0x00,0xff,0x00);
	printLetter(0xff,0x00,0xff,0x00);
	printLetter(0xff,0x00,0xff,0x00);
	printLetter(0xff,0x00,0xff,0x00);
	printLetter(0xff,0x00,0xff,0x00);
	printLetter(0xff,0x00,0xff,0x00);
	printLetter(0x7f,0x00,0x4f,0x33);
	    printLetter(0x32,0x49,0x49,0x26);  // S
    printLetter(0x01,0x7F,0x01,0x01);  // T
    printLetter(0x7F,0x30,0x0E,0x7F);  // N
    printLetter(0x41,0x49,0x49,0x7F);  // E
    printLetter(0x7F,0x06,0x06,0x7F);  // M
    printLetter(0x3F,0x40,0x40,0x3F);  // U
    printLetter(0x46,0x29,0x19,0x7F);  // R
    printLetter(0x01,0x7F,0x01,0x01);  // T
    printLetter(0x32,0x49,0x49,0x26);  // S
    printLetter(0x7F,0x30,0x0E,0x7F);  // N
    printLetter(0x81,0x7F,0x81,0x00);  // I
	while(1)
	{
		AIC_read2(&x_right[i], &x_left[i]);
//		i++;
//		if (i==BLOCK_SIZE)
//		{
			fir(&x_right[0],&LP[0],&r_right[0],&dbuffer_right[0],1,TAPS);
	//		r_right[0]=x_right[0];
			fir(&x_left[0],&LP2[0],&r_left[0],&dbuffer_left[0],1,TAPS);
	//		r_left[0]=x_left[0];
//		}
		AIC_write2(r_right[j],r_left[j]);
//		j++;
	}
}

