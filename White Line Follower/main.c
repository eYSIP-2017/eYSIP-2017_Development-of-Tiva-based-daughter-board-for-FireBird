/****************************************************************************************************
Written by: Ayush Gaurav And Nagesh K.
From eRTS Lab, CSE Department, IIT Bombay.

ADC Connection:
          CH       PORT    Sensor
           2       PE1     White line sensor 3
           1       PE2     White line sensor 2
           0       PE3     White line sensor 1
          11       PB5     IR Proximity analog sensor 1
           7       PD5     IR Proximity analog sensor 2
           4       PD3     IR Proximity analog sensor 3
           6       PD1     IR Proximity analog sensor 4
           8       PE5     IR Proximity analog sensor 5
           3       PE0     IR Proximity analog sensor 7
          10       PB4     Sharp IR range sensor 1
           5       PD2     Sharp IR range sensor 3
           9       PE4     Sharp IR range sensor 5
LCD Connection:
             LCD      Board Pins
              RS  --> PD6
              RW  --> GND
              EN  --> PD7
              DB7 --> PA5
              DB6 --> PA4
              DB5 --> PA3
              DB4 --> PA2
Motor Connection:
                L-1---->PF3;        L-2---->PB3;
                R-1---->PC4;        R-2---->PC6;
                PF2----> PWM L     PC5----> PWM R;

****************************************************************************************************/
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
#include<stdlib.h>

#ifndef     lcdPORT
#define     lcdPORT     GPIO_PORTD_BASE
#endif
#ifndef     lcdDDR
#define     lcdDDR      GPIO_PORTA_BASE
#endif
#ifndef     lcdPIN
#define     lcdPIN      PINC
#endif
#ifndef     RS
#define     RS          GPIO_PIN_6
#endif
#ifndef     EN
#define     EN          GPIO_PIN_7
#endif
#ifndef     D4
#define     D4          GPIO_PIN_2
#endif
#ifndef     D5
#define     D5          GPIO_PIN_3
#endif
#ifndef     D6
#define     D6          GPIO_PIN_4
#endif
#ifndef     D7
#define     D7          GPIO_PIN_5
#endif

#define right           0x41
#define left            0x18
#define softRight       0x10
#define softLeft        0x01
#define forward         0x11
#define backward        0x48
#define stop            0x00

void configCLK();
void peripheralEnable();
void ADC0Enable();
void ADC1Enable();
void ADC2Enable();
unsigned int readADC();
void itoa(long long a,char *arr);
void lcdInit();
void lcdCommand(unsigned char);
void lcdData(unsigned char);
void lcdString(char*);
void lcdGotoxy(unsigned char,unsigned char);
void lcdClear();
void lcdCheck();
void configIOPin();
void _delay_ms(uint64_t delay);
void _delay_us(uint64_t delay);
void motion(uint8_t);
void enablePWM();
void Velocity(uint8_t lSpeed,uint8_t rSpeed);

unsigned char cursorPositionCheck=0;
char WL1, WL2, WL3;
char ch1[20], ch2[20], ch3[20];
char delimeter;
int main(){
    configCLK();
    peripheralEnable();
    configIOPin();
    enablePWM();
    lcdInit();
    lcdClear();

    while(1){
        ADC0Enable();
        WL1 = readADC();
        lcdGotoxy(15,0);
        lcdData(WL1);

        ADC1Enable();
        WL2 = readADC();
        lcdGotoxy(8,0);
        lcdData(WL2);

        ADC2Enable();
        WL3 = readADC();
        lcdGotoxy(0,0);
        lcdData(WL3);

        lcdGotoxy(0,1);

        if (WL3 == '1' && WL2 == '1' && WL1 == '0'){
            //right
            lcdString("Right");
            Velocity(50,50);
            motion(softRight);
            //Velocity(130,50);
        }
        else if (WL3 == '0' && WL2 == '1' && WL1 == '1'){
            //left
            lcdString("Left");
            Velocity(50,50);
            motion(softLeft);
            //Velocity(50,130);
        }
        else{
            //forward
            lcdString("Forward");
            Velocity(100,100);
            motion(forward);

        }
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
    SysCtlPeripheralEnable(SYSCTL_PERIPH_UART0);
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOA);
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOE);
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOD);
    SysCtlPeripheralEnable(SYSCTL_PERIPH_ADC0);
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOB);
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOF);
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOC);
    SysCtlPeripheralEnable(SYSCTL_PERIPH_PWM0); // Enabling PWM0
    SysCtlPeripheralEnable(SYSCTL_PERIPH_PWM1); // Enabling PWM1
    ADCHardwareOversampleConfigure(ADC0_BASE, 64);
 }
