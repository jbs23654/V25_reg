/*
 * Current.h
 *
 *  Created on: Jul 3, 2025
 *      Author: Jakub
 */

#ifndef BRD_CURRENT_H_
#define BRD_CURRENT_H_

#include "stm32c011xx.h"
class Current
{
  public:
    Current();
    virtual ~Current();
    unsigned short meas;
    void init();
    void measure();
};
Current inline current;
#endif /* BRD_CURRENT_H_ */
