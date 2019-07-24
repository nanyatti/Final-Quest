#include "../../include/GV.h"
extern void battle_opening();
extern void battle_opening2();

extern void	battle_graph();
extern void meter_disp();
extern void victory_graph();
extern void gameover_graph();

extern void icon_graph();
extern void mon0_motion();
extern void ch0_motion();

extern void dam_graph();
extern void ani_graph();
extern void add_board(const char * st);
extern void board_graph();
extern void can_sel();
extern void battle_ini();
extern void line_graph();
extern void sakura_calc();
extern void sakura_graph();
//ATB�J�E���^�̎d�l�ɂ��ẮA�d�l��10��
void cnt_calc() {//ATB�J�E���^����
	if (mon[0].btcnt_flag == 1 && gameover_flag == 0 && victory_flag == 0) {//ATB�J�E���^�𑝉�������t���O�������Ă����āA�Q�[���I�[�o�[�ł������ł��Ȃ����
		mon[0].btcnt++;
		if (mon[0].btcnt == 240)//ATB�J�E���^��MAX�Ȃ�
			mon[0].btcnt_flag = 0;//�����t���O��������
	}
	//if(mon[0].btcnt_flag==1 && gameover_flag==0 && victory_flag==0){//ATB�J�E���^�𑝉�������t���O�������Ă����āA�Q�[���I�[�o�[�ł������ł��Ȃ����
	//	mon[0].btcnt++;
	//	if(mon[0].btcnt==240)//ATB�J�E���^��MAX�Ȃ�
	//		mon[0].btcnt_flag=0;//�����t���O��������
	//}
	if (ch[0].btcnt_flag == 1 && gameover_flag == 0 && victory_flag == 0) {
		ch[0].btcnt++;
		if (ch[0].btcnt == 240)
			ch[0].btcnt_flag = 0;
	}
	return;
}
//���j���[�I���v�Z�ɂ��Ă͎d�l��11��
void menu_sel_cal() {
	if (key[KEY_INPUT_UP] == 2) {//��L�[��������Ă�����
		ch[0].menu_sel--;			//�I����Ԃ���̂��̂�
		ch[0].menu_sely--;		//�I���ʒu�����
		if (ch[0].menu_sely == -1) {	//�I���ʒu����ԏ�𒴂�����
			ch[0].menu_sel += 5;	//��ԉ��ցB5�͑I�����ڂ̍ő吔
			ch[0].menu_sely = 4;	//��ԉ��ցB4�͑I��\�����ڂ̍ő吔-1
		}
		PlaySoundMem(se_sound[2], DX_PLAYTYPE_BACK);
	}
	if (key[KEY_INPUT_DOWN] == 2) {
		ch[0].menu_sel++;
		ch[0].menu_sely++;
		if (ch[0].menu_sely == 5) {
			ch[0].menu_sel -= 5;
			ch[0].menu_sely = 0;
		}
		PlaySoundMem(se_sound[2], DX_PLAYTYPE_BACK);
	}
	if (key[KEY_INPUT_X] == 2) {//����{�^����������Ă�����
		ch[0].menu_sel = ch[0].menu_sel * 100;	//����{�^����������邽�тɑI�����*100�ɂȂ�
		ch[0].menu_sely = 0;			//�I���ʒu��������
		if (ch[0].menu_sel < 10000)//�I�����S�Ċ������Ă��Ȃ����
			PlaySoundMem(se_sound[1], DX_PLAYTYPE_BACK);
		else {
			can_sel();
			PlaySoundMem(se_sound[3], DX_PLAYTYPE_BACK);
			ch[0].btmotion_flag = 1;//�L�����̃��[�V�������s���t���O�𗧂Ă�
		}
	}
	else if (key[KEY_INPUT_Z] == 2) {//�L�����Z���Ȃ�
		ch[0].menu_sel = 1;	//�I����Ԃ�߂�
		ch[0].menu_sely = 0;//�I���ʒu��߂�
		PlaySoundMem(se_sound[4], DX_PLAYTYPE_BACK);
	}

	return;
}

void mon_act_dec() {
	mon[0].btmotion_flag = 1;	//�����X�^�[�̃��[�V�����t���O�𗧂Ă�
	return;
}

