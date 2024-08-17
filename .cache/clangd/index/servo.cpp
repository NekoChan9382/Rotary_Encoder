#include "servo.h"

servo::servo(PinName PIN) : _PIN(PIN){
    deg_now=0;
    deg_limit=180;
    pulse_low=0.001;
    pulse_up=0.002;
    _PIN.period(0.02);
}
float servo::deg_pulse(int angle){
    return (pulse_low+((pulse_up - pulse_low)*((float)angle / (float)deg_limit)));

}
void servo::Pos(int angle){
    deg_now=angle;
    _PIN.pulsewidth(servo::deg_pulse(deg_now));

}
void servo::Period(float period){
    _PIN.period(period);
}
int servo::get_angle(void){
    return deg_now;
}