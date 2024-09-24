#include "mbed.h"
#include "PID_new.hpp"


BufferedSerial serial(USBTX, USBRX, 115200);

CAN can(PA_11, PA_12, 1000000);
CANMessage msg;

Pid pid({{400.0,1.2,0.02},20000,-20000}); // P,I,D,Max,Min

int16_t datas[4] = {0};


int main()
{

    int goal = 800;
    int deg = 0;
    bool is_sw_push[5];
    while (1)
    {
        auto now = HighResClock::now();
        static auto pre = now;
        can.read(msg);

        if ( msg.id == 10)
        {
            int16_t enc = msg.data[1] << 8 | msg.data[0];
            float k = 360.0 / (256.0 * 4.0);
            deg = enc * k;

        }

        if (msg.id == 9)
        {
            uint8_t sw = msg.data[5];
            
            for (int i = 0; i < 5; i++)
            {
                is_sw_push[i] = (sw >> i) & 0x01;
            }
            
        }
        
        if (now - pre > 10ms)
        {
            datas[1] = pid.calc(goal,deg,0.01) * -1;
            if (datas[1] < 0 && is_sw_push[0])
            {
                datas[1] = 0;
            }
            printf("deg: %d, output: %d\n",deg,datas[1]);
            CANMessage msg1(4, (const uint8_t *)datas, 8);
            can.write(msg1);

            pre = now;
        }
        

        
    }
}