#include <stdio.h>
#include "bank_display.h"
#include <time.h>
#include <unistd.h>
#include <windows.h>

#define PANEL_SIZE_X        203
#define PANEL_SIZE_Y        38

#define TOP_LEFT_CHAR       201
#define TOP_BOTTOM_CHAR     205
#define TOP_RIGHT_CHAR      187
#define SIDES_CHAR          186
#define BOTTOM_RIGHT_CHAR   188
#define BOTTOM_LEFT         200

#define LOGO_FILE_WIDTH     201



void hidecursor()
{
   HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
   CONSOLE_CURSOR_INFO info;
   info.dwSize = 100;
   info.bVisible = FALSE;
   SetConsoleCursorInfo(consoleHandle, &info);
}
void gotoxy(int x, int y)
{
  COORD coord;
  coord.X = x;
  coord.Y = y;
  SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
  cursor_position.x = x,
  cursor_position.y = y;
}

void Draw_RightTop()
{
    putchar(TOP_RIGHT_CHAR);
}
void Draw_Top()
{
    for(int i = 2; i < PANEL_SIZE_X; i++)
        putchar(TOP_BOTTOM_CHAR);
}
void Draw_TopLeft()
{
    putchar(TOP_LEFT_CHAR);
}
void Draw_TopChar()
{
    putchar(TOP_BOTTOM_CHAR);
}
void Draw_Side()
{
    putchar(SIDES_CHAR);
}
void Draw_BottomLeft()
{
    putchar(BOTTOM_LEFT);
}
void Draw_BottomRight()
{
    putchar(BOTTOM_RIGHT_CHAR);
}
void DrawTopPanel()
{
    Draw_TopLeft();
    Draw_Top();
    Draw_RightTop();
    putchar('\n');
    Draw_Side();
}
void DrawBottomPanel()
{
    Draw_BottomLeft();
    Draw_Top();
    Draw_BottomRight();
}
void DRAW_LOGO()
{
    int counter = 0;
    int newline = 0;
    FILE *logo;
    logo = fopen(".//Images/ascii-art.txt","r");
    if(logo == NULL)
    {
        printf("Logo file missing!");
        //return 1;
    }
    char ch;
    while((ch = fgetc(logo)) != EOF)
    {
        if(ch == '\n')
            putchar(' ');
        if(ch == '\n')
            Draw_Side();
        printf("%c",ch);
        if(ch == '\n')
            Draw_Side();
        counter++;
    }
    Draw_Side();
    putchar('\n');
    
}

void LogoPrompt(void)
{
    DrawTopPanel();
    DRAW_LOGO();
    DrawBottomPanel();
    sleep(5); 
    system("CLS");
}
void Draw_Free_Frame()
{
    for(int i = 1; i < PANEL_SIZE_Y + 1; i++)
    {
        for(int j = 1; j < PANEL_SIZE_X ; j++)
        {
            gotoxy(j,i);
            if(i == 1 && j == 1)
                Draw_TopLeft();
            else if(i == 1 && j < (PANEL_SIZE_X - 1))
                Draw_TopChar();
            else if(i == 1 && j == (PANEL_SIZE_X - 1))
                Draw_RightTop();
            if(i > 1 && (j == 1 || j == (PANEL_SIZE_X - 1)) && i != PANEL_SIZE_Y)
                Draw_Side();
            if(i == (PANEL_SIZE_Y ) && j == 1)
                Draw_BottomLeft();
            else if(i == (PANEL_SIZE_Y ) && j != 1 && j != (PANEL_SIZE_X - 1))
                Draw_TopChar();
            else if(i == (PANEL_SIZE_Y ) && j != 1 && j == (PANEL_SIZE_X - 1))
                Draw_BottomRight();
        }
    }
    gotoxy(80, 2);
    printf("ZIRAAT BANK MANAGEMENT SYSTEM");
    gotoxy(2,2);
}