#include <stdint.h>
#include "../inc/tm4c1294ncpdt.h"


#include "lib/include.h"

#define SENSOR  (*((volatile uint32_t *)0x4002400C))

#define LIGHT   (*((volatile uint32_t *)0x400050FC))

// Linked data structure

struct State {

uint16_t Out;

uint32_t Time; 

uint32_t Next[4];};

typedef const struct State State_t;

#define goN   0

#define waitN 1

#define goE   2

#define waitE 3

State_t FSM[4]={

 {0x21,3000,{goN,waitN,goN,waitN}},

 {0x22, 500,{goE,goE,goE,goE}},

 {0x0C,3000,{goE,goE,waitE,waitE}},

 {0x14, 500,{goN,goN,goN,goN}}};

volatile uint32_t S;  // index to the current state

volatile uint32_t Input;

int main(void){ volatile uint32_t delay;

 SYSCTL_RCGCGPIO_R = SYSCTL_RCGCGPIO_R1|SYSCTL_RCGCGPIO_R4;


  SystemClock_120MHz();       // 80 MHz, Program 10.1

  SysTick_Init();   // Program 10.2

  GPIO_Config();

  SYSCTL_RCGCGPIO_R  |= 0x12;      // B E

  delay = SYSCTL_RCGCGPIO_R;      // no need to unlock

  GPIO_PORTE_AHB_DIR_R &= ~0x03;   // inputs on PE1-0

  GPIO_PORTE_AHB_DEN_R |= 0x03;    // enable digital on PE1-0

  GPIO_PORTB_AHB_DIR_R |= 0x3F;    // outputs on PB5-0

  GPIO_PORTB_AHB_DEN_R |= 0x3F;    // enable digital on PB5-0

  S = goN;  

  while(1){

    LIGHT = FSM[S].Out;  // set lights

    SysTick_Wait10ms(FSM[S].Time);

    Input = SENSOR;     // read sensors

    S = FSM[S].Next[Input]; 

  }

}