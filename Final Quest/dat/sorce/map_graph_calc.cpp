#include "../../include/GV.h"

void map_ini(){//�}�b�v��ʂ̏���������
	int i,j;

	for(i=1;i<CH_MAX;i++){//��������L�������̏������Bch[0]�͎�l���Ȃ̂�1����CH_MAX�܂ł��������B
		ch[i].walk_cnt	=0;
		ch[i].walk_flag	=0;
	}
	for(i=0;i<WIND_WIDE/WIDE;i++){//����20���
		for(j=0;j<WIND_HIGHT/WIDE;j++){//�c��15���
			if(map[stage_map][j][i]>1)//�ʂ�Ȃ��ꏊ�Ȃ�
				mapd[j][i]	=1;			//�ʂ�Ȃ��t���O�𗧂Ă�
			else
				mapd[j][i]	=0;			//�ʂ��t���O�𗧂Ă�
		}
	}
	mapd[ch[0].y/WIDE][ch[0].x/WIDE]=1;	//��l��������ꏊ��ʂ�Ȃ��ꏊ�Ƃ���

	for(i=1;i<CH_MAX;i++){//���̐l��z�u����B[0]�͎�l���Ȃ̂�1����͂��߂�
		ch[i].x=(GetRand(WIND_WIDE /WIDE -3)+1)*WIDE;//�����ŏꏊ�����߂�
		ch[i].y=(GetRand(WIND_HIGHT/WIDE -3)+1)*WIDE;
		if(mapd[ch[i].y/WIDE][ch[i].x/WIDE]==1){//���߂��ꏊ���ʂ�Ȃ��ꏊ�Ȃ������x�ŏ�����
			i--;
			continue;
		}
		ch[i].flag	=1;//�L�����̕`��t���O�𗧂Ă�
		ch[i].muki	=GetRand(3);//�����������_���Ɍ���
		ch[i].kind	=GetRand(3)+1;//�l�̎�ނ������_���Ɍ���@�F0�͎�l��
		mapd[ch[i].y/WIDE][ch[i].x/WIDE]	=1;//�ʂ�Ȃ��ꏊ�ł���t���O�𗧂Ă�
	}
	mapini_flag=0;//�}�b�v�̏������t���O�����낷�B(�������ɏ�����������Ƃ����Ӗ�)
	return ;
}