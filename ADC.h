/*
 * DAC.h
 *
 *  Created on: 30/03/2019
 *      Author: Lilia Lobato
 */

#ifndef ADC_H_
#define ADC_H_

#include <stdio.h>
#include "MK64F12.h"
#include <stdint.h>
#include <GPIO.h>
#include <PushButton.h>
#include <RGB.h>
#include <NVIC.h>

//inicializacion del DAC
void ADC_init(void);

//Regresa el valor actual del DAC
uint16_t ADC_result(uint8_t ADC);


#endif /* ADC_H_ */
