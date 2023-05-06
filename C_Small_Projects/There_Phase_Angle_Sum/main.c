#include <stdio.h>
#include <math.h>

#define PI 3.14159265

int main()
{
    double val = PI / 180;
    double phase1, phase2, phase3;
    for(int i = 1; i <= 360; i++)
    {
        phase1 = sin(val *((double)i + 0));
        phase2 = sin(val *((double)i + 120));
        phase3 = sin(val*((double)i + 240));
        printf("phase 1 : %f, phase 2 : %f, phase 3 : %f, TOTAL : %f\n",phase1, phase2, phase3, (phase1 + phase2 + phase3));
    }
    //double val = PI / 180;
    //printf("%f", sin((double)1));
    return 0;
}