/*
 * Modulation.cpp
 *
 *  Created on: May 16, 2025
 *      Author: Jakub
 */

#include "Modulation.h"
#include "../MCU/stm32c011xx.h"
Modulation::Modulation()
{
  // TODO Auto-generated constructor stub

}

Modulation::~Modulation()
{
  // TODO Auto-generated destructor stub
}

void Modulation::init()
{
  GPIOA->MODER &= ~(0b01 << GPIO_MODER_MODE6_Pos);
  GPIOA->AFR[0] |= 0b1 << GPIO_AFRL_AFSEL6_Pos;

  GPIOA->MODER &= ~(GPIO_MODER_MODE12_Msk); // PA12 input for start

  TIM3->CCMR1 = TIM_CCMR1_OC1M_1 | TIM_CCMR1_OC1M_2 | TIM_CCMR1_OC1FE
      | TIM_CCMR1_OC1PE;
  //TIM3->PSC |= 0x00 <<TIM_PSC_PSC_Pos; //ustawienie czestetliwosci, 48MHz /( PSC * 1000)
  TIM3->ARR = arr;
  TIM3->CCER |= TIM_CCER_CC1E; // wlaczenie kanalu
  //TIM3->BDTR |= TIM_BDTR_MOE;
  TIM3->EGR = TIM_EGR_UG;
}

void Modulation::setup(int pulse_us, int pause_us)
{
  psc = 0;

  arr = (48 * (pulse_us + pause_us) / (psc + 1)) - 1;

  while (arr > 65536)
  {
    arr = (48 * (pulse_us + pause_us) / (psc + 1)) - 1;
    psc++;

  }
  duty = 100 * pulse_us;
  duty /= (pulse_us + pause_us);
  duty *= (arr + 1) / 100;

  if (duty < arr)
  {
    if (duty > 0)
    {

    }
    else
    {
      duty = 0;
    }
  }
  else
  {

    duty = 999;

  }

}

void Modulation::setup(int pulse_us)
{
  int pause_us = 100;
  psc = 0;
  arr = (48 * (pulse_us + pause_us) / (psc + 1)) - 1;
  while (arr > 65536)
  {
    arr = (48 * (pulse_us + pause_us) / (psc + 1)) - 1;
    psc++;

  }

  duty = 100 *  pulse_us;
  duty /= (pulse_us + pause_us);
  duty *= (arr + 1) / 100;
  duty = arr - duty;

  TIM3->CCMR1 &= TIM_CCMR1_OC1M_Msk;
  TIM3->CCMR1 |= (7U << TIM_CCMR1_OC1M_Pos);

  TIM3->CR1 |= TIM_CR1_OPM;
  TIM3->CR1 |= TIM_CR1_ARPE;
  TIM3->EGR = TIM_EGR_UG;

}

void Modulation::setup()
{
  psc = 0;
  duty = 999;
  arr = 999;

}

void Modulation::standby(int pulse_us, int pause_us)
{
  if (pulse_us == 0 && pause_us == 0)
  {
    mode = Mode::con;
  }
  if (pulse_us > 0 && pause_us == 0)
  {
    mode = Mode::one;
  }
  if (pulse_us > 0 && pause_us > 0)
  {
    mode = Mode::imp;
  }

  switch (mode)
  {
    case Mode::off:
    {
      stop ();
      break;
    }
    case Mode::one:
    {
      setup (pulse_us);
      TIM3->SR = 0;
      TIM3->CCR1 = duty;
      TIM3->ARR = arr;
      TIM3->PSC = psc;



    }
      break;
    case Mode::imp:
    {

      setup (pulse_us, pause_us);

      TIM3->CNT = 0;
      TIM3->PSC = psc;
      TIM3->ARR = arr;
      TIM3->CCR1 = duty;


    }
      break;
    case Mode::con:
    {
      setup ();

      TIM3->CNT = 0;
      TIM3->PSC = psc;
      TIM3->ARR = arr;
      TIM3->CCR1 = duty;




    }
      break;
    default:
      break;
  }

  TIM3->CCMR1 &= ~(TIM_CCMR1_OC1M_Msk);
  TIM3->CCMR1 |= (0b100 << TIM_CCMR1_OC1M_Pos);
  TIM3->EGR = TIM_EGR_UG;

}

void Modulation::test(int promils)
{
  if (promils < 999)
  {
    if (promils > 0)
    {
      duty = promils;

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

bool Modulation::is_working()
{
  bool button_presed = GPIOA->IDR & GPIO_IDR_ID12 ? 0 : 1;

  return button_presed;
}

void Modulation::stop()
{

  TIM3->CCMR1 &= ~(TIM_CCMR1_OC1M_Msk);
  TIM3->CCMR1 |= (0b100 << TIM_CCMR1_OC1M_Pos);
  TIM3->CR1 &= ~TIM_CR1_OPM;
  TIM3->CR1 &= ~TIM_CR1_ARPE;

  TIM3->EGR = TIM_EGR_UG;
  TIM3->CR1 &= ~TIM_CR1_CEN;

  mode = Mode::off;

}

bool Modulation::is_pulse_done()
{
  return TIM3->SR & TIM_SR_CC1IF;
}



