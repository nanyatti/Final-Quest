#include "../../include/GV.h"

extern double rano(double sigma, double average);
extern int damdec(ch_t *c,int to,int actkind);
extern int tp_calc(int dam,int hp);

void ani_start(int menu_sel,int target,int actor){//�U���A�j���[�V�����̊J�n
	int i;
	for(i=0;i<ANI_MAX-2;i++){			//�g���ĂȂ��A�j���[�V������T��
		if(ani[i].flag==0)
			break;
	}
	ani[i].flag=1;						//�A�j���[�V�����g�p�t���O�𗧂Ă�
	ani[i].target=target;					//�U���̃^�[�Q�b�g���w��(0���ƓG0������)
	ani[i].kind=menu_sel;				//�A�j���[�V�����̎�ނ��w�肷��B(ch[0].menu_sel�͑I����������)
	ani[i].cnt=0;						//�A�j���[�V�����̃J�E���^��������
	ani[i].actor=actor;
	return ;
}

void dam_c(ch_t* c){
	int i;
	c->dam		=damdec(c,2,c->menu_sel);//�_���[�W����)
	c->bttohp	-=c->dam;				//�̗͂����ԍ��Ō����Ă����A�ŏI�I�ȏI���ʒu
	if(c->bttohp<0)	c->bttohp=0;
	for(i=0;i<POP_DAM_MAX;i++)					//�g�p���Ă��Ȃ��_���[�W�|�b�v�A�j���[�V������T��
		if(pop_dam[i].flag==0)
			break;
	pop_dam[i].flag=1;							//�g�p�t���O�𗧂Ă�
	pop_dam[i].cnt=0;							//�J�E���^������
	pop_dam[i].dam=c->dam;					//�_���[�W�l�w��
	pop_dam[i].x=c->btx-30;						//x,y�l�w��
	pop_dam[i].y=c->bty-25;
	pop_dam[i].type=0;
}

void add_board(const char * st){
	int i;
	for(i=0;i<100;i++)
		if(board[i].flag==0)
			break;
	board[i].flag=1;
	board[i].cnt=0;
	strcpy(board[i].st,st);
	return ;
}

void abi_act(ch_t* c){
	char st[100];
	c->tp+=8+GetRand(5);						//1��̍U���Ŏ����ɂW�`�P�Rtp�����܂�
	if(c->tp>300)	c->tp=300;					//TP��300%���ő�
	switch(c->menu_sel){
		case 30000:
			c->abi[0].flag=1;
			//�w�C�g���������ǉ��K�v����
			break;
		case 30100:
			c->chsts.def	= c->def/3;
			c->chsts.power	= -c->power/3;
			c->abi[1].flag=1;
			c->abi[1].cnt=0;
			add_board("�h��͂��オ����");
			add_board("�U���͂���������");
			break;
		case 30200:
			c->chsts.def	= -c->def/3;
			c->chsts.power	= c->power/3;
			c->abi[2].flag=1;
			c->abi[2].cnt=0;
			add_board("�U���͂��オ����");
			add_board("�h��͂���������");
			break;
		case 30300:
			dam_c(c);
			c->abi[3].flag=1;
			c->abi[3].cnt=0;
			add_board("����U�����Q�{�̃_���[�W�̑̐��ɂȂ���");
			sprintf(st,"���͂̐�̔�����%d�_���[�W���󂯂�",c->dam);
			add_board(st);
			break;
		case 30400:
			c->abi[4].flag=1;
			c->abi[4].cnt=0;
			add_board("����r�����Ԃ�4����1�̑̐��ɂȂ���");
			break;
		default:
			break;
	}
	return ;
}
void cure_act(ch_t* c){
	int i;
	c->dam		=damdec(c,0,c->menu_sel);//�_���[�W����)
	c->mp-=9;//MP�g��������������
	c->hp+=c->dam;
	c->bttohp+=c->dam;
	if(c->hp>c->hp_max){c->hp=c->hp_max; c->bttohp=c->hp;}
	if(c->mp<0)	c->mp=0;
	c->tp+=8+GetRand(5);						//1��̍U���Ŏ����ɂW�`�P�Rtp�����܂�
	if(c->tp>300)	c->tp=300;					//TP��300%���ő�
	for(i=0;i<POP_DAM_MAX;i++)					//�g�p���Ă��Ȃ��_���[�W�|�b�v�A�j���[�V������T��
		if(pop_dam[i].flag==0)
			break;
	pop_dam[i].flag=1;							//�g�p�t���O�𗧂Ă�
	pop_dam[i].cnt=0;							//�J�E���^������
	pop_dam[i].dam=c->dam;					//�_���[�W�l�w��
	pop_dam[i].x=c->btx-30;						//x,y�l�w��
	pop_dam[i].y=c->bty-25;
	pop_dam[i].type=1;
	if(c->abi[3].flag==1)c->abi[3].flag=2;
	if(c->abi[4].flag==1)c->abi[4].flag=2;
	return ;
}

void dam_act(ch_t* my,ch_t* you){				//�_���[�W�A�N�V�������s��
	int del_mp[5]={9,8,16,24,32},i;				//����MP
	you->dam		=damdec(my,0,my->menu_sel);//�_���[�W����)
	if(my->abi[3].flag==1)
		you->dam*=2;
	you->bttohp	=you->hp-you->dam;				//�̗͂����ԍ��Ō����Ă����A�ŏI�I�ȏI���ʒu
	you->tp+=tp_calc(you->dam,you->hp_max);		//�_���[�W��HP�}�b�N�X�l���瑊��ɂ��܂�TP���Z�o	
	my->tp+=8+GetRand(5);						//1��̍U���Ŏ����ɂW�`�P�Rtp�����܂�
	if(my->menu_sel>=20000&&my->menu_sel<30000){//���@�Ȃ�
		my->mp-=del_mp[(my->menu_sel-20000)/100];//MP�g��������������
		if(my->mp<0)
			my->mp=0;
	}
	if(my->tp>300)	my->tp=300;					//TP��300%���ő�
	if(you->tp>300)	you->tp=300;
	for(i=0;i<POP_DAM_MAX;i++)					//�g�p���Ă��Ȃ��_���[�W�|�b�v�A�j���[�V������T��
		if(pop_dam[i].flag==0)
			break;
	pop_dam[i].flag=1;							//�g�p�t���O�𗧂Ă�
	pop_dam[i].cnt=0;							//�J�E���^������
	pop_dam[i].dam=you->dam;					//�_���[�W�l�w��
	pop_dam[i].x=you->btx-30;						//x,y�l�w��
	pop_dam[i].y=you->bty-25;
	pop_dam[i].type=0;
	if(my->abi[3].flag==1)my->abi[3].flag=2;
	if(my->abi[4].flag==1)
		my->abi[4].flag=2;
	return ;
}

void end_ini(ch_t *my){	//�I������
	my->menu_sel=1;		//�I�����ڂ�������
	my->menu_sely=0;	//�I���ʒu��������
	my->btmotion_flag=0;//���[�V�����̃t���O��������
	my->btcnt_flag=1;	//ATB�J�E���^�[�����t���O�𗧂Ă�B
	my->btcnt=0;		//�J�E���^������
	return;
}

void bt_walk(ch_t *my,int i){//�L�������O�ɏo������ɉ��������肷�郂�[�V����
	if(i==-1)	my->btx--;	
	else		my->btx++;
	return ;
}

