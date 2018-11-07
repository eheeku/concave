#include "5_mok.h"

int Game_finish() {
	char choose;
	Gotoxy(65, 6);
	printf("게임이 끝났습니다");
	Gotoxy(65, 7);
	printf("다시 시작하시려면 y/그렇지않으면n을 입력해주십시오:");
	Gotoxy(65, 8);
	fflush(stdin);
	scanf(" %c",&choose);

	switch (choose) {
	case 'y': {
		main();
		break;
	}
	case 'n': {
		exit(1);
		break;
	}
	default: {
		Gotoxy(65, 9);
		printf("잘못입력하셨습니다");
		Game_finish();
		break;
	}
	}
	return 0;
}
