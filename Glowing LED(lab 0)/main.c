#include <stdint.h>
#include <stdbool.h>
#include "inc/hw_types.h"
#include "inc/hw_memmap.h"
#include "driverlib/sysctl.h"
#include "driverlib/gpio.h"
#define userSwitch1 GPIO_PIN_0
#define redLed      GPIO_PIN_1
#define blueLed     GPIO_PIN_2
#define greenLed    GPIO_PIN_3
#define userSwitch2 GPIO_PIN_4
void setupCLK();
void configIOPin();
int main(){
    unsigned char RGB = 2;
    setupCLK();
    configIOPin();
    while(1)
    {
        // Turn on the LED
        GPIOPinWrite(GPIO_PORTF_BASE, redLed|blueLed|greenLed, RGB);
        // Delay for a bit
        SysCtlDelay(2000000);
        // Cycle through Red, Green and Blue LEDs
        if (RGB==8)
        {
            RGB=2;
        }
        else
        {
            RGB=RGB<<1;
        }
    }
}
void setupCLK(){
    SysCtlClockSet(SYSCTL_SYSDIV_4|SYSCTL_USE_PLL|SYSCTL_XTAL_16MHZ|SYSCTL_OSC_MAIN);
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOF);
}
void configIOPin(){
    GPIOPinTypeGPIOOutput(GPIO_PORTF_BASE, redLed|blueLed|greenLed);
}
