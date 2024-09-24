#ifndef PID_HP
#define PID_HP

#include "mbed.h"

class PID{
    public:
    PID(float kp, float ki, float kd);
    float calc_output(int goal, int input, float dt);
    void reset();
    void set_gain(float kp, float ki, float kd);

    private:
    float _kp;
    float _ki;
    float _kd;
    float _integral;
    float _last_input;

};
#endif