#include "5_mok.h"

int arr[27][27] = { 0, };

int Drawing_board() {	//�ٵ��� �׸��� �Լ�

	Initialization(back_ground); 
	system("cls");
	printf("��");	//����
	for (int j = 0; j <26; j++) {
		printf("��");
	}
	printf("��\n");

	for (int i = 0; i < 25; i++) {	//���
		printf("��");
		for (int j = 0; j < 26; j++) {
			printf("��");
		}
		printf("��\n");
	}
	printf("��");	//������ ��
	for (int j = 0; j < 26; j++) {
		printf("��");
	}
	printf("��");
	Gotoxy(0, 0);
	return 0;
}