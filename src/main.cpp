#include "mbed.h"
#include "PID.hpp"

BufferedSerial serial(USBTX, USBRX, 115200);

InterruptIn A_rpt(PB_6, PullUp);

InterruptIn B_rpt(PB_8, PullUp);

PID pid(50, 5, 55);

CAN can(PA_11, PA_12, 1000000);
CANMessage msg;

int16_t data[4] = {0};

volatile int count_rot = 0;

volatile bool rptable = 1;


int test;
bool tests=1;

void rise_A()
{
    if (rptable)
    {
        if (B_rpt.read())
        {
            count_rot--;
        }
        else
        {
            count_rot++;
        }
        rptable=0;
        
        test=1;
        tests=1;
    }
}

void fall_A()
{
    if (rptable)
    {
        if (B_rpt.read())
        {
            count_rot++;
        }
        else
        {
            count_rot--;
        }
        rptable=0;
        
        test=2;
        tests=1;
    }
}

void rise_B()
{
    if (!rptable)
    {
        if (A_rpt.read())
        {
            count_rot++;
        }
        else
        {
            count_rot--;
        }
        rptable=1;
        
        test=3;
        tests=1;
    }
}

void fall_B()
{
    if (!rptable)
    {
        if (A_rpt.read())
        {
            count_rot--;
        }
        else
        {
            count_rot++;
        }
        rptable=1;
        
        test=4;
        tests=1;
    }
}

int16_t clamps(int value, int min, int max) {
    if (value < min) {
        return min;
    } else if (value > max) {
        return max;
    } else {
        return value;
    }
}

int main()
{
    A_rpt.rise(&rise_A);
    A_rpt.fall(&fall_A);
    B_rpt.rise(&rise_B);
    B_rpt.fall(&fall_B);
    tests=1;

    while (1)
    {
        int deg = count_rot * 7.5;
        float output = pid.calc_output(1600, count_rot, 0.01);
        int16_t output_int16 = static_cast<int16_t>(output);
        output_int16 = clamps(output_int16, -20000, 20000);
        data[0] = output_int16;
        CANMessage msg(4, (const uint8_t *)data, 8);
        can.write(msg);
        printf("count_rot: %d , output: %d\n", count_rot, output_int16);


        ThisThread::sleep_for(10ms);
    }
}