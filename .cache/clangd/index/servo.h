#ifndef servo_H
#define servo_H

#include "mbed.h"

class servo{

    private:
    PwmOut _PIN;
    int deg_now;
    float deg_pulse(int angle);

    public:
    servo(PinName PIN);
    int deg_limit;
    float pulse_low,pulse_up;
    void Period(float period);
    void Pos(int angle);
    int get_angle(void);
};
#endif