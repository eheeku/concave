#include "5_mok.h"


int Initialization(ground *back_ground) {	//초기화 함수

	(*back_ground).user = 1;	//	1 = 흑돌,2 = 백돌 (차례)
	(*back_ground).dot_data = 0;	//	흑돌 = 1,백돌 =2 (승리판단에 사용)
	(*back_ground).x = 0;	//	x 좌표 값
	(*back_ground).y = 1;	//	y 좌표 값
	memset(arr, 0, 27*27);
	
	return 0;
}