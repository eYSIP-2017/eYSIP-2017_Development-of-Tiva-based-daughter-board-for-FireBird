/********************************************************************************
   Written by: Ayush Gaurav And Nagesh K.
   From ERTS Lab, CSE Department, IIT Bombay.

   Date: 24th June 2017

   In this experiment demonstrate PortExapnder.

   Concepts covered:  Port Expander and I2C

   I2C Connections: I2C0.
   I2C1SCL-------->SCL on Port Expander.
   I2C1SDA-------->SDA on Port Expander.

 Note: Make sure that in the configuration options following settings are
 done for proper operation of the code.
 ******************************************************************************/
 #include <stdarg.h>
#include <stdbool.h>
#include <stdint.h>
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
void InitI2C0(void);
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
    InitI2C0();
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
* This function is used to enable I2C0
*****************************************/
void InitI2C0(void){
    SysCtlPeripheralEnable(SYSCTL_PERIPH_I2C0);
    SysCtlPeripheralReset(SYSCTL_PERIPH_I2C0);
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOB);
    GPIOPinConfigure(GPIO_PB2_I2C0SCL);
    GPIOPinConfigure(GPIO_PB3_I2C0SDA);
    GPIOPinTypeI2CSCL(GPIO_PORTB_BASE, GPIO_PIN_2);
    GPIOPinTypeI2C(GPIO_PORTB_BASE, GPIO_PIN_3);
    // Enable and initialize the I2C0 master module.  Use the system clock for
    // the I2C0 module.  The last parameter sets the I2C data transfer rate.
    // If false the data rate is set to 100kbps and if true the data rate will
    // be set to 400kbps.
    I2CMasterInitExpClk(I2C0_BASE, SysCtlClockGet(), false);
    //clear I2C FIFOs
    HWREG(I2C0_BASE + I2C_O_FIFOCTL) = 80008000;
    I2CSend(0x20,2,0x0A,1<<6);
}
/***********************************************************************
 * This function is used to send n number of data on serial Data line
 ***********************************************************************/
void I2CSend(uint8_t slave_addr, uint8_t num_of_args, ...)
{
    // Tell the master module what address it will place on the bus when
    // communicating with the slave.
    I2CMasterSlaveAddrSet(I2C0_BASE, slave_addr, false);

    //stores list of variable number of arguments
    va_list vargs;

    //specifies the va_list to "open" and the last fixed argument
    //so vargs knows where to start looking
    va_start(vargs, num_of_args);

    //put data to be sent into FIFO
    I2CMasterDataPut(I2C0_BASE, va_arg(vargs, uint32_t));

    //if there is only one argument, we only need to use the
    //single send I2C function
    if(num_of_args == 1)
    {
        //Initiate send of data from the MCU
        I2CMasterControl(I2C0_BASE, I2C_MASTER_CMD_SINGLE_SEND);

        // Wait until MCU is done transferring.
        while(I2CMasterBusy(I2C0_BASE));

        //"close" variable argument list
        va_end(vargs);
    }

    //otherwise, we start transmission of multiple bytes on the
    //I2C bus
    else
    {
        //Initiate send of data from the MCU
        I2CMasterControl(I2C0_BASE, I2C_MASTER_CMD_BURST_SEND_START);

        // Wait until MCU is done transferring.
        while(I2CMasterBusy(I2C0_BASE));

        //send num_of_args-2 pieces of data, using the
        //BURST_SEND_CONT command of the I2C module
        uint8_t i ;
        for(i = 1; i < (num_of_args - 1); i++)
        {
            //put next piece of data into I2C FIFO
            I2CMasterDataPut(I2C0_BASE, va_arg(vargs, uint32_t));
            //send next data that was just placed into FIFO
            I2CMasterControl(I2C0_BASE, I2C_MASTER_CMD_BURST_SEND_CONT);

            // Wait until MCU is done transferring.
            while(I2CMasterBusy(I2C0_BASE));
        }

        //put last piece of data into I2C FIFO
        I2CMasterDataPut(I2C0_BASE, va_arg(vargs, uint32_t));
        //send next data that was just placed into FIFO
        I2CMasterControl(I2C0_BASE, I2C_MASTER_CMD_BURST_SEND_FINISH);
        // Wait until MCU is done transferring.
        while(I2CMasterBusy(I2C0_BASE));

        //"close" variable args list
        va_end(vargs);
    }
}
/***********************************************************************
* This function is used to send string data on serial Data line
***********************************************************************/
void I2CSendString(uint32_t slave_addr, char array[])
{
    // Tell the master module what address it will place on the bus when
    // communicating with the slave.
    I2CMasterSlaveAddrSet(I2C0_BASE, slave_addr, false);

    //put data to be sent into FIFO
    I2CMasterDataPut(I2C0_BASE, array[0]);

    //if there is only one argument, we only need to use the
    //single send I2C function
    if(array[1] == '\0')
    {
        //Initiate send of data from the MCU
        I2CMasterControl(I2C0_BASE, I2C_MASTER_CMD_SINGLE_SEND);

        // Wait until MCU is done transferring.
        while(I2CMasterBusy(I2C0_BASE));
    }

    //otherwise, we start transmission of multiple bytes on the
    //I2C bus
    else
    {
        //Initiate send of data from the MCU
        I2CMasterControl(I2C0_BASE, I2C_MASTER_CMD_BURST_SEND_START);

        // Wait until MCU is done transferring.
        while(I2CMasterBusy(I2C0_BASE));

        //initialize index into array
        uint8_t i = 1;

        //send num_of_args-2 pieces of data, using the
        //BURST_SEND_CONT command of the I2C module
        while(array[i + 1] != '\0')
        {
            //put next piece of data into I2C FIFO
            I2CMasterDataPut(I2C0_BASE, array[i++]);

            //send next data that was just placed into FIFO
            I2CMasterControl(I2C0_BASE, I2C_MASTER_CMD_BURST_SEND_CONT);

            // Wait until MCU is done transferring.
            while(I2CMasterBusy(I2C0_BASE));
        }

        //put last piece of data into I2C FIFO
        I2CMasterDataPut(I2C0_BASE, array[i]);

        //send next data that was just placed into FIFO
        I2CMasterControl(I2C0_BASE, I2C_MASTER_CMD_BURST_SEND_FINISH);

        // Wait until MCU is done transferring.
        while(I2CMasterBusy(I2C0_BASE));
    }
}
/***********************************************************************
 * This function is used to receive 1 data on serial Data line
 ***********************************************************************/
uint32_t I2CReceive(uint32_t slave_addr, uint8_t reg)
{
    //specify that we are writing (a register address) to the
    //slave device
    I2CMasterSlaveAddrSet(I2C0_BASE, slave_addr, false);

    //specify register to be read
    I2CMasterDataPut(I2C0_BASE, reg);

    //send control byte and register address byte to slave device
    I2CMasterControl(I2C0_BASE, I2C_MASTER_CMD_BURST_SEND_START);

    //wait for MCU to finish transaction
    while(I2CMasterBusy(I2C0_BASE));

    //specify that we are going to read from slave device
    I2CMasterSlaveAddrSet(I2C0_BASE, slave_addr, true);

    //send control byte and read from the register we
    //specified
    I2CMasterControl(I2C0_BASE, I2C_MASTER_CMD_SINGLE_RECEIVE);

    //wait for MCU to finish transaction
    while(I2CMasterBusy(I2C0_BASE));

    //return data pulled from the specified register
    return I2CMasterDataGet(I2C0_BASE);
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
