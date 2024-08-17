#include "mbed.h"
#include "PID.hpp"

BufferedSerial serial(USBTX, USBRX, 115200);

InterruptIn A_rpt(PB_6, PullUp);

InterruptIn B_rpt(PB_8, PullUp);

PID pid(65, 5, 40);

CAN can(PA_11, PA_12, 1000000);
CANMessage msg;

int16_t data[4] = {0};

volatile int count_rot = 0;

volatile bool rptable = 1;


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
    uint16_t allowable_error_count = 10;
    uint16_t speed_limit = 800;
    int goal = 48;

    while (1)
    {
        int deg = count_rot * 7.5;

        if (abs(goal - count_rot) < allowable_error_count && abs(data[1]) < speed_limit)
        {
            data[1] = 0;
        }else{

        float output = pid.calc_output(goal, count_rot, 0.01);
        int16_t output_int16 = static_cast<int16_t>(output);
        output_int16 = clamps(output_int16, -20000, 20000);
        data[1] = output_int16;
        }
        CANMessage msg(4, (const uint8_t *)data, 8);
        can.write(msg);
        printf("deg: %d , output: %d\n", deg, data[1]);


        ThisThread::sleep_for(10ms);
    }
}