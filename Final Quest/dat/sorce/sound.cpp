#include "../../include/GV.h"

void music_sound(){//音楽制御
	if(func_states==0)//マップ画面の時
		if(CheckSoundMem(map_sound[0])==0)//マップ用のサウンドが流れていなかったら流す
			PlaySoundMem(map_sound[0],DX_PLAYTYPE_LOOP);

	return ;
}