#include "AbstructScene.h"

/*!
* @brief �V�[������V�[���Ǘ��҂ɐ����E�j�����R�[���o�b�N���邽�߂̃��X�i�[�C���^�t�F�[�X
* @param sc_listener	�V�[���ύX�̃��X�i�[�E�V�[���Ǘ���
* @param parameter		�O�̃V�[����������p���p�����[�^
*/
AbstructScene::AbstructScene(IOnSceneChangedListener * sc_listener, const Parameter & parameter) {

	scene_change_listener_ = sc_listener;
}
