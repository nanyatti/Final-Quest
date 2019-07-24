#include <DxLib.h>
#include "Looper.h"
#include "Input/Keyboard.h"
#include "Scene/DungeonScene.h"
#include "Scene/Parameter.h"
#include "Scene/BattleScene.h"
#include "Scene/TitleScene.h"
#include "Tool/Error.h"

Looper::Looper() {

	// Keyboard�̃C���X�^���X����
	Keyboard::Create();
	keyboard_ = Keyboard::GetInstance();

	// �Q�[���J�n���̓^�C�g���V�[�����X�^�b�N�֒ǉ�
	Parameter parameter;
	const bool is_pop_scene = false;
	const bool is_clear_stack = false;
	OnSceneChanged(Define::Scene::TITLE, parameter, is_pop_scene, is_clear_stack);
}

Looper::~Looper() {

	// Keyboard�̃C���X�^���X�j��
	Keyboard::Delete();
}

/*!
* @brief FPS�v���E�L�[��ԁE�Q�[�������E�`��̍X�V
* @return �Q�[�����I�����邩�ǂ���
*/
bool Looper::Update() {

	// FPS�v���E�ҋ@����
	fps_counter_.Wait();
	float delta_msec = fps_counter_.CalcDeltaMSec();
	fps_counter_.CalcFPS(delta_msec);
	DrawFormatString(0, 0, GetColor(255, 255, 255), "%f FPS", fps_counter_.GetFPS());

	// �L�[��ԍX�V
	if (keyboard_ != nullptr) {
		keyboard_->Update();
	}

	// �Q�[�������E�`��
	if (!scene_stack_.empty()) {
		scene_stack_.top()->Update();
		scene_stack_.top()->Draw();
	}

	return true;
}

/*!
* @brief �V�[���X�^�b�N�ւ̒ǉ��E�N���A(�e�V�[������Ăяo��)
* @param scene			�ύX����V�[����enum
* @param parameter		�O�̃V�[����������p���p�����[�^
* @param is_pop_scene	���݂̃V�[����j�����邩
* @param is_clear_stack	�V�[���X�^�b�N���N���A���邩
*/
void Looper::OnSceneChanged(const Define::Scene scene, const Parameter & paramter, const bool is_pop_scene, const bool is_clear_stack) {

	// ���݂̃V�[���̔j��
	if (is_pop_scene) {
		if (!scene_stack_.empty()) {
			scene_stack_.pop();
		}
	}

	// �X�^�b�N�̃N���A
	if (is_clear_stack) {
		while (!scene_stack_.empty()) {
			scene_stack_.pop();
		}
	}

	// �X�^�b�N�ւ̃V�[���ǉ�
	switch (scene) {
	case Define::Scene::TITLE:
		scene_stack_.push(std::make_shared<TitleScene>(this, paramter));
		break;
	case Define::Scene::DUNGEON:
		scene_stack_.push(std::make_shared<DungeonScene>(this, paramter));
		break;
	case Define::Scene::BATTLE:
		scene_stack_.push(std::make_shared<BattleScene>(this, paramter));
		break;
	case Define::Scene::NONE:
		break;
	default:
		SHOW_ERROR("�s���ȃV�[���̎w��");
		break;
	}
}
