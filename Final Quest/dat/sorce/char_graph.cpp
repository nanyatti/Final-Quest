#include "../../include/GV.h"

/*�}�b�v�̃L�����͉��ɂ���(�܂肙���W�����Ȃ�����)�L��������`�悷��K�v������*/
void char_graph(){//�L�����̕`��
	int i,j;
	for(i=0;i<WIND_HIGHT/WIDE;i++){//�c�̃E�B���h�E�T�C�Y���P��ԃT�C�Y�Ŋ��������A�܂�c�̋�Ԍ������[�v
		for(j=0;j<CH_MAX;j++){//�L������
			if(ch[j].y/WIDE==i)//���ݒ������Ă��邙���W�Ɠ����Ȃ�`��
				DrawGraph( ch[j].x , ch[j].y-16 , ch[j].img , TRUE);
		}
	}
	return ;
}