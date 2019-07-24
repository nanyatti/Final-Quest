#include <DxLib.h>
#include "DungeonScene.h"
#include "IOnSceneChangedListener.h"
#include "Parameter.h"
#include "../ActorObject/Character.h"
#include "../ActorObject/Monster.h"
#include "../Input/Keyboard.h"


#define LOAD_NUM 44.0	//����disp_load()�����ł����

void disp_load() {//���݉������[�h���Ă��邩�\������
	static int load_now_num = 0;

	ClearDrawScreen();

	load_now_num++;

	DrawFormatString(Define::WINDOW_WIDTH / 2 - 60, Define::WINDOW_HEIGHT/ 2 + 160, GetColor(255, 255, 255), "now loading....");
	DrawFormatString(Define::WINDOW_WIDTH / 2 - 20, Define::WINDOW_HEIGHT / 2 + 200, GetColor(255, 255, 255), "%.0f��", load_now_num / LOAD_NUM * 100);

	ScreenFlip();

	return;
}

void dat_load() {//�f�[�^�̃��[�h

	//color[0] = GetColor(255, 255, 255);
	//color[1] = GetColor(255, 0, 0);
	//color[2] = GetColor(0, 255, 0);
	//color[3] = GetColor(0, 0, 255);
	//color[4] = GetColor(255, 255, 0);
	//color[5] = GetColor(0, 255, 255);
	//color[6] = GetColor(50, 150, 150);
	//color[7] = GetColor(100, 100, 100);
	//color[8] = GetColor(200, 0, 0);
	//color[9] = GetColor(200, 200, 0);
	//color[10] = GetColor(0, 255, 100);

	//fhandle[0] = CreateFontToHandle("HG�ۺ޼��M-PRO", 18, 3, DX_FONTTYPE_ANTIALIASING_EDGE);
	//	fhandle[0]=CreateFontToHandle( "Highlight LET" , 18 , 3 ,DX_FONTTYPE_ANTIALIASING_EDGE) ;
	//	fhandle[0]=CreateFontToHandle( "John Handy LET" , 18 , 3 ,DX_FONTTYPE_ANTIALIASING_EDGE) ;
	//	fhandle[0]=CreateFontToHandle( "MV Boli" , 18 , 3 ,DX_FONTTYPE_ANTIALIASING_EDGE) ;
	//	fhandle[0]=CreateFontToHandle( "Orange LET" , 18 , 3 ,DX_FONTTYPE_ANTIALIASING_EDGE) ;



	//enemy_img[0] = LoadGraph("dat/img/mons/0.png");
	//disp_load();
	//icon_img = LoadGraph("dat/img/icon/100.png");
	//disp_load();
	//btetc_img[0] = LoadGraph("dat/img/animation/2.png");
	//disp_load();
	//btetc_img[1] = LoadGraph("dat/img/battle/0.png");
	//disp_load();
	//btetc_img[2] = LoadGraph("dat/img/battle/2.png");
	//disp_load();

	//se_sound[0] = LoadSoundMem("dat/sound/SE/0.ogg");
	////disp_load();
	////se_sound[1] = LoadSoundMem("dat/sound/SE/1.ogg");
	////disp_load();
	//Defi/*ne::se_sound[2] = LoadSoundMem("dat/sound/SE/2.ogg");
	//disp_load();
	//Define::se_sound[3] = LoadSoundMem("dat/sound/SE/3.ogg");*/
	//disp_load();
	////se_sound[4] = LoadSoundMem("dat/sound/SE/4.ogg");
	////disp_load();
	////se_sound[5] = LoadSoundMem("dat/sound/SE/5.ogg");
	////disp_load();
	//se_sound[6] = LoadSoundMem("dat/sound/SE/6.ogg");
	//disp_load();
	//se_sound[100] = LoadSoundMem("dat/sound/SE/100.ogg");
	//disp_load();
	//se_sound[200] = LoadSoundMem("dat/sound/SE/200.ogg");
	//disp_load();
	//se_sound[201] = LoadSoundMem("dat/sound/SE/201.ogg");
	//disp_load();
	//se_sound[202] = LoadSoundMem("dat/sound/SE/202.ogg");
	//disp_load();
	//se_sound[203] = LoadSoundMem("dat/sound/SE/203.ogg");
	//disp_load();
	//se_sound[204] = LoadSoundMem("dat/sound/SE/204.ogg");
	//disp_load();

	//se_sound[301] = LoadSoundMem("dat/sound/SE/301.ogg");
	//disp_load();
	//se_sound[302] = LoadSoundMem("dat/sound/SE/302.ogg");
	//disp_load();
	//se_sound[303] = LoadSoundMem("dat/sound/SE/303.ogg");
	//disp_load();
	//se_sound[304] = LoadSoundMem("dat/sound/SE/304.ogg");
	//disp_load();

	//se_sound[100]~[200]�܂ł͗\��

	LoadDivGraph("dat/img/mapchip/0/0.png", 4, 4, 1, 32, 32, Define::mapchip_img[0]);
	disp_load();

	return;
}

