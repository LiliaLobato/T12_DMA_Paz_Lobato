#include "MK64F12.h"
#include "NVIC.h"
#include "GPIO.h"
#include "Bits.h"
#include "PushButton.h"
#include "PIT.h"
#include "DAC.h"
#include <stdio.h>



int main(void) {
	PushButton_sw2_config();
	PushButton_sw3_config();
#ifdef GEN
	GPIO_callback_init(GPIO_A, &signal_sequence);
	DAC_Config();
	PIT0_DMA_config(SYSTEM_CLOCK, DELAYTRG);
#endif

	//DMA init
	DMA_clock_gating();
	DMA_init_completeArray(); /* Configure the T*/
	//DMA_init_halfArray(); /* Configure the T*/
	//DMA_init_oddArray(); /* Configure the T*/
	//DMA_init();
	//DMA_init_clase();

	NVIC_set_basepri_threshold(PRIORITY_12);
#ifdef GEN
	NVIC_enable_interrupt_and_priotity(PORTA_IRQ, PRIORITY_3);
#endif
	NVIC_enable_interrupt_and_priotity(DMA_CH0_IRQ, PRIORITY_5);

	NVIC_global_enable_interrupts;

	for (;;) {

	}
	/* Never leave main */
	return 0;
}
////////////////////////////////////////////////////////////////////////////////
// EOF
////////////////////////////////////////////////////////////////////////////////
