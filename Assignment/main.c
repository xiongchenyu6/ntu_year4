///*
// * Audio Bypass Project
// */
//
//#include <usbstk5515.h>
//#include <usbstk5515_i2c.h>
//#include <AIC_func.h>
//#include <stdio.h>
//#include <Dsplib.h>
//#include "sar.h"
//#include "led.h"
//#include "LCD_FCN.h"
//#include "lcd_disp.h"
//
//#define TAPS	256
//
//const char *band_gain_db[9] = {"-12dB", "-9dB", "-6dB", "-3dB", "0dB", "3dB", "6dB", "9dB", "12dB"};
//// Compute hex of gain (linear gain is normalized by a factor of 4)
//Int16 band_gain_hex[9] = {0x080A, 0x0B5B, 0x100A, 0x16A7, 0x2000, 0x2D34, 0x3FD9, 0x5A30, 0x7F65};
//Int16 band_selection=0;
//
//Int16 BAND1_COEF[TAPS] = {
//	#include "band1_coef.dat"
//};
//Int16 band1_gain_selection=4; 
//Int16 band1_coef_changed[TAPS];
//
//Int16 BAND2_COEF[TAPS] = {
//	#include "band2_coef.dat"
//};
//Int16 band2_gain_selection=4; 
//Int16 band2_coef_changed[TAPS];
//
//Int16 BAND3_COEF[TAPS] = {
//	#include "band3_coef.dat"
//};
//Int16 band3_gain_selection=4; 
//Int16 band3_coef_changed[TAPS];
//
//Int16 band_coef_mixed[TAPS];
//
//Int16 dbuffer_left[TAPS+2] = {0};
//Int16 dbuffer_right[TAPS+2] = {0};
//
//void band_mix();
//void check_btn_push(Uint16 value);
//void calculate_new_coef();
//void filter_init();
//
//void main(void)
//{
//	Int16 x_right[1], x_left[1]; //AIC inputs
//	Int16 r_right[1], r_left[1]; //AIC outputs
//	Uint16 btn_value;
//
//	USBSTK5515_init(); 	//Initializing the Processor
//	AIC_init(); 		//Initializing the Audio Codec
//	Init_SAR();
//	LCD_init();
//	My_LED_init();
//	LCD_Clear();
//	LCD_disp_init();
//	filter_init();
//	
//	toggle_LED(band_selection);
//	LCD_disp_update(band_selection, band1_gain_selection, band2_gain_selection, band3_gain_selection);
//	
//	while(1)
//	{
//		btn_value = Get_Key_Human();
//		if (btn_value != NoKey)
//			check_btn_push(btn_value);
//				
//		AIC_read2(&x_right[0], &x_left[0]);
//		if (band_selection != 0){
//			fir(&x_right[0],&band_coef_mixed[0],&r_right[0],&dbuffer_right[0],1,TAPS);
//			fir(&x_left[0],&band_coef_mixed[0],&r_left[0],&dbuffer_left[0],1,TAPS);
//			AIC_write2(r_right[0],r_left[0]);
//		} else {
//			AIC_write2(x_right[0],x_left[0]);
//		}
//		
//	}
//}
//void filter_init(){	
//	int i;
//	for(i=0;i<TAPS;i++){
//		band1_coef_changed[i]=(Int16)(((Int32)BAND1_COEF[i]*(Int32)band_gain_hex[band1_gain_selection])>>15);
//		band2_coef_changed[i]=(Int16)(((Int32)BAND2_COEF[i]*(Int32)band_gain_hex[band2_gain_selection])>>15);
//		band3_coef_changed[i]=(Int16)(((Int32)BAND3_COEF[i]*(Int32)band_gain_hex[band3_gain_selection])>>15);
//	}
//	band_mix();
//}
//
//void check_btn_push(Uint16 value){
//	if (value == SW2){
//		if (band_selection == 1){
//			band1_gain_selection++;
//			band1_gain_selection = band1_gain_selection % 9;
//			calculate_new_coef();
//			printf("Band 1 gain is %s.\n", band_gain_db[band1_gain_selection]);
//		} else if (band_selection == 2){
//			band2_gain_selection++;
//			band2_gain_selection = band2_gain_selection % 9;
//			calculate_new_coef();
//			printf("Band 2 gain is %s.\n", band_gain_db[band2_gain_selection]);
//		} else if (band_selection == 3){
//			band3_gain_selection++;
//			band3_gain_selection = band3_gain_selection % 9;
//			calculate_new_coef();
//			printf("Band 3 gain is %s.\n", band_gain_db[band3_gain_selection]);
//		}		
//		band_mix();
//	} else if (value == SW1){
//		toggle_LED(band_selection);
//		band_selection++;
//		band_selection = band_selection % 4;
//		toggle_LED(band_selection);
//		if (band_selection == 0)
//			printf("Bypass mode is selected.\n");
//		else if (band_selection == 1)
//			printf("Band %d is selected.\n", band_selection);
//		else if (band_selection == 2)
//			printf("Band %d is selected.\n", band_selection);
//		else if (band_selection == 3)
//			printf("Band %d is selected.\n", band_selection);
//	}
//	
//	LCD_disp_update(band_selection, band1_gain_selection, band2_gain_selection, band3_gain_selection);
//	if (value == SW1 && band_selection == 0){
//		toggle_LED(band_selection);
//	}
//}
//
//void calculate_new_coef(){
//	int i;
//	if (band_selection == 1){
//		for(i=0;i<TAPS;i++)
//			band1_coef_changed[i]=(Int16)(((Int32)BAND1_COEF[i]*(Int32)band_gain_hex[band1_gain_selection])>>15);
//	} else if (band_selection == 2){
//		for(i=0;i<TAPS;i++)
//			band2_coef_changed[i]=(Int16)(((Int32)BAND2_COEF[i]*(Int32)band_gain_hex[band2_gain_selection])>>15);
//	} else if (band_selection == 3){
//		for(i=0;i<TAPS;i++)
//			band3_coef_changed[i]=(Int16)(((Int32)BAND3_COEF[i]*(Int32)band_gain_hex[band3_gain_selection])>>15);
//	}
//}
//
//void band_mix(){
//	int i;
//	for(i=0;i<TAPS;i++)
//		band_coef_mixed[i] = band1_coef_changed[i] + band2_coef_changed[i] + band3_coef_changed[i];
//}

