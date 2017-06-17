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
 PB2 : External interrupt for left motor position encoder
 PF0 : External interrupt for the right position encoder
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
//This header File is important to Unlock GPIO Pins
#include "inc/hw_gpio.h"
#include "driverlib/sysctl.h"
#include "driverlib/gpio.h"
#define right           0x40
#define left            0x18
#define forward         0x10
#define backward        0x48
#define stop            0x00
void setupCLK();
void peripheralEnable();
void configIOPin();
void delay_ms(uint64_t delay);
void delay_ms(uint64_t delay);
void motion(uint8_t);
void interruptEnable();
void encoderInterruptEncountered();
void encoderInterruptEncountered1();
void angleRotate(uint16_t Degrees);
void linearDistanceMM(unsigned int DistanceInMM);
void rightDegrees(unsigned int Degrees);
void leftDegrees(unsigned int Degrees);
void forwardMM(unsigned int DistanceInMM);
void backwardMM(unsigned int DistanceInMM);
volatile unsigned long int ShaftCountRight = 0;
volatile unsigned long int ShaftCountLeft = 0;
int main(void) {
    setupCLK();
    peripheralEnable();
    configIOPin();
    interruptEnable();
    while(1){
    forwardMM(100);
    delay_ms(1000);
    leftDegrees(90);
    delay_ms(1000);

    forwardMM(100);
    delay_ms(1000);
    leftDegrees(90);
    delay_ms(1000);

    forwardMM(100);
    delay_ms(1000);
    leftDegrees(90);
    delay_ms(1000);

    forwardMM(100);
    delay_ms(1000);
    leftDegrees(90);
    delay_ms(1000);
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
}
/*******************************
 * Enabling System Peripherals
 * PORTF,PORTB and PORTC in this case
 ******************************/
void peripheralEnable(){
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOB);
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOF);
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOC);
}
/*************************************
 * Configuring Pin as Input Or Output
 *************************************/
void configIOPin(){
    GPIOPinTypeGPIOOutput(GPIO_PORTB_BASE,GPIO_PIN_3);
    GPIOPinTypeGPIOOutput(GPIO_PORTC_BASE,GPIO_PIN_4|GPIO_PIN_5|GPIO_PIN_6);
    GPIOPinTypeGPIOOutput(GPIO_PORTF_BASE,GPIO_PIN_3|GPIO_PIN_2);
    GPIOPinWrite(GPIO_PORTF_BASE,GPIO_PIN_2,255);
    GPIOPinWrite(GPIO_PORTC_BASE,GPIO_PIN_5,255);
    HWREG(GPIO_PORTF_BASE + GPIO_O_LOCK) = GPIO_LOCK_KEY;
    HWREG(GPIO_PORTF_BASE + GPIO_O_CR) |= 0x01;
    HWREG(GPIO_PORTF_BASE + GPIO_O_LOCK) = 0;
    GPIOPinTypeGPIOInput(GPIO_PORTF_BASE, GPIO_PIN_0);
    GPIOPadConfigSet(GPIO_PORTF_BASE ,GPIO_PIN_0,GPIO_STRENGTH_2MA,GPIO_PIN_TYPE_STD_WPU);
    GPIOPinTypeGPIOInput(GPIO_PORTB_BASE, GPIO_PIN_2);
    GPIOPadConfigSet(GPIO_PORTB_BASE ,GPIO_PIN_2,GPIO_STRENGTH_2MA,GPIO_PIN_TYPE_STD_WPU);

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
    GPIOPinWrite(GPIO_PORTB_BASE,GPIO_PIN_3,~direction);
    GPIOPinWrite(GPIO_PORTC_BASE,GPIO_PIN_4|GPIO_PIN_6,direction);
    GPIOPinWrite(GPIO_PORTF_BASE,GPIO_PIN_3,direction);
}
void interruptEnable(){
    GPIOIntDisable(GPIO_PORTF_BASE,GPIO_PIN_0);
    GPIOIntClear(GPIO_PORTF_BASE,GPIO_PIN_0);
    GPIOIntRegister(GPIO_PORTF_BASE, encoderInterruptEncountered);
    GPIOIntTypeSet(GPIO_PORTF_BASE,GPIO_PIN_0,GPIO_FALLING_EDGE);
    GPIOIntEnable(GPIO_PORTF_BASE,GPIO_PIN_0);

    GPIOIntDisable(GPIO_PORTB_BASE,GPIO_PIN_2);
    GPIOIntClear(GPIO_PORTB_BASE,GPIO_PIN_2);
    GPIOIntRegister(GPIO_PORTB_BASE, encoderInterruptEncountered1);
    GPIOIntTypeSet(GPIO_PORTB_BASE,GPIO_PIN_2,GPIO_FALLING_EDGE);
    GPIOIntEnable(GPIO_PORTB_BASE,GPIO_PIN_2);
}
void encoderInterruptEncountered(){
   if(GPIOIntStatus(GPIO_PORTF_BASE, false)&GPIO_PIN_0){
       ShaftCountRight++;
       GPIOIntClear(GPIO_PORTF_BASE, GPIO_PIN_0);
   }
   GPIOIntClear(GPIO_PORTF_BASE, GPIO_PIN_0);
}
void encoderInterruptEncountered1(){
   if(GPIOIntStatus(GPIO_PORTB_BASE, false)&GPIO_PIN_2){
       ShaftCountLeft++;
       GPIOIntClear(GPIO_PORTB_BASE, GPIO_PIN_2);
   }
   GPIOIntClear(GPIO_PORTB_BASE, GPIO_PIN_2);
}
/*************************************
 * Calculating Delays
 *************************************/
void angleRotate(uint16_t Degrees){
     unsigned long int ReqdShaftCountInt = 0;  // division by resolution to get shaft count
     ReqdShaftCountInt = Degrees/ 4.09;;
     ShaftCountRight = 0;
     while (1){
         if((ShaftCountRight>=ReqdShaftCountInt))
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

