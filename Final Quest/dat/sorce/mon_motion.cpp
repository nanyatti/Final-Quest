#include "../../include/GV.h"
//����
extern void ani_start(int menu_sel,int target,int actor);
extern void dam_act(ch_t* my,ch_t* you);
extern void end_ini(ch_t *my);
extern void bt_walk(ch_t *my,int i);
extern void cure_act(ch_t* c);
extern void abi_act(ch_t* c);
extern void add_board(const char * st);
/*�֐��̓��e��ch_motion.cpp��ch0_motion()�Ƃقړ����Ȃ̂ł����������������*/

void mon0_motion(){//�����X�^�[0���ʏ�U���������̃��[�V����
	char st[100];
	static int cnt=0,cnt1=0;

	if(gameover_flag==1 || victory_flag==1){
		cnt=0;	return ;
	}
	if(20<cnt && 40>=cnt)
		bt_walk(&mon[0],1);

	if(cnt==50)	
		ani_start(10000,100,0);
	
	if(mon[0].btact_flag==1){
		mon[0].menu_sel=10000;
		switch(mon[0].menu_sel){
			case 10000:
			case 10100:
			case 20100:
			case 20200:
			case 20300:
			case 20400:
				dam_act(&mon[0],&ch[0]);			//�_���[�W��^����A�N�V�����̊֐�(&����,&�_���[�W��^���鑊��)
				sprintf(st,"%d�̃_���[�W���󂯂�",ch[0].dam);
				add_board(st);				break;
			case 20000:
				cure_act(&mon[0]);
				sprintf(st,"�G��HP��%d�񕜂���",mon[0].dam);
				add_board(st);
				break;
			case 30000:
			case 30001:
			case 30002:
			case 30003:
			case 30004:
				abi_act(&mon[0]);
				break;
		}
		mon[0].btact_flag=0;
		cnt1++;
	}

	if(0<cnt1 && 20>=cnt1)
		bt_walk(&mon[0],-1);

	cnt++;
	if(cnt1>0)
		cnt1++;

	if(cnt1==60){
		cnt=0;		cnt1=0;
		end_ini(&mon[0]);
	}

	if(gameover_flag==2 || victory_flag==2){
		cnt=0;		cnt1=0;
	}
	return;
}
