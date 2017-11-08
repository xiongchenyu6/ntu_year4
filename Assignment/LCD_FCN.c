#include <usbstk5515.h>
#include <usbstk5515_i2c.h>
#include <usbstk5515_gpio.h>

#define OSD9616_I2C_ADDR 0x3C

#pragma DATA_SECTION(CharGen_6x8, ".charrom")
Uint16 CharGen_6x8[256*3];

Uint8 TOP [128];
Uint8 BOTTOM [128];

Int16 OSD9616_send( Uint16 comdat, Uint16 data )
{
    Uint8 cmd[2];
    cmd[0] = comdat & 0x00FF;     // Specifies whether data is Command or Data
    cmd[1] = data & 0x00FF ;                // Command / Data

    return USBSTK5515_I2C_write( OSD9616_I2C_ADDR, cmd, 2 );
}

Int16 OSD9616_multiSend( Uint8* data, Uint16 len )
{
    Uint16 x;
    Uint8 cmd[10];
    for(x=0;x<len;x++)               // Command / Data
    {
    	cmd[x] = data[x] & 0x00FF;
    }
    return USBSTK5515_I2C_write( OSD9616_I2C_ADDR, cmd, len );
}

void LCD_init()
{
	Uint8 cmd [10];
	USBSTK5515_I2C_init();
	
	USBSTK5515_GPIO_setDirection( 12, 1 );  // Output
    USBSTK5515_GPIO_setOutput( 12, 1 );     // Enable 13V 
    
    /* Initialize OSD9616 display */
    OSD9616_send(0x00,0x00); // Set low column address
    OSD9616_send(0x00,0x10); // Set high column address
    OSD9616_send(0x00,0x40); // Set start line address

    cmd[0] = 0x00 & 0x00FF;  // Set contrast control register
    cmd[1] = 0x81;
    cmd[2] = 0x7f;
    USBSTK5515_I2C_write( OSD9616_I2C_ADDR, cmd, 3 );

    OSD9616_send(0x00,0xa0); // Set segment re-map 95 to 0
    OSD9616_send(0x00,0xa6); // Set normal display

    cmd[0] = 0x00 & 0x00FF;  // Set multiplex ratio(1 to 16)
    cmd[1] = 0xa8; 
    cmd[2] = 0x0f;
    USBSTK5515_I2C_write( OSD9616_I2C_ADDR, cmd, 3 );

    OSD9616_send(0x00,0xd3); // Set display offset
    OSD9616_send(0x00,0x00); // Not offset
    OSD9616_send(0x00,0xd5); // Set display clock divide ratio/oscillator frequency
    OSD9616_send(0x00,0xf0); // Set divide ratio

    cmd[0] = 0x00 & 0x00FF;  // Set pre-charge period
    cmd[1] = 0xd9;
    cmd[2] = 0x22;
    USBSTK5515_I2C_write( OSD9616_I2C_ADDR, cmd, 3 );

    cmd[0] = 0x00 & 0x00FF;  // Set com pins hardware configuration
    cmd[1] = 0xda;
    cmd[2] = 0x02;
    USBSTK5515_I2C_write( OSD9616_I2C_ADDR, cmd, 3 );

    OSD9616_send(0x00,0xdb); // Set vcomh
    OSD9616_send(0x00,0x49); // 0.83*vref
    
    cmd[0] = 0x00 & 0x00FF;  //--set DC-DC enable
    cmd[1] = 0x8d;
    cmd[2] = 0x14;
    USBSTK5515_I2C_write( OSD9616_I2C_ADDR, cmd, 3 );

    OSD9616_send(0x00,0xaf); // Turn on oled panel
	OSD9616_send(0x00,0x2E); //stops scrolling if there is any

}

