/*
 * Com.h
 *
 *  Created on: May 27, 2025
 *      Author: Jakub
 */

#ifndef BRD_COM_H_
#define BRD_COM_H_

#include <cstring>

#include "stm32c011xx.h"
#include "LasReg.h"
#include "DMA.h"
#include "Sync.h"
#include "Status.h"

class Com
{
    static constexpr int buffer_size = 64;
    static constexpr int Baud = 115'200;

    unsigned char data_tx[buffer_size];
    unsigned char data_rx[buffer_size];

    int to_send;
    int in_counter;
    int out_index;
    int pre_rx_len;
    int out_time;

    USART_TypeDef &usart;
    DMA rxdma;
    DMA txdma;
    void restart_Rx_DMA()
    {
      rxdma.per2mem (data_rx, (unsigned char*) &usart.RDR, sizeof(data_rx));
    }
  public:
    Com() : usart (*USART2), rxdma (DMA_MUX::USART2_RX), txdma (DMA_MUX::USART2_TX)
    {
      RCC->APBENR1 |= RCC_APBENR1_USART2EN;
      RCC->IOPENR |= RCC_IOPENR_GPIOAEN;

      restart_Rx_DMA ();

      GPIOA->MODER &= ~GPIO_MODER_MODE8_Msk;
      GPIOA->MODER |= 0b10 << GPIO_MODER_MODE8_Pos;

      GPIOA->OTYPER |= GPIO_OTYPER_OT8;
      GPIOA->AFR[1] &= GPIO_AFRH_AFSEL8_Msk;
      GPIOA->AFR[1] |= 1 << GPIO_AFRH_AFSEL8_Pos;

      usart.CR1 = 0;
      usart.BRR = 48'000'000 / Baud;
      usart.CR3 = USART_CR3_HDSEL | USART_CR3_DMAR | USART_CR3_DMAT;
      usart.CR1 = USART_CR1_TE | USART_CR1_RE;
      usart.CR1 |= USART_CR1_UE;
    }

    enum class Command : unsigned short
    {
      nottthing, setpwr = 128, setmod, las_select, setsync,
    };
    Command cmd = Command::nottthing;


    class Header
    {
      public:
	Command cmd;
	unsigned char len;
	unsigned char crc;

	bool is_crc_ok(unsigned int rec_len)
	{
	  if (rec_len < sizeof(Header)) return false;

	  unsigned char res = 0;
	  unsigned char *d = (unsigned char*) this;

	  for (unsigned int i = 0; i < rec_len; i++)
	  {
	    res ^= d[i];
	  }

	  return res == 0;
	}
    };
    class Frame
    {
      public:
	Header header;
	char data[buffer_size - sizeof(Header)];

	bool is_len_ok(int rec_len)
	{
	  return header.len == rec_len;
	}
    };

    Frame frame;
    class Frame_power
    {
      public:
	Header header;
	unsigned short power;

    };
    Frame_power f_power;
    class Frame_modulation
    {
      public:
	Header header;
	unsigned int pulse;
	unsigned int pause;
    };
    Frame_modulation f_mod;
    class Frame_select
    {
      public:
	Header header;
	unsigned char laserA;
	unsigned char laserB;
    };
    Frame_select f_select;

    class Frame_sync
    {
      public:
	Header header;
	unsigned int freq;
    };
    Frame_sync f_sync;
    class Frame_state
          {
            public:
   	Header header;
      	unsigned char status;
          };

       Frame_state f_state;
    void RX_data();
    void Tramsmit(const void *src, int len);
    void Tramsmit(const char *txt);



    int operator()();
    void restartRec()
    {
      restart_Rx_DMA ();
      usart.ICR = USART_ICR_RTOCF;
    }

    template<class T>
      T* getData()
      {
	return (T*) data_rx;
      }
};
Com inline com;
#endif /* BRD_COM_H_ */
