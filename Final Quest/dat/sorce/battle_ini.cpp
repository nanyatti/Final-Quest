#include "../../include/GV.h"

void can_sel(){
	switch(ch[0].menu_sel){
//		case 10100:
		case 10200:
		case 10300:
		case 10400:
			ch[0].menu_sel=10000;
			break;
		case 30000:
			ch[0].menu_sel=10000;
			break;
		case 40000:
		case 40100:
		case 40200:
		case 40300:
		case 40400:
			ch[0].menu_sel=10000;
			break;
		case 50000:
		case 50100:
		case 50200:
		case 50300:
		case 50400:
			ch[0].menu_sel=10000;
			break;
	}
	return;
}

void battle_ini(){
	int i,r;
	r=GetRand(20);
	mon[0].btx=BTMON_X;
	mon[0].bty=BTMON_Y;
	mon[0].hp		=600+r;
	mon[0].hp_max	=600+r;
	mon[0].btcnt	=GetRand(235);	//カウンター240で行動可
	mon[0].btcnt_flag=1;			//カウンターを増加させるかのフラグ
	mon[0].btcnt_spd=1.0;			//カウンターが増加するスピード(double)
	mon[0].btgraph_flag=1;			//描画するかどうかのフラグ
	mon[0].btmotion_flag=0;			//モーションをするかのフラグ
	mon[0].btani_flag=0;			//アニメーションをするかのフラグ
	mon[0].img=enemy_img[0];		//敵の描画画像
	mon[0].power=20;				//攻撃力
	mon[0].def=20;					//防御力
	mon[0].strong=20;				//力
	mon[0].weapon=20;				//武器の攻撃力
	mon[0].equip=20;				//装備の防御力
	mon[0].magic=20;
	mon[0].lv=10;	
	mon[0].chsts.power=0;
	mon[0].chsts.def=0;
	mon[0].chsts.strong=0;
	mon[0].chsts.weapon=0;
	mon[0].chsts.equip=0;
	mon[0].chsts.magic=0;
	mon[0].dam_flag=0;				//ダメージ表示するかのフラグ
	mon[0].btact_flag=0;				//フラグ
	mon[0].bttohp=mon[0].hp;
	mon[0].mp		=136;
	mon[0].mp_max	=136;
	mon[0].tp		=0;
	mon[0].menu_sel=10000;
	mon[0].menu_sely=0;
	for(i=0;i<ABI_MAX;i++){
		mon[0].abi[i].flag=0;
		ch[0].abi[i].flag=0;
	}

	ch[0].btx=BTCH_X;				//バトルでのｘ座標
	ch[0].bty=BTCH_Y;				//バトルでのｙ座標
	ch[0].btcnt	=GetRand(235);		//カウンター240で行動可
	ch[0].btcnt_flag=1;
	ch[0].btcnt_spd=1.0;
	ch[0].btgraph_flag=1;
	ch[0].btmotion_flag=0;
	ch[0].btani_flag=0;
	ch[0].dam_flag=0;
	ch[0].btact_flag=0;				//フラグ
	ch[0].bttohp=ch[0].hp;
	ch[0].menu_sel=1;
	ch[0].menu_sely=0;
	ch[0].chsts.power=0;
	ch[0].chsts.def=0;
	ch[0].chsts.strong=0;
	ch[0].chsts.weapon=0;
	ch[0].chsts.equip=0;
	ch[0].chsts.magic=0;
	for(i=0;i<POP_DAM_MAX;i++)	//ダメージを表示するフラグを初期化
		pop_dam[i].flag=0;
	for(i=0;i<ANI_MAX;i++)		//ダメージを表示するフラグを初期化
		ani[i].flag=0;
	ch[0].menu_sel=1;						//メニューの選択状態を1に初期化
	ch[0].menu_sely=0;					//メニューの選択位置を初期化
	victory_flag=0;					//勝利フラグを初期化
	gameover_flag=0;				//ゲームオーバーフラグを初期化
	line.cnt=0;
	line.flag=1;
	line.target=0;
	for(i=0;i<100;i++)
		board[i].flag=0;
	double ran;
	for(i=0;i<100;i++){
		if(i<60){
			r	=GetRand((int)(WIND_HIGHT*sqrt(2.0)));
			sakura[i].x		=GetRand(WIND_WIDE)+r;
			sakura[i].y		=0.0-r;
		}
		else{
			r	=GetRand((int)(WIND_HIGHT*sqrt(2.0)));
			sakura[i].x		=WIND_WIDE+r;
			sakura[i].y		=GetRand(WIND_HIGHT)-r;
		}
		sakura[i].cnt	=0;
		sakura[i].flag	=1;
		if(i<30 || i>=60 && i<80)
			ran=GetRand(80)/100.0+0.1;
		else
			ran=GetRand(40)/100.0+0.1;
		sakura[i].spd	=ran*2;
		sakura[i].enl	=ran;
		sakura[i].rota	=GetRand(60)/100.0+0.3;
	}
typedef struct{
	int flag,cnt;
	double x,y,enl,spd,rota;
}sakura_val_t;
	return ;
}
