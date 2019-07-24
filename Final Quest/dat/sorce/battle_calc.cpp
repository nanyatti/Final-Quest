#include "../../include/GV.h"
extern void battle_opening();
extern void battle_opening2();

extern void	battle_graph();
extern void meter_disp();
extern void victory_graph();
extern void gameover_graph();

extern void icon_graph();
extern void mon0_motion();
extern void ch0_motion();

extern void dam_graph();
extern void ani_graph();
extern void add_board(const char * st);
extern void board_graph();
extern void can_sel();
extern void battle_ini();
extern void line_graph();
extern void sakura_calc();
extern void sakura_graph();
//ATBカウンタの仕様については、仕様書10へ
void cnt_calc() {//ATBカウンタ制御
	if (mon[0].btcnt_flag == 1 && gameover_flag == 0 && victory_flag == 0) {//ATBカウンタを増加させるフラグが立っていたて、ゲームオーバーでも勝利でもなければ
		mon[0].btcnt++;
		if (mon[0].btcnt == 240)//ATBカウンタがMAXなら
			mon[0].btcnt_flag = 0;//増加フラグを下げる
	}
	//if(mon[0].btcnt_flag==1 && gameover_flag==0 && victory_flag==0){//ATBカウンタを増加させるフラグが立っていたて、ゲームオーバーでも勝利でもなければ
	//	mon[0].btcnt++;
	//	if(mon[0].btcnt==240)//ATBカウンタがMAXなら
	//		mon[0].btcnt_flag=0;//増加フラグを下げる
	//}
	if (ch[0].btcnt_flag == 1 && gameover_flag == 0 && victory_flag == 0) {
		ch[0].btcnt++;
		if (ch[0].btcnt == 240)
			ch[0].btcnt_flag = 0;
	}
	return;
}
//メニュー選択計算については仕様書11へ
void menu_sel_cal() {
	if (key[KEY_INPUT_UP] == 2) {//上キーが押されていたら
		ch[0].menu_sel--;			//選択状態を上のものへ
		ch[0].menu_sely--;		//選択位置を上へ
		if (ch[0].menu_sely == -1) {	//選択位置が一番上を超えたら
			ch[0].menu_sel += 5;	//一番下へ。5は選択項目の最大数
			ch[0].menu_sely = 4;	//一番下へ。4は選択表示項目の最大数-1
		}
		PlaySoundMem(se_sound[2], DX_PLAYTYPE_BACK);
	}
	if (key[KEY_INPUT_DOWN] == 2) {
		ch[0].menu_sel++;
		ch[0].menu_sely++;
		if (ch[0].menu_sely == 5) {
			ch[0].menu_sel -= 5;
			ch[0].menu_sely = 0;
		}
		PlaySoundMem(se_sound[2], DX_PLAYTYPE_BACK);
	}
	if (key[KEY_INPUT_X] == 2) {//決定ボタンが押されていたら
		ch[0].menu_sel = ch[0].menu_sel * 100;	//決定ボタンが押されるたびに選択状態*100になる
		ch[0].menu_sely = 0;			//選択位置を初期に
		if (ch[0].menu_sel < 10000)//選択が全て完了していなければ
			PlaySoundMem(se_sound[1], DX_PLAYTYPE_BACK);
		else {
			can_sel();
			PlaySoundMem(se_sound[3], DX_PLAYTYPE_BACK);
			ch[0].btmotion_flag = 1;//キャラのモーションを行うフラグを立てる
		}
	}
	else if (key[KEY_INPUT_Z] == 2) {//キャンセルなら
		ch[0].menu_sel = 1;	//選択状態を戻す
		ch[0].menu_sely = 0;//選択位置を戻す
		PlaySoundMem(se_sound[4], DX_PLAYTYPE_BACK);
	}

	return;
}

void mon_act_dec() {
	mon[0].btmotion_flag = 1;	//モンスターのモーションフラグを立てる
	return;
}

