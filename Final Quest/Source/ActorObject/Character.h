#pragma once
#include <Windows.h>
#include "AbstructObject.h"
#include "../Define/Define.h"

class Monster;

/*!
* @brief �v���C���[���������L�����N�^�[
*/
class Character final : public AbstructObject {

public:

	Character();
	~Character() {}
	void Update() final;
	void Draw() const final;
	bool IsFinishWalk() const;
	bool IsEncountEnemy() const;
	void SetIsEncountEnemey(bool flg);
	bool IsCommandState() const;
	void SetIsCommandState(bool flg);
	POINT GetPosition() const;
	int GetHP() const;
	const Define::Status & GetStatus() const;
	int Attack(const Monster & monster);
	void Damage(int damage);

private:

	void MoveDungeon();
	void BattleCommand();

private:

	Define::Scene scene_;	// �V�[��
	
	POINT position_;		// �}�b�v��̈ʒu�E�}�X�P��
	POINT prev_position_;	// �O�t���[���̈ʒu
	Direction direction_;	// �̂̌���
	int move_count_;		// �ړ�����J�E���g�E�t���[����
	int num_move_frame_;	// �ړ������ɂ�����t���[����
	bool is_can_move_;		// �ړ��\�ł��邩
	bool is_finish_walk_;	// �ړ�����������������
	bool is_encount_enemy;	// �G�Ƒ���������

	Define::Status status_;	// �L�����X�e�[�^�X
	POINT battle_position_; // �o�g�����̈ʒu
	bool is_command_state_;	// �o�g�����ōs���I����Ԃł��邩
};