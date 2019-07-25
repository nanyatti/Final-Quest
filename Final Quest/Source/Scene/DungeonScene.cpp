#include <DxLib.h>
#include "DungeonScene.h"
#include "IOnSceneChangedListener.h"
#include "Parameter.h"
#include "../ActorObject/Character.h"
#include "../ActorObject/Monster.h"
#include "../Input/Keyboard.h"


DungeonScene::DungeonScene(IOnSceneChangedListener * sc_listener, const Parameter & parameter) :
	AbstructScene(sc_listener, parameter) {

	state_ = State::PREPARATION;
	player_ = new Character;

	LoadDivGraph("dat/img/mapchip/0/0.png", 4, 4, 1, 32, 32, mapchip_img[0]);
}

DungeonScene::~DungeonScene() {

	delete player_;
	delete monster_;
}

/*!
* @brief 更新処理
*/
void DungeonScene::Update() {


	switch (state_) {

		// 初期化
	case State::PREPARATION:

		monster_ = new Monster;
		state_ = State::MAP_CREATION;
		break;


	case State::MAP_CREATION: {

		// マップの初期化
		CreateMap();

		state_ = State::ADVENTURE;
		break;
	}


	case State::ADVENTURE:


		// キャラ位置の更新
		player_->Update();

		if (player_->IsFinishWalk()) {
			if (player_->IsEncountEnemy()) {
				state_ = State::BATTLE;
			}
		}

		break;


	case State::BATTLE: {

		// バトルシーンの追加
		Parameter parameter;
		parameter.Set("player", static_cast<void*>(player_));
		parameter.Set("monster", static_cast<void*>(monster_));
		bool is_pop_scene = false;
		bool is_clear_stack = false;
		scene_change_listener_->OnSceneChanged(Define::Scene::BATTLE, parameter, is_pop_scene, is_clear_stack);
		state_ = State::ADVENTURE;
		break;
	}

	default:
		break;
	}
}

/*!
* @brief 描画処理
*/
void DungeonScene::Draw() {

	switch (state_) {
	case State::ADVENTURE:

		DrawMap();//マップの描画
		player_->Draw();
		break;
	default:
		break;
	}

}


/*!
* @brief マップの作成
*/
void DungeonScene::CreateMap() {

	for (int x = 0; x < Define::WINDOW_WIDTH/ Define::WIDE; x++) {//横の20区間
		for (int y = 0; y < Define::WINDOW_WIDTH / Define::WIDE; y++) {//縦の15区間
			if (map[2][y][x] > 1)//通れない場所なら
				mapd[y][x] = 1;			//通れないフラグを立てる
			else
				mapd[y][x] = 0;			//通れるフラグを立てる
		}
	}

	return;
}

/*!
* @brief マップの描画
*/
void DungeonScene::DrawMap() {

	int i, j;


	for (i = 0; i < Define::WINDOW_WIDTH / Define::WIDE; i++) {//横のウィンドウサイズ/１区間のサイズ＝横の区間個数
		for (j = 0; j < Define::WINDOW_HEIGHT / Define::WIDE; j++) {//縦のウィンドウサイズ/１区間のサイズ＝縦の区間個数
			DrawGraph(i * Define::WIDE, j * Define::WIDE, mapchip_img[0][0], TRUE);//いったん全ての区間に芝生を描画
			if (map[2][j][i] != 0)//芝生の上に画像を表示する区間の時
				DrawGraph(i * Define::WIDE, j * Define::WIDE, mapchip_img[0][map[0][j][i]], TRUE);//その画像を描画
		}
	}
	return;
}