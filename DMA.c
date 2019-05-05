/*
 * DMA.c
 *
 *  Created on: 05/05/2019
 *      Author: best buy
 */

#include "DMA.h"


uint16_t g_data_source[ARRAY_SIZE] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12,
		13, 14, 15, 16 }; //defines source data space
uint16_t g_data_desti[4 * ARRAY_SIZE]; //defines destination data space

uint8_t sw = 1;

//Array para la triangular
static uint16_t trg[GEN_SIZE] = { 3, 74, 148, 222, 296, 370, 444, 592, 629, 703,
		777, 851, 925, 999, 1073, 1147, 1221, 1295, 1369, 1443, 1517, 1591,
		1665, 1739, 1813, 1887, 1961, 2035, 2109, 2183, 2257, 2331, 2405, 2479,
		2553, 2627, 2701,  2775, 2849, 2923, 2997, 3071, 3145, 3219, 3293, 3367,
		3441, 3515, 3589, 3663, 3700, 3663, 3626, 3478, 3404, 3330, 3256, 3182,
		3108, 3034, 2960, 2886, 2812, 2738, 2664, 2590, 2516, 2442, 2368, 2294,
		2220, 2146, 2072, 1998, 1924, 1850, 1776, 1702, 1628, 1554, 1480, 1406,
		1332, 1258, 1184, 1110, 1036, 962, 888, 814, 740, 666, 592, 518, 444,
		370, 296, 222, 74, 3 };
//Array para el sen
static uint16_t sen[GEN_SIZE] = { 1850, 1966, 2082, 2197, 2310, 2422, 2531,
		2638, 2741, 2841, 2937, 3029, 3116, 3199, 3275, 3347, 3412, 3471, 3524,
		3570, 3609, 3642, 3667, 3685, 3696, 3700, 3696, 3685, 3667, 3642, 3609,
		3570, 3524, 3471, 3412, 3347, 3275, 3199, 3116, 3029, 2937, 2841, 2741,
		2638, 2531, 2422, 2310, 2197, 2082, 1966, 1850, 1734, 1618, 1503, 1390,
		1278, 1169, 1062, 959, 859, 763, 671, 584, 501, 425, 353, 288, 229, 176,
		130, 91, 58, 33, 15, 4, 0, 4, 15, 33, 58, 91, 130, 176, 229, 288, 353,
		425, 501, 584, 671, 763, 859, 959, 1062, 1169, 1278, 1390, 1503, 1618,
		1734};
//Array para el sqr
static uint16_t sqr[GEN_SIZE] = { 3570, 3570, 3570, 3570, 3570, 3570, 3570,
		3570, 3570, 3570, 3570, 3570, 3570, 3570, 3570, 3570, 3570, 3570, 3570,
		3570, 3570, 3570, 3570, 3570, 3570, 3570, 3570, 3570, 3570, 3570, 3570,
		3570, 3570, 3570, 3570, 3570, 3570, 3570, 3570, 3570, 3570, 3570, 3570,
		3570, 3570, 3570, 3570, 3570, 3570, 3570, 3570, 0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};

//Array para el gen
static uint16_t gen[GEN_SIZE];

void DMA0_IRQHandler(void) {

	uint8_t i;

	DMA0->INT = DMA_CH0;

#ifdef GEN
	switch (sw) {
		case 1:
			if (&sen[GEN_SIZE-1] <= DMA0->TCD[0].SADDR) {
					DMA0->TCD[0].SADDR = (uint32_t) (&sen[FALSE]);
				}
			break;
		case 2:
			if (&trg[GEN_SIZE-1] <= DMA0->TCD[0].SADDR) {
					DMA0->TCD[0].SADDR = (uint32_t) (&trg[FALSE]);
				}
			break;
		case 3:
			if (&sqr[GEN_SIZE-1] <= DMA0->TCD[0].SADDR) {
					DMA0->TCD[0].SADDR = (uint32_t) (&sqr[FALSE]);
				}
			break;
		}
#else
	for (i = 0; i <= ARRAY_SIZE; ++i) {
		printf("%d,", g_data_desti[i]);
	}
	printf("\n");
#endif


}

void signal_sequence(void){
	if (3 == sw) {
			sw = 1;
		} else {
			sw++;
		}

		switch (sw) {
		case 1:
			DMA0->TCD[0].SADDR = (uint32_t) (&sen[0]);
			break;
		case 2:
			DMA0->TCD[0].SADDR = (uint32_t) (&trg[0]);
			break;
		case 3:
			DMA0->TCD[0].SADDR = (uint32_t) (&sqr[0]);
			break;
		}
}

void DMA_clock_gating(void) {
	SIM->SCGC7 |= SIM_SCGC7_DMA_MASK;
	SIM->SCGC6 |= SIM_SCGC6_DMAMUX_MASK;
}

