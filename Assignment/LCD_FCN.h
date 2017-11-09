#ifndef LCD_FCN_H_
#define LCD_FCN_H_

Int16 OSD9616_send( Uint16 comdat, Uint16 data );
Int16 OSD9616_multiSend( Uint8* data, Uint16 len );
void LCD_init(void);
void LCD_Display(Int16 * array, Int16 power);
Int16 printchar(unsigned char a);
Int16 printstring(char *a);
Int16 clear_lcd();
Int16 print_ti();
Int16 printLetter(Uint16 first,Uint16 second,Uint16 third,Uint16 forth);
void LCD_disp_update(Int16 mode, Int16 b1, Int16 b2, Int16 b3);
#endif /*LCD_FCN_H_*/
