#include "../../include/GV.h"

#define MONMT_X 15
#define MONMT_Y 380

#define CH1MT_X 250
#define CH1MT_Y 380
#define SUB 85

extern void hp_sub(ch_t*);

void board_graph(){
	int fl=0,i;
	for(i=0;i<100;i++){
		if(board[i].flag==1){
			if(board[i].cnt==120){board[i].flag=0;continue;}
			DrawGraph(10,26,btetc_img[1],TRUE);
			DrawFormatString(14,28,color[0],"%s",board[i].st);
			board[i].cnt++;
			return ;
		}
	}
	return;
}

void sakura_graph(){
	int i;

	SetDrawBlendMode( DX_BLENDMODE_ALPHA , 200 ) ;
	for(i=0;i<100;i++){
		if(sakura[i].flag==1)
			DrawRotaGraph( (int)sakura[i].x , (int)sakura[i].y , sakura[i].enl , PI*2.0 / 180.0 *((int)(sakura[i].cnt*sakura[i].rota)%180) , btetc_img[2] , TRUE ) ;
		sakura[i].cnt++;
	}
	SetDrawBlendMode( DX_BLENDMODE_NOBLEND , 0 ) ;
	return ;
}

void tp_graph(int x,int y,int tp){//TPの％数値を画像で表現
	//(MONMT_X+30,MONMT_Y+53,mon[0].tp){
	int i,n;
	char tp_s[4];
	sprintf(tp_s,"%d",tp);
	n=(int)strlen(tp_s);
	for(i=0;i<n;i++)
		DrawGraph(x+i*15-7*n,y,num_img[1][tp_s[i]-'0'],TRUE);
	DrawGraph(x+i*15,y,num_img[1][10],TRUE);
	return ;
}

#define MDLEN 50

void mtdeco(int x,int y,int ht,int len){//白い線をスーっとメーターにデコレート
	int i,x2;

	if(len==0)	return;	//0割り禁止

	x2=x+count%len;

	for(i=0;i<MDLEN;i++){
		SetDrawBlendMode( DX_BLENDMODE_ALPHA , 200/MDLEN*i ) ;
		DrawLine(x2,y,x2,y+ht,color[0]);
		x2++;
		if(x2>=x+len)	x2=x;
	}
	SetDrawBlendMode( DX_BLENDMODE_NOBLEND , 0 ) ;
	return ;
}

#define LEN1 5
#define LEN2 7

void hpmpmt_graph(int x,int y,int hp,int hp_max,int bttohp,int mp,int mp_max,int tp,int cnt){//HP,MP,TP描画
#define Y1 25
#define Y2 25
	int col_m[4],tpg[2];
	tpg[0]=tp%101;
	tpg[1]=tp%101;
	if(tp>100)	tpg[0]=100;	if(tp>200)	tpg[1]=100;		

	if(cnt<240)	col_m[0]=color[6];//メーターがまだ満タンじゃなかったら 灰色を格納
	else		col_m[0]=GetColor(count*3%256,(count*3+85)%256,(count*3+170)%256);					//レインボーを格納

	DrawBox( x , y	   , x+150, y+LEN1					  , color[5] , FALSE);						//HPメーターの枠を描画
	DrawBox( x , y	   , x+150*hp/hp_max , y+LEN1	, color[5] , TRUE);								//HPメーターの中身を描画
	DrawBox( x+150*bttohp/hp_max  , y	, x+150*hp/hp_max , y+LEN1 , color[8] , TRUE);				//HPメーターの中身を描画
	mtdeco(x,y,LEN1,150*bttohp/hp_max);

	DrawBox( x , y+Y1	   , x+150, y+Y1+LEN1				  , color[9] , FALSE);					//MPメーターの枠を描画
	DrawBox( x , y+Y1	   , x+150*mp/mp_max , y+Y1+LEN1 , color[9] , TRUE);						//MPメーターの中身を描画
	mtdeco(x,y+Y1,LEN1,150*mp/mp_max);

	DrawBox( x , y+Y1+Y2	   , x+150, y+Y1+Y2+LEN2					  , color[7] , FALSE);		//TPメーターの枠を描画
	DrawBox( x , y+Y1+Y2	   , x+150*tpg[0]/100 , y+Y1+Y2+LEN2 , color[7] , TRUE);				//TPメーターの中身を描画
	if(tp>100)	DrawBox( x , y+Y1+Y2	   , x+150*tpg[1]/100 , y+Y1+Y2+LEN2 , color[10] , TRUE);	//TPメーターの中身を描画
	if(tp>200)	DrawBox( x , y+Y1+Y2	   , x+150*(tp-200)/100 , y+Y1+Y2+LEN2 , color[1] , TRUE);	//TPメーターの中身を描画

	if(tp<=100)			mtdeco(x,y+Y1+Y2,LEN2,150*tp/100);											//デコレーション
	else if(tp<=200)	mtdeco(x,y+Y1+Y2,LEN2,150*(tp-100)/100);
	else				mtdeco(x,y+Y1+Y2,LEN2,150*(tp-200)/100);

	tp_graph(x+65,y+Y1+Y2+7,tp);																	//TPの％描画

	DrawFormatStringToHandle( x , y+4 , color[0] , fhandle[0] , "%d/%d" , hp , hp_max ) ;			//HP数値表示
	DrawFormatStringToHandle( x , y+Y1+4 , color[0] , fhandle[0] , "%d/%d" , mp , mp_max ) ;		//MP数値表示

	DrawBox( x , y+SUB , x+150			  , y+SUB+3 , col_m[0] , FALSE);//ATBメーターの枠を描画
	DrawBox( x , y+SUB , x+150*cnt/240	  , y+SUB+3 , col_m[0] , TRUE);//ATBメーターの中身描画
	return ;
}

