#include "5_mok.h"

int Who_win() {	//�¸� ���� �Լ�
	int sum1 = 0;	// �¸�����
	int sum2 = 0;

	for (int i = -4; i <5; i++) {	// ���� �˻�
		if (arr[(*back_ground).x][(*back_ground).y - i] == (*back_ground).dot_data) {
			if (arr[(*back_ground).x][(*back_ground).y] == 1) {
				sum1++;
			}
			else if (arr[(*back_ground).x][(*back_ground).y] == 2) {
				sum2++;
			}
		}
		else {
			sum1 = 0;
			sum2 = 0;
		}
		if (sum1 == 5) {
			Gotoxy(65, 5);
			printf("�浹 �¸�");
			Game_finish();
		}
		else if (sum2 == 5) {
			Gotoxy(65, 5);
			printf("�鵹 �¸�");
			Game_finish();
		}
	}

	for (int i = -5; i <5; i++) {	//	���� �˻�
		if (arr[(*back_ground).x + (2 * i)][(*back_ground).y] == (*back_ground).dot_data) {
			if (arr[(*back_ground).x][(*back_ground).y] == 1) {
				sum1++;
			}
			else if (arr[(*back_ground).x][(*back_ground).y] == 2) {
				sum2++;
			}
		}
		else {
			sum1 = 0;
			sum2 = 0;
		}
		if (sum1 == 5) {
			Gotoxy(65, 5);
			printf("�浹 �¸�");
			Game_finish();
		}
		else if (sum2 == 5) {
			Gotoxy(65, 5);
			printf("�鵹 �¸�");
			Game_finish();
		}
	}

	for (int i = -5; i <5; i++) {	//	y=-x �˻�
		if (arr[(*back_ground).x + (2 * i)][(*back_ground).y + i] == (*back_ground).dot_data) {
			if (arr[(*back_ground).x][(*back_ground).y] == 1) {
				sum1++;
			}
			else if (arr[(*back_ground).x][(*back_ground).y] == 2) {
				sum2++;
			}
		}
		else {
			sum1 = 0;
			sum2 = 0;
		}
		if (sum1 == 5) {
			Gotoxy(65, 5);
			printf("�浹 �¸�");
			Game_finish();
		}
		else if (sum2 == 5) {
			Gotoxy(65, 5);
			printf("�鵹 �¸�");
			Game_finish();
		}
	}

	for (int i = -5; i <5; i++) {	//	y=x �˻�
		if (arr[(*back_ground).x + (2 * i)][(*back_ground).y - i] == (*back_ground).dot_data) {
			if (arr[(*back_ground).x][(*back_ground).y] == 1) {
				sum1++;
			}
			else if (arr[(*back_ground).x][(*back_ground).y] == 2) {
				sum2++;
			}
		}
		else {
			sum1 = 0;
			sum2 = 0;
		}
		if (sum1 == 5) {
			Gotoxy(65, 5);
			printf("�浹 �¸�");
			Game_finish();
		}
		else if (sum2 == 5) {
			Gotoxy(65, 5);
			printf("�鵹 �¸�");
			Game_finish();
		}
	}
	return 0;
}