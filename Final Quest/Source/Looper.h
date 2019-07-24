#pragma once
#include <memory>
#include <stack>
#include "Scene/IOnSceneChangedListener.h"
#include "Tool/FPSCounter.h"

class Keyboard;
class Parameter;
class AbstructScene;

/*!
* @brief 入力・ゲーム処理・描画を一定の間隔で処理
*/
class Looper final : public IOnSceneChangedListener {

public:

	Looper();
	~Looper();
	bool Update();
	void OnSceneChanged(const Define::Scene scene, const Parameter & paramter, const bool is_pop_scene, const bool is_clear_stack) final;
	
private:

	FPSCounter fps_counter_;							// FPS・経過時間の計測
	Keyboard * keyboard_;								// キー入力管理
	std::stack<std::shared_ptr<AbstructScene>> scene_stack_;	// シーン管理用スタック
};