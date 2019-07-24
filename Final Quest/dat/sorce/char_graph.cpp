#include "../../include/GV.h"

/*マップのキャラは奥にいる(つまりｙ座標が少ないもの)キャラから描画する必要がある*/
void char_graph(){//キャラの描画
	int i,j;
	for(i=0;i<WIND_HIGHT/WIDE;i++){//縦のウィンドウサイズを１区間サイズで割った物、つまり縦の区間個数分ループ
		for(j=0;j<CH_MAX;j++){//キャラ分
			if(ch[j].y/WIDE==i)//現在調査しているｙ座標と同じなら描画
				DrawGraph( ch[j].x , ch[j].y-16 , ch[j].img , TRUE);
		}
	}
	return ;
}