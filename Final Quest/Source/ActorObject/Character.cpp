#include <DxLib.h>
#include "Character.h"
#include "../Input/Keyboard.h"
#include "../ActorObject/Monster.h"
#include "../Scene/DungeonScene.h"

Character::Character() {

	scene_				= Define::Scene::DUNGEON;
	position_			= { 2, 2 };
	prev_position_		= position_;
	direction_			= Direction::DOWN;
	move_count_			= 0;
	num_move_frame_		= 20;
	is_can_move_		= true;
	is_finish_walk_		= false;
	is_encount_enemy	= false;

	status_.level		= 10;
	status_.hp			= 100;
	status_.hp_max		= 100;
	status_.power		= 20;
	status_.deffence	= 20;
	status_.agility		= 10;
	status_.battle_count = GetRand(235);

	battle_position_ = { 15, 5};
	is_command_state_ = false;
}

/*!
* @brief �X�V����
*/
void Character::Update() {

	// �V�[���ɉ������X�V�������s��
	switch (scene_) {

	case Define::Scene::DUNGEON:
		MoveDungeon();
		break;

	case Define::Scene::BATTLE:
		BattleCommand();
		break;

	default:
		break;
	}
}

/*!
* @brief �`�揈��
*/
void Character::Draw() const {

	switch (scene_) {

	case Define::Scene::DUNGEON:
		// �ړ��ߒ��`��
		if (0 < move_count_) {
			int x = position_.x * Define::WIDE - (position_.x - prev_position_.x) * move_count_ * Define::WIDE / num_move_frame_;
			int y = position_.y * Define::WIDE - (position_.y - prev_position_.y) * move_count_ * Define::WIDE / num_move_frame_;
			DrawCircle(x + Define::WIDE / 2, y + Define::WIDE / 2, Define::WIDE / 2, GetColor(0, 0, 255));
		}
		else {
			// �摜�̑傫�����l������Y�l�͒�������
			DrawCircle(position_.x * Define::WIDE + Define::WIDE / 2, position_.y * Define::WIDE + Define::WIDE / 2, Define::WIDE / 2, GetColor(0, 0, 255));
		}
		break;

	case Define::Scene::BATTLE:
		DrawCircle(battle_position_.x * Define::WIDE + Define::WIDE / 2, battle_position_.y * Define::WIDE + Define::WIDE / 2, Define::WIDE / 2, GetColor(0, 0, 255));
		break;

	default:
		break;
	}
}

/*!
* @brief �ړ��������������������擾
*/
bool Character::IsFinishWalk() const {

	return is_finish_walk_;
}

/*!
* @brief �G�ƃG���J�E���g���������擾
*/
bool Character::IsEncountEnemy() const {

	return is_encount_enemy;
}

/*!
* @brief �G�ƃG���J�E���g��������ݒ�
*/
void Character::SetIsEncountEnemey(bool flg) {

	is_encount_enemy = flg;
}

/*!
* @brief �o�g�����̍s���I����Ԃł��邩���擾
*/
bool Character::IsCommandState() const {

	return is_command_state_;
}

/*!
* @brief �o�g�����̍s���I����Ԃł��邩��ݒ�
*/
void Character::SetIsCommandState(bool flg) {

	is_command_state_ = flg;
}

/*!
* @brief �ʒu���擾
*/
POINT Character::GetPosition() const {

	return position_;
}

/*!
* @brief �o�g�����̍s���I����Ԃł��邩��ݒ�
*/
int Character::GetHP() const {

	return status_.hp;
}

/*!
* @brief �X�e�[�^�X�̎擾
*/
const Define::Status & Character::GetStatus() const {

	return status_;
}

/*!
* @brief �U���E�_���[�W�擾
*/
int Character::Attack(const Monster & monster) {

	Define::Status monster_status = monster.GetStatus();

	int damage = status_.level * 2 + status_.power - monster_status.deffence;

	return damage;
}

/*!
* @brief ��_���[�W
*/
void Character::Damage(int damage) {

	status_.hp -= damage;
}


/*!
* @brief �_���W�����T�����̈ړ�����
*/
void Character::MoveDungeon() {

	Keyboard * keyboard = Keyboard::GetInstance();
	if (keyboard == nullptr) {
		return;
	}

	// �ړ����̏ꍇ
	if (0 < move_count_) {
		move_count_--;
		is_can_move_ = false;

		// �ړ������t���O
		if (move_count_ == 0) {
			is_finish_walk_ = true;

			// �����̐؂�ւ�
			if (is_encount_enemy) {
				scene_ = Define::Scene::BATTLE;
			}
		}
	}
	else {
		is_can_move_ = true;
		is_finish_walk_ = false;
	}

	// �L�[���͂ɂ��L��������
	if (is_can_move_) {

		// �ʒu�̕ێ�
		prev_position_ = position_;

		// �\���L�[�ɂ��ړ��E�����̍X�V
		// �ړ������̂��߈ړ��ɂ�����t���[������ݒ�
		if (keyboard->IsPushKey(VK_UP)) {
			direction_ = Direction::UP;
			position_.y--;
			move_count_ = num_move_frame_;
		}
		else if (keyboard->IsPushKey(VK_RIGHT)) {
			direction_ = Direction::RIGHT;
			position_.x++;
			move_count_ = num_move_frame_;
		}
		else if (keyboard->IsPushKey(VK_DOWN)) {
			direction_ = Direction::DOWN;
			position_.y++;
			move_count_ = num_move_frame_;
		}
		else if (keyboard->IsPushKey(VK_LEFT)) {
			direction_ = Direction::LEFT;
			position_.x--;
			move_count_ = num_move_frame_;
		}

		// �ړ��悪���s�\�ȏꍇ
		if (/*DungeonScene::mapd[position_.y][position_.x]*/1 == 0) {

			// �G���J�E���g���I
			is_encount_enemy = GetRand(15) == 0;
		}
		else {

			// �ʒu��߂�
			if (direction_ == Direction::UP) {
				position_.y++;
			}
			else if (direction_ == Direction::RIGHT) {
				position_.x--;
			}
			else if (direction_ == Direction::DOWN) {
				position_.y--;
			}
			else if (direction_ == Direction::LEFT) {
				position_.x++;
			}
		}
	}
}

/*!
* @brief �o�g�����̏���
*/
void Character::BattleCommand() {

	Keyboard * keyboard = Keyboard::GetInstance();
	if (keyboard == nullptr) {
		return;
	}

	if (!is_encount_enemy) {
		scene_ = Define::Scene::DUNGEON;
	}

	// �s���\���Ԃ܂őҋ@
	if (!is_command_state_) {
		status_.battle_count += status_.agility;
		if (status_.battle_count > 2400) {
			is_command_state_ = true;
		}
	}
	else {
		status_.battle_count = 0;
	}
}
