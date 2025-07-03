/*
 * LasReg.cpp
 *
 *  Created on: Jun 23, 2025
 *      Author: jsobo
 */

#include <LasReg.h>
#include "stm32c011xx.h"

LasReg::LasReg()
{
  // TODO Auto-generated constructor stub

}

LasReg::~LasReg()
{
  // TODO Auto-generated destructor stub
}

void LasReg::current_set(int current)
{
  power.setup (current);
}

void LasReg::modulation_set(int pulse_us, int pause_us)
{
  mod.standby (pulse_us, pause_us);
}

void LasReg::select(unsigned char laserA, unsigned char laserB)
{
  (laserA == 1 ? GPIOA->BSRR : GPIOA->BRR) = 1 << 2;
  (laserB == 1 ? GPIOA->BSRR : GPIOA->BRR) = 1 << 3;
}

void LasReg::start()
{
  GPIOA->BSRR = 1 << 4;
  work = true;

  switch (mod.mode)
  {

    case Modulation::Mode::imp:
    {

      TIM3->CCMR1 &= ~(TIM_CCMR1_OC1M_Msk);
      TIM3->CCMR1 |= (0b110 << TIM_CCMR1_OC1M_Pos);
      break;
    }
    case Modulation::Mode::one:
    {
      TIM3->CCMR1 &= TIM_CCMR1_OC1M_Msk;
      TIM3->CCMR1 |= (7U << TIM_CCMR1_OC1M_Pos);

      TIM3->CR1 |= TIM_CR1_OPM;
      TIM3->CR1 |= TIM_CR1_ARPE;
      break;
    }
    case Modulation::Mode::con:
    {

      TIM3->CCMR1 &= ~(TIM_CCMR1_OC1M_Msk);
      TIM3->CCMR1 |= (0b110 << TIM_CCMR1_OC1M_Pos);

    }
    default:
      break;
  }

  TIM3->EGR = TIM_EGR_UG;
  TIM3->CR1 |= TIM_CR1_CEN;
}

void LasReg::stop()
{
  GPIOA->BRR = 1 << 4;
  work = false;

  TIM3->CCMR1 &= ~(TIM_CCMR1_OC1M_Msk);
  TIM3->CCMR1 |= (0b100 << TIM_CCMR1_OC1M_Pos);
  TIM3->CR1 &= ~TIM_CR1_OPM;
  TIM3->CR1 &= ~TIM_CR1_ARPE;

  TIM3->EGR = TIM_EGR_UG;
  TIM3->CR1 &= ~TIM_CR1_CEN;

}

bool LasReg::is_working()
{
  bool button_presed = GPIOA->IDR & GPIO_IDR_ID12 ? true : false;

  return button_presed;
}
