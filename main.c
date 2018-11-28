#include <driverlib.h>
#include <interrupt_set_up.h>
#include <myclocks.h>
/**
 * main.c
 */

#define ONE_SECOND 800000

volatile unsigned short pushButton1 = 1;
volatile unsigned short button1InitState = 0;

void initGPIO (void);
//void myButtonIsr(void)
#define ONE_SECOND 800000
#define HALF_SECOND 400000


int main(void) {
    WDT_A_hold(WDT_A_BASE);

    initGPIO();
    _enable_interrupts();
	_delay_cycles(ONE_SECOND);
	GPIO_toggleOutputOnPin(GPIO_PORT_P9, GPIO_PIN7);
	while (1)
	{

	    if (pushButton1 == button1InitState) {
	    GPIO_toggleOutputOnPin(GPIO_PORT_P1, GPIO_PIN0);
	    GPIO_toggleOutputOnPin(GPIO_PORT_P9, GPIO_PIN7);
	    //_delay_cycles(ONE_SECOND);

	    pushButton1 = 1;

	    }
	}
	return 0;
}

void initGPIO (void)
{
    GPIO_setAsOutputPin (GPIO_PORT_P1, GPIO_PIN0);
    GPIO_setAsOutputPin(GPIO_PORT_P9, GPIO_PIN7);
    PMM_unlockLPM5();
    GPIO_setAsInputPinWithPullUpResistor(GPIO_PORT_P1, GPIO_PIN1);
    GPIO_setAsInputPinWithPullUpResistor(GPIO_PORT_P1, GPIO_PIN2);
    init_interrupt();
}
/*

*/
#pragma vector=PORT1_VECTOR
 __interrupt void myButtonIsr(void)
{
    switch(__even_in_range( P1IV, 0x10 )) {
    case 0x00: break; // None
    case 0x02: break; // Pin 0
    case 0x04: pushButton1 = 0;
    break; // Pin 1
    case 0x06: pushButton1 = 0; // Pin 2
    break;
    case 0x08: break; // Pin 3
    case 0x0A: break; // Pin 4
    case 0x0C: break; // Pin 5
    case 0x0E: break; // Pin 6
    case 0x10: break; // Pin 7
    default: _never_executed();
    }
    }
