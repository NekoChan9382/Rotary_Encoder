#ifndef LOLICON_HP
#define LOLICON_HP

#include "mbed.h"


class LOLICON{
    public:
    LOLICON(PinName PIN_A, PinName PIN_B, int PPR);
    void start();
    

    private:
    void rise();
    void fall();

    InterruptIn _LOLI_A;
    DigitalIn _LOLI_B;
    int _PPR;
    int _count_rot;

};

#endif