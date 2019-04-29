/*
 * DAC.c
 *
 *  Created on: 30/03/2019
 *      Author: Lilia Lobato
 */

#include <stdio.h>
#include "MK64F12.h"
#include <stdint.h>
#include <GPIO.h>
#include <PushButton.h>
#include <NVIC.h>

void ADC_init(){
	//Configuración de clock;
	SIM->SCGC6 |= SIM_SCGC6_ADC0_MASK;
	//Configuración ADC (PTE(24))
	ADC0->CFG1 = ADC_CFG1_ADIV(0) | ADC_CFG1_ADLSMP_MASK |
	ADC_CFG1_MODE(1) | ADC_CFG1_ADICLK(0);
	ADC0->CFG2 = 0;
	ADC0->SC2 = 0;
	ADC0->SC3 = ADC_SC3_AVGE_MASK | ADC_SC3_AVGS(2); //Con esta linea se hace el promedio de 16 muestras
}

uint16_t ADC_result(uint8_t ADC) {
	uint16_t adc_result;
	ADC0->SC1[0] = ADC_SC1_ADCH(17); //PTE24 tarjeta, ADC0SE17 mapeado en 10001
	while ((ADC0->SC1[0] & ADC_SC1_COCO_MASK) == 0)
		;
	adc_result = ADC0->R[0];

	return (adc_result);
}
