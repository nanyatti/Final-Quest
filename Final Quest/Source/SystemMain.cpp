#include <DxLib.h>
#include "SystemMain.h"
#include "Looper.h"
#include "Tool/Error.h"

/*!
* @brief DX���C�u������Q�[���̏�������
*/
bool SystemMain::Initialize() const {

	// �E�B���h�E���[�h�ŋN��
	if (ChangeWindowMode(true) != DX_CHANGESCREEN_OK) {
		SHOW_ERROR("�E�B���h�E���[�h�̐ݒ�");
		return false;
	}

	// �E�B���h�E�T�C�Y
	int num_color_bit = 32;
	if (SetGraphMode(Define::WINDOW_WIDTH, Define::WINDOW_HEIGHT, num_color_bit) != DX_CHANGESCREEN_OK) {
		SHOW_ERROR("�E�B���h�E�T�C�Y�̐ݒ�");
		return false;
	}

	// ���������𖳌���
	if (SetWaitVSyncFlag(false) == -1) {
		SHOW_ERROR("���������̐ݒ�");
		return false;
	}

	// ��A�N�e�B�u���̓����L����
	if (SetAlwaysRunFlag(true) == -1) {
		SHOW_ERROR("��A�N�e�B�u���̓���ݒ�");
		return false;
	}

	// DX���C�u����������
	if (DxLib_Init() == -1) {
		SHOW_ERROR("DX���C�u�����̏�����");
		return false;
	}

	// �t���[���o�b�t�@�ւ̕`����_�u���o�b�t�@�����O�ōs��
	if (SetDrawScreen(DX_SCREEN_BACK) == -1) {
		SHOW_ERROR("�t���[���o�b�t�@�ւ̕`��ݒ�");
		return false;
	}

	return true;
}

/*!
* @brief DX���C�u������Q�[���̏I������
*/
void SystemMain::Finalize() const {

	DxLib_End();
}

/*!
* @brief ���C������
*/
void SystemMain::Main() const {

	Looper looper;

	// ���C�����[�v
	while (true) {

		// �E�B���h�E���b�Z�[�W�����E�I������
		if (ProcessMessage()) {
			break;
		}

		// ��ʃN���A
		if (ClearDrawScreen()) {
			SHOW_ERROR("��ʃN���A");
			break;
		}

		// �X�V
		if (!looper.Update()) {
			break;
		}

		// �t���[���o�b�t�@�̍X�V
		if (ScreenFlip()) {
			SHOW_ERROR("�t���[���o�b�t�@�̍X�V");
			break;
		}
	}
}
