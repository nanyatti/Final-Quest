#pragma once
#include <Windows.h>
#include "AbstructObject.h"
#include "../Define/Define.h"

class Character;

/*!
* @brief �v���C���[�̓G�ƂȂ郂���X�^�[
*/
class Monster final : public AbstructObject {

public:

	Monster();
	~Monster() {}
	void Update() final;
	void Draw() const final;
	bool IsCommandState() const;
	void SetIsCommadnState(bool flg);
	int GetHP() const;
	const Define::Status & GetStatus() const;
	int Attack(const Character & monster) const;
	void Damage(int damage);

private:

	void BattleUpdate();

private:

	Define::Status status_;	// �X�e�[�^�X
	POINT battle_position_;	// �o�g�����̈ʒu
	bool is_command_state_; // �o�g�����ōs���I����Ԃł��邩
};
