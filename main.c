// This function draws three empty boxes. The user touches the box
// to fill the box and turn on a corresponding external light.

#include "LCD.H"
#include "init.h"

unsigned char *PA = (unsigned char *) 0x40004000;
unsigned char *PB = (unsigned char *) 0x40005000;
unsigned char *SYSCTL = (unsigned char *) 0x400FE000;
unsigned char *SSI0 = (unsigned char *) 0x40008000;
volatile unsigned int SSI0_SR __attribute__((at(0x4000800C)));


int main(void)
{
  INIT_PLL();
	GPIO_INIT();
	INIT_SSI0();
	
	
	//setup_SSIO_0(); //setup SPI on PA2-PA5
	//setup_PB();     //Setup D/C on PB0
	
	LCD_Init();
    while (1)
    {
        flash_screen(red);
    }

}
