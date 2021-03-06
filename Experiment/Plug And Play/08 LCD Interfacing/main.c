/*****************************************************************************************
 Written by: Ayush Gaurav And Nagesh K.
 From ERTS Lab, CSE Department, IIT Bombay.

 Date: 16th June 2017

 This experiment demonstrates LCD interfacing in 4 bit mode

 Concepts covered:  LCD interfacing

Connections:
               Plug and play board
             LCD      Board Pins
              RS  --> PD6
              RW  --> GND
              EN  --> PD7
              DB7 --> PA5
              DB6 --> PA4
              DB5 --> PA3
              DB4 --> PA2

 Note: Make sure that in the configuration options following settings are
 done for proper operation of the code.
*****************************************************************************************/
#include <stdint.h>
#include <stdbool.h>
#include "inc/hw_types.h"
#include "inc/hw_memmap.h"
#include "inc/hw_gpio.h" //To unlock locked pins for GPIO
#include "driverlib/sysctl.h"
#include "driverlib/gpio.h"
#include<math.h>
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
unsigned char cursorPositionCheck=0;
void lcdInit();
void lcdCommand(unsigned char);
void lcdData(unsigned char);
void lcdString(char*);
void lcdGotoxy(unsigned char,unsigned char);
void lcdClear();
void lcdCheck();
void setupCLK();
void peripheralEnable();
void configIOPin();
void _delay_ms(uint64_t delay);
void _delay_us(uint64_t delay);
int main(){
    setupCLK();
    peripheralEnable();
    configIOPin();
    lcdInit();
    lcdGotoxy(0,0);
    lcdString("TIVA C Series");
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
    SysCtlClockSet(SYSCTL_SYSDIV_4|SYSCTL_USE_PLL|SYSCTL_XTAL_16MHZ|SYSCTL_OSC_MAIN);
}
/*******************************
 * Enabling System Peripherals
 * PORTA and PORTD in this case
 ******************************/
void peripheralEnable(){
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOA);
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOD);
}
/*************************************
 * Configuring LCD Pins as Output
 *************************************/
void configIOPin(){
    HWREG(GPIO_PORTD_BASE + GPIO_O_LOCK) = GPIO_LOCK_KEY;   //getting the key
    HWREG(GPIO_PORTD_BASE + GPIO_O_CR) |= (1<<7);   //unlocking the pin
    HWREG(GPIO_PORTD_BASE + GPIO_O_LOCK) = 0;   //relocking the pin
    GPIOPinTypeGPIOOutput(GPIO_PORTD_BASE,EN|RS);
    GPIOPinTypeGPIOOutput(GPIO_PORTA_BASE,D4|D5|D6|D7);

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
    GPIOPinWrite(lcdDDR,D4|D5|D6|D7,(command>>2));  //Putting first 4 bits in data lines of LCD
    _delay_ms(1);
    GPIOPinWrite(lcdPORT,EN|RS,0x80);   //setting enable pin for a period of 1ms
    _delay_us(100);
    GPIOPinWrite(lcdPORT,EN,0);
    _delay_us(100);
    GPIOPinWrite(lcdDDR,D4|D5|D6|D7,(command<<2));  //Putting last 4 bits in data lines of LCD
    _delay_ms(1);
    GPIOPinWrite(lcdPORT,EN|RS,0x80);   //setting enable pin for a period of 1ms
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
    GPIOPinWrite(lcdDDR,D4|D5|D6|D7,(data>>2));     //Putting the first 4 bits in data lines of LCD
    _delay_us(100);
    GPIOPinWrite(lcdPORT,EN|RS,0xc0);   //setting enable pin for a period of 1ms
    _delay_ms(1);
    GPIOPinWrite(lcdPORT,EN,0);
    _delay_us(100);
    GPIOPinWrite(lcdDDR,D4|D5|D6|D7,(data<<2)); //putting last 4 bits in data lines of lCD
    _delay_us(100);
    GPIOPinWrite(lcdPORT,EN|RS,0xc0);   //setting enable pin for a period of 1ms
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

