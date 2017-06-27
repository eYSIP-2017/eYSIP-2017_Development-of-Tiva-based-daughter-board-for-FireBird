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
void configCLK(){
    SysCtlClockSet(SYSCTL_SYSDIV_5|SYSCTL_USE_PLL|SYSCTL_OSC_MAIN|SYSCTL_XTAL_16MHZ);
}
void peripheralEnable(){
    SysCtlPeripheralEnable(SYSCTL_PERIPH_UART3);
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOC);//Enablinig TIMER0
 }
void uartEnable(){
    GPIOPinConfigure(GPIO_PC6_U3RX);//Configure Pin PC6 as RX of U0
    GPIOPinConfigure(GPIO_PC7_U3TX);//Configure Pin PC7 as TX of U0
    GPIOPinTypeUART(GPIO_PORTC_BASE, GPIO_PIN_6 | GPIO_PIN_7);
    UARTConfigSetExpClk(UART3_BASE, SysCtlClockGet(), 9600,
        (UART_CONFIG_WLEN_8 | UART_CONFIG_STOP_ONE | UART_CONFIG_PAR_NONE));
}
void tranString(char * data,char delimeter){
    int k=0;
    while(data[k]){
        UARTCharPut(UART3_BASE,data[k++]);
    }
    UARTCharPut(UART3_BASE,delimeter);
}
void uartInterruptEnable(){
    IntMasterEnable();//Enable processor interrupt
    IntEnable(INT_UART3);//Enable interrupt on UART0
    UARTIntEnable(UART3_BASE, UART_INT_RX | UART_INT_RT);//Enable RX interrupt ant rx Timeout interrupt
}
void UARTIntHandler(void){
    uint32_t ui32Status;
    ui32Status = UARTIntStatus(UART3_BASE, true); //get interrupt status
    UARTIntClear(UART3_BASE, ui32Status); //clear the asserted interrupts
    while(UARTCharsAvail(UART3_BASE)){ //loop while there are chars
        UARTCharPut(UART3_BASE, UARTCharGet(UART3_BASE));
    }
}
