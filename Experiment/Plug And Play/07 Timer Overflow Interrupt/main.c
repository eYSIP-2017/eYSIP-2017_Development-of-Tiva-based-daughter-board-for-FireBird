/*****************************************************************************************
 Written by: Ayush Gaurav And Nagesh K.
 From eRTS Lab, CSE Department, IIT Bombay.

 Date: 16th June 2017

 This experiment demonstrates use of timer overflow interrupt

 Concepts covered:  Use of timer overflow interrupt to do tasks in a periodic way

 In this example timer 0's(subtimer A) overflow interrupt is used to turn on and off buzzer
 with the time period of 1 second

 Connections: Buzzer is connected to PF4 on plug and play board and to PA2 on uC board.

 Note: Make sure that in the configuration options following settings are
 done for proper operation of the code.
*****************************************************************************************/
#include <stdint.h>
#include <stdbool.h>
#include "inc/hw_types.h"
#include "inc/hw_memmap.h"
#include "inc/tm4c123gh6pm.h"
//This header File is important to Unlock GPIO Pins
#include "inc/hw_gpio.h"
#include "driverlib/sysctl.h"
#include "driverlib/gpio.h"
//Used for enabling the timer
#include "driverlib/timer.h"
//Used for enabling interrupt
#include "driverlib/interrupt.h"
/**** Useful Macros Definition******/
/******Remove the comments if you are using uC board******/
#define buzzerEnable    SYSCTL_PERIPH_GPIOA
#define buzzer          GPIO_PORTA_BASE
#define buzzerPin       GPIO_PIN_2
/**********************************************************/

/******Remove the comments if you are using uC board******
#define buzzerEnable    SYSCTL_PERIPH_GPIOF
#define buzzer          GPIO_PORTF_BASE
#define buzzerPin       GPIO_PIN_4
**********************************************************/

#define buzzerOn()      GPIOPinWrite(buzzer,buzzerPin,255)
#define buzzerOff()     GPIOPinWrite(buzzer,buzzerPin,0)
/***********************************/
void setupCLK();
void peripheralEnable();
void configIOPin();
void timerEnable();

uint32_t ui32Period;    // used for generating one second delay
int flag = 0;           //used to monitor the state of buzzer
int main(void) {
    setupCLK();
    peripheralEnable();
    configIOPin();
    timerEnable();
    while(1){

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
 * buzzer Port in this case
 * buzzerPin for buzzer output
 * Enabling Timer 0
 ******************************/
void peripheralEnable(){
    SysCtlPeripheralEnable(buzzerEnable);
    SysCtlPeripheralEnable(SYSCTL_PERIPH_TIMER0);
    /***** Just in case you are not familiar with macros*****
        SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOF);
     *************This is enabling PORTF*********************/
}
/*************************************
 * Configuring Pin as Input Or Output
 *************************************/
void configIOPin(){
    GPIOPinTypeGPIOOutput(buzzer, buzzerPin);
    /***** Just in case you are not familiar with macros*****
        GPIOPinTypeGPIOOutput(buzzer, GPIO_PIN_4);
     *****************This is P4 output*********************/
}
/*******************************
 * Enabling Timer 0
 * Timer is configured to be periodic
 ******************************/
void timerEnable(){
    TimerConfigure(TIMER0_BASE, TIMER_CFG_PERIODIC);
    ui32Period = (SysCtlClockGet() / 100) / 2;
    TimerLoadSet(TIMER0_BASE, TIMER_A, ui32Period -1);
    IntEnable(INT_TIMER0A);
    TimerIntEnable(TIMER0_BASE, TIMER_TIMA_TIMEOUT);
    IntMasterEnable();
    TimerEnable(TIMER0_BASE, TIMER_A);
}
/*******************************************************
 * This function is executed when the timer overflows
 * In this example the buzzer is switched on and off
 ******************************************************/
void Timer0IntHandler(void)
{
    // Clear the timer interrupt
    TimerIntClear(TIMER0_BASE, TIMER_TIMA_TIMEOUT);
    if(flag == 0){
        buzzerOn();
        flag = 1;
    }
    else{
        buzzerOff();
    }
}
