#include "../../include/GV.h"

#define WALK_SPD 1	//�L�����̓�������

void char_calc(){//�L�����̈ړ�
	int i;
//x,y�f�[�^�����̂悤�ɏ������ƂŔz��v�f����muki��������Ƃ����e�����ɏ������\
	for(i=0;i<CH_MAX;i++){
		if(ch[i].walk_flag==1){
			ch[i].x += proceed_x[ ch[i].muki ] * WALK_SPD;
			ch[i].y += proceed_y[ ch[i].muki ] * WALK_SPD;
		}
	}
	return;
}