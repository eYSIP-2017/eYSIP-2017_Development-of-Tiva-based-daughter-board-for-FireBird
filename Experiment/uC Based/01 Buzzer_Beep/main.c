/*****************************************************************************************
 Written by: Ayush Gaurav And Nagesh K.
 From ERTS Lab, CSE Department, IIT Bombay.

 Date: 16th June 2017

 This experiment demonstrates the simple operation of Buzzer ON/OFF with
 one delay. Buzzer is connected to PF4 on plug and play board and to PA2 on uC board.

 Concepts covered:
 Output operation, generating delay,setting operating frequency of the board.

 Note: Make sure that in the configuration options following settings are
 done for proper operation of the code.
*****************************************************************************************/
#include <stdint.h>
#include <stdbool.h>
#include "inc/hw_types.h"
#include "inc/hw_memmap.h"
//This header File is important to Unlock GPIO Pins
#include "inc/hw_gpio.h"
#include "driverlib/sysctl.h"
#include "driverlib/gpio.h"

/**** Useful Macros Definition******/
/******Remove the comments if you are using uC board******/
#define buzzerEnable    SYSCTL_PERIPH_GPIOA
#define buzzer          GPIO_PORTA_BASE
#define buzzerPin       GPIO_PIN_2
/*********************************************************/

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
void delay_ms(uint64_t delay);
void delay_ms(uint64_t delay);
int main(void) {
    setupCLK();
    peripheralEnable();
    configIOPin();
    while(1){
        buzzerOn();
        delay_ms(1000);
        buzzerOff();
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
 * buzzer Port in this case
 * buzzerPin for buzzer output
 ******************************/
void peripheralEnable(){
    SysCtlPeripheralEnable(buzzerEnable);
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
/*********************************************
 * Calculating Delays
 * extern void SysCtlDelay(uint32_t ui32Count)
 * waits until the counting has been completed
 **********************************************/
void delay_ms(uint64_t delay){
    SysCtlDelay(delay*SysCtlClockGet()/3000.0);
}
void delay_us(uint64_t delay){
    SysCtlDelay(delay*SysCtlClockGet()/3000000.0);
}
