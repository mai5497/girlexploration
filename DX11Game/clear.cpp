// 背景描画
#include "Scene.h"
#include "clear.h"
#include "polygon.h"
#include "Texture.h"


// マクロ定義
#define PATH_CLEARTEXTURE	(L"data/texture/logo002.png")
#define CLEAR_POS_X			(0.0f)
#define CLEAR_POS_Y			(0.0f)
#define CLEAR_WIDTH			(1200.0f / 2)
#define CLEAR_HEIGHT		(180.0f / 2)
#define CLEAR_CNT			(600)


//グローバル変数宣言
static ID3D11ShaderResourceView* g_pTexture;
float g_posTexCoordClear;
float g_nTimer;

//===================
//
//	初期化
//
//===================
HRESULT	InitClear() {
	HRESULT hr = S_OK;
	ID3D11Device* pDevice = GetDevice();

	g_posTexCoordClear = 0.0f;
	g_nTimer = CLEAR_CNT;

	hr = CreateTextureFromFile(pDevice, PATH_CLEARTEXTURE, &g_pTexture);

	return hr;
}

//===================
//
//	終了処理
//
//===================
void UninitClear() {
	// 背景テクスチャ開放
	SAFE_RELEASE(g_pTexture);
}

//===================
//
//	更新
//
//===================
void	UpdateClear() {
	g_nTimer--;
	if (g_nTimer < 0) {
		SetScene(SCENE_MODE);
	}
}

//===================
//
//	描画
//
//===================
void DrawClear() {
	ID3D11DeviceContext* pDC = GetDeviceContext();

	SetPolygonPos(0.0f, 0.0f);
	SetPolygonSize(SCREEN_WIDTH, SCREEN_HEIGHT);
	SetPolygonUV(0.0f, 0.0f);
	SetPolygonFrameSize(1.0f, 1.0f);
	SetPolygonTexture(nullptr);
	SetPolygonColor(1.0f, 1.0f, 1.0f);
	SetPolygonAlpha(0.5f);
	DrawPolygon(GetDeviceContext());

	SetPolygonSize(CLEAR_WIDTH, CLEAR_HEIGHT);
	SetPolygonPos(CLEAR_POS_X, CLEAR_POS_Y);
	SetPolygonUV(g_posTexCoordClear, 0.0f);
	SetPolygonAlpha(1.0f);
	SetPolygonTexture(g_pTexture);
	DrawPolygon(pDC);

	SetPolygonUV(0.0f, 0.0f);
	SetPolygonAlpha(1.0f);
}

