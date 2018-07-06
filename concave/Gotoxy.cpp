#include "5_mok.h"

void Gotoxy(int x, int y) {	//커서 이동함수
	COORD Pos = { x - 1, y - 1 };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), Pos);
} 