/*************************************
 * Configuring LCD Pins as Output
 *************************************/
void configIOPin(){
    HWREG(GPIO_PORTD_BASE + GPIO_O_LOCK) = GPIO_LOCK_KEY;
    HWREG(GPIO_PORTD_BASE + GPIO_O_CR) |= (1<<7);
    HWREG(GPIO_PORTD_BASE + GPIO_O_LOCK) = 0;
    GPIOPinTypeGPIOOutput(GPIO_PORTD_BASE,EN|RS);
    GPIOPinTypeGPIOOutput(GPIO_PORTA_BASE,D4|D5|D6|D7);
    GPIOPinTypeGPIOOutput(GPIO_PORTB_BASE,GPIO_PIN_3);
    GPIOPinTypeGPIOOutput(GPIO_PORTC_BASE,GPIO_PIN_4|GPIO_PIN_5|GPIO_PIN_6);
    GPIOPinTypeGPIOOutput(GPIO_PORTF_BASE,GPIO_PIN_3|GPIO_PIN_2);
}
/********************************************************
 * This function is used to enable ADC0
 * 4 step sequencer is used
 * Change the channel number to use any of the other ADCs
 ********************************************************/
void ADC0Enable(){
    ADCSequenceConfigure(ADC0_BASE, 1, ADC_TRIGGER_PROCESSOR, 0);
    ADCSequenceStepConfigure(ADC0_BASE, 1, 0, ADC_CTL_CH0);
    ADCSequenceStepConfigure(ADC0_BASE, 1, 1, ADC_CTL_CH0);
    ADCSequenceStepConfigure(ADC0_BASE, 1, 2, ADC_CTL_CH0);
    ADCSequenceStepConfigure(ADC0_BASE,1,3,ADC_CTL_CH0|ADC_CTL_IE|ADC_CTL_END);
    ADCSequenceEnable(ADC0_BASE, 1);
    GPIOPinTypeADC(GPIO_PORTE_BASE, GPIO_PIN_3);
}
void ADC1Enable(){
    ADCSequenceConfigure(ADC0_BASE, 1, ADC_TRIGGER_PROCESSOR, 0);
    ADCSequenceStepConfigure(ADC0_BASE, 1, 0, ADC_CTL_CH1);
    ADCSequenceStepConfigure(ADC0_BASE, 1, 1, ADC_CTL_CH1);
    ADCSequenceStepConfigure(ADC0_BASE, 1, 2, ADC_CTL_CH1);
    ADCSequenceStepConfigure(ADC0_BASE,1,3,ADC_CTL_CH1|ADC_CTL_IE|ADC_CTL_END);
    ADCSequenceEnable(ADC0_BASE, 1);
    GPIOPinTypeADC(GPIO_PORTE_BASE, GPIO_PIN_2);
}
void ADC2Enable(){
    ADCSequenceConfigure(ADC0_BASE, 1, ADC_TRIGGER_PROCESSOR, 0);
    ADCSequenceStepConfigure(ADC0_BASE, 1, 0, ADC_CTL_CH2);
    ADCSequenceStepConfigure(ADC0_BASE, 1, 1, ADC_CTL_CH2);
    ADCSequenceStepConfigure(ADC0_BASE, 1, 2, ADC_CTL_CH2);
    ADCSequenceStepConfigure(ADC0_BASE,1,3,ADC_CTL_CH2|ADC_CTL_IE|ADC_CTL_END);
    ADCSequenceEnable(ADC0_BASE, 1);
    GPIOPinTypeADC(GPIO_PORTE_BASE, GPIO_PIN_1);
}
/*************************************************************
 * This function is used to read the value from ADC
 * Average of 4 values is returned to the calling function
 ************************************************************/
