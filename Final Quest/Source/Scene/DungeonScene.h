#pragma once
#include "AbstructScene.h"

class Character;
class Monster;

/*!
* @brief ダンジョンシーン
*/
class DungeonScene final : public AbstructScene {

private:

	// ダンジョンシーンの状態を列挙
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

	State state_;			// シーンの状態
	Character * player_;	// プレイヤー
	Monster * monster_;		// モンスター
};