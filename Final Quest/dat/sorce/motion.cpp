#include "../../include/GV.h"

extern double rano(double sigma, double average);
extern int damdec(ch_t *c,int to,int actkind);
extern int tp_calc(int dam,int hp);

void ani_start(int menu_sel,int target,int actor){//攻撃アニメーションの開始
	int i;
	for(i=0;i<ANI_MAX-2;i++){			//使ってないアニメーションを探す
		if(ani[i].flag==0)
			break;
	}
	ani[i].flag=1;						//アニメーション使用フラグを立てる
	ani[i].target=target;					//攻撃のターゲットを指定(0だと敵0を示す)
	ani[i].kind=menu_sel;				//アニメーションの種類を指定する。(ch[0].menu_selは選択した項目)
	ani[i].cnt=0;						//アニメーションのカウンタを初期化
	ani[i].actor=actor;
	return ;
}

void dam_c(ch_t* c){
	int i;
	c->dam		=damdec(c,2,c->menu_sel);//ダメージ決定)
	c->bttohp	-=c->dam;				//体力が時間差で減っていく、最終的な終着位置
	if(c->bttohp<0)	c->bttohp=0;
	for(i=0;i<POP_DAM_MAX;i++)					//使用していないダメージポップアニメーションを探す
		if(pop_dam[i].flag==0)
			break;
	pop_dam[i].flag=1;							//使用フラグを立てる
	pop_dam[i].cnt=0;							//カウンタ初期化
	pop_dam[i].dam=c->dam;					//ダメージ値指定
	pop_dam[i].x=c->btx-30;						//x,y値指定
	pop_dam[i].y=c->bty-25;
	pop_dam[i].type=0;
}

void add_board(const char * st){
	int i;
	for(i=0;i<100;i++)
		if(board[i].flag==0)
			break;
	board[i].flag=1;
	board[i].cnt=0;
	strcpy(board[i].st,st);
	return ;
}

void abi_act(ch_t* c){
	char st[100];
	c->tp+=8+GetRand(5);						//1回の攻撃で自分に８～１３tpがたまる
	if(c->tp>300)	c->tp=300;					//TPは300%が最大
	switch(c->menu_sel){
		case 30000:
			c->abi[0].flag=1;
			//ヘイト増加処理追加必要あり
			break;
		case 30100:
			c->chsts.def	= c->def/3;
			c->chsts.power	= -c->power/3;
			c->abi[1].flag=1;
			c->abi[1].cnt=0;
			add_board("防御力が上がった");
			add_board("攻撃力が下がった");
			break;
		case 30200:
			c->chsts.def	= -c->def/3;
			c->chsts.power	= c->power/3;
			c->abi[2].flag=1;
			c->abi[2].cnt=0;
			add_board("攻撃力が上がった");
			add_board("防御力が下がった");
			break;
		case 30300:
			dam_c(c);
			c->abi[3].flag=1;
			c->abi[3].cnt=0;
			add_board("次回攻撃時２倍のダメージの体制になった");
			sprintf(st,"武力の泉の反動で%dダメージを受けた",c->dam);
			add_board(st);
			break;
		case 30400:
			c->abi[4].flag=1;
			c->abi[4].cnt=0;
			add_board("次回詠唱時間が4分の1の体制になった");
			break;
		default:
			break;
	}
	return ;
}
void cure_act(ch_t* c){
	int i;
	c->dam		=damdec(c,0,c->menu_sel);//ダメージ決定)
	c->mp-=9;//MP使った分だけ減少
	c->hp+=c->dam;
	c->bttohp+=c->dam;
	if(c->hp>c->hp_max){c->hp=c->hp_max; c->bttohp=c->hp;}
	if(c->mp<0)	c->mp=0;
	c->tp+=8+GetRand(5);						//1回の攻撃で自分に８～１３tpがたまる
	if(c->tp>300)	c->tp=300;					//TPは300%が最大
	for(i=0;i<POP_DAM_MAX;i++)					//使用していないダメージポップアニメーションを探す
		if(pop_dam[i].flag==0)
			break;
	pop_dam[i].flag=1;							//使用フラグを立てる
	pop_dam[i].cnt=0;							//カウンタ初期化
	pop_dam[i].dam=c->dam;					//ダメージ値指定
	pop_dam[i].x=c->btx-30;						//x,y値指定
	pop_dam[i].y=c->bty-25;
	pop_dam[i].type=1;
	if(c->abi[3].flag==1)c->abi[3].flag=2;
	if(c->abi[4].flag==1)c->abi[4].flag=2;
	return ;
}

void dam_act(ch_t* my,ch_t* you){				//ダメージアクションを行う
	int del_mp[5]={9,8,16,24,32},i;				//消費MP
	you->dam		=damdec(my,0,my->menu_sel);//ダメージ決定)
	if(my->abi[3].flag==1)
		you->dam*=2;
	you->bttohp	=you->hp-you->dam;				//体力が時間差で減っていく、最終的な終着位置
	you->tp+=tp_calc(you->dam,you->hp_max);		//ダメージとHPマックス値から相手にたまるTPを算出	
	my->tp+=8+GetRand(5);						//1回の攻撃で自分に８～１３tpがたまる
	if(my->menu_sel>=20000&&my->menu_sel<30000){//魔法なら
		my->mp-=del_mp[(my->menu_sel-20000)/100];//MP使った分だけ減少
		if(my->mp<0)
			my->mp=0;
	}
	if(my->tp>300)	my->tp=300;					//TPは300%が最大
	if(you->tp>300)	you->tp=300;
	for(i=0;i<POP_DAM_MAX;i++)					//使用していないダメージポップアニメーションを探す
		if(pop_dam[i].flag==0)
			break;
	pop_dam[i].flag=1;							//使用フラグを立てる
	pop_dam[i].cnt=0;							//カウンタ初期化
	pop_dam[i].dam=you->dam;					//ダメージ値指定
	pop_dam[i].x=you->btx-30;						//x,y値指定
	pop_dam[i].y=you->bty-25;
	pop_dam[i].type=0;
	if(my->abi[3].flag==1)my->abi[3].flag=2;
	if(my->abi[4].flag==1)
		my->abi[4].flag=2;
	return ;
}

void end_ini(ch_t *my){	//終了処理
	my->menu_sel=1;		//選択項目を初期化
	my->menu_sely=0;	//選択位置を初期化
	my->btmotion_flag=0;//モーションのフラグを初期化
	my->btcnt_flag=1;	//ATBカウンター増加フラグを立てる。
	my->btcnt=0;		//カウンタ初期化
	return;
}

void bt_walk(ch_t *my,int i){//キャラが前に出たり後ろに下がったりするモーション
	if(i==-1)	my->btx--;	
	else		my->btx++;
	return ;
}

