/*
 * LasReg.h
 *
 *  Created on: Jun 23, 2025
 *      Author: jsobo
 */

#ifndef BRD_LASREG_H_
#define BRD_LASREG_H_

#include "Power.h"
#include "Modulation.h"
class LasReg
{
  private:
    Power power;
    Modulation mod;
  public:
    LasReg();
    virtual ~LasReg();

    bool work = false;

    void current_set(int current);

    void modulation_set(int pulse_us, int pause_us);

    void select(unsigned char laserA, unsigned char laserB);

    void start();
    void stop();
    bool is_working();

};
LasReg inline lasreg;
#endif /* BRD_LASREG_H_ */
