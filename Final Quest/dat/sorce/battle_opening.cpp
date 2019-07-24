#include "../../include/GV.h"
#define ACCEL 1.5	//加速度の大きさ。大きいほど早く落ちる。

//バトルオープニングの仕様については仕様13参照
void battle_opening(){
	int i,j;
	static int cnt=0;
	static double stbtx[16],stbty[16],randx[16],randy[16];

	if(cnt==0){//最初に処理が行われた時、16個の画像の初期座標を設定
		PlaySoundMem(se_sound[0],DX_PLAYTYPE_BACK);
		for(i=0;i<4;i++){
			for(j=0;j<4;j++){
				stbtx[i*4+j]=WIND_WIDE/4*j;//描画する各ｘ座標
				stbty[i*4+j]=WIND_HIGHT/4*i;//描画する各ｙ座標
				randx[i*4+j]=GetRand(30);//ばらけさせるための乱数
				randy[i*4+j]=GetRand(30);//ばらけさせるための乱数
			}
		}
	}
	if(cnt<8){//8カウントの間中心から外へ散らばらせる
		for(i=0;i<4;i++){
			for(j=0;j<4;j++){
				stbtx[i*4+j]+=(-45+randx[i*4+j]+30*j)/8.0;//四方八方に飛び散らせる
				stbty[i*4+j]+=(-45+randy[i*4+j]+30*i)/8.0;//四方八方に飛び散らせる
			}
		}
	}
	if(cnt==8){	////落ちる時にばらけさせるための乱数生成
		for(i=0;i<4;i++){
			for(j=0;j<4;j++){
				randx[i*4+j]=-2.0+GetRand(40)/10.0;
				randy[i*4+j]=1.0+GetRand(10)/10.0;
			}
		}
	}
	if(cnt>=60 && cnt<=150){	//落ちるモーション
		double t=(cnt-60.0)*17/1000;
		for(i=0;i<4;i++){
			for(j=0;j<4;j++){
				stbtx[i*4+j]+=randx[i*4+j];
				stbty[i*4+j]+=t*t*ACCEL*randy[i*4+j]/2.0*10;//落ちる時加速度をもって計算。ACCELの値で変更可能
			}
		}
	}
	for(i=0;i<16;i++)//描画
		DrawGraph((int)stbtx[i],(int)stbty[i],stbt_img[i],FALSE);
	cnt++;
	if(cnt==150){//150になったら次のシーンへ
//	if(cnt==1){//150になったら次のシーンへ
		cnt=0;
		func_states=2;
	}
	return;
}

#define STBTTIME 120.0

void battle_opening2(){//戦闘に入る時のオープニング２
	static int cnt=0;
	if(cnt==0){//オープニング２が始まる瞬間、一旦全部描画して、その画面をキャプチャして反映させる前にクリアする。この１枚のキャプチャした画像でオープニングを作る
		PlaySoundMem(battle_sound[0],DX_PLAYTYPE_LOOP);
		DrawGraph(0,0,back_img[0],FALSE);
		DrawGraph(BTMON_X ,BTMON_Y ,mon[0].img,TRUE);
		DrawGraph(BTCH_X,BTCH_Y,ch_img[0][0],TRUE);
		stbt_img[0] = MakeGraph( WIND_WIDE , WIND_HIGHT ) ;
		GetDrawScreenGraph( 0 , 0 , WIND_WIDE , WIND_HIGHT , stbt_img[0] ) ;
		ClearDrawScreen();
	}
	if(cnt>83 && cnt<=170)
		DrawRotaGraph( -50+cnt , 100 , 2.0f , 0 , stbt_img[0] , FALSE ) ;
	if(cnt>170 && cnt<=255)
		DrawRotaGraph( 500-cnt , 400 , 2.0f , 0 , stbt_img[0] , FALSE ) ;
	if(cnt>255 && cnt<=255+STBTTIME){
		int t=cnt-255;
		DrawExtendGraph( (int)((WIND_WIDE/2+WIND_WIDE/4)-(WIND_WIDE/2+WIND_WIDE/4)*t/STBTTIME) , 0 , (int)(WIND_WIDE*t/STBTTIME) , (int)(WIND_HIGHT*t/STBTTIME) , stbt_img[0] , TRUE ) ;
	}
	cnt++;
	if(cnt==255+STBTTIME){//時間になったらオープニングを終了して戦闘へ
//	if(cnt==1){//時間になったらオープニングを終了して戦闘へ
		cnt=0;
		func_states=3;
	}
	return;
}