#include <usbstk5515.h>
#include <usbstk5515_interrupts.h>
#include <usbstk5515_led.h>
#include <AIC_func.h>
#include <stdio.h>
#include <usbstk5515_spi.h>

#define TIMENT1_0 = *((ioport volatile Uint16 *)0x1814)
#define TIME_START 0x8001
#define TIME_STOP 0x8000
Uint32 Timer_count = 0;
Int16  Data_In_Buff[64];
Int16  Data_Out_Buff[64];
Uint16 mask = 512;
Uint32 DBO_index = 0;
Int16* Data_Out_ptr = Data_Out_Buff;
Uint32 Out_going = 0;
void Reset();

interrupt void Timer_Handler()
{
	Timer_count++;
//	T_INT_0 = 0x0001;
	TIAFR = 0x0001;
	printf("In interrupt Handler\n");
}

Uint16 time_set;
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
	TPR0_1  = 199; //Set all counters and period regs to the same value
	TPR0_2 = TCR0_2 = TCR0_2 = 0;

	TIAFR = 0x0007;//Set the three bits to zero
	TCR0 |= TIME_START_AUTOLOAD;
}

interrupt void SPI_ISR(void)
{
	IFR0 &= (1 << SPI_BIT);//clear the flag
	Out_going++;
}

void SPI_Setup()
{
	SPICDR = 99; //	clock divide 100MHz to 1MHz
	SPIDCR1 = 1 << 1;//Chip select 0 active high
	SPICMD1 = 1 << 14; //Character Interrupt
	SPICMD2 = (0xF << 3); //Set character Length to 16bits

	//Make interrupt
	*((Uint32*)((reset_loc + SPI_OFFSET)>>1)) = (Uint32)SPI_ISR;

	IER0 |= (1 << SPI_BIT);//enable interrupt
	IFR0 &= (1 << SPI_BIT);//clear the flag
}
void SPI_Send(Int16 *data)
{
	//Frame length in Command register 1

	//Set Character length

	//save data into data reg 2 then data reg 1
	SPIDAT2 = *data;
	//then set the Command register 2 to write
	SPICMD2 |=  0x2;
}

interrupt void I2S_ISR()
{
	Int16 right, left, /*out,*/ x;
	x = (Int16)((1L << 16) / 480);
	AIC_read2(&right, &left);
	//out = fir_filter(right);
	if(right < 0) right = right * -1;
	right = right / x;
	right += 31;
	Data_Out_Buff[DBO_index++] = right;
}

void I2S_Setup()
{
	*((Uint32*)((reset_loc + I2S_ISR_OFFSET)>>1)) = (Uint32)I2S_ISR;

	IER0 |= (1 << I2S_BIT_POS);//enable interrupt
	IFR0 &= (1 << I2S_BIT_POS);//clear the flag
}

void main(void)
{
//	printf("Timer Setup\n");
	USBSTK5515_init();
	USBSTK5515_ULED_init();
	SPI_Setup();

	Timer_setup();
	I2S_Setup();
	AIC_init();
	_enable_interrupts();

	if(IER0 == 0)
	{
		printf("WTF, no enabled interrupts\n");
		goto TERMINATE;
	}

	while(1)
	{
		/*if(Timer_count >= (Uint32)(1000L * 48L))
		{
			Timer_count = 0;
			LEDs = LEDs << 1;
			if(LEDs >= 0xF) LEDs = 1;
			USBSTK5515_ULED_setall(LEDs);
			SPI_Send(LEDs);
		}*/
		if(DBO_index >= 512)
		{
			DBO_index = 0;
			while(Out_going < 512)
			{
				SPI_Send(Data_Out_Buff + Out_going);
			}
			Out_going = 0;
		}
	}
TERMINATE:
printf("TERMINATING\n");

}
