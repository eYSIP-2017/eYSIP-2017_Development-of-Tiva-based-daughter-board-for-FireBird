/********************************************************************************
 Written by: Ayush Gaurav

 Date: 29th May 2017

 This experiment demonstrates the simple operation of Buzzer ON/OFF with
 one second delay. Buzzer is connected to PORTC.3 of TM4C123GH6PM(Tiva C Series)

 Concepts covered:
 Output operation, generating exact delay

 Note: Make sure that in the configuration options following settings are
 done for proper operation of the code
*********************************************************************************/
#include <stdint.h>
#include <stdbool.h>
#include "inc/hw_types.h"
#include "inc/hw_memmap.h"
//This header File is important to Unlock GPIO Pins
#include "inc/hw_gpio.h"
#include "driverlib/sysctl.h"
#include "driverlib/gpio.h"

/**** Useful Macros Definition******/
#define PORTF       GPIO_PORTF_BASE
#define buzzerPin   GPIO_PIN_1
#define userSwitch2 GPIO_PIN_0
#define redLed      GPIO_PIN_1
#define blueLed     GPIO_PIN_2
#define greenLed    GPIO_PIN_3
#define userSwitch1 GPIO_PIN_4
#define buzzerOn()     GPIOPinWrite(PORTF,buzzerPin,2)
#define buzzerOff()   GPIOPinWrite(PORTF,buzzerPin,0)
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
 * PORTF in this case
 * PF1 for buzzer output
 ******************************/
void peripheralEnable(){
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOF);
}
/*************************************
 * Configuring Pin as Input Or Output
 *************************************/
void configIOPin(){
    GPIOPinTypeGPIOOutput(GPIO_PORTF_BASE, buzzerPin);
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
