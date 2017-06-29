/*****************************************************************************************
 Written by: Ayush Gaurav And Nagesh K.
 From eRTS Lab, CSE Department, IIT Bombay.

 Date: 24th June 2017

 In this experiment demonstrate USB to Serial Communication.

 Concepts covered:  Port Expander and I2C

UART Connection: I1C1.
I2C1SCL-------->SCL on Port Expander.
I2C1SDA-------->SDA on Port Expander.

 Note: Make sure that in the configuration options following settings are
 done for proper operation of the code.
*****************************************************************************************/
#include <stdarg.h>
#include <stdbool.h>
#include <stdint.h>
#include "inc/hw_i2c.h"
#include "inc/hw_memmap.h"
#include "inc/hw_types.h"
#include "inc/hw_gpio.h"
#include "driverlib/i2c.h"
#include "driverlib/sysctl.h"
#include "driverlib/gpio.h"
#include "driverlib/pin_map.h"
#include "inc/tm4c123gh6pm.h"
#include "driverlib/interrupt.h"
void setupCLK();
void peripheralEnable();
void gpioEnable();
void InitI2C1(void);
void I2CSendString(uint32_t slave_addr, char array[]);
void I2CSend(uint8_t slave_addr, uint8_t num_of_args, ...);
uint32_t I2CReceive(uint32_t slave_addr, uint8_t reg);
void portExpanderIO(unsigned char port,unsigned char pin);
void portExpanderSetOutput(unsigned char,unsigned char);
unsigned char portExpanderReadInput(unsigned char);
void portExpanderInterruptEnableAnyChange(unsigned char,unsigned char);
void portExpanderpullup(unsigned char,unsigned char);
void portExpanderInterruptHandler();
int main(void) {
    setupCLK();
    peripheralEnable();
    gpioEnable();
    InitI2C1();
    portExpanderIO(0x00,0xff);
    portExpanderIO(0x01,0x00);
    portExpanderSetOutput(0x01,0x00);
    portExpanderpullup(0x00,0x0f);
    portExpanderInterruptEnableAnyChange(0x00,0xff);
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
 * PortC in this case
 ******************************/
void peripheralEnable(){
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOC);
}
/************************************************
 * Making Pin Port C7 as input with weak pull up
 ************************************************/
void gpioEnable(){
    GPIOPinTypeGPIOOutput(GPIO_PORTC_BASE, GPIO_PIN_7);;
    GPIOPinTypeGPIOInput(GPIO_PORTC_BASE, GPIO_PIN_7);
    GPIOPadConfigSet(GPIO_PORTC_BASE ,GPIO_PIN_7,GPIO_STRENGTH_2MA,GPIO_PIN_TYPE_STD_WPU);
}
/****************************************
* This function is used to enable I2C1
****************************************/
void InitI2C1(void){
    SysCtlPeripheralEnable(SYSCTL_PERIPH_I2C1);
    SysCtlPeripheralReset(SYSCTL_PERIPH_I2C1);
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOA);
    GPIOPinConfigure(GPIO_PA6_I2C1SCL);
    GPIOPinConfigure(GPIO_PA7_I2C1SDA);
    GPIOPinTypeI2CSCL(GPIO_PORTA_BASE, GPIO_PIN_6);
    GPIOPinTypeI2C(GPIO_PORTA_BASE, GPIO_PIN_7);
    // Enable and initialize the I2C1 master module.  Use the system clock for
    // the I2C1 module.  The last parameter sets the I2C data transfer rate.
    // If false the data rate is set to 100kbps and if true the data rate will
    // be set to 400kbps.
    I2CMasterInitExpClk(I2C1_BASE, SysCtlClockGet(), false);
    //clear I2C FIFOs
    HWREG(I2C1_BASE + I2C_O_FIFOCTL) = 80008000;
    I2CSend(0x20,2,0x0A,1<<6);
}
/***********************************************************************
 * This function is used to send n number of data on serial Data line
 ***********************************************************************/
void I2CSend(uint8_t slave_addr, uint8_t num_of_args, ...){
    I2CMasterSlaveAddrSet(I2C1_BASE, slave_addr, false);
    va_list vargs;
    va_start(vargs, num_of_args);
    I2CMasterDataPut(I2C1_BASE, va_arg(vargs, uint32_t));
    if(num_of_args == 1){
        I2CMasterControl(I2C1_BASE, I2C_MASTER_CMD_SINGLE_SEND);
        while(I2CMasterBusy(I2C1_BASE));

        va_end(vargs);
    }
    else{
        I2CMasterControl(I2C1_BASE, I2C_MASTER_CMD_BURST_SEND_START);
        while(I2CMasterBusy(I2C1_BASE));
        uint8_t i ;
        for(i = 1; i < (num_of_args - 1); i++){
            I2CMasterDataPut(I2C1_BASE, va_arg(vargs, uint32_t));
            I2CMasterControl(I2C1_BASE, I2C_MASTER_CMD_BURST_SEND_CONT);
            while(I2CMasterBusy(I2C1_BASE));
        }
        I2CMasterDataPut(I2C1_BASE, va_arg(vargs, uint32_t));
        I2CMasterControl(I2C1_BASE, I2C_MASTER_CMD_BURST_SEND_FINISH);
        while(I2CMasterBusy(I2C1_BASE));
        va_end(vargs);
    }
}
/***********************************************************************
 * This function is used to send string data on serial Data line
 ***********************************************************************/
