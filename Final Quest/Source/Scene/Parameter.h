#pragma once
#include <map>

/*!
* @brief �V�[���J�ڎ��ɑJ�ڐ�̃V�[���֓n���p�����[�^
*/
class Parameter {

public:

	Parameter() {};
	virtual ~Parameter() {};
	void Set(const char * key, void * value);
	void * Get(const char * key) const;

private:

	std::map<const char*, void*> parameter_;	// �p�����[�^�Ǘ��p�}�b�v
};