#define _GLOBAL_INSTANCE_ 
#include "../../include/GV.h"

void ini(){//�L�����N�^�̏�����
	ch[0].x		=WIDE*10;
	ch[0].y		=WIDE*10;
	ch[0].walk_cnt	=0;
	ch[0].walk_flag	=0;
	ch[0].muki		=3;//�L�����̂ނ��Ă�����������ɃZ�b�g
	ch[0].img_flag	=1;//�`�悷�邩�ǂ����̃t���O
	ch[0].hp	=1352;
	ch[0].hp_max=1452;
	ch[0].mp	=97;
	ch[0].mp_max=102;
	ch[0].tp=0;
	ch[0].magic=20;

	ch[0].power=20;		//�U����
	ch[0].def=20;		//�h���
	ch[0].strong=20;	//��
	ch[0].weapon=20;	//����
	ch[0].equip=20;		//����
	ch[0].lv=10;		//���x��

	mapini_flag=1;		//�}�b�v�����������邩�ǂ����̃t���O
	func_states=0;		//main�֐��łǂ̊֐��ɏ�����n�����𔻒f����ϐ�
	return;
}

int WINAPI WinMain( HINSTANCE hInstance, HINSTANCE hPrevInstance,LPSTR lpCmdLine, int nCmdShow ){
	
	// ����������
	if (SetOutApplicationLogValidFlag(FALSE) ||
		ChangeWindowMode(TRUE) != DX_CHANGESCREEN_OK ||
		DxLib_Init() ||
		SetWindowSizeExtendRate(1.0)) {
		return -1;
	}
	//if( SetOutApplicationLogValidFlag(FALSE) || DxLib_Init()) return -1;//�t���X�N���[�����[�h

	SetDrawScreen( DX_SCREEN_BACK );

	// ���\�[�X�̓Ǎ�
	// �F���@�����H
	// �摜�E���y
	// ���[�f�B���O
	// �f�ޕҏW
	dat_load();


	while(!ProcessMessage() && !ClearDrawScreen() && !GetHitKeyStateAll( key ) && key[KEY_INPUT_ESCAPE]==0){

		// ���͏��
		input_key();


		// ��ԑJ��
		switch(func_states){

			// ������
			case -1://����������

				// �L�����̏�����
				// �}�b�v�������t���O
				// ��ԍX�V
				ini();
				break;



			// ���[���h�}�b�v�X�e�[�g
			case 0://�}�b�v���

				// �}�b�v�̏�����
				// �ړ��ł��邩
				// NPC�̔z�u
				if(mapini_flag==1)
					map_ini();//�}�b�v�̏�����

				// �X�V����

				// �L�����ʒu�̍X�V
				char_calc();//�L�����N�^�̕`��ȊO�̌v�Z

				// ���͂ɂ��L��������
				// �L�����ړ��ɂ��}�b�v����
				// �}�b�v�̏�����
				// 1�}�X�ړ�
				// �ړ��������_���G���J�E���g
				char_graph_calc();//�L�����N�^�̕`��̌v�Z

				// NPC�̈ړ�����
				mchar_graph_calc();//���̃L�����̕`��̌v�Z

				// �`�揈��
				map_graph();//�}�b�v�̕`��
				char_graph();//�L�����N�^�̕`��

				
				if(stbt_capch_flag==1)//�����퓬�ɓ���u�ԂȂ�
					stbt_capch();//��ʂ�16�������ăL���v�`��
				break;


			// �o�g���X�e�[�g
			case 1://�o�g�����
			case 2:
			case 3:

				// ��Ԃɉ����ăI�[�s�j���O�E�퓬�E�������o�Ȃǂ��s��
				battle_calc();//�o�g�����C����
				break;


			// �s���ȏ��
			default:
				exit (98);
				break;
		}

		music_sound();	//���y����
		wait_calc();	//FPS����iFPS��60�ɕۂ��߂̊֐��j
		fps_calc();		//���݂�FPS���v�Z
		fps_graph();	//FPS��`��

		count++;		//count�͏��1�����������A�����ȊO�ŕύX����邱�Ƃ̖����ϐ��B���I�ɕω����鉽���ɐF�X�g����B
		ScreenFlip();
	}

	DxLib_End();
	return 0;
}