/*
 * Clock.cpp
 *
 *  Created on: May 16, 2025
 *      Author: Jakub
 */
#include "Clock.h"
#include "../MCU/stm32c011xx.h"

void Clock_Init()
{

  RCC->APBENR1 |= RCC_APBENR1_PWREN;
  FLASH->ACR |= 1 << FLASH_ACR_LATENCY_Pos;

  RCC->CR = RCC_CR_HSEON;
  while ((RCC->CR & RCC_CR_HSERDY) == 0);

  // Freq set

  RCC->CFGR |= (1UL << RCC_CFGR_SW_Pos);
  while ((RCC->CFGR & RCC_CFGR_SWS) != RCC_CFGR_SWS_HSE);

  RCC->CR &= ~(RCC_CR_HSION_Msk);

  // Clock enable
  RCC->IOPENR |= RCC_IOPENR_GPIOAEN;
  RCC->IOPENR |= RCC_IOPENR_GPIOBEN;
  RCC->APBENR1 |= RCC_APBENR1_TIM3EN;
  RCC->APBENR2 |= RCC_APBENR2_TIM1EN;
  RCC->APBENR2 |= RCC_APBENR2_TIM16EN;

  //GPIO SET
  GPIOA->MODER &= ~GPIO_MODER_MODE2_Msk;
  GPIOA->MODER |= 0b01 << GPIO_MODER_MODE2_Pos;
  GPIOA->MODER &= ~GPIO_MODER_MODE3_Msk;
  GPIOA->MODER |= 0b01 << GPIO_MODER_MODE3_Pos;
  GPIOA->MODER &= ~GPIO_MODER_MODE4_Msk;
  GPIOA->MODER |= 0b01 << GPIO_MODER_MODE4_Pos;
  //
  SysTick->LOAD = 48000UL - 1;
  SysTick->CTRL = SysTick_CTRL_ENABLE_Msk |
#ifdef SLEEPING_ENABLE

      SysTick_CTRL_TICKINT_Msk |
#endif
      SysTick_CTRL_CLKSOURCE_Msk;

  DELAY_MS(50);

}