void LCD_Display(Int16 * array, Int16 power)//Numbers 1-32 inclusively
{
	Uint16 i, index;
	Int16 temp;

	for(i=0; i<128; i++)
	{
		if(power == 0)
			index = i;
		else if(power > 0)
			index = i>>power;
		else
			index = i<<-power;	
		temp = (array[index] & 0x7FFF); // remove sign bit
		temp = temp >> 12;
		if(array[index] <0 )//Is negative check
		{
			if(temp == 0)
				BOTTOM[i] = 0x80;
			else	
				BOTTOM[i] = 1 << (8-temp);
			TOP[i] = 0;
		}
		else
		{
			BOTTOM[i] = 0;
			if(temp == 0)
				TOP[i] = ( (array[index] & 0x7FFF) >> 12);// 0x80;
			else	
				TOP[i] = 1 << (8-temp);
		}			
	}
	//Display the Top plane
	OSD9616_send(0x00,0x00);   // Set low column address
    OSD9616_send(0x00,0x10);   // Set high column address
    OSD9616_send(0x00,0xb0); // Set page for page 0 to page 5
    for(i=0; i<128; i++)
    {	
    	OSD9616_send(0x40, TOP[i] | 0x80);
    }
    //Display Bottom plane
    OSD9616_send(0x00,0x00);   // Set low column address
    OSD9616_send(0x00,0x10);   // Set high column address
    OSD9616_send(0x00,0xb1); // Set page for page 0 to page 5
	for(i=0; i<128; i++)
	{
    	OSD9616_send(0x40, BOTTOM[i]);
	}
}
Int16 printchar(unsigned char a)
{
	Uint8 data;

	data = ((CharGen_6x8[a*3])>>8) & 0x00FF;
    OSD9616_send(0x40,data);
    data = (CharGen_6x8[a*3]) & 0x00FF;
    OSD9616_send(0x40,data);
    data = ((CharGen_6x8[a*3+1])>>8) & 0x00FF;
    OSD9616_send(0x40,data);
    data = (CharGen_6x8[a*3+1]) & 0x00FF;
    OSD9616_send(0x40,data);
    data = ((CharGen_6x8[a*3+2])>>8) & 0x00FF;
    OSD9616_send(0x40,data);
    data = (CharGen_6x8[a*3+2]) & 0x00FF;
    OSD9616_send(0x40,data);

    return 0;
}

/* ------------------------------------------------------------------------ *
 *                                                                          *
 *  Int16 printstring(char *a)              *
 *                                                                          *
 *      print a string                               *
 *                                                                          *
 * ------------------------------------------------------------------------ */
Int16 printstring(char *a)
{
	Uint16 i, len;
	
	len = strlen(a);
	if ((len ==0) | (len>22)) len=16;
	
	for (i=0; i<len; i++) {
		printchar(a[i]);
	}
	return 0;	
}	
Int16 clear_lcd()
{
	Uint16 i;

    /* clear page 0 */ 
    OSD9616_send(0x00,0x00);   // Set low column address
    OSD9616_send(0x00,0x10);   // Set high column address
    OSD9616_send(0x00,0xb0+0); // Set page for page 0 to page 5		
	for (i=0; i<128; i++) {
		OSD9616_send(0x40,0x00);
	}
    /* clear page 1 */ 
    OSD9616_send(0x00,0x00);   // Set low column address
    OSD9616_send(0x00,0x10);   // Set high column address
    OSD9616_send(0x00,0xb0+1); // Set page for page 0 to page 5	
    for (i=0; i<128; i++) {
		OSD9616_send(0x40,0x00);
	}
	OSD9616_send(0x00,0x00);   // Set low column address
    OSD9616_send(0x00,0x10);   // Set high column address
    OSD9616_send(0x00,0xb0+0); // Set page for page 0 to page 5		
	return 0;	
}
Int16 print_ti()
{
	char ti[23]; 
		
	OSD9616_send(0x00,0x2e); // Turn off scrolling 
	clear_lcd();
	sprintf(ti,"                       "); //clear	
	    /* Write to page 1 */
    OSD9616_send(0x00,0x00);   // Set low column address
    OSD9616_send(0x00,0x10);   // Set high column address
    OSD9616_send(0x00,0xb0+1); // Set page for page 0 to page 5
   	
   	sprintf(ti,"  Texas Instruments");
	printstring(ti);
	    /* Write to page 0*/ 
    OSD9616_send(0x00,0x00);   // Set low column address
    OSD9616_send(0x00,0x10);   // Set high column address
    OSD9616_send(0x00,0xb0+0); // Set page for page 0 to page 5
	sprintf(ti," C5535 eZdsp USB stick");
	printstring(ti);
	
	OSD9616_send(0x00,0x2f); // Turn on scrolling 
	
	return 0;
}
Int16 printLetter(Uint16 first,Uint16 second,Uint16 third,Uint16 forth)
{
	
    OSD9616_send(0x40,forth);
      OSD9616_send(0x40,third);
    OSD9616_send(0x40,second);
  
      OSD9616_send(0x40,first);
    OSD9616_send(0x40,0x00);  // Line blank for space
    
    return 0;
}
