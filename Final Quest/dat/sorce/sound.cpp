#include "../../include/GV.h"

void music_sound(){//���y����
	if(func_states==0)//�}�b�v��ʂ̎�
		if(CheckSoundMem(map_sound[0])==0)//�}�b�v�p�̃T�E���h������Ă��Ȃ������痬��
			PlaySoundMem(map_sound[0],DX_PLAYTYPE_LOOP);

	return ;
}