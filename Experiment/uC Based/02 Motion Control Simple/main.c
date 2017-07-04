/********************************************************************************
 Written by: Ayush Gaurav and Nagesh K.
From eRTS Lab, CSE Department, IIT Bombay.

 Date: 16th June 2017

This experiment demonstrates simple motion control.

 Concepts covered: Simple motion control

 There are two components to the motion control:
 1. Direction control using.
 2. Velocity control by PWM.

 In this experiment for the simplicity PB4 and PB5 are kept at logic 1.

 Pins for PWM are kept at logic 1.

 Connection Details:
                        L-1---->PB0;        L-2---->PB1;
                        R-1---->PF4;        R-2---->PA5;
                        PF3----> PWM L     PA6----> PWM R;


*********************************************************************************/
#include <stdint.h>
#include <stdbool.h>
#include "inc/hw_types.h"
#include "inc/hw_memmap.h"
//This header File is important to Unlock GPIO Pins
#include "inc/hw_gpio.h"
#include "driverlib/sysctl.h"
#include "driverlib/gpio.h"
#define right           0x22
#define left            0x11
#define softRight       0x02
#define softLeft        0x10
#define forward         0x12
#define backward        0x21
#define stop            0x00
void setupCLK();
void peripheralEnable();
void configIOPin();
void delay_ms(uint64_t delay);
void delay_ms(uint64_t delay);
void motion(uint8_t);
int main(void) {
    setupCLK();
    peripheralEnable();
    configIOPin();
    while(1){
        motion(forward);
        delay_ms(1000);
        motion(right);
        delay_ms(1000);
        motion(left);
        delay_ms(1000);
        motion(backward);
        delay_ms(1000);
    }
}
/***************************************************************************************
 * This function is used to setup Clock frequency of the controller
 * It can be changed through codes
 * In this we have set frequency as 40Mhz
 * Frequency is set by SYSDIV which can be found in data sheet for different frequencies
 ***************************************************************************************/
void setupCLK(){
    SysCtlClockSet(SYSCTL_SYSDIV_5|SYSCTL_USE_PLL|SYSCTL_XTAL_16MHZ|SYSCTL_OSC_MAIN);
}
/*******************************
 * Enabling System Peripherals
 * PORTF,PORTB and PORTC in this case
 ******************************/
void peripheralEnable(){
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOB);
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOF);
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOA);
}
/*************************************
 * Configuring Pin as Input Or Output
 * And Setting PWM Pin to Always High
 *************************************/
void configIOPin(){
    GPIOPinTypeGPIOOutput(GPIO_PORTB_BASE,GPIO_PIN_0|GPIO_PIN_1);
    GPIOPinTypeGPIOOutput(GPIO_PORTA_BASE,GPIO_PIN_6|GPIO_PIN_5);
    GPIOPinTypeGPIOOutput(GPIO_PORTF_BASE,GPIO_PIN_4|GPIO_PIN_3);
    GPIOPinWrite(GPIO_PORTF_BASE,GPIO_PIN_3,255);
    GPIOPinWrite(GPIO_PORTA_BASE,GPIO_PIN_6,255);
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
/******************************************************
 * This function is for giving the direction of motion
 * Macros have been defined at starting
 * Macros for directions are 8 bits
 * Out of these 8 bits only 4 are used
 * Bit 0 (LSB) corresponds to PB0
 * Bit 1       corresponds to PF1
 * Bit 4       corresponds to PF4
 * Bit 5       corresponds to PA5
 *****************************************************/
void motion(uint8_t direction){
    GPIOPinWrite(GPIO_PORTB_BASE,GPIO_PIN_0|GPIO_PIN_1,direction);
    GPIOPinWrite(GPIO_PORTA_BASE,GPIO_PIN_5,direction);
    GPIOPinWrite(GPIO_PORTF_BASE,GPIO_PIN_4,direction);
}
