#ifndef __BANK_DISPLAY__
#define __BANK_DISPLAY__
struct position
{
    int x;
    int y;
}cursor_position;
void LogoPrompt(void);
void gotoxy(int x, int y);
void hidecursor();
void Draw_Free_Frame(void);
#endif