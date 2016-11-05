// This function draws three empty boxes. The user touches the box
// to fill the box and turn on a corresponding external light.

#include "LCD.H"
#include "init.h"

unsigned char *PA = (unsigned char *) 0x40004000;
unsigned char *PB = (unsigned char *) 0x40005000;
unsigned char *SYSCTL = (unsigned char *) 0x400FE000;
unsigned char *SSI0 = (unsigned char *) 0x40008000;
volatile unsigned int SSI0_SR __attribute__((at(0x4000800C)));

void Fill_Red(void) {
		int p,C,P;
	
	C = 240;
	P = 320;
	
	//set column
	writeCmd(0x2A);
	writeDat2(0x2B);
	writeDat2(0x6C);
	//set page
	writeCmd(0x2B);
	writeDat2(0x43);
	writeDat2(0x89);
	
	writeCmd(0x2C);
	for(p = 0; p < C*P; p++)
		writeDat2(red);
	
}

int main(void)
{
  INIT_PLL();
	GPIO_INIT();
	INIT_SSI0();
	
	// Draw_Empty_Red();
	// Draw_Empty_Green();
	// Draw_Empty_Yellow();
	Fill_Red();
	// Fill_Green();
	// Fill_Yellow();
	
	//setup_SSIO_0(); //setup SPI on PA2-PA5
	//setup_PB();     //Setup D/C on PB0
	
	LCD_Init();
    while (1)
    {
        Fill_Red();
    }

}
