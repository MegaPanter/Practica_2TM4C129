


#include "lib/include.h"


int main() {

  while (1)
  {
        //
        // Turn on the LED.
        //
        GPIO_Config();
         GPION->DATA |= 0x01;
        //GPIO_PORTN_DATA_R |= 0x01;

        //
        // Delay for a bit.
        //
        Delay();
         GPION->DATA |= 0x02;
        //GPIO_PORTN_DATA_R |= 0x01;

        //
        // Delay for a bit.
        //
       Delay();
        //
        // Turn off the LED.
        //
        GPION->DATA &= ~(0x01);
        //GPIO_PORTN_DATA_R &= ~(0x01);

        //
        // Delay for a bit.
        //
       Delay();
                GPION->DATA &= ~(0x02);
        //GPIO_PORTN_DATA_R &= ~(0x01);

        //
        // Delay for a bit.
        //
        Delay();
  }
}