void DMA_init_completeArray(void) {

	DMAMUX->CHCFG[0] = 0;
	DMAMUX->CHCFG[0] = DMAMUX_CHCFG_ENBL_MASK | /*enables DMA MUX channel*/
	DMAMUX_CHCFG_SOURCE(DMA_SOURCE_GPIO);/*source is FTM0 channel 0*/

	DMA0->ERQ = DMA_ERQ_ERQ0_MASK; //enables DMA0 request

	DMA0->TCD[0].SADDR = (uint32_t) (&g_data_source[0]);/*defines source data address*/
	DMA0->TCD[0].SOFF = DMA_COMPLETE_ARRAY_SOFF;/*Source address signed offset;it is expressed in number of bytes*/
	DMA0->TCD[0].DADDR = (uint32_t) (&g_data_desti[0]);/*defines destination data address*/
	DMA0->TCD[0].DOFF = DMA_COMPLETE_ARRAY_DOFF;/*destination address signed offset;it is expressed in number of bytes*/
	/*CITER represents the number of minor loops that compose a major loop, every time a minor loop is completed CITTER is decremented by one.
	 * Once CITTER is 0 the DMA copy BITTER into CITTER and adjust SADDR and DADDR with the values specified in SLAST and DLAST_SGA respectively
	 *  SADDR  = SADDR + SLAST and DADDR + DLAST_SGA*/
	DMA0->TCD[0].CITER_ELINKNO = DMA_CITER_ELINKNO_CITER(NUM_STEPS);
	/* Once a major loop is completed, BITTER is copy to CITTER*/
	DMA0->TCD[0].BITER_ELINKNO = DMA_BITER_ELINKNO_BITER(NUM_STEPS);
	DMA0->TCD[0].NBYTES_MLNO = DMA_COMPLETE_ARRAY_NBYTES_MLNO;/*byte number*/

	DMA0->TCD[0].ATTR = 0x000 | DMA_ATTR_SSIZE(DMA_SSIZE_MUX_8_BITS);/*8 bit transfer size, in order to transfer see Kinetis user manual*/
	DMA0->TCD[0].SLAST = -DMA_SLAST_32; //restores the source address to the initial value, which is expressed in the amount of bytes to restore*/
	DMA0->TCD[0].DLAST_SGA = -DMA_DLAST_32;/*restores the destination address to the initial value, which is expressed in the amount of bytes to restore*/
	DMA0->TCD[0].CSR = DMA_CSR_INTMAJOR_MASK;/*The end-of-major loop interrupt is enabled*/
}

void DMA_init_halfArray(void) {

	DMAMUX->CHCFG[0] = 0;
	DMAMUX->CHCFG[0] = DMAMUX_CHCFG_ENBL_MASK | /*enables DMA MUX channel*/
	DMAMUX_CHCFG_SOURCE(DMA_SOURCE_GPIO);/*source is FTM0 channel 0*/

	DMA0->ERQ = DMA_ERQ_ERQ0_MASK; //enables DMA0 request

	DMA0->TCD[0].SADDR = (uint32_t) (&g_data_source[0]);/*defines source data address*/
	DMA0->TCD[0].SOFF = DMA_HALF_ARRAY_SOFF;/*Source address signed offset;it is expressed in number of bytes*/
	DMA0->TCD[0].DADDR = (uint32_t) (&g_data_desti[0]);/*defines destination data address*/
	DMA0->TCD[0].DOFF = DMA_HALF_ARRAY_DOFF;/*destination address signed offset;it is expressed in number of bytes*/
	/*CITER represents the number of minor loops that compose a major loop, every time a minor loop is completed CITTER is decremented by one.
	 * Once CITTER is 0 the DMA copy BITTER into CITTER and adjust SADDR and DADDR with the values specified in SLAST and DLAST_SGA respectively
	 *  SADDR  = SADDR + SLAST and DADDR + DLAST_SGA*/
	DMA0->TCD[0].CITER_ELINKNO = DMA_CITER_ELINKNO_CITER(NUM_STEPS_HALF);
	/* Once a major loop is completed, BITTER is copy to CITTER*/
	DMA0->TCD[0].BITER_ELINKNO = DMA_BITER_ELINKNO_BITER(NUM_STEPS_HALF);
	DMA0->TCD[0].NBYTES_MLNO = DMA_HALF_ARRAY_NBYTES_MLNO;/*byte number*/

	DMA0->TCD[0].ATTR = 0x000 | DMA_ATTR_SSIZE(DMA_SSIZE_MUX_8_BITS);/*8 bit transfer size, in order to transfer see Kinetis user manual*/
	DMA0->TCD[0].SLAST = -DMA_SLAST_32; //restores the source address to the initial value, which is expressed in the amount of bytes to restore*/
	DMA0->TCD[0].DLAST_SGA = -DMA_DLAST_32;/*restores the destination address to the initial value, which is expressed in the amount of bytes to restore*/
	DMA0->TCD[0].CSR = DMA_CSR_INTMAJOR_MASK;/*The end-of-major loop interrupt is enabled*/
}

