/*
 * Modulation.h
 *
 *  Created on: May 16, 2025
 *      Author: Jakub
 */

#ifndef BRD_MODULATION_H_
#define BRD_MODULATION_H_

class Modulation
{
  public:
    Modulation();
    virtual ~Modulation();

    enum class Mode
    {
      off, one, imp, con
    };
    Mode mode = Mode::off;
    unsigned int duty = 0;
    unsigned int psc = 0;
    unsigned int arr = 999;
    bool click_off = 0;

    void init();
    void test(int promils);
    void setup(int pulse_us, int pause_us); //imp
    void setup(int pulse_us); // one
    void setup(); // dc

    bool is_working();
    bool is_pulse_done();


    void standby(int pulse_us, int pause_us);
    void stop();


};
Modulation inline mod;
#endif /* BRD_MODULATION_H_ */
