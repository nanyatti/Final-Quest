
#include "../../include/GV.h"

void boad_string_calc(){//項目の説明を表示するために文字列を格納する関数
	if(ch[0].btcnt==240 && ch[0].menu_sel<10000){
		switch(ch[0].menu_sel){
			case 1:
				strcpy(board_string,"攻撃を行います。");
				break;
			case 2:
				strcpy(board_string,"魔法攻撃を行います。");
				break;
			case 3:
				strcpy(board_string,"アビリティを使用します。");
				break;
			case 4:
				strcpy(board_string,"アイテムを使用します。");
				break;
			case 5:
				strcpy(board_string,"戦闘から逃げます。");
				break;
			case 100:
				strcpy(board_string,"通常攻撃を行います。");
				break;
			case 101:
				strcpy(board_string,"TPを使用して特殊攻撃を行います。");
				break;
			case 200:
				strcpy(board_string,"MP9消費して回復魔法を行います。");
				break;
			case 201:
				strcpy(board_string,"MP8消費して風の魔法攻撃を行います。");
				break;
			case 202:
				strcpy(board_string,"MP16消費して火の魔法攻撃を行います。");
				break;
			case 203:
				strcpy(board_string,"MP24消費して氷の魔法攻撃を行います。");
				break;
			case 204:
				strcpy(board_string,"MP36消費して雷の魔法攻撃を行います。");
				break;
			case 300:
				strcpy(board_string,"挑発して相手を自分に引き付けます。(30秒後再使用可)");
				break;
			case 301:
				strcpy(board_string,"2分間攻撃力を下げて防御力を上げます。(2分後再使用可)");
				break;
			case 302:
				strcpy(board_string,"2分間攻撃力を上げて防御力を下げます。(2分後再使用可)");
				break;
			case 303:
				strcpy(board_string,"自分の体力を削って敵に2倍のダメージを与えます。(30秒後再使用可)");
				break;
			case 304:
				strcpy(board_string,"MPを2倍消費して詠唱時間を1/4にします。(30秒後再使用可)");
				break;
			case 400:
				strcpy(board_string,"HPが少し回復します。");
				break;
			case 401:
				strcpy(board_string,"HPが多く回復します。");
				break;
			case 402:
				strcpy(board_string,"攻撃力が増加します。");
				break;
			case 403:
				strcpy(board_string,"防御力が増加します。");
				break;
			case 404:
				strcpy(board_string,"MPが少し回復します。");
				break;
			case 500:
				strcpy(board_string,"戦闘から逃げます。");
				break;
			case 501:
				strcpy(board_string,"マネーを落として高確率で戦闘から逃げます。");
				break;
			default:
				strcpy(board_string,"");
				break;
		}
	}
	else
		strcpy(board_string,"");
	return ;
}