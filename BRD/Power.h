/*
 * Power.h
 *
 *  Created on: May 16, 2025
 *      Author: Jakub
 */

#ifndef BRD_POWER_H_
#define BRD_POWER_H_

class Power
{
  public:
    Power();
    virtual ~Power();
    //ustawić timer, itd
    void init();


    //podać wartość od 0..999 pwm wyjściowego
    void setup(int promils);

};
Power inline power;
#endif /* BRD_POWER_H_ */
