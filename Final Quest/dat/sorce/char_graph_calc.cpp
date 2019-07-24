#include "../../include/GV.h"

#define BATTLE_PRO 1	//���}�X��������o�g���ɂȂ邩�̊m��
#define BATTLE_NO_NUM 4	//�Œች�}�X�͐퓬�ɂȂ�Ȃ�

/*�������ۂ��̃t���Owalk_flag��x,y���W��32�̔{���̎��̂ݕύX�����B*/

int decide_battle(){//�����Ă���Œ��o�g���ɓ˓����邩�ǂ��������߂�֐�
	static int cnt=0,x=0,y=0;
	if(cnt>BATTLE_NO_NUM){//�Œ�BATTLE_NO_NUM��ԕ����Ȃ��Ɛ퓬�ɂȂ�Ȃ�
		if(GetRand(BATTLE_PRO)==0 && (x!=ch[0].x || y!=ch[0].y)){//BATTLE_PRO���̂P�̊m���@���@�O�̍��W�Ɠ����łȂ���ΐ퓬(�ǂɂԂ������܂ܕ����Ă��鎞�ɐ퓬�ɂȂ�Ȃ��悤�ɂ�������)
//			stbt_capch();
			stbt_capch_flag=1;//�퓬�ɓ���I�[�v�j���O�摜����邽�߂ɉ�ʂ�16�����L���v�`�����邽�߂̃t���O�𗧂Ă�
			cnt=0;//����ԕ��������������J�E���^��0��
			func_states=1;//�}�b�v��ʂ���퓬�I�[�v�j���O��ʂɊ֐��̐���ϐ���ύX
			StopSoundMem(map_sound[0]);//�o�����I�Ɖ��𗬂��B
			return 1;
		}
	}
	if(x==ch[0].x && y==ch[0].y)
		return 0;
	cnt++;
	x=ch[0].x;
	y=ch[0].y;
	return 0;
}

int can_walk_decide(int x,int y,int muki){//�������������Ƃ��Ă���������i�s�\�ł��邩�����߂�֐�
	if(decide_battle()==1)
		return 2;
	else if(mapd[ y/WIDE + proceed_y[muki] ][ x/WIDE + proceed_x[muki] ]==0)
		return 0;
	else
		return 1;
}


void char_graph_calc(){//�L�����̑���(�ړ�)����
	int i,inkey[4]={KEY_INPUT_LEFT,KEY_INPUT_UP,KEY_INPUT_RIGHT,KEY_INPUT_DOWN};

	if(ch[0].x<=0 || ch[0].y<=0 || ch[0].x>=WIND_WIDE-WIDE || ch[0].y>=WIND_HIGHT-WIDE){//�}�b�v���O�ɏo���Ƃ�
		if		(ch[0].x<=0){//���ɏo����
			ch[0].x=WIND_WIDE -WIDE*2;//y���̂܂܂ň�ԉE��
			stage_map--;//�}�b�v����-1(����͂��̃}�b�v�ړ��̎d�l�ɂ��������ĕύX����)
		}
		else if	(ch[0].y<=0){//��ɏo����
			ch[0].y=WIND_HIGHT-WIDE*2;//x���̂܂܂ň�ԉ���
			stage_map--;//�}�b�v����-1(����͂��̃}�b�v�ړ��̎d�l�ɂ��������ĕύX����)
		}
		else if	(ch[0].x>=WIND_WIDE-WIDE){//�E�ɏo����
			ch[0].x=WIDE;
			stage_map++;
		}
		else{//���ɏo����
			ch[0].y=WIDE;
			stage_map++;
		}
		mapini_flag=1;//�}�b�v�f�[�^������������B
		ch[0].walk_cnt =0;//�L�������������J�E���^��������
		ch[0].walk_flag=0;//�L�����������Ă��邩�ǂ����������J�E���^��������
	}

	else if(ch[0].x%WIDE==0 && ch[0].y%WIDE==0){	//x��y�����W��32�̔{���ł��鎞
		if(key[KEY_INPUT_LEFT]==0 && key[KEY_INPUT_UP]==0 && key[KEY_INPUT_RIGHT]==0 && key[KEY_INPUT_DOWN]==0){//�L�[��������ĂȂ���
			ch[0].walk_cnt=0;	//�����J�E���^��߂�
			ch[0].walk_flag=0;
		}
		else{	//�L�[������������Ă��鎞
			for(i=0;i<4;i++){
				if(key[ inkey[i] ] > 0){	//���͂���Ă���L�[�̕�������muki���Z�b�g����
					ch[0].muki=i;
					if(can_walk_decide(ch[0].x,ch[0].y,ch[0].muki)==0){//�����Ă�������ʂ��ꏊ�Ȃ�
						ch[0].walk_flag=1;
						mapd[ ch[0].y/WIDE							][ ch[0].x/WIDE							]=0;
						mapd[ ch[0].y/WIDE + proceed_y[ch[0].muki]	][ ch[0].x/WIDE + proceed_x[ch[0].muki] ]=1;
					}
					else
						ch[0].walk_flag=0;
					break;
				}
			}
			ch[0].walk_cnt++;	//���muki�̕����֕���
		}
	}
	else	//�����ł͂Ȃ���
		ch[0].walk_cnt++;	//���muki�̕����֕���
	
	//walk_cnt��1�s�N�Z��������1������B���֕`�悷��摜���Z�b�g
	ch[0].img = ch_img[0][ (ch[0].walk_cnt%32)/(WIDE/4) + ch[0].muki*4 ];//0~3�͍������摜 4~7�͏�����摜�E�E�Ɛ��l��ϊ�

	return ;
}