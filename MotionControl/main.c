/********************************************************************************
 Written by: Ayush Gaurav

 Date: 29th May 2017

 This experiment demonstrates the simple operation of Buzzer ON/OFF with
 one second delay. Buzzer is connected to PORTC.3 of TM4C123GH6PM(Tiva C Series)

This experiment demonstrates simple motion control.

 Concepts covered: Simple motion control

 There are two components to the motion control:
 1. Direction control using pins PORTA0 to PORTA3
 2. Velocity control by PWM on pins PL3 and PL4 using OC5A and OC5B of timer 5.

 In this experiment for the simplicity PL3 and PL4 are kept at logic 1.

 Pins for PWM are kept at logic 1.

 Connection Details:    L-1---->PB0;        L-2---->PB1;
                        R-1---->PB2;        R-2---->PB3;
                        PB4 ----> PWM L  PB5----> PWM R;


*********************************************************************************/
//This header File is important to Unlock GPIO Pins
#include <stdint.h>
#include <stdbool.h>
#include "inc/tm4c123gh6pm.h"
#include "inc/hw_memmap.h"
#include "inc/hw_types.h"
#include "driverlib/sysctl.h"
#include "driverlib/gpio.h"
#include "driverlib/debug.h"
#include "driverlib/pwm.h"
#include "driverlib/pin_map.h"
#include "inc/hw_gpio.h"
#include "driverlib/rom.h"
#include "driverlib/interrupt.h"
#include "driverlib/timer.h"
#define motorPort           GPIO_PORTB_BASE
#define leftMotor1          GPIO_PIN_0
#define leftMotor2          GPIO_PIN_1
#define leftMotorPWM        GPIO_PIN_4
#define rightMotor1         GPIO_PIN_2
#define rightMotor2         GPIO_PIN_3
#define rightMotorPWM       GPIO_PIN_5
#define right               0x0A
#define left                0x05
#define forward             0x06
#define backward            0x09
#define stop                0x00
#define PWMFrequency        125 //5000 counts
#define PWMresolution       20
#define PWMRightMotorOn()   PWMOutputState(PWM0_BASE, PWM_OUT_3_BIT, true)
#define PWMLeftMotorOn()    PWMOutputState(PWM0_BASE, PWM_OUT_2_BIT, true)
#define PWMRightMotorOff()  PWMOutputState(PWM0_BASE, PWM_OUT_3_BIT, false)
#define PWMLeftMotorOff()   PWMOutputState(PWM0_BASE, PWM_OUT_2_BIT, false)
void setupCLK();
void peripheralEnable();
void configIOPin();
void delay_ms(uint64_t delay);
void delay_ms(uint64_t delay);
void motion(uint8_t);
void enablePWM();
void speed(uint8_t lSpeed,uint8_t rSpeed);
int main(void) {
    setupCLK();
    peripheralEnable();
    configIOPin();
    enablePWM();
    motion(forward);
    uint8_t i;
    while(1){
        ///speed(100,249);
        for(i=0;i<250;i+=10){
            speed(i,i);
            delay_ms(500);
        }
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
    SysCtlPWMClockSet(SYSCTL_PWMDIV_64);//625kHz PWM Clock
}
/*******************************
 * Enabling System Peripherals
 * PORTF in this case
 * PF1 for buzzer output
 ******************************/
void peripheralEnable(){
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOB);
    SysCtlPeripheralEnable(SYSCTL_PERIPH_PWM0);//Enabling PWM0
}
/*************************************
 * Configuring Pin as Input Or Output
 *************************************/
void configIOPin(){
    GPIOPinTypeGPIOOutput(motorPort,rightMotor1|rightMotor2|leftMotor1|leftMotor2);
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
    GPIOPinWrite(motorPort,rightMotor1|rightMotor2|leftMotor1|leftMotor2,direction);
}
void enablePWM(){
    GPIOPinTypePWM(motorPort, leftMotorPWM);
    GPIOPinConfigure(GPIO_PB4_M0PWM2);
    GPIOPinTypePWM(motorPort, rightMotorPWM);
    GPIOPinConfigure(GPIO_PB5_M0PWM3);
    PWMGenConfigure(PWM0_BASE, PWM_GEN_1, PWM_GEN_MODE_DOWN);//Count Down Mode
    PWMGenPeriodSet(PWM0_BASE, PWM_GEN_1,4999); //Load Count value
    //PWMOutputState(PWM0_BASE, PWM_OUT_2_BIT, true);
    //PWMOutputState(PWM0_BASE, PWM_OUT_3_BIT, true);
    PWMRightMotorOn();
    PWMLeftMotorOn();
    PWMGenEnable(PWM0_BASE, PWM_GEN_1);
}
void speed(uint8_t lSpeed,uint8_t rSpeed){
        lSpeed=(lSpeed>249)?249:lSpeed;
        rSpeed=(rSpeed>249)?249:rSpeed;
        PWMPulseWidthSet(PWM0_BASE, PWM_OUT_2,(lSpeed*PWMresolution)+1);
        PWMPulseWidthSet(PWM0_BASE, PWM_OUT_3,(rSpeed*PWMresolution)+1);
}
