#include "../../include/GV.h"

void fps_graph(){//FPS�`��
	if(fps_average!=0)//0����֎~�ɂ��AFPS���ς�0����Ȃ�������`��
		DrawFormatString(0,0,GetColor(255,255,255),"FPS %.1f",1000.0/(double)fps_average);
	return;
}