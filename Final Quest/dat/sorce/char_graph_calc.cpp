#include "../../include/GV.h"

#define BATTLE_PRO 1	//何マス歩いたらバトルになるかの確率
#define BATTLE_NO_NUM 4	//最低何マスは戦闘にならない

/*歩くか否かのフラグwalk_flagはx,y座標が32の倍数の時のみ変更される。*/

int decide_battle(){//歩いている最中バトルに突入するかどうかを決める関数
	static int cnt=0,x=0,y=0;
	if(cnt>BATTLE_NO_NUM){//最低BATTLE_NO_NUM区間歩かないと戦闘にならない
		if(GetRand(BATTLE_PRO)==0 && (x!=ch[0].x || y!=ch[0].y)){//BATTLE_PRO分の１の確率　かつ　前の座標と同じでなければ戦闘(壁にぶつかったまま歩いている時に戦闘にならないようにしたもの)
//			stbt_capch();
			stbt_capch_flag=1;//戦闘に入るオープニング画像を作るために画面を16分割キャプチャするためのフラグを立てる
			cnt=0;//何区間歩いたかを示すカウンタを0に
			func_states=1;//マップ画面から戦闘オープニング画面に関数の制御変数を変更
			StopSoundMem(map_sound[0]);//バリン！と音を流す。
			return 1;
		}
	}
	if(x==ch[0].x && y==ch[0].y)
		return 0;
	cnt++;
	x=ch[0].x;
	y=ch[0].y;
	return 0;
}

int can_walk_decide(int x,int y,int muki){//自分が歩こうとしている向きが進行可能であるかを決める関数
	if(decide_battle()==1)
		return 2;
	else if(mapd[ y/WIDE + proceed_y[muki] ][ x/WIDE + proceed_x[muki] ]==0)
		return 0;
	else
		return 1;
}


void char_graph_calc(){//キャラの操作(移動)制御
	int i,inkey[4]={KEY_INPUT_LEFT,KEY_INPUT_UP,KEY_INPUT_RIGHT,KEY_INPUT_DOWN};

	if(ch[0].x<=0 || ch[0].y<=0 || ch[0].x>=WIND_WIDE-WIDE || ch[0].y>=WIND_HIGHT-WIDE){//マップより外に出たとき
		if		(ch[0].x<=0){//左に出たら
			ch[0].x=WIND_WIDE -WIDE*2;//yそのままで一番右へ
			stage_map--;//マップ情報を-1(これはそのマップ移動の仕様にしたがって変更する)
		}
		else if	(ch[0].y<=0){//上に出たら
			ch[0].y=WIND_HIGHT-WIDE*2;//xそのままで一番下へ
			stage_map--;//マップ情報を-1(これはそのマップ移動の仕様にしたがって変更する)
		}
		else if	(ch[0].x>=WIND_WIDE-WIDE){//右に出たら
			ch[0].x=WIDE;
			stage_map++;
		}
		else{//下に出たら
			ch[0].y=WIDE;
			stage_map++;
		}
		mapini_flag=1;//マップデータを初期化する。
		ch[0].walk_cnt =0;//キャラが歩いたカウンタを初期化
		ch[0].walk_flag=0;//キャラが歩いているかどうかを示すカウンタを初期化
	}

	else if(ch[0].x%WIDE==0 && ch[0].y%WIDE==0){	//xもyも座標が32の倍数である時
		if(key[KEY_INPUT_LEFT]==0 && key[KEY_INPUT_UP]==0 && key[KEY_INPUT_RIGHT]==0 && key[KEY_INPUT_DOWN]==0){//キーが押されてない時
			ch[0].walk_cnt=0;	//歩くカウンタを戻す
			ch[0].walk_flag=0;
		}
		else{	//キーが何か押されている時
			for(i=0;i<4;i++){
				if(key[ inkey[i] ] > 0){	//入力されているキーの方向うにmukiをセットする
					ch[0].muki=i;
					if(can_walk_decide(ch[0].x,ch[0].y,ch[0].muki)==0){//向いてる方向が通れる場所なら
						ch[0].walk_flag=1;
						mapd[ ch[0].y/WIDE							][ ch[0].x/WIDE							]=0;
						mapd[ ch[0].y/WIDE + proceed_y[ch[0].muki]	][ ch[0].x/WIDE + proceed_x[ch[0].muki] ]=1;
					}
					else
						ch[0].walk_flag=0;
					break;
				}
			}
			ch[0].walk_cnt++;	//常にmukiの方向へ歩く
		}
	}
	else	//そうではない時
		ch[0].walk_cnt++;	//常にmukiの方向へ歩く
	
	//walk_cntは1ピクセル歩くと1増える。次へ描画する画像をセット
	ch[0].img = ch_img[0][ (ch[0].walk_cnt%32)/(WIDE/4) + ch[0].muki*4 ];//0~3は左向き画像 4~7は上向き画像・・と数値を変換

	return ;
}