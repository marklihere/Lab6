// This function draws three empty boxes. The user touches the box
// to fill the box and turn on a corresponding external light.

#include "LCD.H"
#include "tm4c123gh6pm.h"
unsigned char *PA = (unsigned char *) 0x40004000;
unsigned char *PB = (unsigned char *) 0x40005000;
unsigned char *PC = (unsigned char *) 0x40006000;
unsigned char *PE = (unsigned char *) 0x40024000;
//unsigned char *SYSCTL = (unsigned char *) 0x400FE000;

unsigned int *PA_int = (unsigned int *) 0x40004000;
unsigned int *PB_int = (unsigned int *) 0x40005000;
unsigned int *PC_int = (unsigned int *) 0x40006000;
unsigned int *PE_int = (unsigned int *) 0x40024000;
unsigned int *SYSCTL_int = (unsigned int *) 0x400FE000;


void INIT_PLL(void) {
  SYSCTL->RCC2 |= 0x80000000;     // Use RCC2
    SYSCTL->RCC2 |= 0x00000800;   // bypass PLL while initializing
    SYSCTL->RCC = (SYSCTL->RCC &~0x000007C0) + 0x00000540;  // 16 MHz
    SYSCTL->RCC2 &= ~0x00000070;  // Cfg for main OSC
    SYSCTL->RCC2 &= ~0x00002000;  // activate PLL by clearing PWRDN
    SYSCTL->RCC2 |= 0x40000000;   // use 400 MHz PLL
    SYSCTL->RCC2 = (SYSCTL->RCC2 & ~0x1FC00000) + (4<<22);  // 80 MHz
    while((SYSCTL->RIS & 0x00000040)==0){};  // Wait for PLL to lock
    SYSCTL->RCC2 &= ~0x00000800;  // enable PLL by clearing bypass
}
 
void INIT_GPIO(void){
	SYSCTL->RCGCGPIO = 0x8;
	GPIOD->DIR = 0x7;
	GPIOD->PUR = 0x7;
	GPIOD->DEN = 0x7;
	
}

int main(void)
{
	int i;
	unsigned char data = 0x00;
	//INIT_PLL();
	INIT_GPIO();
	//setup_data_command_pin(); // - PB0 D/C, PB6 TB_CS
	//setup_wr_rd_pins();				// PA6 and PA7 as /WR and /RD
	//setup_DB8_11_pins();			// PC4-7
	//setup_DB12_15_pins();			// PE0-3
	
	//LCD_Init();
	
	//PD0 = Y, PD1 = G, PD2 = 2
	while(1){
		i = 0;
		while(i < 0x10)
		{
			i++;			
		}
		GPIOD->DATA = data;
	 data = ~data;
	}
 

    while (1)
    {
				flash_screen(red);
    }

}
