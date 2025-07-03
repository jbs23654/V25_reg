/*
 * DMA.cpp
 *
 *  Created on: May 16, 2025
 *      Author: KRIS
 */

#include "DMA.h"

#include "../MCU/stm32c011xx.h"

DMA::DMA(DMA_MUX mux)
{

	RCC->AHBENR |= RCC_AHBENR_DMA1EN;

	for (chno = 0; chno < CHANNELS; chno++)
	{
		if (DMAMUX1[chno].CCR == 0)
		{
			DMAMUX1[chno].CCR = mux << DMAMUX_CxCR_DMAREQ_ID_Pos;
			chp = &static_cast<Channel*>((void*) DMA1_Channel1_BASE)[chno];
			break;
		}
	}

	while (chno >= CHANNELS);
}

void DMA::mem2per_cir(short* mem, int* per, int len)
{
	chp->ccr = 0;
	DMA1->IFCR = 15U << (4 * chno);
	chp->cndtr = len;
	chp->cpar = (unsigned int) per;
	chp->cmar = (unsigned int) mem;
	chp->ccr = DMA_CCR_MINC | DMA_CCR_DIR | 2 << DMA_CCR_PSIZE_Pos | 1 << DMA_CCR_MSIZE_Pos | DMA_CCR_CIRC;
	chp->ccr |= DMA_CCR_EN;
}

void DMA::per2mem(unsigned char* mem, unsigned char* per, int len)
{
	chp->ccr = 0;
	DMA1->IFCR = 15U << (4 * chno);
	chp->cndtr = len;
	chp->cpar = (unsigned int) per;
	chp->cmar = (unsigned int) mem;
	chp->ccr = DMA_CCR_MINC | 0 << DMA_CCR_PSIZE_Pos | 0 << DMA_CCR_MSIZE_Pos;
	chp->ccr |= DMA_CCR_EN;
}

void DMA::per2mem_cir(short* mem, short* per, int len)
{
	chp->ccr = 0;
	DMA1->IFCR = 15U << (4 * chno);
	chp->cndtr = len;
	chp->cpar = (unsigned int) per;
	chp->cmar = (unsigned int) mem;
	chp->ccr = DMA_CCR_MINC | 1 << DMA_CCR_PSIZE_Pos | 1 << DMA_CCR_MSIZE_Pos | DMA_CCR_CIRC;
	chp->ccr |= DMA_CCR_EN;
}

void DMA::mem2per(unsigned char* mem, unsigned char* per, int len)
{
	chp->ccr = 0;
	DMA1->IFCR = 15U << (4 * chno);
	chp->cndtr = len;
	chp->cpar = (unsigned int) per;
	chp->cmar = (unsigned int) mem;
	chp->ccr = DMA_CCR_MINC | DMA_CCR_DIR | 0 << DMA_CCR_PSIZE_Pos | 0 << DMA_CCR_MSIZE_Pos;
	chp->ccr |= DMA_CCR_EN;
}

void DMA::per2mem(short* mem, short* per, int len)
{
	chp->ccr = 0;
	DMA1->IFCR = 15U << (4 * chno);
	chp->cndtr = len;
	chp->cpar = (unsigned int) per;
	chp->cmar = (unsigned int) mem;
	chp->ccr = DMA_CCR_MINC | 1 << DMA_CCR_PSIZE_Pos | 1 << DMA_CCR_MSIZE_Pos;
	chp->ccr |= DMA_CCR_EN;
}
