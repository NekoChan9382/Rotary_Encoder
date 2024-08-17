#include "mbed.h"
#include "servo.h"

servo test(PC_7);

int main(){
    test.pulse_low=0.0005;
    test.pulse_up=0.0025;
    test.deg_limit=180;
    test.Period(0.02);

    test.Pos(0);
    wait(1.0);
    test.Pos(180);
    wait(1.0);

}