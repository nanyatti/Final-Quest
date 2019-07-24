#include "../../include/GV.h"


#define WALK_RAND 100	//町の人間が歩き回る度合い->多いほどたまにしか動かない

extern int can_walk_decide(int x,int y,int muki);

void mchar_graph_calc(){
	int i;
	for(i=0;i<CH_MAX-1;i++){
		if(ch[i+1].x%WIDE==0 && ch[i+1].y%WIDE==0){	//xもyも座標が32の倍数である時
			ch[i+1].walk_cnt=0;	//歩くカウンタを戻す
			ch[i+1].walk_flag=0;
			if(GetRand(WALK_RAND)==0){//歩き始める
				ch[i+1].muki=GetRand(3);
				if(can_walk_decide(ch[i+1].x,ch[i+1].y,ch[i+1].muki)==0){//向いてる方向が通れる場所なら
					ch[i+1].walk_flag=1;
					mapd[ ch[i+1].y/WIDE							][ ch[i+1].x/WIDE							]=0;
					mapd[ ch[i+1].y/WIDE + proceed_y[ch[i+1].muki]][ ch[i+1].x/WIDE + proceed_x[ch[i+1].muki]  ]=1;				
				}
				else
					ch[i+1].walk_flag=0;
				ch[i+1].walk_cnt++;	//常にmukiの方向へ歩く
			}
		}
		else	//そうではない時
			ch[i+1].walk_cnt++;	//常にmukiの方向へ歩く
		//walk_cntは1ピクセル歩くと1増える。次へ描画する画像をセット
		ch[i+1].img = ch_img[ ch[i+1].kind ][ (ch[i+1].walk_cnt%32)/(WIDE/4) + ch[i+1].muki*4 ];//0~3は左向き画像 4~7は上向き画像・・と数値を変換
	}
	return ;
}