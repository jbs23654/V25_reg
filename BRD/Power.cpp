/*
 * Power.cpp
 *
 *  Created on: May 16, 2025
 *      Author: Jakub
 */

#include "Power.h"
#include "../MCU/stm32c011xx.h"

Power::Power()
{
  // TODO Auto-generated constructor stub

}

Power::~Power()
{
  // TODO Auto-generated destructor stub
}

void Power::init()
{

  GPIOA->MODER &= ~(0b01 << GPIO_MODER_MODE5_Pos);
  GPIOA->AFR[0] |= 0b101 << GPIO_AFRL_AFSEL5_Pos;

  TIM1->CCMR1 = TIM_CCMR1_OC1M_1 | TIM_CCMR1_OC1M_2 | TIM_CCMR1_OC1PE
      | TIM_CCMR1_OC1FE;
  //TIM1->PSC |= 0x00 <<TIM_PSC_PSC_Pos; //ustawienie czestetliwosci, 48MHz /( PSC * 1000)
  TIM1->ARR = 999;
  TIM1->CCER |= TIM_CCER_CC1E; // wlaczenie kanalu

  TIM1->BDTR |= TIM_BDTR_MOE;
  TIM1->CR1 |= TIM_CR1_CEN;
  TIM1->EGR = TIM_EGR_UG;

}

void Power::setup(int promils)
{

  if (promils < 999)
  {
    if (promils > 0)
    {
      TIM1->CCR1 = promils;

    }
    else
    {
      promils = 0;
    }
  }
  else
  {

    promils = 999;

  }
}
