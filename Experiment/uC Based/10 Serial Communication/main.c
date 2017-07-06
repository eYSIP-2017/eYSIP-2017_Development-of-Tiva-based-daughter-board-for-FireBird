/*****************************************************************************************
 Written by: Ayush Gaurav And Nagesh K.
 From ERTS Lab, CSE Department, IIT Bombay.

 Date: 24th June 2017

 In this experiment demonstrate Wireless Serial Communication.

 Concepts covered:  UART and its Interrupt

UART Connection: UART1 RX and TX.
U1RX is connected to TX of FT232.
U1TX is connected to RX of FT232.

 Note: Make sure that in the configuration options following settings are
 done for proper operation of the code.
*****************************************************************************************/
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include<math.h>
#include "inc/hw_memmap.h"
#include "inc/hw_types.h"
#include "driverlib/pin_map.h"
#include "driverlib/sysctl.h"
#include "driverlib/uart.h"
#include "driverlib/debug.h"
#include "driverlib/interrupt.h"
#include "driverlib/gpio.h"
#include "inc/tm4c123gh6pm.h"
void configCLK();
void peripheralEnable();
void uartEnable();
void uartInterruptEnable();
void UARTIntHandler(void);
void tranString(char *,char);
void uartInteger(int64_t number);
int main(){
    configCLK();
    peripheralEnable();
    uartEnable();
    uartInterruptEnable();
    while(1){
    }
}
/***************************************************************************************
 * This function is used to setup Clock frequency of the controller
 * It can be changed through codes
 * In this we have set frequency as 40Mhz
 * Frequency is set by SYSDIV which can be found in data sheet for different frequencies
 ***************************************************************************************/
void configCLK(){
    SysCtlClockSet(SYSCTL_SYSDIV_5|SYSCTL_USE_PLL|SYSCTL_OSC_MAIN|SYSCTL_XTAL_16MHZ);
}
/*******************************
 * Enabling System Peripherals
 * UART1 and PortC in this case
 ******************************/
void peripheralEnable(){
    SysCtlPeripheralEnable(SYSCTL_PERIPH_UART1);
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOC);//Enablinig TIMER0
 }
/****************************************
 * This function is used to enable UART1
 * The baudrate is set at 9600
 ****************************************/
void uartEnable(){
    GPIOPinConfigure(GPIO_PC4_U1RX);//Configure Pin A0 as RX of U0
    GPIOPinConfigure(GPIO_PC5_U1TX);//Configure Pin A1 as TX of U0
    GPIOPinTypeUART(GPIO_PORTC_BASE, GPIO_PIN_4 | GPIO_PIN_5);
    UARTConfigSetExpClk(UART1_BASE, SysCtlClockGet(), 9600,
        (UART_CONFIG_WLEN_8 | UART_CONFIG_STOP_ONE | UART_CONFIG_PAR_NONE));
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
/********************************************************************
 * This function is used to enable UART1 Rx And Rx timeout Interrupt
 *******************************************************************/
void uartInterruptEnable(){
    IntMasterEnable();//Enable processor interrupt
    IntEnable(INT_UART1);//Enable interrupt on UART0
    UARTIntEnable(UART1_BASE, UART_INT_RX | UART_INT_RT);//Enable RX interrupt ant rx Timeout interrupt
}
/****************************************
 * Interrupt sub routine for Uart0
 * Change the name of ISR in startup file
 * Refer to manual for proper instruction
 ****************************************/
void UARTIntHandler(void){
    uint32_t ui32Status;
    ui32Status = UARTIntStatus(UART1_BASE, true); //get interrupt status
    UARTIntClear(UART1_BASE, ui32Status); //clear the asserted interrupts
    while(UARTCharsAvail(UART1_BASE)){ //loop while there are chars
        UARTCharPut(UART1_BASE, UARTCharGet(UART1_BASE));
    }
}
