#pragma once

class IOnSceneChangedListener;
class Parameter;

/*!
* @brief �e�V�[���̊��ƂȂ钊�ۃN���X
*/
class AbstructScene {

public:

	AbstructScene(IOnSceneChangedListener * sc_listener, const Parameter & parameter);
	virtual ~AbstructScene() {};
	virtual void Update() = 0;
	virtual void Draw() = 0;

protected:

	IOnSceneChangedListener * scene_change_listener_;	// �V�[���Ǘ��҂ւ̃|�C���^
};