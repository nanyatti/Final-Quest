#define _GLOBAL_INSTANCE_ 
#include "../../include/GV.h"

void ini(){//キャラクタの初期化
	ch[0].x		=WIDE*10;
	ch[0].y		=WIDE*10;
	ch[0].walk_cnt	=0;
	ch[0].walk_flag	=0;
	ch[0].muki		=3;//キャラのむいている向きを下にセット
	ch[0].img_flag	=1;//描画するかどうかのフラグ
	ch[0].hp	=1352;
	ch[0].hp_max=1452;
	ch[0].mp	=97;
	ch[0].mp_max=102;
	ch[0].tp=0;
	ch[0].magic=20;

	ch[0].power=20;		//攻撃力
	ch[0].def=20;		//防御力
	ch[0].strong=20;	//力
	ch[0].weapon=20;	//武器
	ch[0].equip=20;		//装備
	ch[0].lv=10;		//レベル

	mapini_flag=1;		//マップを初期化するかどうかのフラグ
	func_states=0;		//main関数でどの関数に処理を渡すかを判断する変数
	return;
}

int WINAPI WinMain( HINSTANCE hInstance, HINSTANCE hPrevInstance,LPSTR lpCmdLine, int nCmdShow ){
	
	// 初期化処理
	if (SetOutApplicationLogValidFlag(FALSE) ||
		ChangeWindowMode(TRUE) != DX_CHANGESCREEN_OK ||
		DxLib_Init() ||
		SetWindowSizeExtendRate(1.0)) {
		return -1;
	}
	//if( SetOutApplicationLogValidFlag(FALSE) || DxLib_Init()) return -1;//フルスクリーンモード

	SetDrawScreen( DX_SCREEN_BACK );

	// リソースの読込
	// 色情報　文字？
	// 画像・音楽
	// ローディング
	// 素材編集
	dat_load();


	while(!ProcessMessage() && !ClearDrawScreen() && !GetHitKeyStateAll( key ) && key[KEY_INPUT_ESCAPE]==0){

		// 入力状態
		input_key();


		// 状態遷移
		switch(func_states){

			// 初期化
			case -1://初期化処理

				// キャラの初期化
				// マップ初期化フラグ
				// 状態更新
				ini();
				break;



			// ワールドマップステート
			case 0://マップ画面

				// マップの初期化
				// 移動できるか
				// NPCの配置
				if(mapini_flag==1)
					map_ini();//マップの初期化

				// 更新処理

				// キャラ位置の更新
				char_calc();//キャラクタの描画以外の計算

				// 入力によるキャラ制御
				// キャラ移動によるマップ制御
				// マップの初期化
				// 1マス移動
				// 移動時ランダムエンカウント
				char_graph_calc();//キャラクタの描画の計算

				// NPCの移動制御
				mchar_graph_calc();//町のキャラの描画の計算

				// 描画処理
				map_graph();//マップの描画
				char_graph();//キャラクタの描画

				
				if(stbt_capch_flag==1)//もし戦闘に入る瞬間なら
					stbt_capch();//画面を16分割してキャプチャ
				break;


			// バトルステート
			case 1://バトル画面
			case 2:
			case 3:

				// 状態に応じてオーピニング・戦闘・勝利演出などを行う
				battle_calc();//バトルメインへ
				break;


			// 不明な状態
			default:
				exit (98);
				break;
		}

		music_sound();	//音楽制御
		wait_calc();	//FPS制御（FPSを60に保つための関数）
		fps_calc();		//現在のFPSを計算
		fps_graph();	//FPSを描画

		count++;		//countは常に1ずつ増え続け、ここ以外で変更されることの無い変数。動的に変化する何かに色々使える。
		ScreenFlip();
	}

	DxLib_End();
	return 0;
}