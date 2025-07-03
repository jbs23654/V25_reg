/*
 * main.cpp
 *
 *  Created on: May 15, 2025
 *      Author: Jakub
 */
#include "../CODE/MCU/stm32c011xx.h"
#include "../CODE/BRD/Clock.h"
#include "../CODE/BRD/Modulation.h"
#include "../CODE/BRD/Power.h"
#include "../CODE/BRD/Com.h"
#include "../CODE/BRD/Sync.h"
#include "../CODE/BRD/Status.h"



void loop_delay();

class Ledzik
{
    int cnt = 0;
  public:
    void operator()()
    {
      if (++cnt == 1000)
      {
	cnt = 0;
	GPIOA->ODR ^= 1 << 5;
      }
    }
};

Ledzik ledzik;
int main(void)
{


  //Ledzik ledzik;
  SysTick_Config (48000000U);
  Clock_Init ();
  power.init ();
  mod.init ();
  sync.Sync_init();
  //int pulse = 1'000'000;
  //int pause = 0;
  //com.Tramsmit("test");
  lasreg.select(1, 0);
  lasreg.current_set(600);
  lasreg.modulation_set(0, 0);
  sync.setup(222'000);
  sync.start();
  while (1)
  {
    loop_delay ();
    com.RX_data ();

    if (lasreg.is_working () && (lasreg.work == false) && (status.state == Status::State::ready))
    {
      lasreg.start ();

    }
    else if (!lasreg.is_working () && (lasreg.work == true) && (status.state == Status::State::works))
    {
      lasreg.stop ();
    }
    com.Tramsmit("test");

    /*if (!modulation.is_working () && modulation.is_pulse_done ())
     {
     modulation.stop ();
     }
     if (modulation.is_working () && modulation.work == false)
     {

     modulation.standby (pulse, pause);

     for (int i = 0; i < 1000; i++);

     }
     */

  }
  return 0;
}

void loop_delay()
{
  while ((SysTick->CTRL & SysTick_CTRL_COUNTFLAG_Msk) == 0);

}

