#include "mbed.h"
#include "lolicon.hpp"

LOLICON::LOLICON(PinName PIN_A, PinName PIN_B, int PPR) : _LOLI_A(PIN_A), _LOLI_B(PIN_B), _PPR(PPR){}

void LOLICON::start(){

    //_LOLI_A.rise(&LOLICON::rise);
    //_LOLI_A.fall(&LOLICON::fall);
    _LOLI_B.mode(PullUp);
    
}

void LOLICON::rise(){
    if (_LOLI_B.read()){
        _count_rot++;
    }else{
        _count_rot--;
    }
}
