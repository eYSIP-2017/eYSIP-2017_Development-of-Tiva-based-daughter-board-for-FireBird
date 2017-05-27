#include <stdint.h>
#include <stdbool.h>
#include <stdlib.h>
#include "inc/hw_memmap.h"
#include "inc/hw_types.h"
#include "driverlib/gpio.h"
#include "driverlib/pin_map.h"
#include "driverlib/sysctl.h"
#include "driverlib/uart.h"
#include "driverlib/debug.h"
#include "driverlib/adc.h"
#include "driverlib/interrupt.h"
#include "driverlib/gpio.h"
#include "driverlib/timer.h"
#include "inc/tm4c123gh6pm.h"
#include "driverlib/debug.h"
#include "driverlib/sysctl.h"
#include "driverlib/adc.h"
#define PORTF       GPIO_PORTF_BASE
#define userSwitch2 GPIO_PIN_0
#define redLed      GPIO_PIN_1
#define blueLed     GPIO_PIN_2
#define greenLed    GPIO_PIN_3
#define userSwitch1 GPIO_PIN_4void configCLK();
void configCLK();
void peripheralEnable();
void ADC0Enable();
void timer0Enable();
void timerInterruptEnable();
unsigned int readADC();
void uartEnable();
void tranString(char * data,char delimeter);
void uartInteger(long long int integer,char delimeter);
void Timer0IntHandler(void);
volatile uint32_t tempValueC;
int main(void) {
	configCLK();
	peripheralEnable();
    ADC0Enable();
    timer0Enable();
    timerInterruptEnable();
    uartEnable();
    while(1){
        tempValueC=readADC();
    }
}
void configCLK(){
    SysCtlClockSet(SYSCTL_SYSDIV_5|SYSCTL_USE_PLL|SYSCTL_OSC_MAIN|SYSCTL_XTAL_16MHZ);
}
void peripheralEnable(){
    //Enables ADC0 and hardware divide by 64
    SysCtlPeripheralEnable(SYSCTL_PERIPH_ADC0);
    ADCHardwareOversampleConfigure(ADC0_BASE, 64);
    //Enable UART0 on pin A0 and A1
    SysCtlPeripheralEnable(SYSCTL_PERIPH_UART0);
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOA);
    SysCtlPeripheralEnable(SYSCTL_PERIPH_TIMER0);//Enablinig TIMER0
 }
void ADC0Enable(){
    ADCSequenceConfigure(ADC0_BASE, 1, ADC_TRIGGER_PROCESSOR, 0);
    ADCSequenceStepConfigure(ADC0_BASE, 1, 0, ADC_CTL_TS);
    ADCSequenceStepConfigure(ADC0_BASE, 1, 1, ADC_CTL_TS);
    ADCSequenceStepConfigure(ADC0_BASE, 1, 2, ADC_CTL_TS);
    ADCSequenceStepConfigure(ADC0_BASE,1,3,ADC_CTL_TS|ADC_CTL_IE|ADC_CTL_END);
    ADCSequenceEnable(ADC0_BASE, 1);
}
unsigned int readADC(){
    unsigned int tempAvg;
    uint32_t ADC0Value[4];
    ADCIntClear(ADC0_BASE, 1);
    ADCProcessorTrigger(ADC0_BASE, 1);
    while(!ADCIntStatus(ADC0_BASE, 1, false));
    ADCSequenceDataGet(ADC0_BASE, 1, ADC0Value);
    tempAvg = (ADC0Value[0] + ADC0Value[1] + ADC0Value[2] + ADC0Value[3] + 2)/4;
    return((1475 - ((2475 * tempAvg)) / 4096)/10);
}
void timer0Enable(){
    TimerConfigure(TIMER0_BASE, TIMER_CFG_PERIODIC);
    unsigned int clockCount= SysCtlClockGet();//Count the number of clock to get 10 HZ
    TimerLoadSet(TIMER0_BASE, TIMER_A,clockCount -1);// Load The clockCount Into TimerA
    TimerEnable(TIMER0_BASE, TIMER_A);
}
void timerInterruptEnable(){
    IntEnable(INT_TIMER0A);
    TimerIntEnable(TIMER0_BASE, TIMER_TIMA_TIMEOUT);
    IntMasterEnable();// Same as sei() of avr, necessary to enable interrupt of any type
}
void uartEnable(){
    GPIOPinConfigure(GPIO_PA0_U0RX);//Configure Pin A0 as RX of U0
    GPIOPinConfigure(GPIO_PA1_U0TX);//Configure Pin A1 as TX of U0
    GPIOPinTypeUART(GPIO_PORTA_BASE, GPIO_PIN_0 | GPIO_PIN_1);
    UARTConfigSetExpClk(UART0_BASE, SysCtlClockGet(), 115200,
        (UART_CONFIG_WLEN_8 | UART_CONFIG_STOP_ONE | UART_CONFIG_PAR_NONE));
}
void tranString(char * data,char delimeter){
    int k=0;
    while(data[k]){
        UARTCharPut(UART0_BASE,data[k++]);
    }
    UARTCharPut(UART0_BASE,delimeter);
}
void Timer0IntHandler(void){
    // Clear the timer interrupt
    TimerIntClear(TIMER0_BASE, TIMER_TIMA_TIMEOUT);
    tranString("Current Temperature",' ');
    UARTCharPut(UART0_BASE,48+(int)tempValueC/10);
    UARTCharPut(UART0_BASE,48+(int)tempValueC%10);
    tranString(" C",'\n');
}
