#include "Parameter.h"

/*!
* @brief �L�[�ƑΉ�����l��map�ɃZ�b�g
* @param key	�L�[
* @param value	�i�[����l
*/
void Parameter::Set(const char * key, void * value) {

	parameter_[key] = value;
}

/*!
* @brief �L�[���C���f�b�N�X�̑���Ƃ��Ēl���擾
* @param key	�L�[
*/
void * Parameter::Get(const char * key) const {

	// �L�[����
	std::map<const char*, void*>::const_iterator iterator = parameter_.find(key);

	if (iterator != parameter_.end()) {
		return iterator->second;
	}
	else {
		return nullptr;
	}
}
