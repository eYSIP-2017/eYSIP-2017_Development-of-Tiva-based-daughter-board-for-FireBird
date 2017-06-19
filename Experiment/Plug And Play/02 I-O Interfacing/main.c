/********************************************************************************


 This experiment demonstrates the simple I/O operations.
 This example is only for plug and play board, but this should not discourage
 you from understanding the example as it provide very important example of I/O
 on TIVA platform.
 Concepts covered:
 input/Output operation, generating exact delay

 Connections:
 Switch2 PF0
 Red led PF1
 Blue led PF2
 Green led PF3
 Switch1 PF4

 Explanation of the working:
 In this lab you have to use switch SW1, SW2 and RGB LED present on Tiva C series board.
1. Use switch SW1 to Turn on Red LED on first switch press, Green LED on second
switch press and Blue LED on third switch press. Repeat the same cycle next switch
press onwards. Note that LED should remain on for the duration switch is kept pressed
i.e. LED should turn off when switch is released.
2. Use switch SW2 and sw2Status (a variable). Your program should increment sw2Status
by one, every time switch is pressed. Note how the value of sw2Status changes on each
switch press. Use debugger and add sw2Status to \Watch Expression" window.
(You will find Continuous Refresh button on top of the Expression Window). You can
use step debugging or breakpoints to check the variable value.
Hint:To add variable to Expression Window, select and right click the variable name
and select \Add Watch Expression". To view Expression Window, click on View but-
ton from CCS menu bar and select Expressions.
*********************************************************************************/
#include <stdint.h>
#include <stdbool.h>
#include "inc/hw_types.h"
#include "inc/hw_memmap.h"
#include "inc/hw_gpio.h" //To unlock locked pins for GPIO
#include "driverlib/sysctl.h"
#include "driverlib/gpio.h"
#define userSwitch1 GPIO_PIN_0
#define redLed      GPIO_PIN_1
#define blueLed     GPIO_PIN_2
#define greenLed    GPIO_PIN_3
#define userSwitch2 GPIO_PIN_4
#define LOCK_F (*((volatile unsigned long *)0x40025520))
#define CR_F   (*((volatile unsigned long *)0x40025524))
void setupCLK();
void configIOPin();
void delay_ms(uint64_t delay);
void delay_us(uint64_t delay);
int main(){
    setupCLK();
    SysCtlDelay(3);
    configIOPin();
    unsigned char pinData=1;
    unsigned char state=2;
    unsigned char countSwitch2=0;
    unsigned char flagSW1=0;
    unsigned char flagSW2=0;
    while(1){
        pinData=GPIOPinRead(GPIO_PORTF_BASE,userSwitch2|userSwitch1);
        if((pinData&0x01)==0)
            flagSW1=1;
        else if((flagSW1==1)&&(pinData&0x01)==1){
            countSwitch2+=1;
            flagSW1=0;
        }
        if((pinData&0x10)==0){
            GPIOPinWrite(GPIO_PORTF_BASE,redLed|blueLed|greenLed,state);
            flagSW2=1;
        }
        else if(((flagSW2==1)&&(pinData&0x10)==0x10)){
            flagSW2=0;
            GPIOPinWrite(GPIO_PORTF_BASE,redLed|blueLed|greenLed,0);
            state=state*2;
            if(state>8)
                state=2;
        }
        delay_ms(5);
    }
}
/***************************************************************************************
 * This function is used to setup Clock frequency of the controller
 * Enabling System Peripherals
 * PORTF in this case
 ******************************/
void setupCLK(){
    SysCtlClockSet(SYSCTL_SYSDIV_4|SYSCTL_USE_PLL|SYSCTL_XTAL_16MHZ|SYSCTL_OSC_MAIN);
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOF);
}
/**********************************************
 * Configuring Pin as Input Or Output
 * PF0 by default is locked and cannot
 * be used as input unless it is unlocked
 ***********************************************/
void configIOPin(){
    GPIOPinTypeGPIOOutput(GPIO_PORTF_BASE, redLed|blueLed|greenLed);
    HWREG(GPIO_PORTF_BASE + GPIO_O_LOCK) = GPIO_LOCK_KEY;
    HWREG(GPIO_PORTF_BASE + GPIO_O_CR) |= 0x01;
    HWREG(GPIO_PORTF_BASE + GPIO_O_LOCK) = 0;
    GPIOPinTypeGPIOInput(GPIO_PORTF_BASE, userSwitch2|userSwitch1);
    GPIOPadConfigSet(GPIO_PORTF_BASE ,userSwitch2|userSwitch1,GPIO_STRENGTH_12MA,GPIO_PIN_TYPE_STD_WPU);
}
/*************************************
 * Calculating Delays
 *************************************/
void delay_ms(uint64_t delay){
    SysCtlDelay(delay*(SysCtlClockGet()/3000));
}
void delay_us(uint64_t delay){
    SysCtlDelay(delay*(SysCtlClockGet()/3000000UL));
}
