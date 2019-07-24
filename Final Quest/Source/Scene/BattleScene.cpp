#include <DxLib.h>
#include "BattleScene.h"
#include "IOnSceneChangedListener.h"
#include "Parameter.h"
#include "../ActorObject/Character.h"
#include "../ActorObject/Monster.h"
#include "../Input/Keyboard.h"

namespace {

	// �R�}���h�\���p�\����
	struct Command {
		int x;
		int y;
		char name[128];
	};

	// �o�g���p�R�}���h
	Command battle_command[] = {
		{ 500, 400, "�U��" },
		{ 500, 420, "������" },
	};
	int select_command = 0;

	int finalize_counter = 0;
}


BattleScene::BattleScene(IOnSceneChangedListener * sc_listener, const Parameter & parameter) :
	AbstructScene(sc_listener, parameter) {

	state_ = State::INITILIZATION;
	player_ = static_cast<Character*>(parameter.Get("player"));
	monster_ = new Monster;

	is_escape_ = false;
	is_gameover_ = false;
	is_victory_ = false;
}

BattleScene::~BattleScene() {

	delete monster_;
}

/*!
* @brief �X�V����
*/
void BattleScene::Update() {

	switch (state_) {

	case State::INITILIZATION:

		PlaySoundMem(Define:: battle_sound, DX_PLAYTYPE_LOOP);

		state_ = State::OPENING;
		break;

	case State::OPENING:
		//battle_opening();
		state_ = State::BATTLE;
		break;

	case State::BATTLE:

		// �������̌㏈��
		if (is_victory_) {
			finalize_counter++;

			if (finalize_counter == 240) {
				player_->SetIsEncountEnemey(false);
				state_ = State::FINALIZATION;
				Parameter parameter;
				bool is_pop_scene = true;
				bool is_clear_stack = false;
				scene_change_listener_->OnSceneChanged(Define::Scene::NONE, parameter, is_pop_scene, is_clear_stack);
				finalize_counter = 0;
			}
			return;
		}

		// �Q�[���I�[�o���̓V�[���X�^�b�N���N���A
		if (is_gameover_) {
			finalize_counter++;

			if (finalize_counter == 300) {
				player_->SetIsEncountEnemey(false);
				state_ = State::FINALIZATION;
				Parameter parameter;
				bool is_pop_scene = false;
				bool is_clear_stack = true;
				scene_change_listener_->OnSceneChanged(Define::Scene::TITLE, parameter, is_pop_scene, is_clear_stack);
				finalize_counter = 0;
			}

			return;
		}

		// �ǂ�����ҋ@��Ԃ̏ꍇ�̓o�g���J�E���^���X�V
		if (!player_->IsCommandState() && !monster_->IsCommandState()) {
			player_->Update();
			monster_->Update();
		}

		// �s���I��
		if (player_->IsCommandState()) {
			if (SelectCommand()) {

				// �U��
				if (strcmp(battle_command[select_command].name, "�U��") == 0) {

					int damage = player_->Attack(*monster_);
					monster_->Damage(damage);

					if (monster_->GetHP() == 0) {
						is_victory_ = true;
					}
				}

				if (strcmp(battle_command[select_command].name, "������") == 0) {
					is_escape_ = true;
				}

				// �J�E���g�ĊJ
				player_->Update();
				player_->SetIsCommandState(false);
			}
		}

		//// �G�s��
		if (monster_->IsCommandState()) {

			// �U��
			int damage = monster_->Attack(*player_);
			player_->Damage(damage);

			if (player_->GetHP() == 0) {
				is_gameover_ = true;
			}

			monster_->Update();
			monster_->SetIsCommadnState(false);
		}


		if (is_escape_) {
			player_->SetIsEncountEnemey(false);
			state_ = State::FINALIZATION;
			Parameter parameter;
			bool is_pop_scene = true;
			bool is_clear_stack = false;
			scene_change_listener_->OnSceneChanged(Define::Scene::NONE, parameter, is_pop_scene, is_clear_stack);
		}

		break;

	case State::FINALIZATION:
		StopSoundFile();

	default:
		break;
	}
}

