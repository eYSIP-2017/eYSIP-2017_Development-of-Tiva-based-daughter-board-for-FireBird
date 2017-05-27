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
void timer0Enable();
void timerInterruptEnable();
void ADC0Enable();
unsigned int readADC();
void uartEnable();
void tranString(char * data,char delimeter);
void tranStringNonBlocking(char * data,char delimeter);
void uartInterruptEnable();
volatile uint32_t currentTemp,setTemp;
volatile uint8_t incomingFlag=0;
void UARTIntHandler(void);
int main(void) {
    configCLK();
    peripheralEnable();
    GPIOPinTypeGPIOOutput(PORTF,redLed|greenLed);
    ADC0Enable();
    timer0Enable();
    timerInterruptEnable();
    uartEnable();
    uartInterruptEnable();
    setTemp=30;
    while(1){
        currentTemp=readADC();
        if(currentTemp<setTemp)
            GPIOPinWrite(PORTF,greenLed|redLed,8);
        else
            GPIOPinWrite(PORTF,redLed|greenLed,2);
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
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOF);

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
//This function is to be included after enabling the interrupt
void uartInterruptEnable(){
    IntMasterEnable();//Enable processor interrupt
    IntEnable(INT_UART0);//Enable interrupt on UART0
    UARTIntEnable(UART0_BASE, UART_INT_RX | UART_INT_RT);//Enable RX interrupt ant rx Timeout interrupt
}
void UARTIntHandler(void)
{
uint32_t ui32Status;
ui32Status = UARTIntStatus(UART0_BASE, true); //get interrupt status
UARTIntClear(UART0_BASE, ui32Status); //clear the asserted interrupts
while(UARTCharsAvail(UART0_BASE)) //loop while there are chars
{
     char ch=UARTCharGet(UART0_BASE);
    if((ch=='s')){
        incomingFlag=1;
        tranString("Enter the temperature :",' ');
    }
    else if(incomingFlag==1){
        UARTCharPut(UART0_BASE, ch);
        setTemp=(ch-48)*10;
        incomingFlag++;

    }
    else if(incomingFlag==2){
        UARTCharPut(UART0_BASE, ch);
        UARTCharPut(UART0_BASE,'\n');
        setTemp+=(ch-48);
        incomingFlag=0;
        }
    //UARTCharPutNonBlocking(UART0_BASE, UARTCharGetNonBlocking(UART0_BASE));
}
}
void tranStringNonBlocking(char * data,char delimeter){
    int k=0;
    while(data[k]){
        UARTCharPutNonBlocking(UART0_BASE,data[k++]);
    }
    UARTCharPutNonBlocking(UART0_BASE,delimeter);
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
void Timer0IntHandler(void){
    // Clear the timer interrupt
    TimerIntClear(TIMER0_BASE, TIMER_TIMA_TIMEOUT);
    if(incomingFlag==0){tranString("Current Temperature",' ');
    UARTCharPut(UART0_BASE,48+(int)currentTemp/10);
    UARTCharPut(UART0_BASE,48+(int)currentTemp%10);
    tranString(" C,",' ');
    tranString("Set Temperature",' ');
    UARTCharPut(UART0_BASE,48+(int)setTemp/10);
    UARTCharPut(UART0_BASE,48+(int)setTemp%10);
    tranString(" C,",'\n');
    }
}
