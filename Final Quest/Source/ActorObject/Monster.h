#pragma once
#include <Windows.h>
#include "AbstructObject.h"
#include "../Define/Define.h"

class Character;

/*!
* @brief プレイヤーの敵となるモンスター
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

	Define::Status status_;	// ステータス
	POINT battle_position_;	// バトル中の位置
	bool is_command_state_; // バトル内で行動選択状態であるか
};
