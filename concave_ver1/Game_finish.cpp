#include "5_mok.h"

int Game_finish() {
	char choose;
	Gotoxy(65, 6);
	printf("������ �������ϴ�");
	Gotoxy(65, 7);
	printf("�ٽ� �����Ͻ÷��� y/�׷���������n�� �Է����ֽʽÿ�:");
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
		printf("�߸��Է��ϼ̽��ϴ�");
		Game_finish();
		break;
	}
	}
	return 0;
}
