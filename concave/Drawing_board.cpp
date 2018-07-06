#include "5_mok.h"

int arr[27][27] = { 0, };

int Drawing_board() {	//바둑판 그리기 함수

	Initialization(back_ground); 
	system("cls");
	printf("┌");	//위쪽
	for (int j = 0; j <26; j++) {
		printf("┬");
	}
	printf("┐\n");

	for (int i = 0; i < 25; i++) {	//가운데
		printf("├");
		for (int j = 0; j < 26; j++) {
			printf("┼");
		}
		printf("┤\n");
	}
	printf("└");	//마지막 줄
	for (int j = 0; j < 26; j++) {
		printf("┴");
	}
	printf("┘");
	Gotoxy(0, 0);
	return 0;
}