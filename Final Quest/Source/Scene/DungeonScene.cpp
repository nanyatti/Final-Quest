#include <DxLib.h>
#include "DungeonScene.h"
#include "IOnSceneChangedListener.h"
#include "Parameter.h"
#include "../ActorObject/Character.h"
#include "../ActorObject/Monster.h"
#include "../Input/Keyboard.h"


DungeonScene::DungeonScene(IOnSceneChangedListener * sc_listener, const Parameter & parameter) :
	AbstructScene(sc_listener, parameter) {

	state_ = State::PREPARATION;
	player_ = new Character;

	LoadDivGraph("dat/img/mapchip/0/0.png", 4, 4, 1, 32, 32, mapchip_img[0]);
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


	case State::MAP_CREATION: {

		// �}�b�v�̏�����
		CreateMap();

		state_ = State::ADVENTURE;
		break;
	}


	case State::ADVENTURE:


		// �L�����ʒu�̍X�V
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
void DungeonScene::Draw() {

	switch (state_) {
	case State::ADVENTURE:

		DrawMap();//�}�b�v�̕`��
		player_->Draw();
		break;
	default:
		break;
	}

}


/*!
* @brief �}�b�v�̍쐬
*/
void DungeonScene::CreateMap() {

	for (int x = 0; x < Define::WINDOW_WIDTH/ Define::WIDE; x++) {//����20���
		for (int y = 0; y < Define::WINDOW_WIDTH / Define::WIDE; y++) {//�c��15���
			if (map[2][y][x] > 1)//�ʂ�Ȃ��ꏊ�Ȃ�
				mapd[y][x] = 1;			//�ʂ�Ȃ��t���O�𗧂Ă�
			else
				mapd[y][x] = 0;			//�ʂ��t���O�𗧂Ă�
		}
	}

	return;
}

/*!
* @brief �}�b�v�̕`��
*/
void DungeonScene::DrawMap() {

	int i, j;


	for (i = 0; i < Define::WINDOW_WIDTH / Define::WIDE; i++) {//���̃E�B���h�E�T�C�Y/�P��Ԃ̃T�C�Y�����̋�Ԍ�
		for (j = 0; j < Define::WINDOW_HEIGHT / Define::WIDE; j++) {//�c�̃E�B���h�E�T�C�Y/�P��Ԃ̃T�C�Y���c�̋�Ԍ�
			DrawGraph(i * Define::WIDE, j * Define::WIDE, mapchip_img[0][0], TRUE);//��������S�Ă̋�ԂɎŐ���`��
			if (map[2][j][i] != 0)//�Ő��̏�ɉ摜��\�������Ԃ̎�
				DrawGraph(i * Define::WIDE, j * Define::WIDE, mapchip_img[0][map[0][j][i]], TRUE);//���̉摜��`��
		}
	}
	return;
}