/********************************************************************************
 Written by: Ayush Gaurav and Nagesh K.
From ERTS Lab, CSE Department, IIT Bombay.

 Date: 16th June 2017

This experiment demonstrates position control of Servo Motors.

 Concepts covered: Postion Control using PWM.

Note: Refer the hardware manual to identify the ground pin.

 Connection Details:
            For Plug And Play Board
                        Servo1 ------> PF1
                        Servo2 ------> PB6
                        Servo3 ------> PB7

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
#include "driverlib/debug.h"
//Used for PWM
#include "driverlib/pwm.h"

#define PWM_FREQUENCY  55

volatile uint32_t ui32Load;
volatile uint32_t ui32PWMClock;
volatile uint8_t ui8Adjust;

void setupCLK();
void peripheralEnable();
void delay_ms(uint64_t delay);
void delay_ms(uint64_t delay);
void enablePWM();

int main(void){
    setupCLK();
    peripheralEnable();
    enablePWM();
    ui8Adjust=30;
    delay_ms(2000);
    while(1){
        for(ui8Adjust=30; ui8Adjust < 130; ui8Adjust++){
            PWMPulseWidthSet(PWM1_BASE, PWM_OUT_5, ui8Adjust * ui32Load / 1000);
            PWMPulseWidthSet(PWM0_BASE, PWM_OUT_0, ui8Adjust * ui32Load / 1000);
            PWMPulseWidthSet(PWM0_BASE, PWM_OUT_1, ui8Adjust * ui32Load / 1000);
            delay_ms(50);
        }
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
 * PORTF,PORTB and PORTC in this case
 ******************************/
void peripheralEnable(){
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOB);
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOF);
    SysCtlPeripheralEnable(SYSCTL_PERIPH_PWM0); // Enabling PWM0
    SysCtlPeripheralEnable(SYSCTL_PERIPH_PWM1); // Enabling PWM1
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
 * This function is for enabling the PWM Modules
 * PWM can be enabled on a pin based on the datasheet
 *****************************************************/
void enablePWM(){
    GPIOPinTypePWM(GPIO_PORTF_BASE, GPIO_PIN_1);
    GPIOPinConfigure(GPIO_PF1_M1PWM5);
    GPIOPinTypePWM(GPIO_PORTB_BASE, GPIO_PIN_6);
    GPIOPinConfigure(GPIO_PB6_M0PWM0);
    GPIOPinTypePWM(GPIO_PORTB_BASE, GPIO_PIN_7);
    GPIOPinConfigure(GPIO_PB7_M0PWM1);
    ui32PWMClock = SysCtlClockGet() / 64;   //Divide the system clock by 64 to get the PWM frequency
    ui32Load = (ui32PWMClock / PWM_FREQUENCY) - 1;  //Calculate the number of counts required for 55Hz
    PWMGenConfigure(PWM0_BASE, PWM_GEN_0, PWM_GEN_MODE_DOWN | PWM_GEN_MODE_NO_SYNC);//Count Down Mode
    PWMGenPeriodSet(PWM0_BASE, PWM_GEN_0, ui32Load); //Load Count value
    PWMGenConfigure(PWM1_BASE, PWM_GEN_2, PWM_GEN_MODE_DOWN | PWM_GEN_MODE_NO_SYNC);//Count Down Mode
    PWMGenPeriodSet(PWM1_BASE, PWM_GEN_2, ui32Load); //Load Count value
    PWMPulseWidthSet(PWM1_BASE, PWM_OUT_5, ui8Adjust);
    PWMPulseWidthSet(PWM0_BASE, PWM_OUT_0, ui8Adjust);
    PWMPulseWidthSet(PWM0_BASE, PWM_OUT_1, ui8Adjust);
    PWMOutputState(PWM1_BASE, PWM_OUT_5_BIT, true);
    PWMOutputState(PWM0_BASE, PWM_OUT_0_BIT, true);
    PWMOutputState(PWM0_BASE, PWM_OUT_1_BIT, true);
    PWMGenEnable(PWM0_BASE, PWM_GEN_0);
    PWMGenEnable(PWM1_BASE, PWM_GEN_2);
}
