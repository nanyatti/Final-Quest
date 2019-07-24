#pragma once
#include <map>

/*!
* @brief シーン遷移時に遷移先のシーンへ渡すパラメータ
*/
class Parameter {

public:

	Parameter() {};
	virtual ~Parameter() {};
	void Set(const char * key, void * value);
	void * Get(const char * key) const;

private:

	std::map<const char*, void*> parameter_;	// パラメータ管理用マップ
};