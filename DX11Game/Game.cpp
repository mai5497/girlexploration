//************************************************************************************
// 
// ゲーム処理[Game.cpp]
// 編集者：伊地田真衣
// 
//************************************************************************************
//-------------------- インクルード部 --------------------
#include "Scene.h"
#include "Game.h"
#include "polygon.h"
#include "Texture.h"
#include "input.h"
#include "bg.h"
#include "player.h"
#include "Map.h"
//#include "wind.h"
#include "timer.h"
#include "clear.h"



//====================================================================================
//
//	初期化
//
//====================================================================================
HRESULT	InitGame() {
	HRESULT hr = S_OK;

	// 背景初期化
	hr = InitBG();
	if (FAILED(hr)) {
		MessageBox(GetMainWnd(), _T("背景初期化失敗"), NULL, MB_OK);
		return hr;
	}

	// プレイヤー初期化
	hr = InitPlayer();
	if (FAILED(hr)) {
		MessageBox(GetMainWnd(), _T("プレイヤー初期化失敗"), NULL, MB_OK);
		return hr;
	}

	// マップチップ初期化
	hr = InitMap();
	if (FAILED(hr)) {
		MessageBox(GetMainWnd(), _T("マップチップ初期化失敗"), NULL, MB_OK);
		return hr;
	}

	// 風初期化
	//hr = InitWind();
	//if (FAILED(hr)) {
	//	MessageBox(GetMainWnd(), _T("風初期化失敗"), NULL, MB_OK);
	//	return hr;
	//}

	// タイマー初期化
	hr = InitTimer();
	if (FAILED(hr)) {
		MessageBox(GetMainWnd(), _T("タイマー初期化失敗"), NULL, MB_OK);
		return hr;
	}

	// クリア初期化
	hr = InitClear();
	if (FAILED(hr)) {
		MessageBox(GetMainWnd(), _T("クリア初期化失敗"), NULL, MB_OK);
		return hr;
	}

	return hr;
}

//====================================================================================
//
//	終了処理
//
//====================================================================================
void UninitGame() {
	// 背景終了処理
	UninitBG();

	// マップチップ終了処理
	UninitMap();

	// プレイヤー終了処理
	UninitPlayer();

	// 風の終了処理
	//UninitWind();

	// タイマー終了処理
	UninitTimer();

	// クリア終了処理
	UninitClear();

}

//====================================================================================
//
//	更新
//
//====================================================================================
void	UpdateGame() {
	// 背景更新
	UpdateBG();

	// マップチップ描画更新
	UpdateMap();

	// 風更新
	//UpdateWind();

	// プレイヤー更新
	UpdatePlayer();

	// タイマー更新処理
	UpdateTimer();

}

//====================================================================================
//
//	描画
//
//====================================================================================
void DrawGame() {

	// 背景描画
	DrawBG();

	// マップチップ描画
	DrawMap();

	// 風描画
	//DrawWind();

	// タイマー描画
	DrawTimer();

	// プレイヤー描画
	DrawPlayer();
}