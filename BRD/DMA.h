/*
 * DMA.h
 *
 *  Created on: May 16, 2025
 *      Author: KRIS
 */

#pragma once

enum class DMA_MUX
{
	USART2_RX = 52,
	USART2_TX = 53,
};

inline int operator<<(DMA_MUX mux, int sw)
{
	return static_cast<int>(mux) << sw;
}

class DMA
{
	static constexpr int CHANNELS = 3;
	int chno;
public:

	struct Channel
	{
		volatile unsigned int ccr;
		volatile unsigned int cndtr;
		volatile unsigned int cpar;
		volatile unsigned int cmar;
		int reserved;
	};

	DMA(DMA_MUX mux);

	void per2mem_cir(short* mem, short* per, int len);
	void mem2per_cir(short* mem, int* per, int len);
	void per2mem(short* mem, short* per, int len);
	void per2mem(unsigned char* mem, unsigned char* per, int len);
	void mem2per(unsigned char* mem, unsigned char* per, int len);

	int counter()
	{
		return chp->cndtr;
	}

private:
	Channel* chp;
};
