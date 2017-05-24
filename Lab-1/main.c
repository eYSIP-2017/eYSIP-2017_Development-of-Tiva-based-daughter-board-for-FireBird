
#include <stdint.h>
#include <stdbool.h>
#include "inc/hw_types.h"
#include "inc/hw_memmap.h"
#include "inc/hw_gpio.h" //To unlock locked pins for GPIO
#include "driverlib/sysctl.h"
#include "driverlib/gpio.h"
#define userSwitch1 GPIO_PIN_0
#define redLed      GPIO_PIN_1
#define blueLed     GPIO_PIN_2
#define greenLed    GPIO_PIN_3
#define userSwitch2 GPIO_PIN_4
#define LOCK_F (*((volatile unsigned long *)0x40025520))
#define CR_F   (*((volatile unsigned long *)0x40025524))
void setupCLK();
void configIOPin();
int main(){
    setupCLK();
    SysCtlDelay(3);
    configIOPin();
    unsigned char pinData=1;
    unsigned char state=1;
    unsigned char countSwitch2=0;
    unsigned char flag=0;
    while(1){
        pinData=GPIOPinRead(GPIO_PORTF_BASE,userSwitch2|userSwitch1);
        if((pinData&0x01)==0)
            countSwitch2++;
        if(((pinData&0x10)==0)&&(flag==0)){
            flag=1;
            state=(state*2);
            if(state>8) state=2;
            GPIOPinWrite(GPIO_PORTF_BASE,redLed|blueLed|greenLed,state);
            SysCtlDelay(700000);
        }
        else{
            GPIOPinWrite(GPIO_PORTF_BASE,redLed|blueLed|greenLed,0);
            flag=0;
        }
        SysCtlDelay(700);
    }
}
void setupCLK(){
    SysCtlClockSet(SYSCTL_SYSDIV_4|SYSCTL_USE_PLL|SYSCTL_XTAL_16MHZ|SYSCTL_OSC_MAIN);
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOF);
}
void configIOPin(){
    GPIOPinTypeGPIOOutput(GPIO_PORTF_BASE, redLed|blueLed|greenLed);
    HWREG(GPIO_PORTF_BASE + GPIO_O_LOCK) = GPIO_LOCK_KEY;
    HWREG(GPIO_PORTF_BASE + GPIO_O_CR) |= 0x01;
    HWREG(GPIO_PORTF_BASE + GPIO_O_LOCK) = 0;
    GPIOPinTypeGPIOInput(GPIO_PORTF_BASE, userSwitch2|userSwitch1);
    GPIOPadConfigSet(GPIO_PORTF_BASE ,userSwitch2|userSwitch1,GPIO_STRENGTH_2MA,GPIO_PIN_TYPE_STD_WPU);
}
