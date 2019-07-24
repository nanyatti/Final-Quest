#include "AbstructScene.h"

/*!
* @brief シーンからシーン管理者に生成・破棄をコールバックするためのリスナーインタフェース
* @param sc_listener	シーン変更のリスナー・シーン管理者
* @param parameter		前のシーンから引き継ぐパラメータ
*/
AbstructScene::AbstructScene(IOnSceneChangedListener * sc_listener, const Parameter & parameter) {

	scene_change_listener_ = sc_listener;
}
