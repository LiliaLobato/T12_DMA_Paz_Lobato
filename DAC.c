/*
 * DAC.c
 *
 *  Created on: 01/05/2019
 *      Author: Lilia Lobato
 */

#include <stdio.h>
#include "MK64F12.h"
#include <stdint.h>
#include "GPIO.h"


void DAC_Config() {
	//Configuración de clock;
	SIM->SCGC2 = 0x1000;
	//Configuración DAC
	DAC0->C0 = 0xC0;
	DAC0->DAT[0].DATL = 0;
	DAC0->DAT[0].DATH = 0;
}

void DAC_SALIDA(uint32_t Salida) {
	uint8_t SalidaL;
	uint8_t SalidaH;
	SalidaL = (uint16_t) Salida & 0xFF;
	SalidaH = (uint16_t) ((Salida >> 8) & 0x0F);
	DAC0->DAT[0].DATL = SalidaL;
	DAC0->DAT[0].DATH = SalidaH;
}
