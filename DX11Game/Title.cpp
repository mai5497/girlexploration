//************************************************************************************
// 
// タイトル[Title.cpp]
// 編集者：伊地田真衣
// 
//************************************************************************************
//-------------------- インクルード部 --------------------
#include "Scene.h"
#include "Title.h"
#include "polygon.h"
#include "Texture.h"
#include "input.h"


//-------------------- 定数定義部 --------------------
#define TITLE_POS_X			(0.0f)
#define TITLE_POS_Y			(0.0f)
#define TITLE_WIDTH			(SCREEN_WIDTH)
#define TITLE_HEIGHT		(SCREEN_HEIGHT)
#define TITLE_ROGO_POS_X	(0.0f)
#define TITLE_ROGO_POS_Y	(0.0f)
#define TITLE_ROGO_WIDTH	(1707.0f / 3)
#define TITLE_ROGO_HEIGHT	(960.0f / 3)

enum TEX {
	BG = 0,
	TITLEROGO,

	MAX_TEXTURE
};

//-------------------- グローバル変数 --------------------
static LPCWSTR g_pszTexFName[MAX_TEXTURE] = {
	L"data/texture/bg001.jpeg",
	L"data/texture/logo001.png",
};

static ID3D11ShaderResourceView* g_pTexture[MAX_TEXTURE];

//====================================================================================
//
//				初期化
//
//====================================================================================
HRESULT	InitTitle() {
	HRESULT hr = S_OK;
	ID3D11Device* pDevice = GetDevice();


	for (int i = 0; i < MAX_TEXTURE; i++) {
		hr = CreateTextureFromFile(pDevice, g_pszTexFName[i], &g_pTexture[i]);
		if (FAILED(hr)) {
			return hr;
		}
	}

	return hr;
}

//====================================================================================
//
//				終了
//
//====================================================================================
void UninitTitle() {
	// テクスチャ開放
	for (int i = 0; i < MAX_TEXTURE; i++) {
		SAFE_RELEASE(g_pTexture[i]);
	}
}

//====================================================================================
//
//				更新
//
//====================================================================================
void	UpdateTitle() {
	if (GetKeyRelease(VK_RETURN)) {	// エンターキーが押されたら
		//　シーン遷移
		SetScene(SCENE_MODE);
		return;
	}
}

//====================================================================================
//
//				描画
//
//====================================================================================
void DrawTitle() {
	ID3D11DeviceContext* pDC = GetDeviceContext();

	SetPolygonSize(TITLE_WIDTH, TITLE_HEIGHT);
	SetPolygonPos(TITLE_POS_X, TITLE_POS_Y);
	SetPolygonTexture(g_pTexture[BG]);
	DrawPolygon(pDC);

	SetPolygonSize(TITLE_ROGO_WIDTH, TITLE_ROGO_HEIGHT);
	SetPolygonPos(TITLE_ROGO_POS_X, TITLE_ROGO_POS_Y);
	SetPolygonTexture(g_pTexture[TITLEROGO]);
	DrawPolygon(pDC);
}