
/*헤더파일에는 선언만 할 것*/
#include <stdio.h>
#include <conio.h>
#include <windows.h>
#include <stdlib.h>

#define UP 72
#define DOWN 80
#define LEFT 75
#define RIGHT 77
#define SPACE 32

#ifndef Ground
#define Ground
typedef struct Ground {	// rock struct
	int dot_data;
	int x;
	int y;
	int user;
}ground;
extern ground *back_ground;	//global
extern int arr[27][27];	//global
#endif


int main();
void Gotoxy(int x, int y);
int Initialization(ground *back_ground);
int Drawing_board();
int Moving_cursor();
int Who_win();
int Game_finish();
