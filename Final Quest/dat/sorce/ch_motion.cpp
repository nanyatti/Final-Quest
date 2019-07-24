#include "../../include/GV.h"

extern void ani_start(int menu_sel,int target,int actor);
extern void dam_act(ch_t* my,ch_t* you);
extern void end_ini(ch_t *my);
extern void bt_walk(ch_t *my,int i);
extern void cure_act(ch_t* c);
extern void abi_act(ch_t* c);
extern void add_board(const char * st);
void ch0_motion(){//キャラ１が通常攻撃した時のモーション
	char st[100];
	static int cnt=0,cnt1=0;

	if(gameover_flag==1 || victory_flag==1){//ゲームオーバーフラグが立っていたら初期化して処理を抜ける
		cnt=0;	return ;
	}
	if(20<cnt && 40>=cnt)					//20～40カウントの時前へ出る。
		bt_walk(&ch[0],-1);					//2番目の引数は前後どちらに動くかのフラグ

	if(cnt==50)								//50の時行動開始
		ani_start(ch[0].menu_sel,0,100);
	
	if(ch[0].btact_flag==1){				//今の瞬間ダメージアクションをするフラグが立っていたら
		switch(ch[0].menu_sel){
			case 10000:
			case 10100:
			case 20100:
			case 20200:
			case 20300:
			case 20400:
				dam_act(&ch[0],&mon[0]);			//ダメージを与えるアクションの関数(&自分,&ダメージを与える相手)
				sprintf(st,"敵に%dのダメージを与えた",mon[0].dam);
				add_board(st);
				break;
			case 20000:
				cure_act(&ch[0]);
				sprintf(st,"HPが%d回復した",ch[0].dam);
				add_board(st);
				break;
			case 30000:
			case 30100:
			case 30200:
			case 30300:
			case 30400:
				abi_act(&ch[0]);
				break;
			default:
				break;
		}
		ch[0].btact_flag=0;
		cnt1++;
	}

	if(0<cnt1 && 20>=cnt1)					//ダメージアクションから０～２０後に元の位置に戻る
		bt_walk(&ch[0],1);					//2番目の引数は前後どちらに動くかのフラグ

	cnt++;
	if(cnt1>0)								//ダメージアクションの直後からカウント
		cnt1++;

	if(cnt1==60){							//ダメージアクションの直後60カウントでモーション終了
		cnt=0;		cnt1=0;
		end_ini(&ch[0]);
	}
	if(gameover_flag==2 || victory_flag==2){
		cnt=0;		cnt1=0;
	}
	return;
}