void abi_upstop(ch_t* c) {
	int time[ABI_MAX] = { ABI_TIME0,ABI_TIME1,ABI_TIME2,ABI_TIME3,ABI_TIME4 };
	int i;
	for (i = 0; i < ABI_MAX; i++) {
		if (c->abi[i].flag >= 1) {
			c->abi[i].cnt++;
			if (c->abi[i].cnt == time[i] * 60) {
				if (i == 1) {
					c->chsts.def = 0;
					c->chsts.power = 0;
					add_board("ディフェンダーの効果が切れた");
				}
				else if (i == 2) {
					c->chsts.def = 0;
					c->chsts.power = 0;
					add_board("バーサクの効果が切れた");
				}
				else if (i == 3) {
					if (c->abi[i].flag == 1)
						add_board("武力の泉の効果が切れた");
				}
				else if (i == 4) {
					if (c->abi[i].flag == 1)
						add_board("魔力の泉の効果が切れた");
				}
				c->abi[i].flag = 0;
			}
		}
	}
	return;
}

void abi_cntup() {
	abi_upstop(&ch[0]);
	abi_upstop(&mon[0]);
	return;
}
void sakura_calc() {
	int i;
	for (i = 0; i < 100; i++) {
		if (sakura[i].x < -24)
			sakura[i].x = WIND_WIDE + 24;
		if (sakura[i].y > WIND_HIGHT + 24)
			sakura[i].y = -24;
		sakura[i].x -= sakura[i].spd;
		sakura[i].y += sakura[i].spd;
	}
	return;
}
void victory_dec() {//勝利判定と、勝利モーション処理
	static int cnt = 0;
	if (mon[0].hp <= 0)
		victory_flag = 1;
	else
		return;

	if (CheckSoundMem(battle_sound[0]) == 1)//バトルの音楽がかかっていたら止める
		StopSoundMem(battle_sound[0]);

	cnt++;
	if (cnt == 240 - 1)
		victory_flag = 2;
	if (cnt == 240) {
		func_states = 0;//マップ画面へ
		cnt = 0;
	}
	return;
}

void gameover_dec() {//ゲームオーバー判定と、ゲームオーバーモーション処理
	static int cnt = 0;
	if (ch[0].hp <= 0)
		gameover_flag = 1;
	else
		return;

	if (CheckSoundMem(battle_sound[0]) == 1)//バトルの音楽が流れていたら止める
		StopSoundMem(battle_sound[0]);

	cnt++;
	if (cnt == 240 - 1)
		gameover_flag = 2;
	if (cnt == 240) {
		func_states = -1;//ゲームの初期化へ
		cnt = 0;
	}
	return;
}

void battle_calc() {//バトルにおいて、どの関数に処理を渡すかを制御
	static int cnt = 0;

	if (cnt == 0)//初めて戦闘シーンになったとき初期化
		battle_ini();

	switch (func_states) {
	case 1://画面が割れて落ちるシーン
		battle_opening();
		break;
	case 2://戦闘突入シーン
		battle_opening2();
		break;
	case 3://戦闘シーン
		cnt_calc();//カウント計算
		if (gameover_flag == 0 && victory_flag == 0) {//戦闘が終了していなかったら
			if (ch[0].btmotion_flag == 0 && ch[0].btcnt == 240)//行動していなくてATBカウンタがMAXなら
				menu_sel_cal();
			if (mon[0].btmotion_flag == 0 && mon[0].btcnt == 240)
				mon_act_dec();
		}
		if (ch[0].btmotion_flag == 1)//モーションフラグが立っていたらモーションを行う
			ch0_motion();
		if (mon[0].btmotion_flag == 1)
			mon0_motion();

		gameover_dec();//ゲームオーバーかどうかを決める
		victory_dec();//勝利かどうかを決める

		battle_graph();//バトルシーンを描画する
		meter_disp();//メーターを描画する
		//damage_calc();//ダメージを計算する
		dam_graph();//ダメージを描画する
		ani_graph();
		abi_cntup();
		sakura_calc();
		sakura_graph();
		board_graph();
		line_graph();
		if (gameover_flag == 1)//ゲームオーバーフラグが立っていたらゲームオーバー
			gameover_graph();
		else if (victory_flag == 1)//勝利フラグが立っていたら勝利
			victory_graph();
		else if (ch[0].btmotion_flag == 0 && ch[0].btcnt == 240)//ATBカウンタがマックスでモーションしてなかったら選択項目を描画
			icon_graph();
		break;
	default:
		exit(99);
		break;
	}

	cnt++;

	if (func_states <= 0)//戦闘シーンが終わった時にカウンターを戻す。
		cnt = 0;
	return;
}

