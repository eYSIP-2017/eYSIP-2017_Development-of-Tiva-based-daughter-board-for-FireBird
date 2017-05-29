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
#define     lcdPORT     GPIO_PORTB_BASE
#endif
#ifndef     lcdDDR
#define     lcdDDR      GPIO_PORTB_BASE
#endif
#ifndef     lcdPIN
#define     lcdPIN      PINC
#endif
#ifndef     RS
#define     RS          GPIO_PIN_0
#endif
#ifndef     RW
#define     RW          GPIO_PIN_1
#endif
#ifndef     EN
#define     EN          GPIO_PIN_2
#endif
#ifndef     D4
#define     D4          GPIO_PIN_4
#endif
#ifndef     D5
#define     D5          GPIO_PIN_5
#endif
#ifndef     D6
#define     D6          GPIO_PIN_6
#endif
#ifndef     D7
#define     D7          GPIO_PIN_7
#endif
unsigned char cursorPositionCheck=0;
void lcdInit();
//void isBusy();
void lcdCommand(unsigned char);
void lcdData(unsigned char);
void lcdString(char*);
void lcdGotoxy(unsigned char,unsigned char);
void lcdClear();
void lcdCheck();
//void lcdInteger(long long int);
void setupCLK();
void peripheralEnable();
void _delay_ms(uint64_t delay);
void _delay_us(uint64_t delay);
int main(){
    setupCLK();
    peripheralEnable();
    lcdInit();
    while(1){
        lcdClear();
        lcdGotoxy(0,0);
        lcdString("TIVA C Series");
        _delay_ms(100);
    }
}
void setupCLK(){
    SysCtlClockSet(SYSCTL_SYSDIV_4|SYSCTL_USE_PLL|SYSCTL_XTAL_16MHZ|SYSCTL_OSC_MAIN);
}
void peripheralEnable(){
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOB);
}
void lcdInit(){
    GPIOPinTypeGPIOOutput(lcdPORT, RS|RW|EN|D4|D5|D6|D7);
    lcdCommand(0x02);//get the cursor to home
    lcdCommand(0x28);
    /**************************
    0x30 8bit mode single line*
    0x38 8bit mode double line*
    0x20 4bit mode single line*
    0x28 4bit mode double line*
    ***************************/
    lcdCommand(0x06);//entry mode and auto increment mode
    lcdCommand(0x0c);//
    /********************************
    Display off Cursor off      0x08*
    Display on Cursor on        0x0E*
    Display on Cursor off       0x0C*
    Display on Cursor blinking  0x0F*
    *********************************/
}
void lcdCommand(unsigned char command){
    GPIOPinWrite(lcdPORT,RS|RW|EN|D4|D5|D6|D7,0);
    //lcdPORT=0;
    _delay_ms(1);
    //GPIOPinWrite(lcdPORT,RS|RW|EN|D4|D5|D6|D7,0xf0&command);
    GPIOPinWrite(lcdPORT,D4|D5|D6|D7,command);
    //lcdPORT=(0xf0&command);
    _delay_us(100);
    GPIOPinWrite(lcdPORT,RS|RW|EN,0x04);
    //lcdPORT|=(0<<RS)|(0<<RW)|(1<<EN);
    _delay_us(100);
    GPIOPinWrite(lcdPORT,EN,0);
    //lcdPORT&=~(1<<EN);
    _delay_us(100);
    GPIOPinWrite(lcdPORT,D4|D5|D6|D7,command<<4);
    //lcdPORT=(0x0f&command)<<4;
    _delay_us(100);
    GPIOPinWrite(lcdPORT,RS|RW|EN,0x04);
    //lcdPORT|=(0<<RS)|(0<<RW)|(1<<EN);
    _delay_us(100);
    GPIOPinWrite(lcdPORT,EN,0);
  //lcdPORT&=~(1<<EN);
    _delay_us(100);
}
void lcdData(unsigned char data){
    lcdCheck();
    GPIOPinWrite(lcdPORT,RS|RW|EN|D4|D5|D6|D7,0);
    //lcdPORT=0;
    GPIOPinWrite(lcdPORT,D4|D5|D6|D7,data);
    //lcdPORT=(0xf0&data);
    _delay_us(100);
    GPIOPinWrite(lcdPORT,RS|RW|EN,0x05);
    //lcdPORT|=(0<<RW)|(1<<EN)|(1<<RS);
    _delay_ms(1);
    GPIOPinWrite(lcdPORT,EN,0);
    //lcdPORT&=~(1<<EN);
    _delay_us(100);
    GPIOPinWrite(lcdPORT,D4|D5|D6|D7,data<<4);
    //lcdPORT=(0x0f&(data))<<4;
    _delay_us(100);
    GPIOPinWrite(lcdPORT,RS|RW|EN,0x05);
    //lcdPORT|=(0<<RW)|(1<<EN)|(1<<RS);
    _delay_us(100);
    GPIOPinWrite(lcdPORT,EN,0);
    //lcdPORT&=~(1<<EN);
    cursorPositionCheck=(cursorPositionCheck+1)%32;
}
void lcdString(char* string){
    unsigned char i=0;
    while(string[i])
        lcdData(string[i++]);
}
/*void lcdInteger(long long int integer){
    char ch[20];
    itoa(integer,ch,10);
    lcdString(ch);
}*/
void lcdGotoxy(unsigned char x,unsigned char y)
{
    cursorPositionCheck=y*16+x;
    lcdCommand(0x80+x+(64*y));
}
void lcdClear(){
    cursorPositionCheck=0;
    lcdCommand(0x01);
    _delay_ms(3);
}
void lcdCheck(){
    if(cursorPositionCheck==16)
    lcdGotoxy(0,1);
    else if(cursorPositionCheck==0)
    lcdGotoxy(0,0);
}
void _delay_ms(uint64_t delay){
    SysCtlDelay(delay*(SysCtlClockGet()/3000));
}
void _delay_us(uint64_t delay){
    SysCtlDelay(delay*(SysCtlClockGet()/3000000UL));
}
