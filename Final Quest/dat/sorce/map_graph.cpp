#include "../../include/GV.h"

void map_graph(){//マップの描画
	int i,j;
	for(i=0;i<WIND_WIDE/WIDE;i++){//横のウィンドウサイズ/１区間のサイズ＝横の区間個数
		for(j=0;j<WIND_HIGHT/WIDE;j++){//縦のウィンドウサイズ/１区間のサイズ＝縦の区間個数
			DrawGraph( i*WIDE , j*WIDE , mapchip_img[0][0] , TRUE);//いったん全ての区間に芝生を描画
			if(map[stage_map][j][i]!=0)//芝生の上に画像を表示する区間の時
				DrawGraph( i*WIDE , j*WIDE , mapchip_img[0][ map[stage_map][j][i] ] , TRUE);//その画像を描画
		}
	}
	return ;
}
