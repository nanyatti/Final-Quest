#include "../../include/GV.h"

void stbt_capch(){//�G�ɏo������Ƃ��A��ʂ�16�������ăL���v�`������B
	int i,j;
	for(i=0;i<4;i++){
		for(j=0;j<4;j++){
			stbt_img[i*4+j] = MakeGraph( WIND_WIDE/4 , WIND_HIGHT/4 ) ;//16�摜�i�[�f�[�^�����B
			GetDrawScreenGraph( 0+(WIND_WIDE/4)*j , 0+(WIND_HIGHT/4)*i , 0+(WIND_WIDE/4)*(j+1) , 0+(WIND_HIGHT/4)*(i+1) , stbt_img[i*4+j] ) ;
		}
	}
	stbt_capch_flag=0;
	return ;
}

//0������Ă��Ȃ��@1������Ă���@2���̏u�ԉ����ꂽ
void input_key(){//�L�[�̓��͏�ԊǗ�
	int i;
	static char key_old[256]={};
	for(i=0;i<256;i++){
		if(key_old[i]==0 && key[i]==1)	//�O�ɉ����ĂȂ��āA�������Ă�����
			key[i]=2;					//���̏u�ԉ����ꂽ�Ƃ����Ӗ���2�����B
		key_old[i]=key[i];				//���̓��͏�Ԃ��ߋ��ɓ��͂��ꂽ�f�[�^�Ƃ��ăR�s�[
	}
	return;
}

void wait_calc(){//FPS����
    static int t=0;
    wait_time = GetNowCount()-t;		//�P���̏����ɂ����������Ԃ��v�Z
	if(t==0)							//t==0�܂��ԍŏ��ɏ������s��ꂽ�Ƃ���16����
		wait_time=16;
    t=GetNowCount();					//���݂̎��Ԃ��i�[
    if(16>wait_time)					//�P�T�����������Ԃ�FPS60�܂�P��16ms���������s��ꂽ�Ƃ�
            Sleep(16-wait_time);		//FPS60�ɂȂ�悤�ɁA�܂�P��16ms�܂ő҂B
    return;
}

void fps_calc(){//���񂩂��FPS�l��\�����Ă����炿�炿�炷��̂ŁA60��v�����ĕ��ς�\������
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

