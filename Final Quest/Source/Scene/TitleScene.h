#pragma once
#include "AbstructScene.h"

/*!
* @brief �^�C�g���V�[��
*/
class TitleScene final : public AbstructScene {

public:

	TitleScene(IOnSceneChangedListener * sc_listener, const Parameter & parameter);
	~TitleScene() {}
	void Update() final;
	void Draw() final;
};