unsigned int readADC(){
    unsigned int Avg;
    char val;
    uint32_t ADC0Value[4];
    ADCIntClear(ADC0_BASE, 1);
    ADCProcessorTrigger(ADC0_BASE, 1);
    while(!ADCIntStatus(ADC0_BASE, 1, false));
    ADCSequenceDataGet(ADC0_BASE, 1, ADC0Value);
    Avg = (ADC0Value[0] + ADC0Value[1] + ADC0Value[2] + ADC0Value[3] + 2)/4;
    if(Avg<300)
        val = '1';
    else
        val = '0';
    return(val);
}
/*************************************************************
 * This function is used to convert from integer to ASCII
 ************************************************************/
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
/******************************************
 * This function is used to initialize LCD
 * The LCD is operated in 4 bit mode
 * It is also set in auto increment mode
 *****************************************/
void lcdInit(){
    lcdCommand(0x28);
    /**************************
    0x30 8bit mode single line*
    0x38 8bit mode double line*
    0x20 4bit mode single line*
    0x28 4bit mode double line*
    ***************************/
    lcdCommand(0x06); //entry mode and auto increment mode
    lcdCommand(0x0F);
    /********************************
    Display off Cursor off      0x08*
    Display on Cursor on        0x0E*
    Display on Cursor off       0x0C*
    Display on Cursor blinking  0x0F*
    *********************************/
}
/***************************************************************************************
 * This function is used to send commands to LCD
 * The first 4 bits are sent first and then the last 4 bits
 * The bits are shifted left and right appropriately to fit in middle 4 bits of port A
 ***************************************************************************************/
void lcdCommand(unsigned char command){
    GPIOPinWrite(lcdPORT,RS|EN,0);
    GPIOPinWrite(lcdDDR,D4|D5|D6|D7,0);
    _delay_us(100);
    GPIOPinWrite(lcdDDR,D4|D5|D6|D7,(command>>2));
    _delay_ms(1);
    GPIOPinWrite(lcdPORT,EN|RS,0x80);
    _delay_us(100);
    GPIOPinWrite(lcdPORT,EN,0);
    _delay_us(100);
    GPIOPinWrite(lcdDDR,D4|D5|D6|D7,(command<<2));
    _delay_ms(1);
    GPIOPinWrite(lcdPORT,EN|RS,0x80);
    _delay_us(100);
    GPIOPinWrite(lcdPORT,EN,0);
    _delay_us(100);
}
/***************************************************************************************
 * This function is used to send data to LCD
 * The first 4 bits are sent first and then the last 4 bits
 * The bits are shifted left and right appropriately to fit in middle 4 bits of port A
 ***************************************************************************************/
void lcdData(unsigned char data){
    lcdCheck();
    GPIOPinWrite(lcdPORT,RS|EN,0);
    GPIOPinWrite(lcdDDR,D4|D5|D6|D7,0);
    GPIOPinWrite(lcdDDR,D4|D5|D6|D7,(data>>2));
    _delay_us(100);
    GPIOPinWrite(lcdPORT,EN|RS,0xc0);
    _delay_ms(1);
    GPIOPinWrite(lcdPORT,EN,0);
    _delay_us(100);
    GPIOPinWrite(lcdDDR,D4|D5|D6|D7,(data<<2));
    _delay_us(100);
    GPIOPinWrite(lcdPORT,EN|RS,0xc0);
    _delay_us(100);
    GPIOPinWrite(lcdPORT,EN,0);
    cursorPositionCheck=(cursorPositionCheck+1)%32;
}
/************************************************
 * This function is used to send strings to LCD
 ***********************************************/
