/********************************************************************************
 Written by: Ayush Gaurav and Nagesh K.
From ERTS Lab, CSE Department, IIT Bombay.

 Date: 16th June 2017

This experiment demonstrates simple motion control.

 Concepts covered: Velocity Control Using PWM

 There are two components to the motion control:
 1. Direction control.
 2. Velocity control using PWM.

 Connection Details:
            For Plug And Play Board
                        L-1---->PF3;        L-2---->PB3;
                        R-1---->PC4;        R-2---->PC6;
                        PF2----> PWM L     PC5----> PWM R;

*********************************************************************************/
#include <stdint.h>
#include <stdbool.h>
#include "inc/hw_types.h"
#include "inc/hw_memmap.h"
#include "driverlib/pin_map.h"
//This header File is important to Unlock GPIO Pins
#include "inc/hw_gpio.h"
#include "driverlib/sysctl.h"
#include "driverlib/gpio.h"
//Used for PWM
#include "driverlib/pwm.h"

#define right           0x41
#define left            0x18
#define softRight       0x10
#define softLeft        0x01
#define forward         0x11
#define backward        0x48
#define stop            0x00
void setupCLK();
void peripheralEnable();
void configIOPin();
void delay_ms(uint64_t delay);
void delay_ms(uint64_t delay);
void motion(uint8_t);
void enablePWM();
void Velocity(uint8_t lSpeed,uint8_t rSpeed);
int main(void) {
    setupCLK();
    peripheralEnable();
    configIOPin();
    enablePWM();
    while(1){
        Velocity(150, 150);
        motion(forward);
        delay_ms(2000);
        motion(stop);
        delay_ms(500);
        Velocity(255, 255);
        motion(backward);
        delay_ms(800);
        motion(stop);
        delay_ms(500);
        Velocity(255, 255);
        motion(right);
        delay_ms(1000);
        motion(stop);
        delay_ms(500);
        Velocity(150, 150);
        motion(left);
        delay_ms(1000);
        motion(stop);
        delay_ms(500);
        Velocity(150, 150);
        motion(backward);
        delay_ms(1000);
    }
}
/***************************************************************************************
 * This function is used to setup Clock frequency of the controller
 * It can be changed through codes
 * In this we have set frequency as 40Mhz
 * Frequency is set by SYSDIV which can be found in data sheet for different frequencies
 * The PWM module is clocked by the system clock through a divider, and that divider has
   a range of 2 to 64.
 * By setting the divider to 64, it will run the PWM clock at 625 kHz.
 ***************************************************************************************/
void setupCLK(){
    SysCtlClockSet(SYSCTL_SYSDIV_5|SYSCTL_USE_PLL|SYSCTL_XTAL_16MHZ|SYSCTL_OSC_MAIN);
    SysCtlPWMClockSet(SYSCTL_PWMDIV_64);    //625kHz PWM Clock

}
/*******************************
 * Enabling System Peripherals
 * PORTF,PORTB and PORTC in this case
 ******************************/
void peripheralEnable(){
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOB);
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOF);
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOC);
    SysCtlPeripheralEnable(SYSCTL_PERIPH_PWM0); // Enabling PWM0
    SysCtlPeripheralEnable(SYSCTL_PERIPH_PWM1); // Enabling PWM1
}
/*************************************
 * Configuring Pin as Input Or Output
 * And Setting PWM Pin to Always High
 *************************************/
void configIOPin(){
    GPIOPinTypeGPIOOutput(GPIO_PORTB_BASE,GPIO_PIN_3);
    GPIOPinTypeGPIOOutput(GPIO_PORTC_BASE,GPIO_PIN_4|GPIO_PIN_5|GPIO_PIN_6);
    GPIOPinTypeGPIOOutput(GPIO_PORTF_BASE,GPIO_PIN_3|GPIO_PIN_2);
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
 * Bit 0 (LSB) corresponds to PB3
 * Bit 3       corresponds to PF3
 * Bit 4       corresponds to PC4
 * Bit 6       corresponds to PF6
 *****************************************************/
void motion(uint8_t direction){
    GPIOPinWrite(GPIO_PORTB_BASE,GPIO_PIN_3,direction<<3);
    GPIOPinWrite(GPIO_PORTC_BASE,GPIO_PIN_4|GPIO_PIN_6,direction);
    GPIOPinWrite(GPIO_PORTF_BASE,GPIO_PIN_3,direction);
}
/******************************************************
 * This function is for enabling the PWM Modules
 * PWM can be enabled on a pin based on the datasheet
 *****************************************************/
void enablePWM(){
    GPIOPinTypePWM(GPIO_PORTF_BASE, GPIO_PIN_2);
    GPIOPinConfigure(GPIO_PF2_M1PWM6);
    GPIOPinTypePWM(GPIO_PORTC_BASE, GPIO_PIN_5);
    GPIOPinConfigure(GPIO_PC5_M0PWM7);
    PWMGenConfigure(PWM0_BASE, PWM_GEN_3, PWM_GEN_MODE_DOWN | PWM_GEN_MODE_NO_SYNC);//Count Down Mode
    PWMGenPeriodSet(PWM0_BASE, PWM_GEN_3, 255); //Load Count value
    PWMGenConfigure(PWM1_BASE, PWM_GEN_3, PWM_GEN_MODE_DOWN | PWM_GEN_MODE_NO_SYNC);//Count Down Mode
    PWMGenPeriodSet(PWM1_BASE, PWM_GEN_3, 255); //Load Count value
    PWMGenEnable(PWM0_BASE, PWM_GEN_3);
    PWMGenEnable(PWM1_BASE, PWM_GEN_3);
    PWMOutputState(PWM1_BASE, PWM_OUT_6_BIT, true);
    PWMOutputState(PWM0_BASE, PWM_OUT_7_BIT, true);
}
/*************************************************************
 * This function is used to control the speed of the motors
 * The speed can changed by the PWMPulseWidthSet() function
 * lSpeed is used to control the speed of left motor
 * rSpeed is used to control the speed of right motor
 ************************************************************/
void Velocity(uint8_t lSpeed,uint8_t rSpeed){
        lSpeed=(lSpeed>255)?255:lSpeed;
        rSpeed=(rSpeed>255)?255:rSpeed;
        PWMPulseWidthSet(PWM1_BASE, PWM_OUT_6, lSpeed);
        PWMPulseWidthSet(PWM0_BASE, PWM_OUT_7, rSpeed);
}
