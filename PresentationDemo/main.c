#include <stdint.h>
#include <stdbool.h>
#include "inc/hw_types.h"
#include "inc/hw_memmap.h"
//This header File is important to Unlock GPIO Pins
#include "inc/hw_gpio.h"
#include "driverlib/sysctl.h"
#include "driverlib/gpio.h"
#include "inc/tm4c123gh6pm.h"
#include "driverlib/gpio.h"
#include "driverlib/debug.h"
#include "driverlib/pwm.h"
#include "driverlib/pin_map.h"
#include "driverlib/rom.h"
#include "driverlib/interrupt.h"
#include "driverlib/timer.h"
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
#define motorPort           GPIO_PORTB_BASE
#define leftMotor1          GPIO_PIN_0
#define leftMotor2          GPIO_PIN_1
#define leftMotorPWM        GPIO_PIN_4
#define rightMotor1         GPIO_PIN_2
#define rightMotor2         GPIO_PIN_3
#define rightMotorPWM       GPIO_PIN_5
#define right               0x0A
#define left                0x05
#define forward             0x06
#define backward            0x09
#define stop                0x00
#define PWMFrequency        125 //5000 counts
#define PWMresolution       20
#define PWMRightMotorOn()   PWMOutputState(PWM0_BASE, PWM_OUT_3_BIT, true)
#define PWMLeftMotorOn()    PWMOutputState(PWM0_BASE, PWM_OUT_2_BIT, true)
#define PWMRightMotorOff()  PWMOutputState(PWM0_BASE, PWM_OUT_3_BIT, false)
#define PWMLeftMotorOff()   PWMOutputState(PWM0_BASE, PWM_OUT_2_BIT, false)
/***********************************/
void setupCLK();
void peripheralEnable();
void configIOPin();
void delay_ms(uint64_t delay);
void delay_ms(uint64_t delay);
void motion(uint8_t);
void enablePWM();
void timer0Enable();
void timerInterruptEnable();
void uartEnable();
void tranString(char * data,char delimeter);
void speed(uint8_t lSpeed,uint8_t rSpeed);
void ADC0Enable();
unsigned int readADC();
void itoa(long long a,char *arr);
void uartInteger(long long int);
volatile char indicator=0,flag=0;
volatile uint16_t reading;
int main(void) {
    setupCLK();
    peripheralEnable();
    configIOPin();
    enablePWM();
    timer0Enable();
    timerInterruptEnable();
    ADC0Enable();
    uartEnable();
    delay_ms(1000);
    motion(forward);
    tranString("Front Proximity Sensor Reading:",' ');
    uartInteger(readADC());
    tranString("Forward",'\n');
    int i=0;
    while(1){
        for(i=0;i<252;i=i+50){
            speed(i,i);
            delay_ms(800);
            //SysCtlDelay(13333333);
        }
        buzzerOn();
        while(!flag);
        buzzerOff();
        indicator=(indicator+1)%4;
        tranString("Front Proximity Sensor Reading:",' ');
        switch(indicator){
        case 1: motion(right);
            uartInteger(readADC());
            tranString("Right",'\n');
            break;
        case 2: motion(backward);
            uartInteger(readADC());
            tranString("Backward",'\n');
            break;
        case 3: motion(left);
            uartInteger(readADC());
            tranString("Left",'\n');
            break;
        default: motion(forward);
            uartInteger(readADC());
            tranString("Forward",'\n');
            break;
        }
        flag=0;
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
    SysCtlPWMClockSet(SYSCTL_PWMDIV_64);//625kHz PWM Clock

}
/*******************************
 * Enabling System Peripherals
 * PORTF in this case
 * PF1 for buzzer output
 ******************************/
void peripheralEnable(){
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOF);
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOB);
    SysCtlPeripheralEnable(SYSCTL_PERIPH_PWM0);//Enabling PWM0
    SysCtlPeripheralEnable(SYSCTL_PERIPH_UART0);
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOA);
    SysCtlPeripheralEnable(SYSCTL_PERIPH_TIMER0);//Enablinig TIMER0
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOE);
    SysCtlPeripheralEnable(SYSCTL_PERIPH_ADC0);
    ADCHardwareOversampleConfigure(ADC0_BASE, 64);
}
/*************************************
 * Configuring Pin as Input Or Output
 *************************************/
