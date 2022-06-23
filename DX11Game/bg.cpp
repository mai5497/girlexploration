// 背景描画
#include "bg.h"
#include "polygon.h"
#include "Texture.h"


// マクロ定義
#define PATH_BGTEXTURE	L"data/texture/bg000.png"
#define BG_POS_X		0.0f
#define BG_POS_Y		0.0f
#define BG_WIDTH		SCREEN_WIDTH
#define BG_HEIGHT		SCREEN_HEIGHT

//グローバル変数宣言
static ID3D11ShaderResourceView *g_pTexture;
float g_posTexCoordBG;

//===================
//
//	初期化
//
//===================
HRESULT	InitBG() {
	HRESULT hr = S_OK;
	ID3D11Device *pDevice = GetDevice();

	g_posTexCoordBG = 0.0f;

	hr = CreateTextureFromFile(pDevice, PATH_BGTEXTURE, &g_pTexture);

	return hr;
}

//===================
//
//	終了処理
//
//===================
void UninitBG() {
	// 背景テクスチャ開放
	SAFE_RELEASE(g_pTexture);
}

//===================
//
//	更新
//
//===================
void	UpdateBG() {
	//なにもしない：）
}

//===================
//
//	描画
//
//===================
void DrawBG() {
	ID3D11DeviceContext *pDC = GetDeviceContext();

	SetPolygonSize(BG_WIDTH, BG_HEIGHT);
	SetPolygonPos(BG_POS_X, BG_POS_Y);
	SetPolygonUV(g_posTexCoordBG, 0.0f);
	SetPolygonTexture(g_pTexture);
	DrawPolygon(pDC);

	SetPolygonUV(0.0f, 0.0f);
}

void AddBGTexCoord(float add) {
	g_posTexCoordBG += add;
}