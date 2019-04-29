/*
 * GENSENALES.h
 *
 *  Created on: 12/03/2019
 *      Author: Lilia Lobato
 */

#ifndef GENSENALES_H_
#define GENSENALES_H_

#include "stdint.h"
#include <GENSENALES.h>

//Configuración PIT
void SENALES_PIT_config_5h();
void SENALES_PIT_config_sin();
void SENALES_PIT_config_trg();

//Configuracion DAC
void SENALES_DAC_config();

//Generadores de señales
void SENALES_CUADRADA();
void SENALES_SENOIDAL();
void SENALES_TRIANGULAR();
//void SENALES_fun_1_3(sw_status SW);

//Salida al DAC
void SENALES_SALIDA_DAC(uint32_t Salida);

#endif /* GENSENALES_H_ */
