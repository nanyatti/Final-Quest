#include "../../include/GV.h"

extern void ani_start(int menu_sel,int target,int actor);
extern void dam_act(ch_t* my,ch_t* you);
extern void end_ini(ch_t *my);
extern void bt_walk(ch_t *my,int i);
extern void cure_act(ch_t* c);
extern void abi_act(ch_t* c);
extern void add_board(const char * st);
void ch0_motion(){//�L�����P���ʏ�U���������̃��[�V����
	char st[100];
	static int cnt=0,cnt1=0;

	if(gameover_flag==1 || victory_flag==1){//�Q�[���I�[�o�[�t���O�������Ă����珉�������ď����𔲂���
		cnt=0;	return ;
	}
	if(20<cnt && 40>=cnt)					//20�`40�J�E���g�̎��O�֏o��B
		bt_walk(&ch[0],-1);					//2�Ԗڂ̈����͑O��ǂ���ɓ������̃t���O

	if(cnt==50)								//50�̎��s���J�n
		ani_start(ch[0].menu_sel,0,100);
	
	if(ch[0].btact_flag==1){				//���̏u�ԃ_���[�W�A�N�V����������t���O�������Ă�����
		switch(ch[0].menu_sel){
			case 10000:
			case 10100:
			case 20100:
			case 20200:
			case 20300:
			case 20400:
				dam_act(&ch[0],&mon[0]);			//�_���[�W��^����A�N�V�����̊֐�(&����,&�_���[�W��^���鑊��)
				sprintf(st,"�G��%d�̃_���[�W��^����",mon[0].dam);
				add_board(st);
				break;
			case 20000:
				cure_act(&ch[0]);
				sprintf(st,"HP��%d�񕜂���",ch[0].dam);
				add_board(st);
				break;
			case 30000:
			case 30100:
			case 30200:
			case 30300:
			case 30400:
				abi_act(&ch[0]);
				break;
			default:
				break;
		}
		ch[0].btact_flag=0;
		cnt1++;
	}

	if(0<cnt1 && 20>=cnt1)					//�_���[�W�A�N�V��������O�`�Q�O��Ɍ��̈ʒu�ɖ߂�
		bt_walk(&ch[0],1);					//2�Ԗڂ̈����͑O��ǂ���ɓ������̃t���O

	cnt++;
	if(cnt1>0)								//�_���[�W�A�N�V�����̒��ォ��J�E���g
		cnt1++;

	if(cnt1==60){							//�_���[�W�A�N�V�����̒���60�J�E���g�Ń��[�V�����I��
		cnt=0;		cnt1=0;
		end_ini(&ch[0]);
	}
	if(gameover_flag==2 || victory_flag==2){
		cnt=0;		cnt1=0;
	}
	return;
}
