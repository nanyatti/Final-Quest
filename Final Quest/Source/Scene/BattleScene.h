#pragma once
#include "AbstructScene.h"

class Character;
class Monster;

/*!
* @brief バトルシーン
*/
class BattleScene final : public AbstructScene {

private:

	// バトルシーンの状態を列挙
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

	State state_;			// シーンの状態
	Character * player_;	// プレイヤー
	Monster * monster_;		// モンスター

	bool is_escape_;		// 逃げるか
	bool is_gameover_;		// ゲームオーバであるか
	bool is_victory_;		// 勝利したか
};