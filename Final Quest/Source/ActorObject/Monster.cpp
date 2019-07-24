#include <DxLib.h>
#include "Monster.h"
#include "../ActorObject/Character.h"

Monster::Monster() {

	status_.level		= 10;
	status_.hp			= 100;
	status_.hp_max		= 100;
	status_.power		= 20;
	status_.deffence	= 20;
	status_.agility		= 8;
	status_.battle_count = GetRand(235);

	battle_position_	= { 4, 5 };
	is_command_state_	= false;
}

/*!
* @brief �X�V����
*/
void Monster::Update() {

	BattleUpdate();
}

/*!
* @brief �`�揈��
*/
void Monster::Draw() const {

	DrawCircle(battle_position_.x * Define::WIDE + Define::WIDE / 2, battle_position_.y * Define::WIDE + Define::WIDE / 2, Define::WIDE / 2, GetColor(255, 0, 0));
}

/*!
* @brief �o�g�����̍s���I����Ԃł��邩���擾
*/
bool Monster::IsCommandState() const {

	return is_command_state_;
}

/*!
* @brief �o�g�����̍s���I����Ԃł��邩��ݒ�
*/
void Monster::SetIsCommadnState(bool flg) {

	is_command_state_ = flg;
}

int Monster::GetHP() const {

	return status_.hp;
}

/*!
* @brief �X�e�[�^�X�̎擾
*/
const Define::Status & Monster::GetStatus() const {

	return status_;
}

/*!
* @brief �U���E�_���[�W�擾
*/
int Monster::Attack(const Character & character) const {

	Define::Status monster_status = character.GetStatus();

	int damage = status_.level * 2 + status_.power - monster_status.deffence;
	return damage;
}

/*!
* @brief ��_���[�W
*/
void Monster::Damage(int damage) {

	status_.hp -= damage;

	if (status_.hp < 0) {
		status_.hp = 0;
	}
}

/*!
* @brief �o�g�����̏���
*/
void Monster::BattleUpdate() {

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