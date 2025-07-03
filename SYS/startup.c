/*
 * startup.c
 *
 *  Created on: May 15, 2025
 *      Author: Jakub
 */
#include "../MCU/stm32c011xx.h"
#define VECT_TAB_OFFSET 0
void SystemInit(void)
{

  /* Configure the Vector Table location add offset address ------------------*/
#ifdef VECT_TAB_SRAM
  SCB->VTOR = SRAM_BASE | VECT_TAB_OFFSET; /* Vector Table Relocation in Internal SRAM */
#else
  SCB->VTOR = FLASH_BASE | VECT_TAB_OFFSET; /* Vector Table Relocation in Internal FLASH */
#endif
}


