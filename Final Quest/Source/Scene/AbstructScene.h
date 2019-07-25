#pragma once

class IOnSceneChangedListener;
class Parameter;

/*!
* @brief 各シーンの基底となる抽象クラス
*/
class AbstructScene {

public:

	AbstructScene(IOnSceneChangedListener * sc_listener, const Parameter & parameter);
	virtual ~AbstructScene() {};
	virtual void Update() = 0;
	virtual void Draw() = 0;

protected:

	IOnSceneChangedListener * scene_change_listener_;	// シーン管理者へのポインタ
};