//----- インクルード部 -----
#include "Scene.h"
#include "title.h"
#include "Game.h"
#include "Select.h"

//----- グローバル変数 -----
static EScene g_eScene = SCENE_NONE;

//------------------------------------------------------------------------------------
//
//				初期化
//
//------------------------------------------------------------------------------------
HRESULT InitScene() {
	HRESULT hr = S_OK;

	SetScene(SCENE_TITLE);	// 最初はタイトル画面

	return hr;
}


//------------------------------------------------------------------------------------
//
//				終了
//
//------------------------------------------------------------------------------------
void UninitScene() {
	SetScene(SCENE_NONE);	// 現在の画面を終了
}

//------------------------------------------------------------------------------------
//
//				更新
//
//------------------------------------------------------------------------------------
void UpdateScene() {
	switch (g_eScene) {
	case SCENE_TITLE:	// タイトル画面
		UpdateTitle();
		break;
	case SCENE_MODE:	// モード選択
		UpdateSelect();
		break;
	case SCENE_GAME:	// ゲーム画面
		UpdateGame();
		break;
	default:
		break;
	}
}

//------------------------------------------------------------------------------------
//
//				描画
//
//------------------------------------------------------------------------------------
void DrawScene() {
	switch (g_eScene) {
	case SCENE_TITLE:	// タイトル画面
		DrawTitle();
		break;
	case SCENE_MODE:	// モード選択
		DrawSelect();
		break;
	case SCENE_GAME:	// ゲーム画面
		DrawGame();
		break;
	default:
		break;
	}

}


//------------------------------------------------------------------------------------
//
//				切り替え
//
//------------------------------------------------------------------------------------
void SetScene(EScene eScene) {
	// 現在の画面を終了
	switch (g_eScene) {
	case SCENE_TITLE:		// タイトル画面
		UninitTitle();
		break;
	case SCENE_MODE:	// モード選択
		UninitSelect();
		break;
	case SCENE_GAME:		// ゲーム画面
		UninitGame();
		break;
	default:
		break;

	}
	// 画面を入れ替え
	g_eScene = eScene;
	// 次の画面を初期化
	switch (g_eScene) {
	case SCENE_TITLE:		// タイトル画面
		InitTitle();
		break;
	case SCENE_MODE:	// モード選択
		InitSelect();
		break;
	case SCENE_GAME:		// ゲーム画面
		InitGame();
		break;
	default:
		break;
	}
}

//------------------------------------------------------------------------------------
//
//				シーン番号取得
//
//------------------------------------------------------------------------------------
int GetScene() {
	return g_eScene;
}
