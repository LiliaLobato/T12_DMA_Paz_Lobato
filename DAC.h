/*
 * DAC.h
 *
 *  Created on: 01/05/2019
 *      Author: Lilia Lobato
 */

#ifndef DAC_H_
#define DAC_H_

#include <stdio.h>
#include "MK64F12.h"
#include <stdint.h>
#include "GPIO.h"

void DAC_Config();

void DAC_SALIDA(uint32_t Salida);

#endif /* DAC_H_ */
