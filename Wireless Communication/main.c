#include <stdint.h>
#include <stdbool.h>
#include <stdlib.h>
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
int main(){
    configCLK();
    peripheralEnable();
    uartEnable();
    while(1){
    UARTCharPut(UART1_BASE,'1');
    SysCtlDelay(400000);
    }
}
void configCLK(){
    SysCtlClockSet(SYSCTL_SYSDIV_5|SYSCTL_USE_PLL|SYSCTL_OSC_MAIN|SYSCTL_XTAL_16MHZ);
}
void peripheralEnable(){
    SysCtlPeripheralEnable(SYSCTL_PERIPH_UART1);
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOC);//Enablinig TIMER0
 }
void uartEnable(){
    GPIOPinConfigure(GPIO_PC4_U1RX);//Configure Pin A0 as RX of U0
    GPIOPinConfigure(GPIO_PC5_U1TX);//Configure Pin A1 as TX of U0
    GPIOPinTypeUART(GPIO_PORTC_BASE, GPIO_PIN_4 | GPIO_PIN_5);
    UARTConfigSetExpClk(UART1_BASE, SysCtlClockGet(), 9600,
        (UART_CONFIG_WLEN_8 | UART_CONFIG_STOP_ONE | UART_CONFIG_PAR_NONE));
}
void tranString(char * data,char delimeter){
    int k=0;
    while(data[k]){
        UARTCharPut(UART1_BASE,data[k++]);
    }
    UARTCharPut(UART1_BASE,delimeter);
}
