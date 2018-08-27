#include <usbstk5515.h>
#include "usbstk5515_interrupts.h"
#include <usbstk5515_led.h>
#include <AIC_func.h>
#include <stdio.h>
#include <Dsplib.h>
#include "sar.h"
#include "LCD_FCN.h"
#include "lcd_disp.h"
#define TAPS	256
#define TIMENT1_0 = *((ioport volatile Uint16 *)0x1814)
#define TIME_START 0x8001
#define TIME_STOP 0x8000

const char *band_gain_db[9] = {"-12dB", "-9dB", "-6dB", "-3dB", "0dB", "3dB", "6dB", "9dB", "12dB"};
// Compute hex of gain (linear gain is normalized by a factor of 4)
Int16 band_gain_hex[9] = {0x080A, 0x0B5B, 0x100A, 0x16A7, 0x2000, 0x2D34, 0x3FD9, 0x5A30, 0x7F65};
Int16 band_gain_led[9] = {9,8,7,6,5,4,3,2,1};
Int16 band_selection=0;

Int16 BAND1_COEF[TAPS] = {
	#include "band1_coef.dat"
};
Int16 band1_gain_selection=4; 
Int16 band1_coef_changed[TAPS];

Int16 BAND2_COEF[TAPS] = {
	#include "band2_coef.dat"
};
Int16 band2_gain_selection=4; 
Int16 band2_coef_changed[TAPS];

Int16 BAND3_COEF[TAPS] = {
	#include "band3_coef.dat"
};
Int16 band3_gain_selection=4; 
Int16 band3_coef_changed[TAPS];

Int16 band_coef_mixed[TAPS];

Int16 dbuffer_left[TAPS+2] = {0};
Int16 dbuffer_right[TAPS+2] = {0};

Int16 x_right[1], x_left[1]; //AIC inputs
Int16 r_right[1], r_left[1]; //AIC outputs
Uint16 btn_value;
void band_mix();
void check_btn_push(Uint16 value);
void calculate_new_coef();
void filter_init();
void Reset();

interrupt void Timer_Handler()
{	  
	int timerset0 = TIAFR & 0x0001;
    int timerset1 = (TIAFR & 0x0002) >> 1;
    int timerset2 = (TIAFR & 0x0004) >> 2;
    if(timerset0){
    	TIAFR = 0x0001;
    	USBSTK5515_ULED_toggle(1);
    }
    if(timerset1){
    	TIAFR = 0x0002;
    	USBSTK5515_ULED_toggle(2);
    }
    if(timerset2){
    	TIAFR = 0x0004;
    	USBSTK5515_ULED_toggle(3);
    } 
}

Uint32 reset_loc = (Uint32)Reset;

void Timer_setup()
{

	//Set up Interrupt Vector Pointer Table
	IVPD = reset_loc >> 8;
	IVPH = reset_loc >> 8;

	*((Uint32*)((reset_loc + TINT)>>1)) = (Uint32)Timer_Handler; //Table points to our handler

	IER0 |= (1 << TINT_BIT);//enable interrupt
	IFR0 &= (1 << TINT_BIT);//clear the flag

	TCR0 = TIME_STOP;
	TPR0_1 = 0xffff; //Set all counters and period regs to the same value
	TPR0_2 = 0x0500;

	TCR1 = TIME_STOP;
	TPR1_1 = 0xffff; //Set all counters and period regs to the same value
	TPR1_2 = 0x0500;
	
	TCR2 = TIME_STOP;
	TPR2_1 = 0xffff; //Set all counters and period regs to the same value
	TPR2_2 = 0x0500;
	
	TIAFR = 0x0007;//Set the three bits to zero
	TCR0 |= TIME_START_AUTOLOAD;
	TCR1 |= TIME_START_AUTOLOAD;
	TCR2 |= TIME_START_AUTOLOAD;
}

interrupt void I2S_ISR()
{
	AIC_read2(&x_right[0], &x_left[0]);
	if (band_selection != 0){
		fir(&x_right[0],&band_coef_mixed[0],&r_right[0],&dbuffer_right[0],1,TAPS);
		fir(&x_left[0],&band_coef_mixed[0],&r_left[0],&dbuffer_left[0],1,TAPS);
		AIC_write2(r_right[0],r_left[0]);
	} else {
		AIC_write2(x_right[0],x_left[0]);
	}
	IFR0 &= (1 << I2S_BIT_POS);//clear the flag

}

