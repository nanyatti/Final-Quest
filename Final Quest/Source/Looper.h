#pragma once
#include <memory>
#include <stack>
#include "Scene/IOnSceneChangedListener.h"
#include "Tool/FPSCounter.h"

class Keyboard;
class Parameter;
class AbstructScene;

/*!
* @brief ���́E�Q�[�������E�`������̊Ԋu�ŏ���
*/
class Looper final : public IOnSceneChangedListener {

public:

	Looper();
	~Looper();
	bool Update();
	void OnSceneChanged(const Define::Scene scene, const Parameter & paramter, const bool is_pop_scene, const bool is_clear_stack) final;
	
private:

	FPSCounter fps_counter_;							// FPS�E�o�ߎ��Ԃ̌v��
	Keyboard * keyboard_;								// �L�[���͊Ǘ�
	std::stack<std::shared_ptr<AbstructScene>> scene_stack_;	// �V�[���Ǘ��p�X�^�b�N
};