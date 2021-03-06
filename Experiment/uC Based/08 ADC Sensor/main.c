/*****************************************************************************************
 Written by: Ayush Gaurav And Nagesh K.
 From eRTS Lab, CSE Department, IIT Bombay.

 Date: 16th June 2017

 In this experiment ADC captures the analog sensor values and displays it on the screen using UART

 Concepts covered:  ADC, UART interfacing

ADC Connection for uC based Board:
          CH       PORT    Sensor
           5       PD2     White line sensor 3
           6       PD1     White line sensor 2
           7       PD0     White line sensor 1
           2       PE1     IR Proximity analog sensor 1
           0       PE3     IR Proximity analog sensor 2
           8       PE5     IR Proximity analog sensor 3
           9       PE4     IR Proximity analog sensor 4
          11       PB5     IR Proximity analog sensor 5
           3       PE0     Sharp IR range sensor 1
           1       PE2     Sharp IR range sensor 2
           4       PD3     Sharp IR range sensor 3
          10       PB4     Sharp IR range sensor 5

Refer the Channel numbers mentioned to interface other sensors
Also change Port in ADCtype function in ADC0Enable()

 Note: Make sure that in the configuration options following settings are
 done for proper operation of the code.
*****************************************************************************************/
#include <stdint.h>
#include <stdbool.h>
#include "stdlib.h"
#include "inc/hw_ints.h"
#include "inc/hw_memmap.h"
#include "inc/hw_uart.h"
#include "inc/hw_gpio.h"
#include "inc/hw_pwm.h"
#include "inc/hw_types.h"
#include "driverlib/adc.h"
#include "driverlib/timer.h"
#include "driverlib/gpio.h"
#include "driverlib/interrupt.h"
#include "driverlib/pin_map.h"
#include "driverlib/rom.h"
#include "driverlib/rom_map.h"
#include "driverlib/sysctl.h"
#include "driverlib/uart.h"
#include "driverlib/udma.h"
#include "driverlib/pwm.h"
#include "driverlib/ssi.h"
#include "driverlib/systick.h"
#include "driverlib/adc.h"
#include "utils/uartstdio.h"
#include "utils/uartstdio.c"
#include <string.h>
#include <math.h>

void configCLK();
void peripheralEnable();
void uartEnable();
unsigned int Sharp_GP2D12_estimation(uint16_t adc_reading);
void ADC0Enable();
unsigned int readADC();
void tranString(char * data,char delimeter);
void uartInteger(long long int integer,char delimeter);
void _delay_ms(uint64_t delay);
void itoa(long long a,char *arr);

int main(){
    configCLK();
    peripheralEnable();
    ADC0Enable();
    uartEnable();

    while(1){
        uartInteger(Sharp_GP2D12_estimation(readADC()),' ');
        _delay_ms(1000);
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
 * PortB and PortD in this case
 ******************************/
void peripheralEnable(){
    SysCtlPeripheralEnable(SYSCTL_PERIPH_UART1);
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOC);
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOD);
    SysCtlPeripheralEnable(SYSCTL_PERIPH_ADC0);
    ADCHardwareOversampleConfigure(ADC0_BASE, 64);
 }
/****************************************
 * This function is used to enable UART1
 * The baudrate is set at 9600
 ****************************************/
void uartEnable(){

    GPIOPinConfigure(GPIO_PC4_U1RX);    //Configure Pin C4 as RX of U0
    GPIOPinConfigure(GPIO_PC5_U1TX);    //Configure Pin C5 as TX of U0
    GPIOPinTypeUART(GPIO_PORTC_BASE, GPIO_PIN_5 | GPIO_PIN_4);
    UARTConfigSetExpClk(UART1_BASE, SysCtlClockGet(), 9600,(UART_CONFIG_WLEN_8 | UART_CONFIG_STOP_ONE | UART_CONFIG_PAR_NONE));
}
/********************************************************
 * This function is used to enable ADC0
 * 4 step sequencer is used
 * Change the channel number to use any of the other ADCs
 ********************************************************/
void ADC0Enable(){
    ADCSequenceConfigure(ADC0_BASE, 1, ADC_TRIGGER_PROCESSOR, 0);
    ADCSequenceStepConfigure(ADC0_BASE, 1, 0, ADC_CTL_CH4);
    ADCSequenceStepConfigure(ADC0_BASE, 1, 1, ADC_CTL_CH4);
    ADCSequenceStepConfigure(ADC0_BASE, 1, 2, ADC_CTL_CH4);
    ADCSequenceStepConfigure(ADC0_BASE,1,3,ADC_CTL_CH4|ADC_CTL_IE|ADC_CTL_END);
    ADCSequenceEnable(ADC0_BASE, 1);
    GPIOPinTypeADC(GPIO_PORTD_BASE, GPIO_PIN_3);
}
/*************************************************************
 * This function is used to read the value from ADC
 * Average of 4 values is returned to the calling function
 ************************************************************/
unsigned int readADC(){
    unsigned int Avg;
    uint32_t ADC0Value[4];
    ADCIntClear(ADC0_BASE, 1);
    ADCProcessorTrigger(ADC0_BASE, 1);
    while(!ADCIntStatus(ADC0_BASE, 1, false));
    ADCSequenceDataGet(ADC0_BASE, 1, ADC0Value);
    Avg = (ADC0Value[0] + ADC0Value[1] + ADC0Value[2] + ADC0Value[3] + 2)/4;
    return(Avg);
}
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
 * Calculating Delays
 *************************************/
void _delay_ms(uint64_t delay){
    SysCtlDelay(delay*(SysCtlClockGet()/3000));
}
/*************************************************************
 * This function is used send integers through UART
 ************************************************************/
void uartInteger(long long int integer,char delimeter){
    char ch[20];
    itoa(integer,ch);
    tranString(ch,delimeter);
}
/*************************************************************
 * This function is used to send string through UART
 ************************************************************/
void tranString(char *data,char delimeter){
    int k=0;
    while(data[k]){
        UARTCharPut(UART1_BASE,data[k++]);
    }
    UARTCharPut(UART1_BASE,delimeter);
}
/*********************************************************************
 * This function is used to estimate the distance of the obstacle
 * The linearization is based on "Piecewise Linear Approximation"
 ********************************************************************/
unsigned int Sharp_GP2D12_estimation(uint16_t adc_reading){
    float distance;
    unsigned int distanceInt;
    adc_reading = adc_reading >> 2;
    distance = (6787/(adc_reading-3)-4)*0.725;
    distanceInt = (int)distance;
    if(distanceInt>80)
    {
        distanceInt=80;
    }
    return distanceInt;
}
