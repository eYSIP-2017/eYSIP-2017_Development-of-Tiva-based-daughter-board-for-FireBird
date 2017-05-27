#include "driverlib/pin_map.h"
#include <stdint.h>
#include <stdbool.h>
#include "inc/tm4c123gh6pm.h"
#include "inc/hw_gpio.h"
#include "inc/hw_types.h"
#include "inc/hw_memmap.h"
#include "driverlib/sysctl.h"
#include "driverlib/pin_map.h"
#include "driverlib/gpio.h"
#include "driverlib/pwm.h"
#include "driverlib/timer.h"
#include "driverlib/interrupt.h"

void Manual_mode(void);
void delayMS(int ms) {
    SysCtlDelay( (SysCtlClockGet()/(3*1000))*ms ) ;
}

unsigned char sw1 = 1;
unsigned char sw2 = 1;
unsigned char flag1 = 0;
unsigned char flag2 = 0;
unsigned char flag3 = 0;
unsigned int count = 0;

int
main(void)


{
    uint32_t ui32Period;
    //Set the clock
   //SysCtlClockSet(SYSCTL_SYSDIV_1 | SYSCTL_USE_OSC |   SYSCTL_OSC_MAIN | SYSCTL_XTAL_16MHZ);
    SysCtlClockSet(SYSCTL_SYSDIV_5|SYSCTL_USE_PLL|SYSCTL_XTAL_16MHZ|SYSCTL_OSC_MAIN);

   //Configure PWM Clock to match system
   SysCtlPWMClockSet(SYSCTL_PWMDIV_1);

   // Enable the peripherals used by this program.
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOF);
    SysCtlPeripheralEnable(SYSCTL_PERIPH_PWM1);  //The Tiva Launchpad has two modules (0 and 1). Module 1 covers the LED pins

    //Configure PF1,PF2,PF3 Pins as PWM
    GPIOPinConfigure(GPIO_PF1_M1PWM5);
    GPIOPinConfigure(GPIO_PF2_M1PWM6);
    GPIOPinConfigure(GPIO_PF3_M1PWM7);
    GPIOPinTypePWM(GPIO_PORTF_BASE, GPIO_PIN_1 | GPIO_PIN_2 | GPIO_PIN_3);

    HWREG(GPIO_PORTF_BASE + GPIO_O_LOCK) = GPIO_LOCK_KEY;
    HWREG(GPIO_PORTF_BASE + GPIO_O_CR) |= 0x01;
    HWREG(GPIO_PORTF_BASE + GPIO_O_LOCK) = 0;
    GPIODirModeSet(GPIO_PORTF_BASE, GPIO_PIN_4|GPIO_PIN_0, GPIO_DIR_MODE_IN);
    GPIOPadConfigSet(GPIO_PORTF_BASE, GPIO_PIN_4|GPIO_PIN_0, GPIO_STRENGTH_2MA, GPIO_PIN_TYPE_STD_WPU);


    //Configure PWM Options
    //PWM_GEN_2 Covers M1PWM4 and M1PWM5
    //PWM_GEN_3 Covers M1PWM6 and M1PWM7 See page 207 4/11/13 DriverLib doc
    PWMGenConfigure(PWM1_BASE, PWM_GEN_2, PWM_GEN_MODE_DOWN | PWM_GEN_MODE_NO_SYNC);
    PWMGenConfigure(PWM1_BASE, PWM_GEN_3, PWM_GEN_MODE_DOWN | PWM_GEN_MODE_NO_SYNC);

    //Set the Period (expressed in clock ticks)
    PWMGenPeriodSet(PWM1_BASE, PWM_GEN_2, 360);
    PWMGenPeriodSet(PWM1_BASE, PWM_GEN_3, 360);

    //Set PWM duty-50% (Period /2)
    //PWMPulseWidthSet(PWM1_BASE, PWM_OUT_5,100);
    //PWMPulseWidthSet(PWM1_BASE, PWM_OUT_6,100);
    //PWMPulseWidthSet(PWM1_BASE, PWM_OUT_7,100);

    // Enable the PWM generator
    PWMGenEnable(PWM1_BASE, PWM_GEN_2);
    PWMGenEnable(PWM1_BASE, PWM_GEN_3);

    // Turn on the Output pins
    PWMOutputState(PWM1_BASE, PWM_OUT_5_BIT | PWM_OUT_6_BIT | PWM_OUT_7_BIT, true);
    //PWMOutputState(PWM1_BASE, PWM_OUT_5_BIT|PWM_OUT_6_BIT, true);
    //PWMOutputState(PWM1_BASE, PWM_OUT_7_BIT, false);

    SysCtlPeripheralEnable(SYSCTL_PERIPH_TIMER0);
    TimerConfigure(TIMER0_BASE, TIMER_CFG_PERIODIC);

    ui32Period = (SysCtlClockGet() / 100) / 2;
    TimerLoadSet(TIMER0_BASE, TIMER_A, ui32Period -1);

    IntEnable(INT_TIMER0A);
    TimerIntEnable(TIMER0_BASE, TIMER_TIMA_TIMEOUT);
    IntMasterEnable();

    TimerEnable(TIMER0_BASE, TIMER_A);

    //Fade
    //bool fadeUp = true;
    unsigned long increment = 1;
    unsigned long pwmNow = 10;
    unsigned char i=0,a = 1;
    while(1)
    {
        sw1=sw2=1;
        PWMOutputState(PWM1_BASE, PWM_OUT_5_BIT | PWM_OUT_6_BIT | PWM_OUT_7_BIT, true);

        switch(a)
        {
                    case 1: PWMOutputState(PWM1_BASE, PWM_OUT_6_BIT | PWM_OUT_7_BIT, false);break;
                    case 2: PWMOutputState(PWM1_BASE, PWM_OUT_6_BIT, false);break;
                    case 3: PWMOutputState(PWM1_BASE, PWM_OUT_5_BIT | PWM_OUT_6_BIT, false);break;
                    case 4: PWMOutputState(PWM1_BASE, PWM_OUT_5_BIT, false);break;
                    case 5: PWMOutputState(PWM1_BASE, PWM_OUT_5_BIT | PWM_OUT_7_BIT, false);break;
                    case 6: PWMOutputState(PWM1_BASE, PWM_OUT_7_BIT, false);break;
        }
        if(pwmNow%60 == 0)
            a++;

        delayMS(40);



        pwmNow += increment;
        if(sw1 == 0)
        {
            //count = 1;
            if(sw2 == 0)
            {    flag3 = 1;
                 //sw2 = 1;
                 count = 1;
                 delayMS(150);
                 if(sw2 == 0)
                 {
                     count = 2;
                     delayMS(100);
                     if(sw2 == 0)
                     {
                         count = 3;
                     }
                 }
            }
            /*if(sw2 == 0)
            {    count = 1;
                delayMS(150);
            }
            if(sw2 == 0)
            {    count = 2;
                delayMS(150);
            }
            if(sw2 == 0)
            {    count = 3;
                delayMS(150);
            }*/
            if(count > 0)
                Manual_mode();
            pwmNow += 1;
        }

        if(sw2 == 0)
        {
            delayMS(5);
        }

        if (pwmNow >= 350)
            {pwmNow = 10; a = 1;}

        PWMPulseWidthSet(PWM1_BASE, PWM_OUT_5,pwmNow);
        PWMPulseWidthSet(PWM1_BASE, PWM_OUT_6,pwmNow);
        PWMPulseWidthSet(PWM1_BASE, PWM_OUT_7,pwmNow);


    }

}

