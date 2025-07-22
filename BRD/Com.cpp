/*
 * Com.cpp
 *
 *  Created on: May 27, 2025
 *      Author: Jakub
 */
#include "Com.h"

void Com::RX_data()
{
//send status
  //status.to_send ();
  //Tramsmit (&status.f_state, sizeof(status.f_state));

  //send check command

  int tr = com ();

  if (tr > 0)
  {
    auto frame = com.getData<Frame> ();

    if (frame->is_len_ok (tr))
    {
      switch (frame->header.cmd)
      {
	case Command::nottthing:
	{

	}
	case Command::setpwr:
	{
	  auto frame_power = com.getData<Frame_power> ();

	  lasreg.current_set (frame_power->power);

	  Tramsmit (frame_power, sizeof(frame_power));
	  break;
	}
	case Command::setmod:
	{
	  auto frame_mod = com.getData<Frame_modulation> ();

	  lasreg.modulation_set (frame_mod->pulse, frame_mod->pause);

	  Tramsmit (frame_mod, sizeof(frame_mod));

	  break;
	}
	case Command::las_select:
	{
	  auto frame_select = com.getData<Frame_select> ();

	  lasreg.select (frame_select->laserA, frame_select->laserB);
	  Tramsmit (frame_select, sizeof(frame_select));

	  break;
	}
	case Command::setsync:
	{
	  auto frame_sync = com.getData<Frame_sync> ();

	  sync.setup (frame_sync->freq);
	  sync.start ();
	  Tramsmit (frame_sync, sizeof(frame_sync));

	  break;
	}

      }

    }

  }
}

int Com::operator ()()
{
  int len = sizeof(data_rx) - rxdma.counter ();

  if (len > 0)
  {
    if (out_index > 0)
    {
      if (len >= out_index)
      {
	out_index = 0;
	restartRec ();
      }
    }
    else
    {
      if (len == pre_rx_len)
      {
	if (++out_time >= 10)
	{
	  restartRec ();
	  pre_rx_len = 0;
	  return len;
	}
      }
      else
      {
	out_time = 0;
	pre_rx_len = len;
      }

    }
  }

  return 0;
}

void Com::Tramsmit(const void *src, int len)
{

  if (len > (int) (sizeof(data_tx))) len = sizeof(data_tx);
  out_index = len;
  memcpy (data_tx, src, len);
  txdma.mem2per (data_tx, (unsigned char*) (((&usart.TDR))), len);

}

void Com::Tramsmit(const char *txt)
{
  Tramsmit (txt, strlen (txt));
}

