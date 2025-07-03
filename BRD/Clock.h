/*
 * Clock.h
 *
 *  Created on: May 16, 2025
 *      Author: Jakub
 */

#ifndef BRD_CLOCK_H_
#define BRD_CLOCK_H_

#define DELAY_MS(t) for (int i=0; i<t; i++) while (!(SysTick->CTRL & SysTick_CTRL_COUNTFLAG_Msk))


void Clock_Init();



#endif /* BRD_CLOCK_H_ */
