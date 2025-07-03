/*
 * Status.cpp
 *
 *  Created on: May 23, 2025
 *      Author: Jakub
 */

#include <Status.h>

Status::Status()
{
  // TODO Auto-generated constructor stub

}

Status::~Status()
{
  // TODO Auto-generated destructor stub
}

void Status::to_send()
{
  f_state.status = check_status ();
  unsigned char f[sizeof(Frame_state)];
  f[0] = (unsigned char) f_state.cmd;
  f[1] = (unsigned char) f_state.cmd >> 8;
  f[2] = (unsigned char) f_state.len;
  f[4] = (unsigned char) f_state.status;
  for (int i = 0; i < f_state.len; i++)
  {
    f_state.crc ^= f[i];
  }

  f[3] = f_state.crc;

}

Status::State Status::check_status()
{
  if (lasreg.work)
    return State::works;
  else
  {
    if ((TIM1->CR1 & TIM_CR1_CEN) && (TIM3->CR1 & TIM_CR1_CEN))
    {
      return State::ready;
    }
    else if (error.is_error)
    {
      return State::error;
    }
    else
    {
      return State::idle;
    }
  }
  return State::idle;
}
