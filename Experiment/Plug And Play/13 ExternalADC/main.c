/*****************************************************************************************
 Written by: Ayush Gaurav And Nagesh K.
 From eRTS Lab, CSE Department, IIT Bombay.

 Date: 24th June 2017

 In this experiment demonstrate USB to Serial Communication.

 Concepts covered:  External ADC and I2C

UART Connection: I1C1.
I2C1SCL-------->SCL on external adc.
I2C1SDA-------->SDA on external adc.

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
#include "driverlib/uart.h"
void setupCLK();
void InitI2C1(void);
void peripheralEnable();
void I2CSendString(uint32_t slave_addr, char array[]);
void I2CSend(uint8_t slave_addr, uint8_t num_of_args, ...);
uint32_t I2CReceive(uint32_t slave_addr, uint8_t reg);
uint16_t read2Bytes(uint8_t slave_addr, uint8_t reg);
uint16_t readExternalADC(uint8_t channel);
void uartEnable();
void uartInterruptEnable();
void UARTIntHandler(void);
void tranString(char *,char);
void itoa(long long a,char *arr);
void uartInteger(long long int integer,char delimeter);
void setupExternalADC();
int main(void) {
    setupCLK();
    peripheralEnable();
    uartEnable();
    InitI2C1();
    setupExternalADC();
    while(1){
        uartInteger(readExternalADC(0),' ');
        SysCtlDelay((SysCtlClockGet())/3);
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
 * UART1 and PortB in this case
 ******************************/
void peripheralEnable(){
    SysCtlPeripheralEnable(SYSCTL_PERIPH_UART1);
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOB);
 }
/****************************************
 * This function is used to enable UART0
 * The baudrate is set at 9600
 ****************************************/
void uartEnable(){
    GPIOPinConfigure(GPIO_PB0_U1RX);
    GPIOPinConfigure(GPIO_PB1_U1TX);
    GPIOPinTypeUART(GPIO_PORTB_BASE, GPIO_PIN_0 | GPIO_PIN_1);
    UARTConfigSetExpClk(UART1_BASE, SysCtlClockGet(), 9600,
        (UART_CONFIG_WLEN_8 | UART_CONFIG_STOP_ONE | UART_CONFIG_PAR_NONE));
}

/**********************************************
 * This function converts an integer to string
 **********************************************/
void itoa(long long a,char *arr){
    int i=0,j=0;
    long long tmp=a;
    if(a<0){
            arr[i++]='-';
            tmp*=-1;
            j=1;
        }
    for(;tmp>0;i++){
        arr[i]=(tmp%10)+'0';
        tmp/=10;
    }
    arr[i--]='\0';
    for(;j<i;j++,i--){
            tmp=arr[i];
            arr[i]=arr[j];
            arr[j]=tmp;
    }
}

/*************************************
 * send through serial communication
 *************************************/
void uartInteger(long long int integer,char delimeter){
    char ch[20];
    itoa(integer,ch);
    tranString(ch,delimeter);
}
/***********************************************************************
 * This function is used to send a string of character with a delimiter
 ***********************************************************************/
void tranString(char * data,char delimeter){
    int k=0;
    while(data[k]){
        UARTCharPut(UART1_BASE,data[k++]);
    }
    UARTCharPut(UART1_BASE,delimeter);
}

/*********************************************************************************************
 * Setting up external ADC
 * Wait for 33ms
 * Read the Busy Status Register (address 0Ch). If the 'Not Ready' bit = 1,
 *  then increase the wait time until 'Not Ready' bit = 0 before proceeding to the next step.
 *  Program the Advanced Configuration Register — Address 0Bh:
 *  a. Choose to use the internal or external VREF (bit 0).
 *  b. Choose the mode of operation (bits [2:1]).
 * Program the Conversion Rate Register (address 07h).
 * Choose to enable or disable the channels using the Channel Disable Register (address 08h).
 * Using the Interrupt Mask Register (address 03h), choose to mask or not to mask the interrupt status from
    propagating to the interrupt output pin, INT.
 * Program the Limit Registers (addresses 2Ah – 39h).
 * Set the ‘START’ bit of the Configuration Register (address 00h, bit 0) to 1.
 * Set the 'INT_Clear' bit (address 00h, bit 3) to 0. If needed, program the 'INT_Enable' bit (address 00h, bit 1)
    to 1 to enable the INT output.
 *********************************************************************************************/
void setupExternalADC(){
    SysCtlDelay((5*SysCtlClockGet())/300);
    while(I2CReceive(0x1D,0x0C)&(0x01));
    I2CSend(0x1D,2,0x0B,0x03);
    I2CSend(0x1D,2,0x07,0x01);
    I2CSend(0x1D,2,0x08,0x00);
    I2CSend(0x1D,3,0x2A,0x05);
    I2CSend(0x1D,3,0x2B,0x00);
    I2CSend(0x1D,3,0x2C,0x05);
    I2CSend(0x1D,3,0x2D,0x00);
    I2CSend(0x1D,3,0x2E,0x05);
    I2CSend(0x1D,3,0x2F,0x00);
    I2CSend(0x1D,3,0x30,0x05);
    I2CSend(0x1D,3,0x31,0x00);
    I2CSend(0x1D,3,0x32,0x05);
    I2CSend(0x1D,3,0x33,0x00);
    I2CSend(0x1D,3,0x34,0x05);
    I2CSend(0x1D,3,0x35,0x00);
    I2CSend(0x1D,3,0x36,0x05);
    I2CSend(0x1D,3,0x37,0x00);
    I2CSend(0x1D,3,0x38,0x05);
    I2CSend(0x1D,3,0x39,0x00);
    I2CSend(0x1D,2,0x00,0x01);
}
/****************************************
 * Read ADC value from a mentioned channel
 ****************************************/
uint16_t readExternalADC(uint8_t channel){
    while(I2CReceive(0x1D,0x0C)&(0x02));
    return(read2Bytes(0x1D,(0x20+channel)));
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
   HWREG(I2C1_BASE + I2C_O_FIFOCTL) = 80008000;
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
    if(array[1] == '\0')
    {
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
    return I2CMasterDataGet(I2C1_BASE);//return data pulled from the specified register
}
/***********************************************************************
 * This function is used to receive 2 data on serial Data line
 ***********************************************************************/
uint16_t read2Bytes(uint8_t SLAVE_ADDRESS, uint8_t reg){
    I2CMasterSlaveAddrSet(I2C1_BASE, SLAVE_ADDRESS, false);
    I2CMasterDataPut(I2C1_BASE, reg);
    I2CMasterControl(I2C1_BASE, I2C_MASTER_CMD_BURST_SEND_START);
    while(!(I2CMasterBusy(I2C1_BASE))){};while(I2CMasterBusy(I2C1_BASE)){};
    I2CMasterSlaveAddrSet(I2C1_BASE, SLAVE_ADDRESS, true);
    I2CMasterControl(I2C1_BASE, I2C_MASTER_CMD_BURST_RECEIVE_START);
    while(!(I2CMasterBusy(I2C1_BASE))){};while(I2CMasterBusy(I2C1_BASE)){};
    uint8_t data=I2CMasterDataGet (I2C1_BASE);
    I2CMasterControl(I2C1_BASE, I2C_MASTER_CMD_BURST_RECEIVE_FINISH);
    while(!(I2CMasterBusy(I2C1_BASE))){};
    while(I2CMasterBusy(I2C1_BASE)){};
    uint8_t dummy=I2CMasterDataGet (I2C1_BASE);
    return ((((data<<8)+dummy))>>4);
}
