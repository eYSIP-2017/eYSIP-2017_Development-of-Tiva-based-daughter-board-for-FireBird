/********************************************************************************
 Written by: Ayush Gaurav and Nagesh K.
From eRTS Lab, CSE Department, IIT Bombay.

 Date: 16th June 2017

This experiment demonstrates simple motion control.

 Concepts covered: Velocity Control Using PWM

 There are two components to the motion control:
 1. Direction control.
 2. Velocity control using PWM.

 Connection Details:
            For uC based Board
                        L-1---->PB0;        L-2---->PB1;
                        R-1---->PF4;        R-2---->PA5;
                        PF3 ----> PWM L;     PA6 ----> PWM R;
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

#define right           0x22
#define left            0x11
#define softRight       0x10
#define softLeft        0x02
#define forward         0x12
#define backward        0x21
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
 * * The PWM module is clocked by the system clock through a divider, and that divider has
   a range of 2 to 64.
 * By setting the divider to 64, it will run the PWM clock at 625 kHz.
 ***************************************************************************************/
void setupCLK(){
    SysCtlClockSet(SYSCTL_SYSDIV_5|SYSCTL_USE_PLL|SYSCTL_XTAL_16MHZ|SYSCTL_OSC_MAIN);
    SysCtlPWMClockSet(SYSCTL_PWMDIV_64);    //625kHz PWM Clock

}
/*******************************
 * Enabling System Peripherals
 * PORTF,PORTB and PORTA in this case
 ******************************/
void peripheralEnable(){
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOB);
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOF);
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOA);
    SysCtlPeripheralEnable(SYSCTL_PERIPH_PWM1); // Enabling PWM1
}
/*************************************
 * Configuring Pin as Input Or Output
 * And Setting PWM Pin to Always High
 *************************************/
void configIOPin(){
    GPIOPinTypeGPIOOutput(GPIO_PORTB_BASE,GPIO_PIN_0|GPIO_PIN_1);
    GPIOPinTypeGPIOOutput(GPIO_PORTA_BASE,GPIO_PIN_5);
    GPIOPinTypeGPIOOutput(GPIO_PORTF_BASE,GPIO_PIN_4);
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
 * Bit 0       corresponds to PB0
 * Bit 1       corresponds to PB1
 * Bit 4       corresponds to PF4
 * Bit 5       corresponds to PA5
 *****************************************************/
void motion(uint8_t direction){
    GPIOPinWrite(GPIO_PORTB_BASE,GPIO_PIN_1|GPIO_PIN_0,direction);
    GPIOPinWrite(GPIO_PORTF_BASE,GPIO_PIN_4,direction);
    GPIOPinWrite(GPIO_PORTA_BASE,GPIO_PIN_5,direction);
}
/******************************************************
 * This function is for enabling the PWM Modules
 * PWM can be enabled on a pin based on the datasheet
 *****************************************************/
void enablePWM(){
    GPIOPinTypePWM(GPIO_PORTF_BASE, GPIO_PIN_3);
    GPIOPinConfigure(GPIO_PF3_M1PWM7);
    GPIOPinTypePWM(GPIO_PORTA_BASE, GPIO_PIN_6);
    GPIOPinConfigure(GPIO_PA6_M1PWM2);
    PWMGenConfigure(PWM1_BASE, PWM_GEN_3, PWM_GEN_MODE_DOWN | PWM_GEN_MODE_NO_SYNC);//Count Down Mode
    PWMGenPeriodSet(PWM1_BASE, PWM_GEN_3, 255); //Load Count value
    PWMGenConfigure(PWM1_BASE, PWM_GEN_1, PWM_GEN_MODE_DOWN | PWM_GEN_MODE_NO_SYNC);//Count Down Mode
    PWMGenPeriodSet(PWM1_BASE, PWM_GEN_1, 255); //Load Count value
    PWMGenEnable(PWM1_BASE, PWM_GEN_3); //Enable the generators
    PWMGenEnable(PWM1_BASE, PWM_GEN_1);
    PWMOutputState(PWM1_BASE, PWM_OUT_7_BIT|PWM_OUT_2_BIT, true);
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
        PWMPulseWidthSet(PWM1_BASE, PWM_OUT_7, lSpeed);
        PWMPulseWidthSet(PWM1_BASE, PWM_OUT_2, rSpeed);
}