void meter_disp(){//メーターを描画
	//敵計算
	hp_sub(&mon[0]);
	hpmpmt_graph(MONMT_X,MONMT_Y,mon[0].hp,mon[0].hp_max,mon[0].bttohp,mon[0].mp,mon[0].mp_max,mon[0].tp,mon[0].btcnt);
	//キャラ計算
	hp_sub(&ch[0]);
	hpmpmt_graph(CH1MT_X,CH1MT_Y,ch[0].hp,ch[0].hp_max,ch[0].bttohp,ch[0].mp,ch[0].mp_max,ch[0].tp,ch[0].btcnt);
	return;
}

int line_calc(double x1,double y1,double x2,double y2,double y3,double x){
	double y;
	y=((sqrt(y1-y3)+sqrt(y2-y3))/(x2-x1))*((sqrt(y1-y3)+sqrt(y2-y3))/(x2-x1))*((x-x1)-sqrt(y1-y3)*(x2-x1)/(sqrt(y1-y3)+sqrt(y2-y3)))*((x-x1)-sqrt(y1-y3)*(x2-x1)/(sqrt(y1-y3)+sqrt(y2-y3)))+y3;
	return (int)y;
}
void line_graph(){//ヘイト向き描画
	int i,j;
	double x1,x2,y1,y2,y3,x;

	x1=mon[0].btx+85;
	y1=mon[0].bty;
	x2=ch[0].btx+10;
	y2=ch[0].bty;
	y3=70.0;
	for(x=x1;x<=x2;x+=1.0){
		SetDrawBlendMode( DX_BLENDMODE_ALPHA , 72 ) ;
		if(x>x1+line.cnt)break;
//		if(x<x1+line.cnt-180)continue;
		DrawLine((int)x,line_calc(x1,y1,x2,y2,y3,x),(int)x+1  ,line_calc(x1,y1,x2,y2,y3,x+1),color[5]);
		DrawLine((int)x,line_calc(x1,y1,x2,y2,y3,x)+1,(int)x+1,line_calc(x1,y1,x2,y2,y3,x+1)+1,color[0]);
		DrawLine((int)x,line_calc(x1,y1,x2,y2,y3,x)+2,(int)x+1,line_calc(x1,y1,x2,y2,y3,x+1)+2,color[5]);
	}
	for(i=(int)(x1-128+(count*5%(int)(x2-x1+128))),j=0;i<=(int)(x1+(count*5%(int)(x2-x1+128)));i++,j++){
//		if(i>(x1-128+(count*5%(int)(x2-x1+128))+line.cnt))break;
//		if(i<(x1-128+(count*5%(int)(x2-x1+128))+line.cnt)-180)continue;
		if(i<x1)continue;
		if(i>x2)break;
		SetDrawBlendMode( DX_BLENDMODE_ALPHA , j*3 ) ;
		DrawLine(i,line_calc(x1,y1,x2,y2,y3,i)	,i+1,line_calc(x1,y1,x2,y2,y3,i+1),color[5]);
		DrawLine(i,line_calc(x1,y1,x2,y2,y3,i)+1,i+1,line_calc(x1,y1,x2,y2,y3,i+1)+1,color[5]);
		DrawLine(i,line_calc(x1,y1,x2,y2,y3,i)+2,i+1,line_calc(x1,y1,x2,y2,y3,i+1)+2,color[5]);
	}

	SetDrawBlendMode( DX_BLENDMODE_NOBLEND , 0 ) ;
	if(line.cnt<480)line.cnt+=4;
//	else line.cnt=0;
	return;
}