void configIOPin(){
    GPIOPinTypeGPIOOutput(GPIO_PORTF_BASE, buzzerPin);
    GPIOPinTypeGPIOOutput(motorPort,rightMotor1|rightMotor2|leftMotor1|leftMotor2);
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
void motion(uint8_t direction){
    GPIOPinWrite(motorPort,rightMotor1|rightMotor2|leftMotor1|leftMotor2,direction);
}
void enablePWM(){
    GPIOPinTypePWM(motorPort, leftMotorPWM);
    GPIOPinConfigure(GPIO_PB4_M0PWM2);
    GPIOPinTypePWM(motorPort, rightMotorPWM);
    GPIOPinConfigure(GPIO_PB5_M0PWM3);
    PWMGenConfigure(PWM0_BASE, PWM_GEN_1, PWM_GEN_MODE_DOWN);//Count Down Mode
    PWMGenPeriodSet(PWM0_BASE, PWM_GEN_1,4999); //Load Count value
    PWMRightMotorOn();
    PWMLeftMotorOn();
    PWMGenEnable(PWM0_BASE, PWM_GEN_1);
}
void speed(uint8_t lSpeed,uint8_t rSpeed){
        lSpeed=(lSpeed>249)?249:lSpeed;
        rSpeed=(rSpeed>249)?249:rSpeed;
        PWMPulseWidthSet(PWM0_BASE, PWM_OUT_2,(lSpeed*PWMresolution)+1);
        PWMPulseWidthSet(PWM0_BASE, PWM_OUT_3,(rSpeed*PWMresolution)+1);
}
void uartEnable(){
    GPIOPinConfigure(GPIO_PA0_U0RX);//Configure Pin A0 as RX of U0
    GPIOPinConfigure(GPIO_PA1_U0TX);//Configure Pin A1 as TX of U0
    GPIOPinTypeUART(GPIO_PORTA_BASE, GPIO_PIN_0 | GPIO_PIN_1);
    UARTConfigSetExpClk(UART0_BASE, SysCtlClockGet(), 9600,
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
void timer0Enable(){
    TimerConfigure(TIMER0_BASE, TIMER_CFG_PERIODIC);
    unsigned int clockCount= SysCtlClockGet()*5;//Count the number of clock to get 10 HZ
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
    flag=1;
}
void ADC0Enable(){
    ADCSequenceConfigure(ADC0_BASE, 1, ADC_TRIGGER_PROCESSOR, 0);
    ADCSequenceStepConfigure(ADC0_BASE, 1, 0, ADC_CTL_CH0);
    ADCSequenceStepConfigure(ADC0_BASE, 1, 1, ADC_CTL_CH0);
    ADCSequenceStepConfigure(ADC0_BASE, 1, 2, ADC_CTL_CH0);
    ADCSequenceStepConfigure(ADC0_BASE,1,3,ADC_CTL_CH0|ADC_CTL_IE|ADC_CTL_END);
    ADCSequenceEnable(ADC0_BASE, 1);
    GPIOPinTypeADC(GPIO_PORTE_BASE, GPIO_PIN_3);

}
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
void uartInteger(long long int integer){
    char ch[20];
    itoa(integer,ch);
    tranString(ch,' ');
}
void itoa(long long a,char *arr)
{
    int i=0,j=0;
    long long tmp=a;
    if(a<0)
        {
            arr[i++]='-';
            tmp*=-1;
            j=1;
        }
    for(;tmp>0;i++)
    {
        arr[i]=(tmp%10)+'0';
        tmp/=10;
    }
    arr[i--]='\0';
    for(;j<i;j++,i--)
    {
            tmp=arr[i];
            arr[i]=arr[j];
            arr[j]=tmp;
    }
}

