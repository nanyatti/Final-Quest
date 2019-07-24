#include "../../include/GV.h"

void stbt_capch(){//敵に出会ったとき、画面を16分割してキャプチャする。
	int i,j;
	for(i=0;i<4;i++){
		for(j=0;j<4;j++){
			stbt_img[i*4+j] = MakeGraph( WIND_WIDE/4 , WIND_HIGHT/4 ) ;//16個画像格納データを作る。
			GetDrawScreenGraph( 0+(WIND_WIDE/4)*j , 0+(WIND_HIGHT/4)*i , 0+(WIND_WIDE/4)*(j+1) , 0+(WIND_HIGHT/4)*(i+1) , stbt_img[i*4+j] ) ;
		}
	}
	stbt_capch_flag=0;
	return ;
}

//0押されていない　1押されている　2今の瞬間押された
void input_key(){//キーの入力状態管理
	int i;
	static char key_old[256]={};
	for(i=0;i<256;i++){
		if(key_old[i]==0 && key[i]==1)	//前に押してなくて、今押していたら
			key[i]=2;					//今の瞬間押されたという意味の2を代入。
		key_old[i]=key[i];				//今の入力状態を過去に入力されたデータとしてコピー
	}
	return;
}

void wait_calc(){//FPS制御
    static int t=0;
    wait_time = GetNowCount()-t;		//１周の処理にかかった時間を計算
	if(t==0)							//t==0つまり一番最初に処理が行われたときは16を代入
		wait_time=16;
    t=GetNowCount();					//現在の時間を格納
    if(16>wait_time)					//１週かかった時間がFPS60つまり１周16msよりも早く行われたとき
            Sleep(16-wait_time);		//FPS60になるように、つまり１周16msまで待つ。
    return;
}

void fps_calc(){//毎回かわるFPS値を表示していたらちらちらするので、60回計測して平均を表示する
        int i;
        static int f[60];

        f[count%60]=wait_time;
        if(count%60==59){
                fps_average=0;
                for(i=0;i<60;i++)
                        fps_average+=f[i];
                fps_average/=60;
        }
        return;
}

