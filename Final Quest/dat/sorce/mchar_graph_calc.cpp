#include "../../include/GV.h"


#define WALK_RAND 100	//���̐l�Ԃ��������x����->�����قǂ��܂ɂ��������Ȃ�

extern int can_walk_decide(int x,int y,int muki);

void mchar_graph_calc(){
	int i;
	for(i=0;i<CH_MAX-1;i++){
		if(ch[i+1].x%WIDE==0 && ch[i+1].y%WIDE==0){	//x��y�����W��32�̔{���ł��鎞
			ch[i+1].walk_cnt=0;	//�����J�E���^��߂�
			ch[i+1].walk_flag=0;
			if(GetRand(WALK_RAND)==0){//�����n�߂�
				ch[i+1].muki=GetRand(3);
				if(can_walk_decide(ch[i+1].x,ch[i+1].y,ch[i+1].muki)==0){//�����Ă�������ʂ��ꏊ�Ȃ�
					ch[i+1].walk_flag=1;
					mapd[ ch[i+1].y/WIDE							][ ch[i+1].x/WIDE							]=0;
					mapd[ ch[i+1].y/WIDE + proceed_y[ch[i+1].muki]][ ch[i+1].x/WIDE + proceed_x[ch[i+1].muki]  ]=1;				
				}
				else
					ch[i+1].walk_flag=0;
				ch[i+1].walk_cnt++;	//���muki�̕����֕���
			}
		}
		else	//�����ł͂Ȃ���
			ch[i+1].walk_cnt++;	//���muki�̕����֕���
		//walk_cnt��1�s�N�Z��������1������B���֕`�悷��摜���Z�b�g
		ch[i+1].img = ch_img[ ch[i+1].kind ][ (ch[i+1].walk_cnt%32)/(WIDE/4) + ch[i+1].muki*4 ];//0~3�͍������摜 4~7�͏�����摜�E�E�Ɛ��l��ϊ�
	}
	return ;
}