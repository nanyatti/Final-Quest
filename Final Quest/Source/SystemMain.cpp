#include <DxLib.h>
#include "SystemMain.h"
#include "Looper.h"
#include "Tool/Error.h"

/*!
* @brief DXライブラリやゲームの初期処理
*/
bool SystemMain::Initialize() const {

	// ウィンドウモードで起動
	if (ChangeWindowMode(true) != DX_CHANGESCREEN_OK) {
		SHOW_ERROR("ウィンドウモードの設定");
		return false;
	}

	// ウィンドウサイズ
	int num_color_bit = 32;
	if (SetGraphMode(Define::WINDOW_WIDTH, Define::WINDOW_HEIGHT, num_color_bit) != DX_CHANGESCREEN_OK) {
		SHOW_ERROR("ウィンドウサイズの設定");
		return false;
	}

	// 垂直同期を無効化
	if (SetWaitVSyncFlag(false) == -1) {
		SHOW_ERROR("垂直同期の設定");
		return false;
	}

	// 非アクティブ時の動作を有効化
	if (SetAlwaysRunFlag(true) == -1) {
		SHOW_ERROR("非アクティブ時の動作設定");
		return false;
	}

	// DXライブラリ初期化
	if (DxLib_Init() == -1) {
		SHOW_ERROR("DXライブラリの初期化");
		return false;
	}

	// フレームバッファへの描画をダブルバッファリングで行う
	if (SetDrawScreen(DX_SCREEN_BACK) == -1) {
		SHOW_ERROR("フレームバッファへの描画設定");
		return false;
	}

	return true;
}

/*!
* @brief DXライブラリやゲームの終了処理
*/
void SystemMain::Finalize() const {

	DxLib_End();
}

/*!
* @brief メイン処理
*/
void SystemMain::Main() const {

	Looper looper;

	// メインループ
	while (true) {

		// ウィンドウメッセージ処理・終了判定
		if (ProcessMessage()) {
			break;
		}

		// 画面クリア
		if (ClearDrawScreen()) {
			SHOW_ERROR("画面クリア");
			break;
		}

		// 更新
		if (!looper.Update()) {
			break;
		}

		// フレームバッファの更新
		if (ScreenFlip()) {
			SHOW_ERROR("フレームバッファの更新");
			break;
		}
	}
}
