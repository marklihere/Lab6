# Lab6

LCD 3-button array turn on / off LEDs
ILI9341
  display controller
  command indexes
  display RAM
  display on/off sequences

SPI
LCD

Debounce
Touch & Hold remains in state
Touch outside boundary
Part-in/Part-out touches

Goal
complete interface
use interface to draw

SPO / SPH
00


76x81 for one box
66x71 for inner fill
so outline is 5px wide each side
Red, Green, Yellow


HW
------------------
TP_CS
SPI_CLK
RST

Configure this:
SSIO
PB0  = LCD_RS  (CX)
RST  (active low, so must be 3.3V to be active)
We need to make sure uC provides correct timing - see Ch7

SSIOCR0 only allows word access for writes

4- line serial system interface
where is IM[3:0]? and what is RESX?
0110  4-wire 8-bit data serial interface I
SCL,SDA,D/CX,CSX

SDA or SDI/SDO 

format per pixel color order DBI[2:0] of 3Ah register


The serial interface is initialized when CSX is high.  
In this state, SCL clock pulse and SDA data have no effect. A falling edge on
CSX enables the serial interface and indicates the start of data transmission.



LCD max speed
10 megahertz  for SCL clock

if we choose 80 MHz SysClk
SSIClk = SysClk / (CPSDVSR * (1 + SCR))
10 megahertz = 80 MHz / (   * (1 + 

CPSDVSR from 2 to 254   (SSICPSR REG)
SCR is a value from 0-255

from above,
8 = (CPSDVSR * (1 + SCR))
  = 2 * (1+3)

so we set 
SSICPSR to 0x08
SSICR0 to 0x00000007
