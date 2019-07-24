#pragma once
#include "AbstructScene.h"

class Character;
class Monster;

/*!
* @brief �_���W�����V�[��
*/
class DungeonScene final : public AbstructScene {

private:

	// �_���W�����V�[���̏�Ԃ��
	enum State {
		PREPARATION,
		MAP_CREATION,
		ADVENTURE,
		BATTLE
	};

public:

	DungeonScene(IOnSceneChangedListener * sc_listener, const Parameter & parameter);
	~DungeonScene();
	void Update() final;
	void Draw() const final;

private:

	void CreateMap();

private:

	State state_;			// �V�[���̏��
	Character * player_;	// �v���C���[
	Monster * monster_;		// �����X�^�[
};