/*!
* @brief �`�揈��
*/
void BattleScene::Draw() const {

	switch (state_) {

	case State::BATTLE:

		DrawGraph(0, 0, Define::back_img[0], FALSE);
		DrawGraph(0, 480 - 134, Define::back_img[10], FALSE);

		monster_->Draw();
		player_->Draw();

		const Define::Status & monster_status = monster_->GetStatus();
		const Define::Status & player_status = player_->GetStatus();


		POINT monster_meter = { 15, 380 };
		POINT player_meter = { 250, 380 };

		// HP
		DrawBox(monster_meter.x, monster_meter.y, monster_meter.x + 150, monster_meter.y + 5, GetColor(255, 0, 0), FALSE);
		DrawBox(monster_meter.x, monster_meter.y, monster_meter.x + 150 * monster_status.hp / monster_status.hp_max, monster_meter.y + 5, GetColor(255, 0, 0), TRUE);

		DrawBox(player_meter.x, player_meter.y, player_meter.x + 150, player_meter.y + 5, GetColor(0, 0, 255), FALSE);
		DrawBox(player_meter.x, player_meter.y, player_meter.x + 150 * player_status.hp / player_status.hp_max, player_meter.y + 5, GetColor(0, 0, 255), TRUE);

		// �ҋ@�J�E���g
		POINT count_meter = { 150, 70 };
		DrawBox(monster_meter.x, monster_meter.y + count_meter.y, monster_meter.x + count_meter.x, monster_meter.y + count_meter.y + 5, GetColor(0, 150, 0), FALSE);
		DrawBox(monster_meter.x, monster_meter.y + count_meter.y, monster_meter.x + count_meter.x * monster_status.battle_count / 2400, monster_meter.y + count_meter.y + 3, GetColor(0, 150, 0), TRUE);
		DrawBox(player_meter.x, player_meter.y + count_meter.y, player_meter.x + count_meter.x, player_meter.y + count_meter.y + 5, GetColor(0, 150, 0), FALSE);
		DrawBox(player_meter.x, player_meter.y + count_meter.y, player_meter.x + count_meter.x * player_status.battle_count / 2400, player_meter.y + count_meter.y + 3, GetColor(0, 150, 0), TRUE);

		// �R�}���h�\��
		for (int i = 0; i < 2; i++) {
			DrawFormatString(battle_command[i].x, battle_command[i].y, GetColor(255, 255, 255), battle_command[i].name);
		}

		// �������
		if (is_victory_) {
			SetDrawBlendMode(DX_BLENDMODE_ALPHA, 128);
			DrawBox(0, 0, 640, 480, GetColor(0, 255, 255), TRUE);
			DrawString(300, 230, "VICTORY!!", GetColor(255, 255, 255));
			SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
		}

		// �Q�[���I�[�o���
		if (is_gameover_) {
			SetDrawBlendMode(DX_BLENDMODE_ALPHA, 128);
			DrawBox(0, 0, 640, 480, GetColor(255, 0, 0), TRUE);
			DrawString(300, 230, "GAME OVER", GetColor(255, 255, 255));
			SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
		}

		break;

	}
}

bool BattleScene::SelectCommand() {

	Keyboard * keyboard = Keyboard::GetInstance();

	if (keyboard == nullptr) {
		return false;
	}

	// �R�}���h�̈ړ�
	if (keyboard->IsDownKey(VK_UP)) {
		select_command = abs((select_command + 1) % 2);
		PlaySoundMem(Define::se_sound[0], DX_PLAYTYPE_BACK);
	}
	if (keyboard->IsDownKey(VK_DOWN)) {
		select_command = abs((select_command - 1) % 2);
		PlaySoundMem(Define::se_sound[0], DX_PLAYTYPE_BACK);
	}

	// �ʒu�̍X�V
	for (int i = 0; i < 2; i++) {
		if (i == select_command) {
			battle_command[i].x = 480;
		}
		else {
			battle_command[i].x = 500;
		}
	}

	// �I��
	if (keyboard->IsDownKey('X')) {
		PlaySoundMem(Define::se_sound[1], DX_PLAYTYPE_BACK);
		return true;
	}

	return false;
}