void lcdString(char* string){
    unsigned char i=0;
    while(string[i])
        lcdData(string[i++]);
}
/***********************************************************
 * This function is used to position of the cursor on LCD
 **********************************************************/
void lcdGotoxy(unsigned char x,unsigned char y)
{
    cursorPositionCheck=y*16+x;
    lcdCommand(0x80+x+(64*y));
}
/************************************************
 * This function is used to clear the LCD
 ***********************************************/
void lcdClear(){
    cursorPositionCheck=0;
    lcdCommand(0x01);
    _delay_ms(5);
}
/*void lcd_Char(char x){

}*/
/******************************************************************
 * This function is used to check the position of cursor on LCD
 *****************************************************************/
void lcdCheck(){
    if(cursorPositionCheck==16)
    lcdGotoxy(0,1);
    else if(cursorPositionCheck==0)
    lcdGotoxy(0,0);
}
/*************************************
 * Calculating Delays
 *************************************/
void _delay_ms(uint64_t delay){
    SysCtlDelay(delay*(SysCtlClockGet()/3000));
}
void _delay_us(uint64_t delay){
    SysCtlDelay(delay*(SysCtlClockGet()/3000000UL));
}
/******************************************************
 * This function is for giving the direction of motion
 * Macros have been defined at starting
 * Macros for directions are 8 bits
 * Out of these 8 bits only 4 are used
 * Bit 0 (LSB) corresponds to PB3
 * Bit 3       corresponds to PF3
 * Bit 4       corresponds to PC4
 * Bit 6       corresponds to PF6
 *****************************************************/
void motion(uint8_t direction){
    GPIOPinWrite(GPIO_PORTB_BASE,GPIO_PIN_3,direction<<3);
    GPIOPinWrite(GPIO_PORTC_BASE,GPIO_PIN_4|GPIO_PIN_6,direction);
    GPIOPinWrite(GPIO_PORTF_BASE,GPIO_PIN_3,direction);
}
/******************************************************
 * This function is for enabling the PWM Modules
 * PWM can be enabled on a pin based on the datasheet
 *****************************************************/
void enablePWM(){
    GPIOPinTypePWM(GPIO_PORTF_BASE, GPIO_PIN_2);
    GPIOPinConfigure(GPIO_PF2_M1PWM6);
    GPIOPinTypePWM(GPIO_PORTC_BASE, GPIO_PIN_5);
    GPIOPinConfigure(GPIO_PC5_M0PWM7);
    PWMGenConfigure(PWM0_BASE, PWM_GEN_3, PWM_GEN_MODE_DOWN | PWM_GEN_MODE_NO_SYNC);//Count Down Mode
    PWMGenPeriodSet(PWM0_BASE, PWM_GEN_3, 255); //Load Count value
    PWMGenConfigure(PWM1_BASE, PWM_GEN_3, PWM_GEN_MODE_DOWN | PWM_GEN_MODE_NO_SYNC);//Count Down Mode
    PWMGenPeriodSet(PWM1_BASE, PWM_GEN_3, 255); //Load Count value
    PWMGenEnable(PWM0_BASE, PWM_GEN_3);
    PWMGenEnable(PWM1_BASE, PWM_GEN_3);
    PWMOutputState(PWM1_BASE, PWM_OUT_6_BIT, true);
    PWMOutputState(PWM0_BASE, PWM_OUT_7_BIT, true);
}
/*************************************************************
 * This function is used to control the speed of the motors
 * The speed can changed by the PWMPulseWidthSet() function
 * lSpeed is used to control the speed of left motor
 * rSpeed is used to control the speed of right motor
 ************************************************************/
void Velocity(uint8_t lSpeed,uint8_t rSpeed){
        lSpeed=(lSpeed>255)?255:lSpeed;
        rSpeed=(rSpeed>255)?255:rSpeed;
        PWMPulseWidthSet(PWM1_BASE, PWM_OUT_6, lSpeed);
        PWMPulseWidthSet(PWM0_BASE, PWM_OUT_7, rSpeed);
}