void I2CSendString(uint32_t slave_addr, char array[]){
    I2CMasterSlaveAddrSet(I2C1_BASE, slave_addr, false);
    I2CMasterDataPut(I2C1_BASE, array[0]);
    if(array[1] == '\0'){
        I2CMasterControl(I2C1_BASE, I2C_MASTER_CMD_SINGLE_SEND);
        while(I2CMasterBusy(I2C1_BASE));
    }
    else{
        I2CMasterControl(I2C1_BASE, I2C_MASTER_CMD_BURST_SEND_START);
        while(I2CMasterBusy(I2C1_BASE));
        uint8_t i = 1;
        while(array[i + 1] != '\0'){
            I2CMasterDataPut(I2C1_BASE, array[i++]);
            I2CMasterControl(I2C1_BASE, I2C_MASTER_CMD_BURST_SEND_CONT);
            while(I2CMasterBusy(I2C1_BASE));
        }
        I2CMasterDataPut(I2C1_BASE, array[i]);
        I2CMasterControl(I2C1_BASE, I2C_MASTER_CMD_BURST_SEND_FINISH);
        while(I2CMasterBusy(I2C1_BASE));
    }
}
/***********************************************************************
 * This function is used to receive 1 data on serial Data line
 ***********************************************************************/
uint32_t I2CReceive(uint32_t slave_addr, uint8_t reg){
    I2CMasterSlaveAddrSet(I2C1_BASE, slave_addr, false);
    I2CMasterDataPut(I2C1_BASE, reg);
    I2CMasterControl(I2C1_BASE, I2C_MASTER_CMD_BURST_SEND_START);
    while(I2CMasterBusy(I2C1_BASE));
    I2CMasterSlaveAddrSet(I2C1_BASE, slave_addr, true);
    I2CMasterControl(I2C1_BASE, I2C_MASTER_CMD_SINGLE_RECEIVE);
    while(I2CMasterBusy(I2C1_BASE));
    return I2CMasterDataGet(I2C1_BASE);
}
/***********************************************************************
 * This function is used to set PORTA or PORTB pins as I/O
 ***********************************************************************/
void portExpanderIO(unsigned char port,unsigned char pin){
    I2CSend(0x20,2,port,pin);
}
/***********************************************************************
 * This function is used to give PORTA or PORTB pin output values
 ***********************************************************************/
void portExpanderSetOutput(unsigned char port,unsigned char pin){
    I2CSend(0x20,2,port+(0x12),pin);
}
/***********************************************************************
 * This function is used to read PORTA or PORTB pin values
 ***********************************************************************/
unsigned char portExpanderReadInput(unsigned char port){
    return(I2CReceive(0x20,(port+12)));
}
/***********************************************************************
 * This function is used to enable interrupt on PORTA or PORTB pin
 ***********************************************************************/
void portExpanderInterruptEnableAnyChange(unsigned char port,unsigned char pin){
    portExpanderIO(port,pin);
    I2CSend(0x20,2,(0x04)+port,pin);
    I2CSend(0x20,2,(0x08)+port,pin);
    GPIOIntDisable(GPIO_PORTC_BASE,GPIO_PIN_7);        // Disable interrupt for PF4 (in case it was enabled)
    GPIOIntClear(GPIO_PORTC_BASE,GPIO_PIN_7);      // Clear pending interrupts for PF4
    GPIOIntRegister(GPIO_PORTC_BASE,portExpanderInterruptHandler);     // Register our handler function for port F
    GPIOIntTypeSet(GPIO_PORTC_BASE,GPIO_PIN_7,GPIO_FALLING_EDGE);             // Configure PF4 for falling edge trigger
    GPIOIntEnable(GPIO_PORTC_BASE,GPIO_PIN_7);
}
/**************************************
 * Pin change interrupt service routine
 **************************************/
void portExpanderInterruptHandler(){
    if(GPIOIntStatus(GPIO_PORTC_BASE, false)&GPIO_PIN_7){
        if(I2CReceive(0x20,0x0e)&0x01==0x01){
            portExpanderSetOutput(0x01,0xff);
        }
        I2CReceive(0x20,0x10);
        I2CReceive(0x20,0x11);
        GPIOIntClear(GPIO_PORTC_BASE,GPIO_PIN_7);
    }
}
/***********************************************************************
 * This function is used to give external 100K pull toPORTA or PORTB pin
 ***********************************************************************/
void portExpanderpullup(unsigned char port,unsigned char pin){
    I2CSend(0x20,2,(0x0C)+port,pin);
}
