#include "../../include/GV.h"

void map_graph(){//�}�b�v�̕`��
	int i,j;
	for(i=0;i<WIND_WIDE/WIDE;i++){//���̃E�B���h�E�T�C�Y/�P��Ԃ̃T�C�Y�����̋�Ԍ�
		for(j=0;j<WIND_HIGHT/WIDE;j++){//�c�̃E�B���h�E�T�C�Y/�P��Ԃ̃T�C�Y���c�̋�Ԍ�
			DrawGraph( i*WIDE , j*WIDE , mapchip_img[0][0] , TRUE);//��������S�Ă̋�ԂɎŐ���`��
			if(map[stage_map][j][i]!=0)//�Ő��̏�ɉ摜��\�������Ԃ̎�
				DrawGraph( i*WIDE , j*WIDE , mapchip_img[0][ map[stage_map][j][i] ] , TRUE);//���̉摜��`��
		}
	}
	return ;
}
