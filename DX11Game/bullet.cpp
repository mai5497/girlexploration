//************************************************************************************
// 
// 弾[main.cpp]
// 編集者：伊地田真衣
// 未使用かな
//************************************************************************************
//-------------------- インクルード部 --------------------
#include "bullet.h"
#include "Texture.h"
#include "polygon.h"


//-------------------- 定数定義 --------------------
#define PATH_BULLETTEXTURE L"data/texture/player000.png"
#define BULLET_WIDTH 64
#define BULLET_HEIGHT 64
#define BULLET_SPEED 12.0f
#define BULLET_COUNT_X 4
#define BULLET_COUNT_Y 4
#define BULLET_FRAME 3
#define MAX_BULLET 100

//-------------------- 構造体定義 --------------------
struct BULLET {
	XMFLOAT2 vPos; // 位置
	XMFLOAT2 vVel; // 速度
};

//-------------------- グローバル変数 --------------------
static ID3D11ShaderResourceView* g_pTexture;
static BULLET g_bullet[MAX_BULLET];// 弾情報
static int g_nBullet;// 使用中弾数


//====================================================================================
//
//				初期化
//
//====================================================================================
HRESULT InitBullet()
{
	HRESULT hr = S_OK;
	ID3D11Device* pDevice = GetDevice();
	// テクスチャ読込
	hr = CreateTextureFromFile(
		pDevice,
		PATH_BULLETTEXTURE,
		&g_pTexture);
	if (FAILED(hr)) {
		return hr;
	}
	// 初期化
	g_nBullet = 0;
	return hr;
}


//====================================================================================
//
//				終了処理
//
//====================================================================================
void UninitBullet()
{
	// テクスチャ解放
	SAFE_RELEASE(g_pTexture);
}


//====================================================================================
//
//				更新
//
//====================================================================================
void UpdateBullet()
{
	for (int i = g_nBullet - 1; i >= 0; --i) {
		BULLET* pBullet = &g_bullet[i];
		// 移動
		pBullet->vPos.x += pBullet->vVel.x;
		pBullet->vPos.y += pBullet->vVel.y;
		// 画面外に出たら消去
		if (pBullet->vPos.x <
			(SCREEN_WIDTH + BULLET_WIDTH) * -0.5f ||
			pBullet->vPos.x >
			(SCREEN_WIDTH + BULLET_WIDTH) * 0.5f ||
			pBullet->vPos.y <
			(SCREEN_HEIGHT + BULLET_HEIGHT) * -0.5f ||
			pBullet->vPos.y >
			(SCREEN_HEIGHT + BULLET_HEIGHT) * 0.5f) {
			--g_nBullet;
			*pBullet = g_bullet[g_nBullet];
			continue;
		} // TODO: 当たり判定
	}
}

//====================================================================================
//
//				描画
//
//====================================================================================
void DrawBullet()
{
	ID3D11DeviceContext* pDC = GetDeviceContext();
	SetPolygonSize(BULLET_WIDTH, BULLET_HEIGHT);
	SetPolygonTexture(g_pTexture);
	SetPolygonFrameSize(1.0f / BULLET_COUNT_X,
		1.0f / BULLET_COUNT_Y);
	SetPolygonUV((BULLET_FRAME % BULLET_COUNT_X) /
		(float)BULLET_COUNT_X,
		(BULLET_FRAME / BULLET_COUNT_X) /
		(float)BULLET_COUNT_Y);
	BULLET* pBullet = g_bullet;
	for (int i = 0; i < g_nBullet; ++i, ++pBullet) {
		SetPolygonPos(pBullet->vPos.x,pBullet->vPos.y);
		DrawPolygon(pDC);
	} SetPolygonUV(0.0f, 0.0f);
	SetPolygonFrameSize(1.0f, 1.0f);
}

//====================================================================================
//
//				発射
// 
//====================================================================================
int FireBullet(XMFLOAT2 vPos, int nDir)
{
	if (g_nBullet < MAX_BULLET) {
		BULLET* pBullet = &g_bullet[g_nBullet];
		pBullet->vPos = vPos;
		switch (nDir) {
		case 0://下
			pBullet->vVel.x = 0.0f;
			pBullet->vVel.y = -BULLET_SPEED;
			break;
		case 1://左
			pBullet->vVel.x = -BULLET_SPEED;
			pBullet->vVel.y = 0.0f;
			break;
		case 2://右
			pBullet->vVel.x = BULLET_SPEED;
			pBullet->vVel.y = 0.0f;
			break;
		case 3://上
			pBullet->vVel.x = 0.0f;
			pBullet->vVel.y = BULLET_SPEED;
			break;
		} 
		++g_nBullet;
		return g_nBullet;
	} return 0;
}