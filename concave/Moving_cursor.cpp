#include "5_mok.h"

int Moving_cursor() {	//ȭ��ǥ �����̱� �Լ�

	int ch;
	while (1) {
		ch = getch();
		if (kbhit() != 0) {
			ch = getch();
			switch (ch) {

			case UP: {	//up
				if (((*back_ground).y) >= 0) {
					((*back_ground).y) -= 1;
					if (((*back_ground).y) < 1) {
						((*back_ground).y) = 1;
					}
					Gotoxy(((*back_ground).x), ((*back_ground).y));
					break;
				}
			}
			case DOWN: {	//down
				if (((*back_ground).y) <= 26) {
					(*back_ground).y++;
					Gotoxy((*back_ground).x, (*back_ground).y);
					break;
				}
			}
			case RIGHT: {	//right
				if ((*back_ground).x < 55) {
					(*back_ground).x += 2;
					Gotoxy((*back_ground).x, (*back_ground).y);
					break;
				}
			}
			case LEFT: {	//left
				if ((*back_ground).x >= 0) {
					(*back_ground).x -= 2;
					if ((*back_ground).x < 1) {
						(*back_ground).x = 1;
					}
					Gotoxy((*back_ground).x, (*back_ground).y);
					break;
				}
			}
		}
	}

		(*back_ground).dot_data = 0;	//dot_data �� 0���� �ʱ�ȭ ����

		if (ch == SPACE) {	// �� ������

			while (!arr[(*back_ground).x][(*back_ground).y]) {	// �迭���� 0�� �ƴϸ�
				if ((*back_ground).user == 1) {	//������ 1�̸� �浹 

					(*back_ground).user += 1;	//���� �� 2�� �ٲ���
					(*back_ground).dot_data += 1;	//dot_data�� 1�� ����
					arr[(*back_ground).x][(*back_ground).y] = 1;	//�迭���� 1 ����
					printf("��");	//�浹 ���
					Who_win();	//�¸��Ǵ�
				}
				else if ((*back_ground).user == 2) {	//������ 2�̸� �鵹

					(*back_ground).user -= 1;	//���� �� 1�� �ٲ���
					(*back_ground).dot_data += 2;	//dot_data�� 2�� ����
					arr[(*back_ground).x][(*back_ground).y] = 2;	//�迭���� 2 ����
					printf("��");	//�鵹 ���
					Who_win();	//�¸��Ǵ�
				}

			}
		}
	}
}