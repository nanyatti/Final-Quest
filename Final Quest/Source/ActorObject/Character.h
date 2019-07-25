#pragma once
#include <Windows.h>
#include "AbstructObject.h"
#include "../Define/Define.h"

class Monster;

/*!
* @brief プレイヤーが動かすキャラクター
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

	Define::Scene scene_;	// シーン
	
	POINT position_;		// マップ上の位置・マス単位
	POINT prev_position_;	// 前フレームの位置
	Direction direction_;	// 体の向き
	int move_count_;		// 移動制御カウント・フレーム数
	int num_move_frame_;	// 移動処理にかけるフレーム数
	bool is_can_move_;		// 移動可能であるか
	bool is_finish_walk_;	// 移動処理が完了したか
	bool is_encount_enemy;	// 敵と遭遇したか

	Define::Status status_;	// キャラステータス
	POINT battle_position_; // バトル時の位置
	bool is_command_state_;	// バトル内で行動選択状態であるか
};