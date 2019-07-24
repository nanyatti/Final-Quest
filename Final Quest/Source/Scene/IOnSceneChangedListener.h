#pragma once
#include "../Define/Define.h"

class Parameter;

/*!
* @brief �V�[��������Ǘ��҂փV�[���ύX���R�[���o�b�N���邽�߂̃��X�i�[�C���^�t�G�[�X
*/
class IOnSceneChangedListener {

public:

	IOnSceneChangedListener() {}
	virtual ~IOnSceneChangedListener() {}
	virtual void OnSceneChanged(const Define::Scene scene, const Parameter & paramter, const bool is_pop_scene, const bool is_clear_stack) = 0;
};