void map_graph() {//�}�b�v�̕`��
	int i, j;
	for (i = 0; i < Define::WINDOW_WIDTH / Define::WIDE; i++) {//���̃E�B���h�E�T�C�Y/�P��Ԃ̃T�C�Y�����̋�Ԍ�
		for (j = 0; j < Define::WINDOW_HEIGHT / Define::WIDE; j++) {//�c�̃E�B���h�E�T�C�Y/�P��Ԃ̃T�C�Y���c�̋�Ԍ�
			DrawGraph(i * Define::WIDE, j * Define::WIDE, Define::mapchip_img[0][0], TRUE);//��������S�Ă̋�ԂɎŐ���`��
			if (Define::map[2][j][i] != 0)//�Ő��̏�ɉ摜��\�������Ԃ̎�
				DrawGraph(i * Define::WIDE, j * Define::WIDE, Define::mapchip_img[0][Define::map[2][j][i]], TRUE);//���̉摜��`��
		}
	}
	return;
}


DungeonScene::DungeonScene(IOnSceneChangedListener * sc_listener, const Parameter & parameter) :
	AbstructScene(sc_listener, parameter) {

	////
	dat_load();
	////

	state_ = State::PREPARATION;
	player_ = new Character;
}

DungeonScene::~DungeonScene() {

	delete player_;
	delete monster_;
}

/*!
* @brief �X�V����
*/
void DungeonScene::Update() {


	switch (state_) {

		// ������
	case State::PREPARATION:

		monster_ = new Monster;
		state_ = State::MAP_CREATION;
		break;


	case State::MAP_CREATION:

		// �}�b�v�̏�����
		CreateMap();

		PlaySoundMem(Define::map_sound, DX_PLAYTYPE_LOOP);

		state_ = State::ADVENTURE;
		break;


	case State::ADVENTURE:


		// �L�����ʒu�̍X�V
		// �ړ��������_���G���J�E���g
		player_->Update();

		if (player_->IsFinishWalk()) {
			if (player_->IsEncountEnemy()) {
				state_ = State::BATTLE;
			}
		}

		break;


	case State::BATTLE: {

		// �o�g���V�[���̒ǉ�
		Parameter parameter;
		parameter.Set("player", static_cast<void*>(player_));
		parameter.Set("monster", static_cast<void*>(monster_));
		bool is_pop_scene = false;
		bool is_clear_stack = false;
		scene_change_listener_->OnSceneChanged(Define::Scene::BATTLE, parameter, is_pop_scene, is_clear_stack);
		state_ = State::ADVENTURE;
		break;
	}

	default:
		break;
	}
}

/*!
* @brief �`�揈��
*/
void DungeonScene::Draw() const {

	map_graph();//�}�b�v�̕`��

	player_->Draw();
}

void DungeonScene::CreateMap() {

	for (int x = 0; x < Define::WINDOW_WIDTH/ Define::WIDE; x++) {//����20���
		for (int y = 0; y < Define::WINDOW_WIDTH / Define::WIDE; y++) {//�c��15���
			if (Define::map[2][y][x] > 1)//�ʂ�Ȃ��ꏊ�Ȃ�
				Define::mapd[y][x] = 1;			//�ʂ�Ȃ��t���O�𗧂Ă�
			else
				Define::mapd[y][x] = 0;			//�ʂ��t���O�𗧂Ă�
		}
	}
	POINT position = player_->GetPosition();
	Define::mapd[position.y / Define::WIDE][position.x / Define::WIDE] = 1;	//��l��������ꏊ��ʂ�Ȃ��ꏊ�Ƃ���

	return;
}
