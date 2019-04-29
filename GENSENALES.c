/*
 * GENSENALES.c
 *
 *  Created on: 12/03/2019
 *      Author: Lilia Lobato
 */

#include "MK64F12.h"
#include "GPIO.h"
#include "GENSENALES.h"
#include "PIT.h"
#include "NVIC.h"
#include "Bits.h"

#define SYSTEM_CLOCK (21000000U)
#define DELAY5H (0.2F)
#define DELAYTRG (0.002F)
#define DELAYSIN (0.004F)
#define TOP	3700
#define LOW	0
#define REP_TOP 1
#define SQR_TOP 100

typedef enum {
	SENAL_ON, SENAL_OFF
} senal_status;

//Banderas
static uint8_t sen_counter = LOW;
static uint8_t F_counter = LOW;
static senal_status flag_senal = SENAL_ON;

//Array para la triangular
static uint32_t trg[101] = { 0, 37, 74, 111, 148, 185, 222, 259, 296, 333, 370,
		407, 444, 481, 518, 555, 592, 629, 666, 703, 740, 777, 814, 851, 888,
		925, 962, 999, 1036, 1073, 1110, 1147, 1184, 1221, 1258, 1295, 1332,
		1369, 1406, 1443, 1480, 1517, 1554, 1591, 1628, 1665, 1702, 1739, 1776,
		1813, 1850, 1887, 1924, 1961, 1998, 2035, 2072, 2109, 2146, 2183, 2220,
		2257, 2294, 2331, 2368, 2405, 2442, 2479, 2516, 2553, 2590, 2627, 2664,
		2701, 2738, 2775, 2812, 2849, 2886, 2923, 2960, 2997, 3034, 3071, 3108,
		3145, 3182, 3219, 3256, 3293, 3330, 3367, 3404, 3441, 3478, 3515, 3552,
		3589, 3626, 3663, 3700 };
//Array para el sen
static uint32_t sen[101] = { 1850, 1966, 2082, 2197, 2310, 2422, 2531, 2638,
		2741, 2841, 2937, 3029, 3116, 3199, 3275, 3347, 3412, 3471, 3524, 3570,
		3609, 3642, 3667, 3685, 3696, 3700, 3696, 3685, 3667, 3642, 3609, 3570,
		3524, 3471, 3412, 3347, 3275, 3199, 3116, 3029, 2937, 2841, 2741, 2638,
		2531, 2422, 2310, 2197, 2082, 1966, 1850, 1734, 1618, 1503, 1390, 1278,
		1169, 1062, 959, 859, 763, 671, 584, 501, 425, 353, 288, 229, 176, 130,
		91, 58, 33, 15, 4, 0, 4, 15, 33, 58, 91, 130, 176, 229, 288, 353, 425,
		501, 584, 671, 763, 859, 959, 1062, 1169, 1278, 1390, 1503, 1618, 1734,
		1850 };

void SENALES_PIT_config_trg() {
	PIT_clock_gating();
	PIT_enable();
	NVIC_set_basepri_threshold(PRIORITY_12);
	NVIC_enable_interrupt_and_priotity(PIT_CH0_IRQ, PRIORITY_3);
	NVIC_global_enable_interrupts;
	PIT_delay(PIT_0, SYSTEM_CLOCK, DELAYTRG);
	PIT_enable_interrupt_0(PIT_0);
}

void SENALES_CUADRADA() {
	//LED externo
	RGB_estado1(GPIO_D, bit_1, GPIO_D, bit_3);

	if (SENAL_ON == flag_senal) {

		if (SQR_TOP == F_counter) {
			SENALES_SALIDA_DAC(LOW);
			flag_senal = SENAL_OFF;
			F_counter = LOW;
		} else {
			F_counter++;
		}

	} else {

		if (SQR_TOP == F_counter) {
			SENALES_SALIDA_DAC(TOP);
			flag_senal = SENAL_ON;
			F_counter = LOW;
		} else {
			F_counter++;
		}

	}
	PIT_clear1_interrupt_flag();
}

void SENALES_SENOIDAL() {
	//LED externo
	RGB_estado2(GPIO_D, bit_1, GPIO_D, bit_3);

	if (sen_counter <= 100) {
		if (REP_TOP == F_counter) {
			SENALES_SALIDA_DAC(sen[sen_counter]);
			sen_counter++;
			F_counter = LOW;
		} else {
			F_counter++;
		}
	} else {
		if (REP_TOP == F_counter) {
			sen_counter = LOW;
			SENALES_SALIDA_DAC(sen[sen_counter]);
			F_counter = LOW;
		} else {
			F_counter++;
		}

	}
	PIT_clear1_interrupt_flag();

}

void SENALES_TRIANGULAR() {
	//LED externo
	RGB_estado3(GPIO_D, bit_1, GPIO_D, bit_3);

	if (SENAL_ON == flag_senal) {
		if (sen_counter <= 99) {
			SENALES_SALIDA_DAC(trg[sen_counter]);
			sen_counter++;
		} else {
			SENALES_SALIDA_DAC(trg[sen_counter]);
			flag_senal = SENAL_OFF;
		}
	} else {
		if (sen_counter > 0) {
			SENALES_SALIDA_DAC(trg[sen_counter]);
			sen_counter--;
		} else {
			SENALES_SALIDA_DAC(trg[sen_counter]);
			flag_senal = SENAL_ON;
			sen_counter++;
		}
	}

	PIT_clear1_interrupt_flag();

}
/*
void SENALES_fun_1_3(sw_status SW) {
	if (TRUE == PIT_get1_interrupt_flag_status()) {
		if (SW1 == SW) {
			SENALES_CUADRADA();
		} else if (SW2 == SW) {
			SENALES_SENOIDAL();
		} else if (SW3 == SW) {
			SENALES_TRIANGULAR();
		}
	}
}
*/

void SENALES_DAC_config() {
	//Configuración de clock;
	SIM->SCGC2 = 0x1000;
	//Configuración DAC
	DAC0->C0 = 0xC0;
	DAC0->DAT[0].DATL = 0;
	DAC0->DAT[0].DATH = 0;
}

void SENALES_SALIDA_DAC(uint32_t Salida) {
	uint8_t SalidaL;
	uint8_t SalidaH;
	SalidaL = (uint16_t) Salida & 0xFF;
	SalidaH = (uint16_t) ((Salida >> 8) & 0x0F);
	DAC0->DAT[0].DATL = SalidaL;
	DAC0->DAT[0].DATH = SalidaH;
}

