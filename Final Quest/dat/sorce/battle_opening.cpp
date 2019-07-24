#include "../../include/GV.h"
#define ACCEL 1.5	//�����x�̑傫���B�傫���قǑ���������B

//�o�g���I�[�v�j���O�̎d�l�ɂ��Ă͎d�l13�Q��
void battle_opening(){
	int i,j;
	static int cnt=0;
	static double stbtx[16],stbty[16],randx[16],randy[16];

	if(cnt==0){//�ŏ��ɏ������s��ꂽ���A16�̉摜�̏������W��ݒ�
		PlaySoundMem(se_sound[0],DX_PLAYTYPE_BACK);
		for(i=0;i<4;i++){
			for(j=0;j<4;j++){
				stbtx[i*4+j]=WIND_WIDE/4*j;//�`�悷��e�����W
				stbty[i*4+j]=WIND_HIGHT/4*i;//�`�悷��e�����W
				randx[i*4+j]=GetRand(30);//�΂炯�����邽�߂̗���
				randy[i*4+j]=GetRand(30);//�΂炯�����邽�߂̗���
			}
		}
	}
	if(cnt<8){//8�J�E���g�̊Ԓ��S����O�֎U��΂点��
		for(i=0;i<4;i++){
			for(j=0;j<4;j++){
				stbtx[i*4+j]+=(-45+randx[i*4+j]+30*j)/8.0;//�l�������ɔ�юU�点��
				stbty[i*4+j]+=(-45+randy[i*4+j]+30*i)/8.0;//�l�������ɔ�юU�点��
			}
		}
	}
	if(cnt==8){	////�����鎞�ɂ΂炯�����邽�߂̗�������
		for(i=0;i<4;i++){
			for(j=0;j<4;j++){
				randx[i*4+j]=-2.0+GetRand(40)/10.0;
				randy[i*4+j]=1.0+GetRand(10)/10.0;
			}
		}
	}
	if(cnt>=60 && cnt<=150){	//�����郂�[�V����
		double t=(cnt-60.0)*17/1000;
		for(i=0;i<4;i++){
			for(j=0;j<4;j++){
				stbtx[i*4+j]+=randx[i*4+j];
				stbty[i*4+j]+=t*t*ACCEL*randy[i*4+j]/2.0*10;//�����鎞�����x�������Čv�Z�BACCEL�̒l�ŕύX�\
			}
		}
	}
	for(i=0;i<16;i++)//�`��
		DrawGraph((int)stbtx[i],(int)stbty[i],stbt_img[i],FALSE);
	cnt++;
	if(cnt==150){//150�ɂȂ����玟�̃V�[����
//	if(cnt==1){//150�ɂȂ����玟�̃V�[����
		cnt=0;
		func_states=2;
	}
	return;
}

#define STBTTIME 120.0

void battle_opening2(){//�퓬�ɓ��鎞�̃I�[�v�j���O�Q
	static int cnt=0;
	if(cnt==0){//�I�[�v�j���O�Q���n�܂�u�ԁA��U�S���`�悵�āA���̉�ʂ��L���v�`�����Ĕ��f������O�ɃN���A����B���̂P���̃L���v�`�������摜�ŃI�[�v�j���O�����
		PlaySoundMem(battle_sound[0],DX_PLAYTYPE_LOOP);
		DrawGraph(0,0,back_img[0],FALSE);
		DrawGraph(BTMON_X ,BTMON_Y ,mon[0].img,TRUE);
		DrawGraph(BTCH_X,BTCH_Y,ch_img[0][0],TRUE);
		stbt_img[0] = MakeGraph( WIND_WIDE , WIND_HIGHT ) ;
		GetDrawScreenGraph( 0 , 0 , WIND_WIDE , WIND_HIGHT , stbt_img[0] ) ;
		ClearDrawScreen();
	}
	if(cnt>83 && cnt<=170)
		DrawRotaGraph( -50+cnt , 100 , 2.0f , 0 , stbt_img[0] , FALSE ) ;
	if(cnt>170 && cnt<=255)
		DrawRotaGraph( 500-cnt , 400 , 2.0f , 0 , stbt_img[0] , FALSE ) ;
	if(cnt>255 && cnt<=255+STBTTIME){
		int t=cnt-255;
		DrawExtendGraph( (int)((WIND_WIDE/2+WIND_WIDE/4)-(WIND_WIDE/2+WIND_WIDE/4)*t/STBTTIME) , 0 , (int)(WIND_WIDE*t/STBTTIME) , (int)(WIND_HIGHT*t/STBTTIME) , stbt_img[0] , TRUE ) ;
	}
	cnt++;
	if(cnt==255+STBTTIME){//���ԂɂȂ�����I�[�v�j���O���I�����Đ퓬��
//	if(cnt==1){//���ԂɂȂ�����I�[�v�j���O���I�����Đ퓬��
		cnt=0;
		func_states=3;
	}
	return;
}