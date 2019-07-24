#include "../../include/GV.h"

#define WALK_SPD 1	//キャラの動く早さ

void char_calc(){//キャラの移動
	int i;
//x,yデータをこのように書くことで配列要素名にmukiを代入するとｘｙ各方向に処理が可能
	for(i=0;i<CH_MAX;i++){
		if(ch[i].walk_flag==1){
			ch[i].x += proceed_x[ ch[i].muki ] * WALK_SPD;
			ch[i].y += proceed_y[ ch[i].muki ] * WALK_SPD;
		}
	}
	return;
}