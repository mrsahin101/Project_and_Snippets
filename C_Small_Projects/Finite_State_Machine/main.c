/* State Machine Example */
#include <stdio.h>
#include <unistd.h>
/* Prototype */
void stateA(void);
void stateB(void);
void stateC(void);
void initializeSM(void);
void wait(void);

/* Define an enumarated type for state */
typedef enum
{
    STATE_A = 0,
    STATE_B,
    STATE_C
}State_Type;

/* Define a table of pointers to the functions for each state */
static void(*state_table[])(void) = {stateA, stateB, stateC};

/* Global Decleration */
static State_Type curr_state;       /* The "current_state "*/
static int Clock;
static int out;

void main(void)
{
    /* Initialize the State Machine */
    initializeSM();

    /* The is the main State transition loop */
    while(1)
    {
        state_table[curr_state]();
        wait();
        Clock++;
    }
}
void wait(void)
{
    sleep(1);
}
void stateA(void)
{
    if(Clock == 2)              /* Change State? */
    {
        curr_state = STATE_B;   /* Next State */
        out = 1;                /* New output */
        printf("Entered state A\n");
    }
}
void stateB(void)
{
    if(Clock == 5)              /* Change State? */
    {
        curr_state = STATE_C;   /* Next State */
        out = 2;                /* New output */
        printf("Entered state B\n");
    }
}
void stateC(void)
{
    if(Clock == 9)              /* Change State? */
    {
        Clock = 0;
        curr_state = STATE_A;   /* Next State */
        out = 0;                /* New output */
        printf("Entered state C\n");
    }
}
void initializeSM(void)
{
    curr_state = STATE_A;
    out = 0;
    Clock = 1;
    printf("State Machine initialized\n");
}