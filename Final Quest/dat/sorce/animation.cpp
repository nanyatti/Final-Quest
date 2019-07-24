#define _CRT_SECURE_NO_WARNINGS
#include "../../include/GV.h"

#define TENMETU_T 20

int ani_time[5]={-15,240,360,480,600},eisho_time[5]={40,240,360,480,600},tenmetu_time[5]={-20,240,360,480,600};

void ani_kind0(int i , ch_t *c , ch_t *c2, int x, int y,int k){
	int j,t,t2,t3;
	if(gameover_flag==1 || victory_flag==1)		{StopSoundMem(se_sound[5]);return;}
	if(c2->abi[4].flag==1){
		for(j=1;j<5;j++){
			ani_time[j]/=4;
			eisho_time[j]/=4;
			tenmetu_time[j]/=4;
		}
	}
	t =ani_time  [ani[i].kind%10000/100];
	t2=eisho_time[ani[i].kind%10000/100];
	t3=tenmetu_time[ani[i].kind%10000/100];

	ani[i].cnt++;

	if(ani[i].cnt==5 && ani[i].kind==10000)
		PlaySoundMem(se_sound[6],DX_PLAYTYPE_BACK);//シュッ
	if(ani[i].cnt==5+t2)
		PlaySoundMem(se_sound[ani[i].kind/100],DX_PLAYTYPE_BACK);//それぞれの効果音

	if(ani[i].cnt==5 && ani[i].kind>=20000 && ani[i].kind<30000)
		PlaySoundMem(se_sound[5],DX_PLAYTYPE_LOOP);//詠唱

	if(CheckSoundMem(se_sound[5])==1 && ani[i].kind>=20000 && ani[i].kind<30000){
		DrawGraph(c2->btx-60+GetRand(2),c2->bty-35+GetRand(2),btetc_img[0],TRUE);
		DrawBox(c2->btx+20,c2->bty-25,c2->btx+70,c2->bty-20,color[4],FALSE);
		DrawBox(c2->btx+20,c2->bty-25,(int)(c2->btx+20+((double)(ani[i].cnt-5)/(t3+20))*50.0),c2->bty-20,color[4],TRUE);
	}
	
	if(ani[i].cnt==25+t2 && ani[i].kind>=20000 && ani[i].kind<30000)
		StopSoundMem(se_sound[5]);//ストップ

	for(j=0;j<4;j++){//点滅処理
		if(ani[i].cnt==70+t3+TENMETU_T*j)
			c->btgraph_flag=0;
		if(ani[i].cnt==70+t3+TENMETU_T*j+TENMETU_T/2)
			c->btgraph_flag=1;
	}
	if(ani[i].cnt>=30+t && ani[i].cnt<70+t)//アニメーション描画
		DrawGraph(x,y,ani_img[1][(ani[i].cnt-(30+t))/5+(ani[i].kind%10000)/100*8],TRUE);
//		DrawGraph(x,y,ani_img[1][(ani[i].cnt-(30+t))/5+(ani[i].kind%10000)/100*8+k*8],TRUE);
	if(ani[i].cnt==150+t){
		ani[i].flag=0;
		c2->btact_flag=1;
	}
	if(c2->abi[4].flag==1){
		for(i=1;i<5;i++){
			ani_time[i]*=4;
			eisho_time[i]*=4;
			tenmetu_time[i]*=4;
		}
	}
	return;
}

void ani_kind1(ch_t* c,int i,int x,int y){//キュア
	if(gameover_flag==1 || victory_flag==1)return;

	if(ani[i].cnt==0)	PlaySoundMem(se_sound[200],DX_PLAYTYPE_BACK);

	if(ani[i].cnt<50)
		DrawGraph(c->btx+x,c->bty+y-ani[i].cnt,ani_img[0][10+ani[i].cnt/5],TRUE);

	ani[i].cnt++;
	if(ani[i].cnt==80){
		ani[i].flag=0;
		c->btact_flag=1;
	}
	return;
}

void ani_kind2(ch_t* c,int i,int x,int y){//アビ
	if(gameover_flag==1 || victory_flag==1)return;

	if(ani[i].cnt==0)	PlaySoundMem(se_sound[c->menu_sel/100],DX_PLAYTYPE_BACK);

	if(ani[i].cnt<50)
		DrawGraph(c->btx+x,c->bty+y-ani[i].cnt,ani_img[0][20+ani[i].cnt/10],TRUE);

	ani[i].cnt++;
	if(ani[i].cnt==80){
		ani[i].flag=0;
		c->btact_flag=1;
	}
	return;
}

void ani_graph(){//アニメーションを描画
	int i;
	for(i=0;i<ANI_MAX;i++){
		if(ani[i].flag==1){//アニメーションフラグが立っていたら
			switch(ani[i].kind/10000){//アニメーションの種類によって処理を分岐
				case 1:
					if(ani[i].target==0)//ターゲットが敵no.0だったら
						ani_kind0(i,&mon[0],&ch[0],mon[0].btx+5,mon[0].bty+5,0);
					if(ani[i].target==100)//ターゲットが見方no.0なら
						ani_kind0(i,&ch[0],&mon[0],ch[0].btx-32,ch[0].bty-16,0);
					break;
				case 2:
					if(ani[i].kind==20000){
						if		(ani[i].actor==0)	ani_kind1(&mon[0],i,0,0);
						else if	(ani[i].actor==100)	ani_kind1(&ch[0],i,-30,20);
					}
					else{
						if(ani[i].target==0)//ターゲットが敵no.0だったら
							ani_kind0(i,&mon[0],&ch[0],mon[0].btx+5,mon[0].bty+5,1);
						if(ani[i].target==100)//ターゲットが見方no.0なら
							ani_kind0(i,&ch[0],&mon[0],ch[0].btx-32,ch[0].bty-16,1);
					}
					break;
				case 3:
					if		(ani[i].actor==0)	ani_kind2(&mon[0],i,0,0);
					else if	(ani[i].actor==100)	ani_kind2(&ch[0],i,-30,20);
					break;
				default:
					exit(97);
					break;
			}
		}
	}
	return;
}