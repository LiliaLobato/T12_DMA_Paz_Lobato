/*
 * DMA.h
 *
 *  Created on: 05/05/2019
 *      Author: best buy
 */

#ifndef DMA_H_
#define DMA_H_

#include "MK64F12.h"
#include "NVIC.h"
#include "GPIO.h"
#include "Bits.h"

#define CHANGE
#define GEN

#define SYSTEM_CLOCK (21000000U)
#ifdef CHANGE
#define DELAYTRG (0.000005F)//(0.0000045F) //DELAY maximo, despues empieza a deformar la senoidal
#else
#define DELAYTRG (0.000004F) //Delay para 5KHz exactos, no funciona el callback
#endif
#define NUM_STEPS (1u)
#define NUM_STEPS_HALF (2u)

#define ARRAY_SIZE (16u)
#define GEN_SIZE 100u

#define DMA_CH0 (0x01u)
#define DMA_SOURCE_GPIO (51u)
#define DMA_SOURCE_ALWAYS_ENABLE (0b111010)


#define DMA_COMPLETE_ARRAY_SOFF 1
#define DMA_COMPLETE_ARRAY_DOFF 1
#define DMA_HALF_ARRAY_SOFF 1
#define DMA_HALF_ARRAY_DOFF 1
#define DMA_ODD_ARRAY_SOFF 4
#define DMA_ODD_ARRAY_DOFF 1
#define DMA_2_ARRAY_SOFF 2
#define DMA_1_ARRAY_DOFF 1
#define DMA_COMPLETE_ARRAY_NBYTES_MLNO 32
#define DMA_HALF_ARRAY_NBYTES_MLNO 16
#define DMA_ODD_ARRAY_NBYTES_MLNO 6
#define DMA_2_NBYTES_MLNO 2
#define DMA_SSIZE_MUX_8_BITS 0b000
#define DMA_SSIZE_MUX_16_BITS 0b001
#define DMA_SLAST_32 32
#define DMA_DLAST_32 32
#define DMA_SLAST_20 20
#define DMA_DLAST_2 2

void DMA_clock_gating(void);

void DMA_init_completeArray(void);

void DMA_init_halfArray(void);

void DMA_init_oddArray(void);

void DMA_init(void);

#endif /* DMA_H_ */