void DMA_init_oddArray(void) {

	DMAMUX->CHCFG[0] = 0;
	DMAMUX->CHCFG[0] = DMAMUX_CHCFG_ENBL_MASK | /*enables DMA MUX channel*/
	DMAMUX_CHCFG_SOURCE(DMA_SOURCE_GPIO);/*source is FTM0 channel 0*/

	DMA0->ERQ = DMA_ERQ_ERQ0_MASK; //enables DMA0 request

	DMA0->TCD[0].SADDR = (uint32_t) (&g_data_source[4]);/*defines source data address*/
	DMA0->TCD[0].SOFF = DMA_ODD_ARRAY_SOFF;/*Source address signed offset;it is expressed in number of bytes*/
	DMA0->TCD[0].DADDR = (uint32_t) (&g_data_desti[0]);/*defines destination data address*/
	DMA0->TCD[0].DOFF = DMA_ODD_ARRAY_DOFF;/*destination address signed offset;it is expressed in number of bytes*/
	/*CITER represents the number of minor loops that compose a major loop, every time a minor loop is completed CITTER is decremented by one.
	 * Once CITTER is 0 the DMA copy BITTER into CITTER and adjust SADDR and DADDR with the values specified in SLAST and DLAST_SGA respectively
	 *  SADDR  = SADDR + SLAST and DADDR + DLAST_SGA*/
	DMA0->TCD[0].CITER_ELINKNO = DMA_CITER_ELINKNO_CITER(NUM_STEPS);
	/* Once a major loop is completed, BITTER is copy to CITTER*/
	DMA0->TCD[0].BITER_ELINKNO = DMA_BITER_ELINKNO_BITER(NUM_STEPS);
	DMA0->TCD[0].NBYTES_MLNO = DMA_ODD_ARRAY_NBYTES_MLNO;/*byte number*/

	DMA0->TCD[0].ATTR = 0x000 | DMA_ATTR_SSIZE(DMA_SSIZE_MUX_16_BITS);/*16 bit transfer size, in order to transfer see Kinetis user manual*/
	DMA0->TCD[0].SLAST = -DMA_SLAST_20; //restores the source address to the initial value, which is expressed in the amount of bytes to restore*/
	DMA0->TCD[0].DLAST_SGA = 0;/*restores the destination address to the initial value, which is expressed in the amount of bytes to restore*/
	DMA0->TCD[0].CSR = DMA_CSR_INTMAJOR_MASK;/*The end-of-major loop interrupt is enabled*/
}

void DMA_init(void) {

	DMAMUX->CHCFG[0] = 0;
	DMAMUX->CHCFG[0] = DMAMUX_CHCFG_ENBL_MASK | /*enables DMA MUX channel*/
	DMAMUX_CHCFG_SOURCE(DMA_SOURCE_ALWAYS_ENABLE) | DMAMUX_CHCFG_TRIG(1);/*source is FTM0 channel 0*/

	DMA0->ERQ = DMA_ERQ_ERQ0_MASK; //enables DMA0 request

	DMA0->TCD[0].SADDR = (uint32_t) (&sqr[0]);/*defines source data address*/
	DMA0->TCD[0].SOFF = DMA_2_ARRAY_SOFF;/*Source address signed offset;it is expressed in number of bytes*/
	DMA0->TCD[0].DADDR = (uint32_t) (&DAC0->DAT[0].DATL);/*defines destination data address*/
	DMA0->TCD[0].DOFF = DMA_1_ARRAY_DOFF;/*destination address signed offset;it is expressed in number of bytes*/
	/*CITER represents the number of minor loops that compose a major loop, every time a minor loop is completed CITTER is decremented by one.
	 * Once CITTER is 0 the DMA copy BITTER into CITTER and adjust SADDR and DADDR with the values specified in SLAST and DLAST_SGA respectively
	 *  SADDR  = SADDR + SLAST and DADDR + DLAST_SGA*/
	DMA0->TCD[0].CITER_ELINKNO = DMA_CITER_ELINKNO_CITER(NUM_STEPS);
	/* Once a major loop is completed, BITTER is copy to CITTER*/
	DMA0->TCD[0].BITER_ELINKNO = DMA_BITER_ELINKNO_BITER(NUM_STEPS);
	DMA0->TCD[0].NBYTES_MLNO = DMA_2_NBYTES_MLNO;/*byte number*/

	DMA0->TCD[0].ATTR = 0x000 | DMA_ATTR_SSIZE(DMA_SSIZE_MUX_16_BITS);/*16 bit transfer size, in order to transfer see Kinetis user manual*/
	DMA0->TCD[0].SLAST = 0; //restores the source address to the initial value, which is expressed in the amount of bytes to restore*/
	DMA0->TCD[0].DLAST_SGA = -DMA_DLAST_2;/*restores the destination address to the initial value, which is expressed in the amount of bytes to restore*/
	DMA0->TCD[0].CSR = DMA_CSR_INTMAJOR_MASK;/*The end-of-major loop interrupt is enabled*/
}
