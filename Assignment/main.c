/*
 * Audio Bypass Project
 */

#include <usbstk5515.h>
#include <usbstk5515_i2c.h>
#include <AIC_func.h>
#include <stdio.h>
#include <Dsplib.h>
#include <sar.h>
#include <LCD_FCN.h>

#define TAPS	256

const char *band_gain_db[9] = {"-12dB", "-9dB", "-6dB", "-3dB", "0dB", "3dB", "6dB", "9dB", "12dB"};
// Compute hex of gain (linear gain is normalized by a factor of 4)
Int16 band_gain_hex[9] = {0x080A, 0x0B5B, 0x100A, 0x16A7, 0x2000, 0x2D34, 0x3FD9, 0x5A30, 0x7F65};
Int16 band_selection=0;

Int16 BAND1_COEF[TAPS] = {
	#include "lowBand.dat"
};
Int16 band1_gain_selection=4; 
Int16 band1_coef_changed[TAPS];

Int16 BAND2_COEF[TAPS] = {
	#include "midBand.dat"
};
Int16 band2_gain_selection=4; 
Int16 band2_coef_changed[TAPS];

Int16 BAND3_COEF[TAPS] = {
	#include "highBand.dat"
};
Int16 band3_gain_selection=4; 
Int16 band3_coef_changed[TAPS];

Int16 band_coef_mixed[TAPS];

Int16 dbuffer_left[TAPS+2] = {0};
Int16 dbuffer_right[TAPS+2] = {0};

void band_mix();
void check_btn_push(Uint16 value);
void calculate_new_coef();
void filter_init();

void main(void)
{
	Int16 x_right[1], x_left[1]; //AIC inputs
	Int16 r_right[1], r_left[1]; //AIC outputs
	Uint16 btn_value;

	USBSTK5515_init(); 	//Initializing the Processor
	AIC_init(); 		//Initializing the Audio Codec
	Init_SAR();
	LCD_init();
	My_LED_init();
	LCD_Clear();
	LCD_disp_init();
	filter_init();
	
	toggle_LED(band_selection);
	LCD_disp_update(band_selection, band1_gain_selection, band2_gain_selection, band3_gain_selection);
	
	while(1)
	{
		btn_value = Get_Key_Human();
		if (btn_value != NoKey)
			check_btn_push(btn_value);
				
		AIC_read2(&x_right[0], &x_left[0]);
		if (band_selection != 0){
			fir(&x_right[0],&band_coef_mixed[0],&r_right[0],&dbuffer_right[0],1,TAPS);
			fir(&x_left[0],&band_coef_mixed[0],&r_left[0],&dbuffer_left[0],1,TAPS);
			AIC_write2(r_right[0],r_left[0]);
		} else {
			AIC_write2(x_right[0],x_left[0]);
		}
		
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
	if (value == SW2){
		if (band_selection == 1){
			band1_gain_selection++;
			band1_gain_selection = band1_gain_selection % 9;
			calculate_new_coef();
			printf("Band 1 gain is %s.\n", band_gain_db[band1_gain_selection]);
		} else if (band_selection == 2){
			band2_gain_selection++;
			band2_gain_selection = band2_gain_selection % 9;
			calculate_new_coef();
			printf("Band 2 gain is %s.\n", band_gain_db[band2_gain_selection]);
		} else if (band_selection == 3){
			band3_gain_selection++;
			band3_gain_selection = band3_gain_selection % 9;
			calculate_new_coef();
			printf("Band 3 gain is %s.\n", band_gain_db[band3_gain_selection]);
		}		
		band_mix();
	} else if (value == SW1){
		toggle_LED(band_selection);
		band_selection++;
		band_selection = band_selection % 4;
		toggle_LED(band_selection);
		if (band_selection == 0)
			printf("Bypass mode is selected.\n");
		else if (band_selection == 1)
			printf("Band %d is selected.\n", band_selection);
		else if (band_selection == 2)
			printf("Band %d is selected.\n", band_selection);
		else if (band_selection == 3)
			printf("Band %d is selected.\n", band_selection);
	}
	
	LCD_disp_update(band_selection, band1_gain_selection, band2_gain_selection, band3_gain_selection);
	if (value == SW1 && band_selection == 0){
		toggle_LED(band_selection);
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

