#include <DxLib.h>
#include "Looper.h"
#include "Input/Keyboard.h"
#include "Scene/DungeonScene.h"
#include "Scene/Parameter.h"
#include "Scene/BattleScene.h"
#include "Scene/TitleScene.h"
#include "Tool/Error.h"

Looper::Looper() {

	// Keyboardのインスタンス生成
	Keyboard::Create();
	keyboard_ = Keyboard::GetInstance();

	// ゲーム開始時はタイトルシーンをスタックへ追加
	Parameter parameter;
	const bool is_pop_scene = false;
	const bool is_clear_stack = false;
	OnSceneChanged(Define::Scene::TITLE, parameter, is_pop_scene, is_clear_stack);
}

Looper::~Looper() {

	// Keyboardのインスタンス破棄
	Keyboard::Delete();
}

/*!
* @brief FPS計測・キー状態・ゲーム処理・描画の更新
* @return ゲームを終了するかどうか
*/
bool Looper::Update() {

	// FPS計測・待機処理
	fps_counter_.Wait();
	float delta_msec = fps_counter_.CalcDeltaMSec();
	fps_counter_.CalcFPS(delta_msec);
	DrawFormatString(0, 0, GetColor(255, 255, 255), "%f FPS", fps_counter_.GetFPS());

	// キー状態更新
	if (keyboard_ != nullptr) {
		keyboard_->Update();
	}

	// ゲーム処理・描画
	if (!scene_stack_.empty()) {
		scene_stack_.top()->Update();
		scene_stack_.top()->Draw();
	}

	return true;
}

/*!
* @brief シーンスタックへの追加・クリア(各シーンから呼び出し)
* @param scene			変更するシーンのenum
* @param parameter		前のシーンから引き継ぐパラメータ
* @param is_pop_scene	現在のシーンを破棄するか
* @param is_clear_stack	シーンスタックをクリアするか
*/
void Looper::OnSceneChanged(const Define::Scene scene, const Parameter & paramter, const bool is_pop_scene, const bool is_clear_stack) {

	// 現在のシーンの破棄
	if (is_pop_scene) {
		if (!scene_stack_.empty()) {
			scene_stack_.pop();
		}
	}

	// スタックのクリア
	if (is_clear_stack) {
		while (!scene_stack_.empty()) {
			scene_stack_.pop();
		}
	}

	// スタックへのシーン追加
	switch (scene) {
	case Define::Scene::TITLE:
		scene_stack_.push(std::make_shared<TitleScene>(this, paramter));
		break;
	case Define::Scene::DUNGEON:
		scene_stack_.push(std::make_shared<DungeonScene>(this, paramter));
		break;
	case Define::Scene::BATTLE:
		scene_stack_.push(std::make_shared<BattleScene>(this, paramter));
		break;
	case Define::Scene::NONE:
		break;
	default:
		SHOW_ERROR("不明なシーンの指定");
		break;
	}
}
