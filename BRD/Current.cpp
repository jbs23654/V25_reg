/*
 * Current.cpp
 *
 *  Created on: Jul 3, 2025
 *      Author: Jakub
 */

#include <Current.h>

Current::Current()
{
  // TODO Auto-generated constructor stub

}

Current::~Current()
{
  // TODO Auto-generated destructor stub
}

void Current::init()
{
  RCC->APBENR2 = RCC_APBENR2_ADCEN;
  GPIOA->MODER &= ~GPIO_MODER_MODE0_Msk;
  GPIOA->MODER |= GPIO_MODER_MODE0_1 | GPIO_MODER_MODE0_0;
  GPIOA->AFR[0] |= GPIO_AFRL_AFSEL0;
  RCC->CCIPR |= 2U << RCC_CCIPR_ADCSEL_Pos;

  ADC->CCR |= ADC_CCR_PRESC_0;
  ADC1->CR |= ADC_CR_ADVREGEN;


  ADC1->CR |= ADC_CR_ADCAL;
  while (ADC1->CR & ADC_CR_ADCAL);

  //calibration//
  ADC1->CFGR1 |= ADC_CFGR1_CONT ;
  ADC1->CHSELR |= ADC_CHSELR_CHSEL0;
  //end of calibration//
  ADC1->CR &= ~ADC_CR_ADCAL;
    while(! (ADC1->CR & ADC_CR_ADCAL));
  ADC1->CR |= ADC_CR_ADSTART;
}

void Current::measure()
{
  ADC1->CR |= ADC_CR_ADEN;
  while(ADC1->CR & ADC_CR_ADEN);
  ADC1->ISR = ADC_ISR_OVR;

  ADC

}
