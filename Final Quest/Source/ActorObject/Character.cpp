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
* @brief 更新処理
*/
void Character::Update() {

	// シーンに応じた更新処理を行う
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
* @brief 描画処理
*/
void Character::Draw() const {

	switch (scene_) {

	case Define::Scene::DUNGEON:
		// 移動過程描画
		if (0 < move_count_) {
			int x = position_.x * Define::WIDE - (position_.x - prev_position_.x) * move_count_ * Define::WIDE / num_move_frame_;
			int y = position_.y * Define::WIDE - (position_.y - prev_position_.y) * move_count_ * Define::WIDE / num_move_frame_;
			DrawCircle(x + Define::WIDE / 2, y + Define::WIDE / 2, Define::WIDE / 2, GetColor(0, 0, 255));
		}
		else {
			// 画像の大きさを考慮してY値は調整する
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
* @brief 移動処理が完了したかを取得
*/
bool Character::IsFinishWalk() const {

	return is_finish_walk_;
}

/*!
* @brief 敵とエンカウントしたかを取得
*/
bool Character::IsEncountEnemy() const {

	return is_encount_enemy;
}

/*!
* @brief 敵とエンカウントしたかを設定
*/
void Character::SetIsEncountEnemey(bool flg) {

	is_encount_enemy = flg;
}

/*!
* @brief バトル中の行動選択状態であるかを取得
*/
bool Character::IsCommandState() const {

	return is_command_state_;
}

/*!
* @brief バトル中の行動選択状態であるかを設定
*/
void Character::SetIsCommandState(bool flg) {

	is_command_state_ = flg;
}

/*!
* @brief 位置を取得
*/
POINT Character::GetPosition() const {

	return position_;
}

/*!
* @brief バトル中の行動選択状態であるかを設定
*/
int Character::GetHP() const {

	return status_.hp;
}

/*!
* @brief ステータスの取得
*/
const Define::Status & Character::GetStatus() const {

	return status_;
}

/*!
* @brief 攻撃・ダメージ取得
*/
int Character::Attack(const Monster & monster) {

	Define::Status monster_status = monster.GetStatus();

	int damage = status_.level * 2 + status_.power - monster_status.deffence;

	return damage;
}

/*!
* @brief 被ダメージ
*/
void Character::Damage(int damage) {

	status_.hp -= damage;
}


/*!
* @brief ダンジョン探索中の移動処理
*/
void Character::MoveDungeon() {

	Keyboard * keyboard = Keyboard::GetInstance();
	if (keyboard == nullptr) {
		return;
	}

	// 移動中の場合
	if (0 < move_count_) {
		move_count_--;
		is_can_move_ = false;

		// 移動完了フラグ
		if (move_count_ == 0) {
			is_finish_walk_ = true;

			// 処理の切り替え
			if (is_encount_enemy) {
				scene_ = Define::Scene::BATTLE;
			}
		}
	}
	else {
		is_can_move_ = true;
		is_finish_walk_ = false;
	}

	// キー入力によるキャラ制御
	if (is_can_move_) {

		// 位置の保持
		prev_position_ = position_;

		// 十字キーによる移動・向きの更新
		// 移動処理のため移動にかけるフレーム数を設定
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

		// 移動先が歩行可能な場合
		if (/*DungeonScene::mapd[position_.y][position_.x]*/1 == 0) {

			// エンカウント抽選
			is_encount_enemy = GetRand(15) == 0;
		}
		else {

			// 位置を戻す
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
* @brief バトル中の処理
*/
void Character::BattleCommand() {

	Keyboard * keyboard = Keyboard::GetInstance();
	if (keyboard == nullptr) {
		return;
	}

	if (!is_encount_enemy) {
		scene_ = Define::Scene::DUNGEON;
	}

	// 行動可能時間まで待機
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
