#pragma once
#include "../Define/Define.h"

class Parameter;

/*!
* @brief シーン側から管理者へシーン変更をコールバックするためのリスナーインタフエース
*/
class IOnSceneChangedListener {

public:

	IOnSceneChangedListener() {}
	virtual ~IOnSceneChangedListener() {}
	virtual void OnSceneChanged(const Define::Scene scene, const Parameter & paramter, const bool is_pop_scene, const bool is_clear_stack) = 0;
};