#define ICON_X 480
#define ICON_Y 370

void icon_graph(){//メニューアイコンを描画
	int i,x;
	extern void boad_string_calc();
	if(ch[0].menu_sel<100){//選択状態が最初の状態
		int y;
		y=ch[0].menu_sely;//描画ｙ位置をｙにセット
		for(i=0;i<5;i++){
			x=0;
			if(i==y){//現在選択されている項目は若干左にする
				x=-5;
			}
			DrawGraph(ICON_X+x,ICON_Y+18*i,icon0_img[i],TRUE);//項目描画
		}
	}
	for(int j=0;j<5;j++){
		if(ch[0].menu_sel>=100+100*j && ch[0].menu_sel<200+100*j){//戦う　魔法　ｱﾋﾞﾘﾃｨ・・は100ごとにわかれている
			int y;
			y=ch[0].menu_sely;
			for(i=0;i<5;i++){
				x=0;
				if(i==y){
					x=-5;
				}
				DrawGraph(ICON_X+x,ICON_Y+18*i,icon1_img[j][i],TRUE);
			}
		}
	}
	DrawGraph(ICON_X-20+(count%20)/4-5,ICON_Y+18*ch[0].menu_sely+1,icon_img,TRUE);
	DrawGraph(10,5,btetc_img[1],TRUE);
	boad_string_calc();
	DrawFormatString(14,7,color[0],"%s",board_string);
	return ;
}



void battle_graph(){//バトルの描画

	DrawGraph(0,0,back_img[0],FALSE);
	DrawGraph(0,480-134,back_img[10],FALSE);
	if(mon[0].btgraph_flag==1)
		DrawGraph(mon[0].btx , mon[0].bty ,mon[0].img,TRUE);
	if(mon[0].btani_flag==1)
		DrawGraph(mon[0].btx+12 , mon[0].bty+12 ,mon[0].btani_img,TRUE);
	if(ch[0].btgraph_flag==1)
		DrawGraph(ch[0].btx,ch[0].bty,ch_img[0][0],TRUE);
	if(ch[0].btani_flag==1)
		DrawGraph(ch[0].btx-32 , ch[0].bty-22 ,ch[0].btani_img,TRUE);

	return ;
}

void dam_graph_calc(int t){
	int i,n,y[20]={-1,-3,-4,-5,-4,-3,-1,1,3,7,11,15,22,16,13,12,13,16,22,21},cy;
	char dam[6];
	sprintf(dam,"%d",pop_dam[t].dam);
	n=(int)strlen(dam);
	for(i=0;i<n;i++){
		if(4*i>pop_dam[t].cnt)	return;
		if(pop_dam[t].cnt-4*i<20)cy=y[pop_dam[t].cnt-4*i];
		else cy=22;
		DrawGraph(pop_dam[t].x+15*i,pop_dam[t].y+cy-pop_dam[t].type*14,num_img[2+pop_dam[t].type][dam[i]-'0'],TRUE);
	}
	return;
}

void dam_graph(){//ダメージ数字を描画
	int i;
	for(i=0;i<POP_DAM_MAX;i++){
		if(pop_dam[i].flag==1){//ダメージ数字描画フラグが立っていたら
			dam_graph_calc(i);
			pop_dam[i].cnt++;
			if(pop_dam[i].cnt==130)//描画フラグがたってから120(2秒)たったらフラグを落とす
				pop_dam[i].flag=0;
		}
	}
	return;
}
void victory_graph(){//勝利画面を描画

	SetDrawBlendMode( DX_BLENDMODE_ALPHA , 128 ) ;
	DrawBox(0,0,640,480,color[5],TRUE);
	DrawString(300,230,"VICTORY!!",color[0]);
	SetDrawBlendMode( DX_BLENDMODE_NOBLEND , 0 ) ;

	return ;
}
void gameover_graph(){//ゲームオーバー画面を描画

	SetDrawBlendMode( DX_BLENDMODE_ALPHA , 128 ) ;
	DrawBox(0,0,640,480,color[1],TRUE);
	DrawString(300,230,"GAME OVER",color[0]);
	SetDrawBlendMode( DX_BLENDMODE_NOBLEND , 0 ) ;

	return ;
}
//int ani_flag[ANI_MAX][4];	//[0]フラグ [1]ターゲット　[2]アニメーション種類　[3]カウンタ
//0~99敵　100~見方
