#include "mbed.h"

BufferedSerial serial(USBTX, USBRX, 115200);

InterruptIn A_rpt(PB_6, PullUp);

InterruptIn B_rpt(PB_8, PullUp);

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
        printf("count_rot: %d , deg: %d\n", count_rot, deg);
        ThisThread::sleep_for(10ms);
    }
}