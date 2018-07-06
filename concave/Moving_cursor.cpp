#include "5_mok.h"

int Moving_cursor() {	//화살표 움직이기 함수

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

		(*back_ground).dot_data = 0;	//dot_data 값 0으로 초기화 해줌

		if (ch == SPACE) {	// 돌 놓아짐

			while (!arr[(*back_ground).x][(*back_ground).y]) {	// 배열값이 0이 아니면
				if ((*back_ground).user == 1) {	//유저가 1이면 흑돌 

					(*back_ground).user += 1;	//유저 값 2로 바꿔줌
					(*back_ground).dot_data += 1;	//dot_data에 1값 대입
					arr[(*back_ground).x][(*back_ground).y] = 1;	//배열값도 1 대입
					printf("○");	//흑돌 출력
					Who_win();	//승리판단
				}
				else if ((*back_ground).user == 2) {	//유저가 2이면 백돌

					(*back_ground).user -= 1;	//유저 값 1로 바꿔줌
					(*back_ground).dot_data += 2;	//dot_data에 2값 대입
					arr[(*back_ground).x][(*back_ground).y] = 2;	//배열값도 2 대입
					printf("●");	//백돌 출력
					Who_win();	//승리판단
				}

			}
		}
	}
}