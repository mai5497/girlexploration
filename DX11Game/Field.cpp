//************************************************************************************
// 
// 足場管理[Field.cpp]
// 編集者：伊地田真衣
// 未使用なきする
//************************************************************************************
//-------------------- インクルード部 --------------------
#include "Field.h"
#include "polygon.h"
#include "Texture.h"

//-------------------- 定数定義 --------------------
#define PATH_BGTEXTURE	L"data/texture/kabe.png"
#define KABE_POS_X		0.0f
#define KABE_POS_Y		0.0f
#define KABE_WIDTH		100
#define KABE_HEIGHT		100

//-------------------- 構造体定義 --------------------
struct Field{
	XMFLOAT2 fieldPos;
};

//-------------------- グローバル変数 --------------------
Field g_field[3];
static ID3D11ShaderResourceView *g_pTexture;


//====================================================================================
//
//				初期化
//
//====================================================================================
HRESULT InitField() {
	HRESULT hr = S_OK;
	ID3D11Device *pDevice = GetDevice();

	hr = CreateTextureFromFile(pDevice, PATH_BGTEXTURE, &g_pTexture);
	g_field[0].fieldPos.x = 100.0f;
	g_field[0].fieldPos.y = 100.0f;

	g_field[1].fieldPos.x = 200.0f;
	g_field[1].fieldPos.y = 200.0f;

	g_field[2].fieldPos.x = 300.0f;
	g_field[2].fieldPos.y = 300.0f;

	

	return hr;

}

//====================================================================================
//
//				終了
//
//====================================================================================
void UninitField() {
	// テクスチャ開放
	SAFE_RELEASE(g_pTexture);

}

//====================================================================================
//
//				更新
//
//====================================================================================
void UpdateField() {

}

//====================================================================================
//
//				描画
//
//====================================================================================
void DrawField() {
	ID3D11DeviceContext *pDC = GetDeviceContext();

	SetPolygonSize(KABE_WIDTH, KABE_HEIGHT);
	for (int i = 0; i < 1; i++) {
		SetPolygonPos(g_field[i].fieldPos.x, g_field[i].fieldPos.y);
		SetPolygonTexture(g_pTexture);
		DrawPolygon(pDC);
	}
}


//====================================================================================
//
//				追加
//
//====================================================================================
void AddFieldPos(float add) {
	for (int i = 0; i < 1; i++) {
		g_field[i].fieldPos.x += add;
	}
}