void abi_upstop(ch_t* c) {
	int time[ABI_MAX] = { ABI_TIME0,ABI_TIME1,ABI_TIME2,ABI_TIME3,ABI_TIME4 };
	int i;
	for (i = 0; i < ABI_MAX; i++) {
		if (c->abi[i].flag >= 1) {
			c->abi[i].cnt++;
			if (c->abi[i].cnt == time[i] * 60) {
				if (i == 1) {
					c->chsts.def = 0;
					c->chsts.power = 0;
					add_board("�f�B�t�F���_�[�̌��ʂ��؂ꂽ");
				}
				else if (i == 2) {
					c->chsts.def = 0;
					c->chsts.power = 0;
					add_board("�o�[�T�N�̌��ʂ��؂ꂽ");
				}
				else if (i == 3) {
					if (c->abi[i].flag == 1)
						add_board("���͂̐�̌��ʂ��؂ꂽ");
				}
				else if (i == 4) {
					if (c->abi[i].flag == 1)
						add_board("���͂̐�̌��ʂ��؂ꂽ");
				}
				c->abi[i].flag = 0;
			}
		}
	}
	return;
}

void abi_cntup() {
	abi_upstop(&ch[0]);
	abi_upstop(&mon[0]);
	return;
}
void sakura_calc() {
	int i;
	for (i = 0; i < 100; i++) {
		if (sakura[i].x < -24)
			sakura[i].x = WIND_WIDE + 24;
		if (sakura[i].y > WIND_HIGHT + 24)
			sakura[i].y = -24;
		sakura[i].x -= sakura[i].spd;
		sakura[i].y += sakura[i].spd;
	}
	return;
}
void victory_dec() {//��������ƁA�������[�V��������
	static int cnt = 0;
	if (mon[0].hp <= 0)
		victory_flag = 1;
	else
		return;

	if (CheckSoundMem(battle_sound[0]) == 1)//�o�g���̉��y���������Ă�����~�߂�
		StopSoundMem(battle_sound[0]);

	cnt++;
	if (cnt == 240 - 1)
		victory_flag = 2;
	if (cnt == 240) {
		func_states = 0;//�}�b�v��ʂ�
		cnt = 0;
	}
	return;
}

void gameover_dec() {//�Q�[���I�[�o�[����ƁA�Q�[���I�[�o�[���[�V��������
	static int cnt = 0;
	if (ch[0].hp <= 0)
		gameover_flag = 1;
	else
		return;

	if (CheckSoundMem(battle_sound[0]) == 1)//�o�g���̉��y������Ă�����~�߂�
		StopSoundMem(battle_sound[0]);

	cnt++;
	if (cnt == 240 - 1)
		gameover_flag = 2;
	if (cnt == 240) {
		func_states = -1;//�Q�[���̏�������
		cnt = 0;
	}
	return;
}

void battle_calc() {//�o�g���ɂ����āA�ǂ̊֐��ɏ�����n�����𐧌�
	static int cnt = 0;

	if (cnt == 0)//���߂Đ퓬�V�[���ɂȂ����Ƃ�������
		battle_ini();

	switch (func_states) {
	case 1://��ʂ�����ė�����V�[��
		battle_opening();
		break;
	case 2://�퓬�˓��V�[��
		battle_opening2();
		break;
	case 3://�퓬�V�[��
		cnt_calc();//�J�E���g�v�Z
		if (gameover_flag == 0 && victory_flag == 0) {//�퓬���I�����Ă��Ȃ�������
			if (ch[0].btmotion_flag == 0 && ch[0].btcnt == 240)//�s�����Ă��Ȃ���ATB�J�E���^��MAX�Ȃ�
				menu_sel_cal();
			if (mon[0].btmotion_flag == 0 && mon[0].btcnt == 240)
				mon_act_dec();
		}
		if (ch[0].btmotion_flag == 1)//���[�V�����t���O�������Ă����烂�[�V�������s��
			ch0_motion();
		if (mon[0].btmotion_flag == 1)
			mon0_motion();

		gameover_dec();//�Q�[���I�[�o�[���ǂ��������߂�
		victory_dec();//�������ǂ��������߂�

		battle_graph();//�o�g���V�[����`�悷��
		meter_disp();//���[�^�[��`�悷��
		//damage_calc();//�_���[�W���v�Z����
		dam_graph();//�_���[�W��`�悷��
		ani_graph();
		abi_cntup();
		sakura_calc();
		sakura_graph();
		board_graph();
		line_graph();
		if (gameover_flag == 1)//�Q�[���I�[�o�[�t���O�������Ă�����Q�[���I�[�o�[
			gameover_graph();
		else if (victory_flag == 1)//�����t���O�������Ă����珟��
			victory_graph();
		else if (ch[0].btmotion_flag == 0 && ch[0].btcnt == 240)//ATB�J�E���^���}�b�N�X�Ń��[�V�������ĂȂ�������I�����ڂ�`��
			icon_graph();
		break;
	default:
		exit(99);
		break;
	}

	cnt++;

	if (func_states <= 0)//�퓬�V�[�����I��������ɃJ�E���^�[��߂��B
		cnt = 0;
	return;
}

