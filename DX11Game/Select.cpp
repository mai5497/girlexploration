//************************************************************************************
// 
// 選択画面[Select.cpp]
// 編集者：伊地田真衣
// 
//************************************************************************************
//-------------------- インクルード部 --------------------
#include "Scene.h"
#include "Select.h"
#include "polygon.h"
#include "Texture.h"
#include "input.h"


//-------------------- 定数マクロ定義 --------------------
#define PATH_SELECTTEXTURE	L"data/texture/bg000.png"
#define SELECT_POS_X			(0.0f)
#define SELECT_POS_Y			(0.0f)
#define SELECT_WIDTH			(SCREEN_WIDTH)
#define SELECT_HEIGHT		(SCREEN_HEIGHT)
//#define SELECT_ROGO_POS_X
//#define SELECT_ROGO_POS_Y
//#define SELECT_ROGO_WIDTH
//#define SELECT_ROGO_HEIGHT


//-------------------- グローバル変数定義 --------------------
static ID3D11ShaderResourceView* g_pTexture;
float g_posTexCoordSelect;
static int g_nStageNum;

//====================================================================================
//
//	初期化
//
//====================================================================================
HRESULT	InitSelect() {
	HRESULT hr = S_OK;
	ID3D11Device* pDevice = GetDevice();

	g_posTexCoordSelect = 0.0f;
	g_nStageNum = STAGE1;

	hr = CreateTextureFromFile(pDevice, PATH_SELECTTEXTURE, &g_pTexture);

	return hr;
}

//====================================================================================
//
//	終了処理
//
//====================================================================================
void UninitSelect() {
	// 背景テクスチャ開放
	SAFE_RELEASE(g_pTexture);
}

//====================================================================================
//
//	更新
//
//====================================================================================
void UpdateSelect() {
	if (GetKeyRelease(VK_RETURN)) {	// エンターキーが押されたら
		SetScene(SCENE_GAME);
	}
}

//====================================================================================
//
//	描画
//
//====================================================================================
void DrawSelect() {
	ID3D11DeviceContext* pDC = GetDeviceContext();

	SetPolygonSize(SELECT_WIDTH, SELECT_HEIGHT);
	SetPolygonPos(SELECT_POS_X, SELECT_POS_Y);
	SetPolygonUV(g_posTexCoordSelect, 0.0f);
	SetPolygonTexture(g_pTexture);
	DrawPolygon(pDC);

	SetPolygonUV(0.0f, 0.0f);
}

//====================================================================================
//
//				ステージ番号取得
//
//====================================================================================
int	GetStageNum() {
	return g_nStageNum;
}