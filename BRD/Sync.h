/*
 * Sync.h
 *
 *  Created on: Jun 26, 2025
 *      Author: Jakub
 */

// synchronizacja drivera LT3763


#include "stm32c011xx.h"
#ifndef SYNC_H_
#define SYNC_H_

class Sync
{
  public:
    Sync();
    virtual ~Sync();

    unsigned int psc = 0;
    unsigned int arr = 999;
    void Sync_init();
    void setup( int freq);
    void start();
};
Sync inline sync;
#endif /* SYNC_H_ */