void Timer0IntHandler(void)
{
    // Clear the timer interrupt
    TimerIntClear(TIMER0_BASE, TIMER_TIMA_TIMEOUT);


    if(GPIOPinRead(GPIO_PORTF_BASE,GPIO_PIN_4)==0x00)
    {
        flag1++;
        if(flag1 >= 2)
        {
            sw1 = 0;
            flag1 = 0;

        }
    }
    if(GPIOPinRead(GPIO_PORTF_BASE,GPIO_PIN_0)==0x00)
    {
        flag2++;
        if(flag2 >= 2)
        {
            sw2 = 0;
            flag2 = 0;
        }
    }
    if(GPIOPinRead(GPIO_PORTF_BASE,GPIO_PIN_4)==0x10)
        sw1 = 1;
    if(GPIOPinRead(GPIO_PORTF_BASE,GPIO_PIN_0)==0x01)
        sw2 = 1;

}

void Manual_mode(void)
{
    PWMOutputState(PWM1_BASE, PWM_OUT_5_BIT | PWM_OUT_6_BIT | PWM_OUT_7_BIT, true);
    delayMS(1000);

    switch(count)
    {
    case 1:
        PWMOutputState(PWM1_BASE, PWM_OUT_6_BIT | PWM_OUT_7_BIT, false);
        PWMOutputState(PWM1_BASE, PWM_OUT_5_BIT, true);
        break;
    case 2:
        PWMOutputState(PWM1_BASE, PWM_OUT_5_BIT | PWM_OUT_7_BIT, false);
        PWMOutputState(PWM1_BASE, PWM_OUT_6_BIT, true);
        break;
    case 3:
        PWMOutputState(PWM1_BASE, PWM_OUT_6_BIT | PWM_OUT_5_BIT, false);
        PWMOutputState(PWM1_BASE, PWM_OUT_7_BIT, true);
        break;
    }
    unsigned char val = 0;
     while(1)
     {
                    if(GPIOPinRead(GPIO_PORTF_BASE,GPIO_PIN_4)==0x00)
                        val += 5;
                    if(GPIOPinRead(GPIO_PORTF_BASE,GPIO_PIN_0)==0x00)
                        val -= 5;
                    if(val<10 || val>350)
                        val = 100;
                    PWMPulseWidthSet(PWM1_BASE, PWM_OUT_5, val);
                    PWMPulseWidthSet(PWM1_BASE, PWM_OUT_6, val);
                    PWMPulseWidthSet(PWM1_BASE, PWM_OUT_7, val);
     }
}

