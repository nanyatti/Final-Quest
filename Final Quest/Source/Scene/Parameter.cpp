#include "Parameter.h"

/*!
* @brief キーと対応する値をmapにセット
* @param key	キー
* @param value	格納する値
*/
void Parameter::Set(const char * key, void * value) {

	parameter_[key] = value;
}

/*!
* @brief キーをインデックスの代わりとして値を取得
* @param key	キー
*/
void * Parameter::Get(const char * key) const {

	// キー検索
	std::map<const char*, void*>::const_iterator iterator = parameter_.find(key);

	if (iterator != parameter_.end()) {
		return iterator->second;
	}
	else {
		return nullptr;
	}
}
