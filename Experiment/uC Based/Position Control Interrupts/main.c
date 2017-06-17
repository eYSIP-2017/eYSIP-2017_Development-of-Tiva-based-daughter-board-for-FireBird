/*********************************************************************************
 Written by: Ayush Gaurav and Nagesh K.
From eRTS Lab, CSE Department, IIT Bombay.

 Date: 16th June 2017

 This experiment demonstrates use of position encoders present on both the wheels.

 Concepts covered: External Interrupts, Position control

 Microcontroller pins used:
 L-1---->PB0;        L-2---->PB1;
 R-1---->PF4;        R-2---->PA5;
 PF3----> PWM L     PA6----> PWM R;
 PA4 : External interrupt for left motor position encoder
 PA3 : External interrupt for the right position encoder
**********************************************************************************/

#include <stdint.h>
#include <stdbool.h>
#include "inc/tm4c123gh6pm.h"
#include "inc/hw_memmap.h"
#include "inc/hw_types.h"
#include "inc/hw_gpio.h"
#include "driverlib/sysctl.h"
#include "driverlib/interrupt.h"
#include "driverlib/gpio.h"
#define right           0x22
#define left            0x11
#define softRight       0x02
#define softLeft        0x10
#define forward         0x12
#define backward        0x21
#define stop            0x00
void setupCLK();
void peripheralEnable();
void gpioEnable();
void interruptEnable();
void encoderInterruptEncountered();
void linearDistanceMM(unsigned int);
void angleRotate(uint16_t);
void forwardMM(unsigned int);
void backwardMM(unsigned int);
void leftDegrees(unsigned int);
void rightDegrees(unsigned int);
void delay_ms(uint64_t delay);
void delay_us(uint64_t delay);
void motion(uint8_t direction);
volatile uint16_t ShaftCountRight=0,ShaftCountLeft=0;
int main(void) {
    setupCLK();
    peripheralEnable();
    gpioEnable();
    interruptEnable();
    while(1){
        forwardMM(100);
        delay_ms(1000);
        rightDegrees(90);
        delay_ms(1000);

        forwardMM(100);
        delay_ms(1000);
        rightDegrees(90);
        delay_ms(1000);

        forwardMM(100);
        delay_ms(1000);
        rightDegrees(90);
        delay_ms(1000);

        forwardMM(100);
        delay_ms(1000);
        rightDegrees(90);
        delay_ms(1000);
    }
}
void setupCLK(){
    SysCtlClockSet(SYSCTL_SYSDIV_5|SYSCTL_USE_PLL|SYSCTL_XTAL_16MHZ|SYSCTL_OSC_MAIN);
}
void peripheralEnable(){
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOB);
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOF);
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOA);}
void gpioEnable(){
    GPIOPinTypeGPIOOutput(GPIO_PORTF_BASE,GPIO_PIN_1|GPIO_PIN_2);
    GPIOPinTypeGPIOOutput(GPIO_PORTB_BASE,GPIO_PIN_0|GPIO_PIN_1);
    GPIOPinTypeGPIOOutput(GPIO_PORTA_BASE,GPIO_PIN_6|GPIO_PIN_5);
    GPIOPinTypeGPIOOutput(GPIO_PORTF_BASE,GPIO_PIN_4|GPIO_PIN_3);
    GPIOPinWrite(GPIO_PORTF_BASE,GPIO_PIN_3,255);
    GPIOPinWrite(GPIO_PORTA_BASE,GPIO_PIN_6,255);
    GPIOPinTypeGPIOInput(GPIO_PORTA_BASE, GPIO_PIN_4|GPIO_PIN_3);
    GPIOPadConfigSet(GPIO_PORTA_BASE ,GPIO_PIN_4|GPIO_PIN_5,GPIO_STRENGTH_2MA,GPIO_PIN_TYPE_STD_WPU);
}
void interruptEnable(){
    GPIOIntDisable(GPIO_PORTA_BASE,GPIO_PIN_4|GPIO_PIN_3);
    GPIOIntClear(GPIO_PORTA_BASE, GPIO_PIN_4|GPIO_PIN_3);
    GPIOIntRegister(GPIO_PORTA_BASE, encoderInterruptEncountered);
    GPIOIntTypeSet(GPIO_PORTA_BASE,GPIO_PIN_4|GPIO_PIN_3,GPIO_FALLING_EDGE);
    GPIOIntEnable(GPIO_PORTA_BASE,GPIO_PIN_4|GPIO_PIN_3);
}
void encoderInterruptEncountered(){
   if(GPIOIntStatus(GPIO_PORTA_BASE, false)&GPIO_PIN_4){
       ShaftCountLeft++;
       GPIOIntClear(GPIO_PORTA_BASE, GPIO_PIN_4);
   }
   if(GPIOIntStatus(GPIO_PORTA_BASE, false)&GPIO_PIN_3){
       ShaftCountRight++;
       GPIOIntClear(GPIO_PORTA_BASE, GPIO_PIN_3);
   }
   GPIOIntClear(GPIO_PORTA_BASE, GPIO_PIN_3|GPIO_PIN_4);
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
    GPIOPinWrite(GPIO_PORTB_BASE,GPIO_PIN_0|GPIO_PIN_1,direction);
    GPIOPinWrite(GPIO_PORTA_BASE,GPIO_PIN_5,direction);
    GPIOPinWrite(GPIO_PORTF_BASE,GPIO_PIN_4,direction);
}
void angleRotate(uint16_t Degrees){
     unsigned long int ReqdShaftCountInt = 0;  // division by resolution to get shaft count
     ReqdShaftCountInt = Degrees/ 4.09;;
     ShaftCountRight = 0;
     ShaftCountLeft = 0;
     while (1){
         if((ShaftCountRight>=ReqdShaftCountInt)&&(ShaftCountLeft>=ReqdShaftCountInt))
             break;
     }
     motion(stop);
}
void linearDistanceMM(unsigned int DistanceInMM){
     unsigned long int ReqdShaftCountInt = 0;
     ReqdShaftCountInt =DistanceInMM / 5.338;;
     ShaftCountRight=0;
     ShaftCountLeft=0;
     while(1){
         if((ShaftCountRight > ReqdShaftCountInt)&&(ShaftCountLeft > ReqdShaftCountInt))
             break;
         else if((ShaftCountRight > ReqdShaftCountInt))
             motion(softRight);
         else if((ShaftCountLeft > ReqdShaftCountInt))
             motion(softLeft);
     }
     motion(stop); //Stop robot
}
void forwardMM(unsigned int DistanceInMM){
    motion(forward);
     linearDistanceMM(DistanceInMM);
}

void backwardMM(unsigned int DistanceInMM){
    motion(backward);
    linearDistanceMM(DistanceInMM);
}
void leftDegrees(unsigned int Degrees){
    // 88 pulses for 360 degrees rotation 4.090 degrees per count
    motion(left); //Turn left
angleRotate(Degrees);
}
void rightDegrees(unsigned int Degrees){
    // 88 pulses for 360 degrees rotation 4.090 degrees per count
    motion(right); //Turn right
     angleRotate(Degrees);
}

