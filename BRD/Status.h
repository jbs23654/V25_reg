/*
 * Status.h
 *
 *  Created on: May 23, 2025
 *      Author: Jakub
 */

#ifndef MCU_STATUS_H_
#define MCU_STATUS_H_

#include "LasReg.h"
#include "Error.h"
#include "stm32c011xx.h"
class Status
{
  public:
    Status();
    virtual ~Status();
    enum class State : unsigned char
    {
      idle, ready, works, error
    };

    State state = State::idle;
    class Frame_state
    {
      public:
	unsigned short cmd = 1;
	unsigned char len = 5;
	unsigned char crc = 0;
	State status;
    };
    Frame_state f_state;

    void to_send();
    State check_status();

};
Status inline status;

#endif /* MCU_STATUS_H_ */
