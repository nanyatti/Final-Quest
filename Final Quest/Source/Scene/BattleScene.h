#pragma once
#include "AbstructScene.h"

class Character;
class Monster;

/*!
* @brief �o�g���V�[��
*/
class BattleScene final : public AbstructScene {

private:

	// �o�g���V�[���̏�Ԃ��
	enum State {
		INITILIZATION,
		OPENING,
		BATTLE,
		FINALIZATION,
	};

public:

	BattleScene(IOnSceneChangedListener * sc_listener, const Parameter & parameter);
	~BattleScene();
	void Update() final;
	void Draw() const final;
	bool SelectCommand();

private:

	State state_;			// �V�[���̏��
	Character * player_;	// �v���C���[
	Monster * monster_;		// �����X�^�[

	bool is_escape_;		// �����邩
	bool is_gameover_;		// �Q�[���I�[�o�ł��邩
	bool is_victory_;		// ����������
};