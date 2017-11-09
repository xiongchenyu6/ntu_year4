#include <usbstk5515.h>
#include <usbstk5515_i2c.h>
#include <usbstk5515_gpio.h>

#define OSD9616_I2C_ADDR 0x3C
#define offset (int) 5
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
		
Uint8 font[256][4] = {
                                 {0x00, 0x00, 0x00, 0x00},  // 0x00
                                 {0x00, 0x00, 0x00, 0x00},  // 0x01
                                 {0x00, 0x00, 0x00, 0x00},  // 0x02
                                 {0x00, 0x00, 0x00, 0x00},  // 0x03
                                 {0x00, 0x00, 0x00, 0x00},  // 0x04
                                 {0x00, 0x00, 0x00, 0x00},  // 0x05
                                 {0x00, 0x00, 0x00, 0x00},  // 0x06
                                 {0x00, 0x00, 0x00, 0x00},  // 0x07
                                 {0x00, 0x00, 0x00, 0x00},  // 0x08
                                 {0x00, 0x00, 0x00, 0x00},  // 0x09
                                 {0x00, 0x00, 0x00, 0x00},  // 0x0A
                                 {0x00, 0x00, 0x00, 0x00},  // 0x0B
                                 {0x00, 0x00, 0x00, 0x00},  // 0x0C
                                 {0x00, 0x00, 0x00, 0x00},  // 0x0D
                                 {0x00, 0x00, 0x00, 0x00},  // 0x0E
                                 {0x00, 0x00, 0x00, 0x00},  // 0x0F
                                 {0x00, 0x00, 0x00, 0x00},  // 0x10
                                 {0x00, 0x00, 0x00, 0x00},  // 0x11
                                 {0x00, 0x00, 0x00, 0x00},  // 0x12
                                 {0x00, 0x00, 0x00, 0x00},  // 0x13
                                 {0x00, 0x00, 0x00, 0x00},  // 0x14
                                 {0x00, 0x00, 0x00, 0x00},  // 0x15
                                 {0x00, 0x00, 0x00, 0x00},  // 0x16
                                 {0x00, 0x00, 0x00, 0x00},  // 0x17
                                 {0x00, 0x00, 0x00, 0x00},  // 0x18
                                 {0x00, 0x00, 0x00, 0x00},  // 0x19
                                 {0x00, 0x00, 0x00, 0x00},  // 0x1A
                                 {0x00, 0x00, 0x00, 0x00},  // 0x1B
                                 {0x00, 0x00, 0x00, 0x00},  // 0x1C
                                 {0x00, 0x00, 0x00, 0x00},  // 0x1D
                                 {0x00, 0x00, 0x00, 0x00},  // 0x1E
                                 {0x00, 0x00, 0x00, 0x00},  // 0x1F
                                 {0x00, 0x00, 0x00, 0x00},  // ' '
                                 {0x00, 0x2E, 0x00, 0x00},  // '!'
                                 {0x06, 0x00, 0x06, 0x00},  // '"'
                                 {0x3E, 0x14, 0x3E, 0x00},  // '//'
                                 {0x14, 0x3E, 0x14, 0x00},  // '$'
                                 {0x34, 0x08, 0x16, 0x00},  // '%'
                                 {0x34, 0x2A, 0x3A, 0x00},  // '&'
                                 {0x00, 0x06, 0x00, 0x00},  // '''
                                 {0x1C, 0x22, 0x00, 0x00},  // '('
                                 {0x00, 0x22, 0x1C, 0x00},  // ')'
                                 {0x14, 0x08, 0x14, 0x00},  // '*'
                                 {0x08, 0x1C, 0x08, 0x00},  // '+'
                                 {0x00, 0x30, 0x00, 0x00},  // ','
                                 {0x08, 0x08, 0x08, 0x00},  // '-'
                                 {0x00, 0x20, 0x00, 0x00},  // '.'
                                 {0x30, 0x08, 0x06, 0x00},  // '/'
                                 {0x1C, 0x22, 0x1C, 0x00},  // '0'
                                 {0x24, 0x3E, 0x20, 0x00},  // '1'
                                 {0x32, 0x2A, 0x24, 0x00},  // '2'
                                 {0x22, 0x2A, 0x14, 0x00},  // '3'
                                 {0x0E, 0x08, 0x3E, 0x00},  // '4'
                                 {0x2E, 0x2A, 0x12, 0x00},  // '5'
                                 {0x3E, 0x2A, 0x3A, 0x00},  // '6'
                                 {0x02, 0x3A, 0x06, 0x00},  // '7'
                                 {0x3E, 0x2A, 0x3E, 0x00},  // '8'
                                 {0x2E, 0x2A, 0x3E, 0x00},  // '9'
                                 {0x00, 0x14, 0x00, 0x00},  // ':'
                                 {0x00, 0x34, 0x00, 0x00},  // ';'
                                 {0x08, 0x14, 0x22, 0x00},  // '<'
                                 {0x14, 0x14, 0x14, 0x00},  // '='
                                 {0x22, 0x14, 0x08, 0x00},  // '>'
                                 {0x02, 0x2A, 0x06, 0x00},  // '?'
                                 {0x1C, 0x2A, 0x1C, 0x00},  // '@'
                                 {0x3C, 0x0A, 0x3C, 0x00},  // 'A'
                                 {0x3E, 0x2A, 0x14, 0x00},  // 'B'
                                 {0x1C, 0x22, 0x22, 0x00},  // 'C'
                                 {0x3E, 0x22, 0x1C, 0x00},  // 'D'
                                 {0x3E, 0x2A, 0x22, 0x00},  // 'E'
                                 {0x3E, 0x0A, 0x02, 0x00},  // 'F'
                                 {0x1C, 0x22, 0x3A, 0x00},  // 'G'
                                 {0x3E, 0x08, 0x3E, 0x00},  // 'H'
                                 {0x22, 0x3E, 0x22, 0x00},  // 'I'
                                 {0x32, 0x22, 0x3E, 0x00},  // 'J'
                                 {0x3E, 0x08, 0x36, 0x00},  // 'K'
                                 {0x3E, 0x20, 0x20, 0x00},  // 'L'
                                 {0x3E, 0x0C, 0x3E, 0x00},  // 'M'
                                 {0x3C, 0x02, 0x3E, 0x00},  // 'N'
                                 {0x3E, 0x22, 0x3E, 0x00},  // 'O'
                                 {0x3E, 0x0A, 0x0E, 0x00},  // 'P'
                                 {0x1E, 0x12, 0x3E, 0x00},  // 'Q'
                                 {0x3E, 0x0A, 0x36, 0x00},  // 'R'
                                 {0x2E, 0x2A, 0x3A, 0x00},  // 'S'
                                 {0x02, 0x3E, 0x02, 0x00},  // 'T'
                                 {0x3E, 0x20, 0x3E, 0x00},  // 'U'
                                 {0x1E, 0x20, 0x1E, 0x00},  // 'V'
                                 {0x3E, 0x18, 0x3E, 0x00},  // 'W'
                                 {0x36, 0x08, 0x36, 0x00},  // 'X'
                                 {0x0E, 0x38, 0x0E, 0x00},  // 'Y'
                                 {0x32, 0x2A, 0x26, 0x00},  // 'Z'
                                 {0x3E, 0x22, 0x00, 0x00},  // '{'
                                 {0x06, 0x08, 0x30, 0x00},  // '\'
                                 {0x00, 0x22, 0x3E, 0x00},  // '}'
                                 {0x04, 0x02, 0x04, 0x00},  // '^'
                                 {0x20, 0x20, 0x20, 0x00},  // '_'
                                 {0x00, 0x02, 0x04, 0x00},  // '`'
                                 {0x10, 0x2A, 0x3C, 0x00},  // 'a'
                                 {0x3E, 0x28, 0x10, 0x00},  // 'b'
                                 {0x18, 0x24, 0x24, 0x00},  // 'c'
                                 {0x10, 0x28, 0x3E, 0x00},  // 'd'
                                 {0x1C, 0x2A, 0x2C, 0x00},  // 'e'
                                 {0x00, 0x3C, 0x0A, 0x00},  // 'f'
                                 {0x04, 0x2A, 0x3E, 0x00},  // 'g'
                                 {0x3E, 0x08, 0x38, 0x00},  // 'h'
                                 {0x00, 0x3A, 0x00, 0x00},  // 'i'
                                 {0x20, 0x3A, 0x00, 0x00},  // 'j'
                                 {0x3C, 0x10, 0x28, 0x00},  // 'k'
                                 {0x00, 0x3C, 0x00, 0x00},  // 'l'
                                 {0x3C, 0x08, 0x3C, 0x00},  // 'm'
                                 {0x38, 0x04, 0x38, 0x00},  // 'n'
                                 {0x18, 0x24, 0x18, 0x00},  // 'o'
                                 {0x3C, 0x14, 0x08, 0x00},  // 'p'
                                 {0x08, 0x14, 0x3C, 0x00},  // 'q'
                                 {0x3C, 0x08, 0x04, 0x00},  // 'r'
                                 {0x28, 0x3C, 0x14, 0x00},  // 's'
                                 {0x08, 0x3C, 0x28, 0x00},  // 't'
                                 {0x3C, 0x20, 0x3C, 0x00},  // 'u'
                                 {0x1C, 0x20, 0x1C, 0x00},  // 'v'
                                 {0x3C, 0x10, 0x3C, 0x00},  // 'w'
                                 {0x24, 0x18, 0x24, 0x00},  // 'x'
                                 {0x0C, 0x28, 0x3C, 0x00},  // 'y'
                                 {0x24, 0x34, 0x2C, 0x00},  // 'z'
                                 {0x14, 0x2A, 0x00, 0x00},  // '{'
                                 {0x00, 0x3E, 0x00, 0x00},  // '|'
                                 {0x00, 0x2A, 0x14, 0x00},  // '}'
                                 {0x04, 0x04, 0x0C, 0x00},  // '~'
                                 {0x00, 0x00, 0x00, 0x00},  // 0x7F
                                 {0x00, 0x00, 0x00, 0x00},  // 0x80
                                 {0x00, 0x00, 0x00, 0x00},  // 0x81
                                 {0x00, 0x00, 0x00, 0x00},  // 0x82
                                 {0x00, 0x00, 0x00, 0x00},  // 0x83
                                 {0x00, 0x00, 0x00, 0x00},  // 0x84
                                 {0x00, 0x00, 0x00, 0x00},  // 0x85
                                 {0x00, 0x00, 0x00, 0x00},  // 0x86
                                 {0x00, 0x00, 0x00, 0x00},  // 0x87
                                 {0x00, 0x00, 0x00, 0x00},  // 0x88
                                 {0x00, 0x00, 0x00, 0x00},  // 0x89
                                 {0x00, 0x00, 0x00, 0x00},  // 0x8A
                                 {0x00, 0x00, 0x00, 0x00},  // 0x8B
                                 {0x00, 0x00, 0x00, 0x00},  // 0x8C
                                 {0x00, 0x00, 0x00, 0x00},  // 0x8D
                                 {0x00, 0x00, 0x00, 0x00},  // 0x8E
                                 {0x00, 0x00, 0x00, 0x00},  // 0x8F
                                 {0x00, 0x00, 0x00, 0x00},  // 0x90
                                 {0x00, 0x00, 0x00, 0x00},  // 0x91
                                 {0x00, 0x00, 0x00, 0x00},  // 0x92
                                 {0x00, 0x00, 0x00, 0x00},  // 0x93
                                 {0x00, 0x00, 0x00, 0x00},  // 0x94
                                 {0x00, 0x00, 0x00, 0x00},  // 0x95
                                 {0x00, 0x00, 0x00, 0x00},  // 0x96
                                 {0x00, 0x00, 0x00, 0x00},  // 0x97
                                 {0x00, 0x00, 0x00, 0x00},  // 0x98
                                 {0x00, 0x00, 0x00, 0x00},  // 0x99
                                 {0x00, 0x00, 0x00, 0x00},  // 0x9A
                                 {0x00, 0x00, 0x00, 0x00},  // 0x9B
                                 {0x00, 0x00, 0x00, 0x00},  // 0x9C
                                 {0x00, 0x00, 0x00, 0x00},  // 0x9D
                                 {0x00, 0x00, 0x00, 0x00},  // 0x9E
                                 {0x00, 0x00, 0x00, 0x00},  // 0x9F
                                 {0x00, 0x00, 0x00, 0x00},  // 0xA0
                                 {0x00, 0x00, 0x00, 0x00},  // 0xA1
                                 {0x00, 0x00, 0x00, 0x00},  // 0xA2
                                 {0x00, 0x00, 0x00, 0x00},  // 0xA3
                                 {0x00, 0x00, 0x00, 0x00},  // 0xA4
                                 {0x00, 0x00, 0x00, 0x00},  // 0xA5
                                 {0x00, 0x00, 0x00, 0x00},  // 0xA6
                                 {0x00, 0x00, 0x00, 0x00},  // 0xA7
                                 {0x00, 0x00, 0x00, 0x00},  // 0xA8
                                 {0x00, 0x00, 0x00, 0x00},  // 0xA9
                                 {0x00, 0x00, 0x00, 0x00},  // 0xAA
                                 {0x00, 0x00, 0x00, 0x00},  // 0xAB
                                 {0x00, 0x00, 0x00, 0x00},  // 0xAC
                                 {0x00, 0x00, 0x00, 0x00},  // 0xAD
                                 {0x00, 0x00, 0x00, 0x00},  // 0xAE
                                 {0x00, 0x00, 0x00, 0x00},  // 0xAF
                                 {0x00, 0x00, 0x00, 0x00},  // 0xB0
                                 {0x00, 0x00, 0x00, 0x00},  // 0xB1
                                 {0x00, 0x00, 0x00, 0x00},  // 0xB2
                                 {0x00, 0x00, 0x00, 0x00},  // 0xB3
                                 {0x00, 0x00, 0x00, 0x00},  // 0xB4
                                 {0x00, 0x00, 0x00, 0x00},  // 0xB5
                                 {0x00, 0x00, 0x00, 0x00},  // 0xB6
                                 {0x00, 0x00, 0x00, 0x00},  // 0xB7
                                 {0x00, 0x00, 0x00, 0x00},  // 0xB8
                                 {0x00, 0x00, 0x00, 0x00},  // 0xB9
                                 {0x00, 0x00, 0x00, 0x00},  // 0xBA
                                 {0x00, 0x00, 0x00, 0x00},  // 0xBB
                                 {0x00, 0x00, 0x00, 0x00},  // 0xBC
                                 {0x00, 0x00, 0x00, 0x00},  // 0xBD
                                 {0x00, 0x00, 0x00, 0x00},  // 0xBE
                                 {0x00, 0x00, 0x00, 0x00},  // 0xBF
                                 {0x00, 0x00, 0x00, 0x00},  // 0xC0
                                 {0x00, 0x00, 0x00, 0x00},  // 0xC1
                                 {0x00, 0x00, 0x00, 0x00},  // 0xC2
                                 {0x00, 0x00, 0x00, 0x00},  // 0xC3
                                 {0x00, 0x00, 0x00, 0x00},  // 0xC4
                                 {0x00, 0x00, 0x00, 0x00},  // 0xC5
                                 {0x00, 0x00, 0x00, 0x00},  // 0xC6
                                 {0x00, 0x00, 0x00, 0x00},  // 0xC7
                                 {0x00, 0x00, 0x00, 0x00},  // 0xC8
                                 {0x00, 0x00, 0x00, 0x00},  // 0xC9
                                 {0x00, 0x00, 0x00, 0x00},  // 0xCA
                                 {0x00, 0x00, 0x00, 0x00},  // 0xCB
                                 {0x00, 0x00, 0x00, 0x00},  // 0xCC
                                 {0x00, 0x00, 0x00, 0x00},  // 0xCD
                                 {0x00, 0x00, 0x00, 0x00},  // 0xCE
                                 {0x00, 0x00, 0x00, 0x00},  // 0xCF
                                 {0x00, 0x00, 0x00, 0x00},  // 0xD0
                                 {0x00, 0x00, 0x00, 0x00},  // 0xD1
                                 {0x00, 0x00, 0x00, 0x00},  // 0xD2
                                 {0x00, 0x00, 0x00, 0x00},  // 0xD3
                                 {0x00, 0x00, 0x00, 0x00},  // 0xD4
                                 {0x00, 0x00, 0x00, 0x00},  // 0xD5
                                 {0x00, 0x00, 0x00, 0x00},  // 0xD6
                                 {0x00, 0x00, 0x00, 0x00},  // 0xD7
                                 {0x00, 0x00, 0x00, 0x00},  // 0xD8
                                 {0x00, 0x00, 0x00, 0x00},  // 0xD9
                                 {0x00, 0x00, 0x00, 0x00},  // 0xDA
                                 {0x00, 0x00, 0x00, 0x00},  // 0xDB
                                 {0x00, 0x00, 0x00, 0x00},  // 0xDC
                                 {0x00, 0x00, 0x00, 0x00},  // 0xDD
                                 {0x00, 0x00, 0x00, 0x00},  // 0xDE
                                 {0x00, 0x00, 0x00, 0x00},  // 0xDF
                                 {0x00, 0x00, 0x00, 0x00},  // 0xE0
                                 {0x00, 0x00, 0x00, 0x00},  // 0xE1
                                 {0x00, 0x00, 0x00, 0x00},  // 0xE2
                                 {0x00, 0x00, 0x00, 0x00},  // 0xE3
                                 {0x00, 0x00, 0x00, 0x00},  // 0xE4
                                 {0x00, 0x00, 0x00, 0x00},  // 0xE5
                                 {0x00, 0x00, 0x00, 0x00},  // 0xE6
                                 {0x00, 0x00, 0x00, 0x00},  // 0xE7
                                 {0x00, 0x00, 0x00, 0x00},  // 0xE8
                                 {0x00, 0x00, 0x00, 0x00},  // 0xE9
                                 {0x00, 0x00, 0x00, 0x00},  // 0xEA
                                 {0x00, 0x00, 0x00, 0x00},  // 0xEB
                                 {0x00, 0x00, 0x00, 0x00},  // 0xEC
                                 {0x00, 0x00, 0x00, 0x00},  // 0xED
                                 {0x00, 0x00, 0x00, 0x00},  // 0xEE
                                 {0x00, 0x00, 0x00, 0x00},  // 0xEF
                                 {0x00, 0x00, 0x00, 0x00},  // 0xF0
                                 {0x00, 0x00, 0x00, 0x00},  // 0xF1
                                 {0x00, 0x00, 0x00, 0x00},  // 0xF2
                                 {0x00, 0x00, 0x00, 0x00},  // 0xF3
                                 {0x00, 0x00, 0x00, 0x00},  // 0xF4
                                 {0x00, 0x00, 0x00, 0x00},  // 0xF5
                                 {0x00, 0x00, 0x00, 0x00},  // 0xF6
                                 {0x00, 0x00, 0x00, 0x00},  // 0xF7
                                 {0x00, 0x00, 0x00, 0x00},  // 0xF8
                                 {0x00, 0x00, 0x00, 0x00},  // 0xF9
                                 {0x00, 0x00, 0x00, 0x00},  // 0xFA
                                 {0x00, 0x00, 0x00, 0x00},  // 0xFB
                                 {0x00, 0x00, 0x00, 0x00},  // 0xFC
                                 {0x00, 0x00, 0x00, 0x00},  // 0xFD
                                 {0x00, 0x00, 0x00, 0x00},  // 0xFE
                                 {0x00, 0x00, 0x00, 0x00},  // 0xFF
};
