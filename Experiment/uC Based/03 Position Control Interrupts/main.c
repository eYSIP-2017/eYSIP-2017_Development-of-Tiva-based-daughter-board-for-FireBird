/*********************************************************************************
 Written by: Ayush Gaurav and Nagesh K.
From ERTS Lab, CSE Department, IIT Bombay.

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
 * PORTF,PORTB and PORTA in this case
 ******************************/
void peripheralEnable(){
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOB);
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOF);
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOA);
}

/*************************************
 * Configuring Pin as Input Or Output
 * Setting PWM Pins to Always High
 * Weak Pull to the Input Pins
 *************************************/
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
/****For Enabling Interrupt on PortA****/
void interruptEnable(){
    GPIOIntDisable(GPIO_PORTA_BASE,GPIO_PIN_4|GPIO_PIN_3);
    GPIOIntClear(GPIO_PORTA_BASE, GPIO_PIN_4|GPIO_PIN_3);
    GPIOIntRegister(GPIO_PORTA_BASE, encoderInterruptEncountered);
    GPIOIntTypeSet(GPIO_PORTA_BASE,GPIO_PIN_4|GPIO_PIN_3,GPIO_FALLING_EDGE);
    GPIOIntEnable(GPIO_PORTA_BASE,GPIO_PIN_4|GPIO_PIN_3);
}
/**** ISR For External Interrupt on PortA************************
 * Check on which pin of the PORTA has encountered an interrupt
 * There is only one ISR for complete PORT
 * No two PORTs can have same ISR
 ****************************************************************/
void encoderInterruptEncountered(){
   if(GPIOIntStatus(GPIO_PORTA_BASE, false)&GPIO_PIN_4){
       ShaftCountLeft++;
       GPIOIntClear(GPIO_PORTA_BASE, GPIO_PIN_4);
   }
   if(GPIOIntStatus(GPIO_PORTA_BASE, false)&GPIO_PIN_3){
       ShaftCountRight++;
       GPIOIntClear(GPIO_PORTA_BASE, GPIO_PIN_3);
   }
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
    GPIOPinWrite(GPIO_PORTB_BASE,GPIO_PIN_0|GPIO_PIN_1,direction);
    GPIOPinWrite(GPIO_PORTA_BASE,GPIO_PIN_5,direction);
    GPIOPinWrite(GPIO_PORTF_BASE,GPIO_PIN_4,direction);
}
/****************************************************
 * Function to Rotate to desired Angle
 * Resolution can be Change to Get Higher Precision
 ****************************************************/
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
/****************************************************
 * Function to Move in a Linear Distance
 * Resolution can be Change to Get Higher Precision
 ****************************************************/
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
    motion(left); //Turn left
    angleRotate(Degrees);
}
void rightDegrees(unsigned int Degrees){
    motion(right); //Turn right
     angleRotate(Degrees);
}
