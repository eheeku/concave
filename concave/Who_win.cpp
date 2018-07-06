#include "5_mok.h"

int Who_win() {	//½Â¸® °ËÁ¤ ÇÔ¼ö
	int sum1 = 0;	// ½Â¸®ÆÇÁ¤
	int sum2 = 0;

	for (int i = -4; i <5; i++) {	// ¼¼·Î °Ë»ç
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
			printf("Èæµ¹ ½Â¸®");
			Game_finish();
		}
		else if (sum2 == 5) {
			Gotoxy(65, 5);
			printf("¹éµ¹ ½Â¸®");
			Game_finish();
		}
	}

	for (int i = -5; i <5; i++) {	//	°¡·Î °Ë»ç
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
			printf("Èæµ¹ ½Â¸®");
			Game_finish();
		}
		else if (sum2 == 5) {
			Gotoxy(65, 5);
			printf("¹éµ¹ ½Â¸®");
			Game_finish();
		}
	}

	for (int i = -5; i <5; i++) {	//	y=-x °Ë»ç
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
			printf("Èæµ¹ ½Â¸®");
			Game_finish();
		}
		else if (sum2 == 5) {
			Gotoxy(65, 5);
			printf("¹éµ¹ ½Â¸®");
			Game_finish();
		}
	}

	for (int i = -5; i <5; i++) {	//	y=x °Ë»ç
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
			printf("Èæµ¹ ½Â¸®");
			Game_finish();
		}
		else if (sum2 == 5) {
			Gotoxy(65, 5);
			printf("¹éµ¹ ½Â¸®");
			Game_finish();
		}
	}
	return 0;
}