void I2S_Setup()
{
	*((Uint32*)((reset_loc + I2S_ISR_OFFSET)>>1)) = (Uint32)I2S_ISR;

	IER0 |= (1 << I2S_BIT_POS);//enable interrupt
	IFR0 &= (1 << I2S_BIT_POS);//clear the flag
}

void main(void)
{
	USBSTK5515_init();
	USBSTK5515_ULED_init();
	Timer_setup();
	I2S_Setup();
	AIC_init();
	Init_SAR();
	LCD_init();
	LCD_Clear();
	LCD_disp_init();
	filter_init();
	LCD_disp_update(band_selection, band1_gain_selection, band2_gain_selection, band3_gain_selection);
	USBSTK5515_ULED_on(0);
	_enable_interrupts();
	while(1){
	  btn_value = Get_Key_Human();
	  if (btn_value != NoKey)
		check_btn_push(btn_value);
	}
}

void filter_init(){	
	int i;
	for(i=0;i<TAPS;i++){
		band1_coef_changed[i]=(Int16)(((Int32)BAND1_COEF[i]*(Int32)band_gain_hex[band1_gain_selection])>>15);
		band2_coef_changed[i]=(Int16)(((Int32)BAND2_COEF[i]*(Int32)band_gain_hex[band2_gain_selection])>>15);
		band3_coef_changed[i]=(Int16)(((Int32)BAND3_COEF[i]*(Int32)band_gain_hex[band3_gain_selection])>>15);
	}
	band_mix();
}

void check_btn_push(Uint16 value){
	if (value == SW12){
		band_selection--;
		if(band_selection == -1){
		band_selection = 3;
		}
	} else if (value == SW1){
		band_selection++;
		if(band_selection == 4){
		band_selection = 0;
		}
		if (band_selection == 0){
	        USBSTK5515_ULED_on(0);
		}
		else if (band_selection == 1){
		    USBSTK5515_ULED_off(0);
		}
			
	}else if(value == SW2) {
	if (band_selection == 0){
	        USBSTK5515_ULED_on(0);
		}
		else if (band_selection == 3){
		    USBSTK5515_ULED_off(0);
			}
		if (band_selection == 1){
			band1_gain_selection++;
			band1_gain_selection = band1_gain_selection % 9;
			TPR0_2 = band_gain_led[band1_gain_selection] *100;
			calculate_new_coef();
		} else if (band_selection == 2){
			band2_gain_selection++;
			band2_gain_selection = band2_gain_selection % 9;
			TPR1_2 = band_gain_led[band2_gain_selection] *100;
			calculate_new_coef();
		} else if (band_selection == 3){
			band3_gain_selection++;
			band3_gain_selection = band3_gain_selection % 9;
			TPR2_2 = band_gain_led[band3_gain_selection] *100;
			calculate_new_coef();
		}		
		band_mix();
	}
	
	LCD_disp_update(band_selection, band1_gain_selection, band2_gain_selection, band3_gain_selection);
	if (value == SW1 && band_selection == 0){
		USBSTK5515_ULED_toggle(band_selection);
	}
}

void calculate_new_coef(){
	int i;
	if (band_selection == 1){
		for(i=0;i<TAPS;i++)
			band1_coef_changed[i]=(Int16)(((Int32)BAND1_COEF[i]*(Int32)band_gain_hex[band1_gain_selection])>>15);
	} else if (band_selection == 2){
		for(i=0;i<TAPS;i++)
			band2_coef_changed[i]=(Int16)(((Int32)BAND2_COEF[i]*(Int32)band_gain_hex[band2_gain_selection])>>15);
	} else if (band_selection == 3){
		for(i=0;i<TAPS;i++)
			band3_coef_changed[i]=(Int16)(((Int32)BAND3_COEF[i]*(Int32)band_gain_hex[band3_gain_selection])>>15);
	}
}

void band_mix(){
	int i;
	for(i=0;i<TAPS;i++)
		band_coef_mixed[i] = band1_coef_changed[i] + band2_coef_changed[i] + band3_coef_changed[i];
}
