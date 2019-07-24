#include "../../include/GV.h"

void map_ini(){//マップ画面の初期化処理
	int i,j;

	for(i=1;i<CH_MAX;i++){//町を歩くキャラ分の初期化。ch[0]は主人公なので1からCH_MAXまでを初期化。
		ch[i].walk_cnt	=0;
		ch[i].walk_flag	=0;
	}
	for(i=0;i<WIND_WIDE/WIDE;i++){//横の20区間
		for(j=0;j<WIND_HIGHT/WIDE;j++){//縦の15区間
			if(map[stage_map][j][i]>1)//通れない場所なら
				mapd[j][i]	=1;			//通れないフラグを立てる
			else
				mapd[j][i]	=0;			//通れるフラグを立てる
		}
	}
	mapd[ch[0].y/WIDE][ch[0].x/WIDE]=1;	//主人公がいる場所を通れない場所とする

	for(i=1;i<CH_MAX;i++){//町の人を配置する。[0]は主人公なので1からはじめる
		ch[i].x=(GetRand(WIND_WIDE /WIDE -3)+1)*WIDE;//乱数で場所を決めて
		ch[i].y=(GetRand(WIND_HIGHT/WIDE -3)+1)*WIDE;
		if(mapd[ch[i].y/WIDE][ch[i].x/WIDE]==1){//決めた場所が通れない場所ならもう一度最初から
			i--;
			continue;
		}
		ch[i].flag	=1;//キャラの描画フラグを立てる
		ch[i].muki	=GetRand(3);//向きをランダムに決定
		ch[i].kind	=GetRand(3)+1;//人の種類をランダムに決定　：0は主人公
		mapd[ch[i].y/WIDE][ch[i].x/WIDE]	=1;//通れない場所であるフラグを立てる
	}
	mapini_flag=0;//マップの初期化フラグをおろす。(もう既に初期化したよという意味)
	return ;
}