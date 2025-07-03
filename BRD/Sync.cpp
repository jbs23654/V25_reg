/*
 * Sync.cpp
 *
 *  Created on: Jun 26, 2025
 *      Author: Jakub
 */

#include "Sync.h"

Sync::Sync()
{
  // TODO Auto-generated constructor stub

}

Sync::~Sync()
{
  // TODO Auto-generated destructor stub
}

void Sync::Sync_init()
{
  GPIOB->MODER &= ~(0b01 << GPIO_MODER_MODE7_Pos);
  GPIOB->AFR[0] |= 0b1010 << GPIO_AFRL_AFSEL7_Pos; //af10

  TIM16->CCMR1 = TIM_CCMR1_OC1M_1 | TIM_CCMR1_OC1M_2 | TIM_CCMR1_OC1FE
      | TIM_CCMR1_OC1PE;
  //TIM3->PSC |= 0x00 <<TIM_PSC_PSC_Pos; //ustawienie czestetliwosci, 48MHz /( PSC * 1000)
  TIM16->ARR = arr;
  TIM16->CCR1 = 0;
  TIM16->CCER |= TIM_CCER_CC1E; // wlaczenie kanalu
  TIM16->BDTR |= TIM_BDTR_MOE;
  TIM16->EGR = TIM_EGR_UG;

  TIM16->CR1 = TIM_CR1_CEN;
}

void Sync::setup(int freq)
{
  psc = 0;

  auto t_arr = (48'000'000 / ((psc + 1) * freq)) - 1;

  while (arr > 65536)
  {
    t_arr = (48 / (psc + 1)) - 1;
    psc++;

  }
  arr = t_arr;

}

void Sync::start()
{
  TIM16->ARR = arr;
  TIM16->PSC = psc;
  //TIM16->CCR1 = arr / 2;


}
