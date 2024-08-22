#include "PID.hpp"
#include "mbed.h"

PID::PID(float kp, float ki, float kd) : _kp(kp), _ki(ki), _kd(kd), _integral(0), _last_input(0) {}

float PID::calc_output(int goal, int input, float dt){
    int error = goal - input;
    _integral += error * dt;
    float deriv = (input - _last_input) / dt;
    float output = _kp * error + _ki * _integral - _kd * deriv;
    _last_input = input;
    return output;
}

void PID::reset(){
    _integral = 0;
    _last_input = 0;
}

void PID::set_gain(float kp, float ki, float kd){
    _kp = kp;
    _ki = ki;
    _kd = kd;
}