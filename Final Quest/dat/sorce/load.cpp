#include "../../include/GV.h"
#define LOAD_NUM 44.0	//下でdisp_load()をよんでいる回数

void disp_load(){//現在何％ロードしているか表示する
	static int load_now_num=0;

	ProcessMessage();
	ClearDrawScreen();

	load_now_num++;

	DrawFormatString(WIND_WIDE/2-60,WIND_HIGHT/2+160,color[0],"now loading....");
	DrawFormatString(WIND_WIDE/2-20,WIND_HIGHT/2+200,color[0],"%.0f％",load_now_num/LOAD_NUM*100);

	ScreenFlip();

	return ;
}

void dat_load(){//データのロード

	color[0]=GetColor(255,255,255);
	color[1]=GetColor(255,	0,	0);
	color[2]=GetColor(	0,255,	0);
	color[3]=GetColor(	0,	0,255);
	color[4]=GetColor(255,255,	0);
	color[5]=GetColor(	0,255,255);
	color[6]=GetColor( 50,150,150);
	color[7]=GetColor(100,100,100);
	color[8]=GetColor(200,	0,	0);
	color[9]=GetColor(200,200,	0);
	color[10]=GetColor(	0,255,100);

	fhandle[0]=CreateFontToHandle( "HG丸ｺﾞｼｯｸM-PRO" , 18 , 3 ,DX_FONTTYPE_ANTIALIASING_EDGE) ;
//	fhandle[0]=CreateFontToHandle( "Highlight LET" , 18 , 3 ,DX_FONTTYPE_ANTIALIASING_EDGE) ;
//	fhandle[0]=CreateFontToHandle( "John Handy LET" , 18 , 3 ,DX_FONTTYPE_ANTIALIASING_EDGE) ;
//	fhandle[0]=CreateFontToHandle( "MV Boli" , 18 , 3 ,DX_FONTTYPE_ANTIALIASING_EDGE) ;
//	fhandle[0]=CreateFontToHandle( "Orange LET" , 18 , 3 ,DX_FONTTYPE_ANTIALIASING_EDGE) ;


	back_img[0]		=LoadGraph("dat/img/back/0.png");
	disp_load() ;
	back_img[10]	=LoadGraph("dat/img/battle/10.png");
	disp_load() ;
	enemy_img[0]	=LoadGraph("dat/img/mons/0.png");
	disp_load() ;
	icon_img		=LoadGraph("dat/img/icon/100.png");
	disp_load() ;
	btetc_img[0]	=LoadGraph("dat/img/animation/2.png");
	disp_load() ;
	btetc_img[1]	=LoadGraph("dat/img/battle/0.png");
	disp_load() ;
	btetc_img[2]	=LoadGraph("dat/img/battle/2.png");
	disp_load() ;

	se_sound[0]		=LoadSoundMem("dat/sound/SE/0.ogg");
	disp_load() ;
	se_sound[1]		=LoadSoundMem("dat/sound/SE/1.ogg");
	disp_load() ;
	se_sound[2]		=LoadSoundMem("dat/sound/SE/2.ogg");
	disp_load() ;
	se_sound[3]		=LoadSoundMem("dat/sound/SE/3.ogg");
	disp_load() ;
	se_sound[4]		=LoadSoundMem("dat/sound/SE/4.ogg");
	disp_load() ;
	se_sound[5]		=LoadSoundMem("dat/sound/SE/5.ogg");
	disp_load() ;
	se_sound[6]		=LoadSoundMem("dat/sound/SE/6.ogg");
	disp_load() ;
	se_sound[100]		=LoadSoundMem("dat/sound/SE/100.ogg");
	disp_load() ;
	se_sound[200]		=LoadSoundMem("dat/sound/SE/200.ogg");
	disp_load() ;
	se_sound[201]		=LoadSoundMem("dat/sound/SE/201.ogg");
	disp_load() ;
	se_sound[202]		=LoadSoundMem("dat/sound/SE/202.ogg");
	disp_load() ;
	se_sound[203]		=LoadSoundMem("dat/sound/SE/203.ogg");
	disp_load() ;
	se_sound[204]		=LoadSoundMem("dat/sound/SE/204.ogg");
	disp_load() ;

	se_sound[301]		=LoadSoundMem("dat/sound/SE/301.ogg");
	disp_load() ;
	se_sound[302]		=LoadSoundMem("dat/sound/SE/302.ogg");
	disp_load() ;
	se_sound[303]		=LoadSoundMem("dat/sound/SE/303.ogg");
	disp_load() ;
	se_sound[304]		=LoadSoundMem("dat/sound/SE/304.ogg");
	disp_load() ;

	//se_sound[100]~[200]までは予約
	map_sound[0]	=LoadSoundMem("dat/sound/map/0.ogg");
	disp_load() ;
	battle_sound[0]	=LoadSoundMem("dat/sound/battle/0.ogg");
	disp_load() ;

	LoadDivGraph( "dat/img/icon/0.png" , 5 , 1 , 5 , 97 , 17 , icon0_img);
	disp_load() ;
	LoadDivGraph( "dat/img/mapchip/0/0.png" , 4 , 4 , 1 , 32 , 32 , mapchip_img[0]);
	disp_load() ;
	LoadDivGraph( "dat/img/char/0.png" , 16 , 4 , 4 , 32 , 53 , ch_img[0]);
	disp_load() ;
	LoadDivGraph( "dat/img/char/1.png" , 16 , 4 , 4 , 32 , 48 , mch_img[0]);
	disp_load() ;
	LoadDivGraph( "dat/img/char/2.png" , 16 , 4 , 4 , 32 , 48 , mch_img[1]);
	disp_load() ;
	LoadDivGraph( "dat/img/char/3.png" , 16 , 4 , 4 , 32 , 48 , mch_img[2]);
	disp_load() ;
	LoadDivGraph( "dat/img/char/4.png" , 16 , 4 , 4 , 32 , 48 , mch_img[3]);
	disp_load() ;
	LoadDivGraph( "dat/img/icon/1.png" , 5 , 1 , 5 , 157 , 17 , icon1_img[0]);
	disp_load() ;
	LoadDivGraph( "dat/img/icon/2.png" , 5 , 1 , 5 , 157 , 17 , icon1_img[1]);
	disp_load() ;
	LoadDivGraph( "dat/img/icon/3.png" , 5 , 1 , 5 , 157 , 17 , icon1_img[2]);
	disp_load() ;
	LoadDivGraph( "dat/img/icon/4.png" , 5 , 1 , 5 , 157 , 17 , icon1_img[3]);
	disp_load() ;
	LoadDivGraph( "dat/img/icon/5.png" , 5 , 1 , 5 , 157 , 17 , icon1_img[4]);
	disp_load() ;
	LoadDivGraph( "dat/img/num/0.png" , 10 , 10 , 1 , 16 , 10 , num_img[0]);
	disp_load() ;
	LoadDivGraph( "dat/img/num/1.png" , 11 , 11 , 1 , 15 , 19 , num_img[1]);
	disp_load() ;
	LoadDivGraph( "dat/img/num/2.png" , 10 , 10 , 1 , 16 , 18 , num_img[2]);
	disp_load() ;
	LoadDivGraph( "dat/img/num/3.png" , 10 , 10 , 1 , 16 , 18 , num_img[3]);
	disp_load() ;


	LoadDivGraph( "dat/img/animation/0.png" , 25 , 5 , 5 , 96 , 96 , ani_img[0]);
	disp_load() ;
	LoadDivGraph( "dat/img/animation/1.png" , 40 , 8 , 5 , 96 , 96 , ani_img[1]);
	disp_load() ;

	/*キャラクタの素材画像が主人公と町のキャラで種類が違う。
	実際に画像を見たら解ると思うが、素材によって向いている向きが違うので
	ここで、みんなが同じ向きを向くように修正。
	素材をきちんと作っておけばこの処理の必要は無い*/
	int uk[4]={1,3,2,0};
	for(int s=0;s<4;s++)
		for(int i=0;i<4;i++)
			for(int j=0;j<4;j++)
				ch_img[1+s][i*4+j] = mch_img[s][uk[i]*4+j];
	//これで全てのキャラ素材が左、上、右、下の順に並んだ。
	return ;
}