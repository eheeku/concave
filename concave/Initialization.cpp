#include "5_mok.h"


int Initialization(ground *back_ground) {	//�ʱ�ȭ �Լ�

	(*back_ground).user = 1;	//	1 = �浹,2 = �鵹 (����)
	(*back_ground).dot_data = 0;	//	�浹 = 1,�鵹 =2 (�¸��Ǵܿ� ���)
	(*back_ground).x = 0;	//	x ��ǥ ��
	(*back_ground).y = 1;	//	y ��ǥ ��
	memset(arr, 0, 27*27);
	
	return 0;
}