/********************************************************************************
 Written by: Ayush Gaurav

 Date: 29th May 2017

This experiment demonstrates simple motion control.

 Concepts covered: Simple motion control

 There are two components to the motion control:
 1. Direction control using pins PORTA0 to PORTA3
 2. Velocity control by PWM on pins PA4 and PA5 using OC5A and OC5B of timer 5.

 In this experiment for the simplicity PL3 and PL4 are kept at logic 1.

 Pins for PWM are kept at logic 1.

 Connection Details:    L-1---->PB0;        L-2---->PB1;
                        R-1---->PB2;        R-2---->PB3;
                        PB4 ----> PWM L  PB5----> PWM R;


*********************************************************************************/
#include <stdint.h>
#include <stdbool.h>
#include "inc/hw_types.h"
#include "inc/hw_memmap.h"
//This header File is important to Unlock GPIO Pins
#include "inc/hw_gpio.h"
#include "driverlib/sysctl.h"
#include "driverlib/gpio.h"
#define motorPort       GPIO_PORTB_BASE
#define leftMotor1      GPIO_PIN_0
#define leftMotor2      GPIO_PIN_1
#define leftMotorPWM    GPIO_PIN_4
#define rightMotor1     GPIO_PIN_2
#define rightMotor2     GPIO_PIN_3
#define rightMotorPWM   GPIO_PIN_5
#define right           0x3A
#define left            0x35
#define forward         0x36
#define backward        0x39
#define stop            0x30
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
 * PORTF in this case
 * PF1 for buzzer output
 ******************************/
void peripheralEnable(){
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOB);
}
/*************************************
 * Configuring Pin as Input Or Output
 *************************************/
void configIOPin(){
    GPIOPinTypeGPIOOutput(motorPort,rightMotor1|rightMotor2|rightMotorPWM|leftMotorPWM|leftMotor1|leftMotor2);
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
void motion(uint8_t direction){
    GPIOPinWrite(motorPort,rightMotor1|rightMotor2|rightMotorPWM|leftMotorPWM|leftMotor1|leftMotor2,direction);
}
