#include <DxLib.h>
#include "IOnSceneChangedListener.h"
#include "Parameter.h"
#include "TitleScene.h"
#include "../Input/Keyboard.h"

TitleScene::TitleScene(IOnSceneChangedListener * sc_listener, const Parameter & parameter) :
	AbstructScene(sc_listener, parameter){
}

/*!
* @brief çXêVèàóù
*/
void TitleScene::Update() {

	Keyboard * keyboard = Keyboard::GetInstance();
	if (keyboard != nullptr) {
		if (keyboard->IsDownKey('X')) {
			Parameter parameter;
			const bool is_pop_scene = true;
			const bool is_stack_clear = false;
			scene_change_listener_->OnSceneChanged(Define::Scene::DUNGEON, parameter, is_pop_scene, is_stack_clear);
		}
	}
}

/*!
* @brief ï`âÊèàóù
*/
void TitleScene::Draw() const {

	DrawString(100, 100, "FINAL QUEST", GetColor(255, 255, 255));
	DrawString(100, 200, "PRESS  X  KEY", GetColor(255, 255, 255));
}
