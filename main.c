// This function draws three empty boxes. The user touches the box
// to fill the box and turn on a corresponding external light.

#include "LCD.H"
#include "init.h"

unsigned char *PA = (unsigned char *) 0x40004000;
unsigned char *PB = (unsigned char *) 0x40005000;
unsigned char *SYSCTL = (unsigned char *) 0x400FE000;
unsigned char *SSI0 = (unsigned char *) 0x40008000;
volatile unsigned int SSI0_SR __attribute__((at(0x4000800C)));

void mywriteCmd(unsigned char CMD) {
	// wait until FIFO is not busy and also FIFO is empty
	while((SSI0b->SR & 0x11) != 0x01);
	GPIOB->DATA = 0x0;  // command is 0
	SSI0b->DR = CMD;
}

void mywriteDat(unsigned char DAT) {
	// wait until FIFO is not busy and also FIFO is empty
	while((SSI0b->SR & 0x11) != 0x01);
	GPIOB->DATA = 0x1;  // data is 1
	SSI0b->DR = DAT;
}

void mywriteDat2(unsigned short DAT) {
	// wait until FIFO is not busy and also FIFO is empty
	while((SSI0b->SR & 0x11) != 0x01);
	GPIOB->DATA = 0x1;  // data is 1
	SSI0b->DR = DAT >> 8;
	while((SSI0b->SR & 0x11) != 0x01);
	SSI0b->DR = DAT;
}

void mywriteDat4(unsigned int DAT) {
	// wait until FIFO is not busy and also FIFO is empty
	while((SSI0b->SR & 0x2) == 0x0);
	GPIOB->DATA = 0x1;  // data is 1
	SSI0b->DR = DAT >> 24;
	while((SSI0b->SR & 0x2) == 0x0);
	SSI0b->DR = DAT >> 16;
	while((SSI0b->SR & 0x2) == 0x0);
	SSI0b->DR = DAT >> 8;
	while((SSI0b->SR & 0x2) == 0x0);
	SSI0b->DR = DAT;
}

void mysetArea(unsigned short x1, unsigned short x2, unsigned short y1, unsigned short y2) {
  // Column Address Set 0x2A
	// columns range from 0 to 239
	mywriteCmd(0x2A);
	mywriteDat2(x1);
	mywriteDat2(x2);
	
	// Page Address Set 0x2B
	// pages range from 0 to 319
	mywriteCmd(0x2B);
	mywriteDat2(y1);
	mywriteDat2(y2);
}


void mywriteColor(unsigned short color) {
	int i;
	int cols;
	int rows;
	cols = 240;
	rows = 320;

  mywriteCmd(0x2C);
	for(i = 0; i < cols*rows; i++)
	  mywriteDat2(color);
}



int main(void)
{
  INIT_PLL();
	GPIO_INIT();
	INIT_SSI0();
	
	LCD_Init();
	
	// draw_init();
	mysetArea(0, 239, 0, 319);
	mywriteColor(black);
	mysetArea(62, 142, 40, 115);
	mywriteColor(red);
  mysetArea(67, 137, 45, 110);
	mywriteColor(black);
	mysetArea(62, 142, 123, 198);
	mywriteColor(green);
  mysetArea(67, 137, 128, 193);
	mywriteColor(black);
	mysetArea(62, 142, 206, 281);
	mywriteColor(yellow);
  mysetArea(67, 137, 211, 277);
	mywriteColor(black);	
	
    while (1)
    {
      
    }

}
