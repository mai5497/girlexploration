//************************************************************************************
// 
// タイマー処理[timer.cpp]
// 編集者：伊地田真衣
// 
//************************************************************************************
//-------------------- インクルード部 --------------------
#include "timer.h"
#include "number.h"
#include "Texture.h"
#include "polygon.h"
#include "debugproc.h"

//-------------------- 定数定義 --------------------
#define SEC_CHRCNT				(3)																	// 秒文字数
#define TIMER_POS_Y				(SCREEN_HEIGHT / 2 - NUMBER_SIZE_Y / 4)								// タイマー基準位置
#define TIMER_POS_X				(SCREEN_WIDTH / 2 - NUMBER_SIZE_X *  SEC_CHRCNT + 1)	

#define TIMERROGO_POS_X			(TIMER_POS_X - (SEC_CHRCNT - 1) * NUMBER_SIZE_X)					// タイマーロゴ位置
#define TIMERROGO_POS_Y			(TIMER_POS_Y - NUMBER_SIZE_Y * 0.5)		

#define SECNUM_POS_X			(TIMER_POS_X - NUMBER_SIZE_X - NUMBER_SIZE_X / 2)					// 秒数字表示基準位置
#define SECCHR_POS_X			(SECNUM_POS_X + SEC_CHRCNT * NUMBER_SIZE_X + NUMBER_SIZE_X / 2)		// 秒文字表示基準位置

#define BOX_SIZE_X				(240.0f)															// 表示枠サイズ
#define BOX_SIZE_Y				(108.0f)
#define BOX_POS_X				(SCREEN_WIDTH / 2 - BOX_SIZE_X / 2)									// 表示枠基準位置
#define BOX_POS_Y				(SCREEN_HEIGHT / 2 - BOX_SIZE_Y / 2)

#define TIMER_START				(18060)																// タイマーのスタート

enum TEXNUM {
	TEX_BOX = 0,
	TEX_TIMER,

	MAX_TEXTURE,
};

enum TIMERROGONUM {
	MIN = 10,
	SEC,
	TIMER,
};

//-------------------- グローバル変数定義 --------------------
static int g_nTimer;
static LPCWSTR g_pszTexFName[MAX_TEXTURE] = {
	L"data/texture/box000.png",
	L"data/texture/number000.png",
};
static ID3D11ShaderResourceView *g_pTexture[MAX_TEXTURE];

									
//====================================================================================
//
//				初期化
//
//====================================================================================
HRESULT InitTimer() {
	HRESULT hr = S_OK;
	ID3D11Device *pDevice = GetDevice();
	for (int i = 0; i < MAX_TEXTURE; i++) {
		hr = CreateTextureFromFile(pDevice, g_pszTexFName[i], &g_pTexture[i]);
		if (FAILED(hr)) {
			return hr;
		}
	}


	// 変数初期化
	g_nTimer = TIMER_START;

	return hr;
}


//====================================================================================
//
//				終了
//
//====================================================================================
void UninitTimer() {
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
void UpdateTimer() {
	// カウントダウン
	g_nTimer--;
}

//====================================================================================
//
//				描画
//
//====================================================================================
void DrawTimer() {
	int sec;
	ID3D11DeviceContext *pDC = GetDeviceContext();

	SetPolygonSize(BOX_SIZE_X, BOX_SIZE_Y);
	SetPolygonPos(BOX_POS_X, BOX_POS_Y);
	SetPolygonTexture(g_pTexture[TEX_BOX]);
	DrawPolygon(pDC);

	SetPolygonFrameSize(1.0f / NUMBER_COUNT_X, 1.0f / NUMBER_COUNT_Y);
	SetPolygonSize(NUMBER_SIZE_X, NUMBER_SIZE_Y);
	SetPolygonPos(TIMERROGO_POS_X, TIMERROGO_POS_Y);
	SetPolygonUV((TIMER % NUMBER_COUNT_X) / (float)NUMBER_COUNT_X,
				(TIMER / NUMBER_COUNT_X) / (float)NUMBER_COUNT_Y);
	SetPolygonTexture(g_pTexture[TEX_TIMER]);
	DrawPolygon(pDC);

	SetPolygonFrameSize(1.0f / NUMBER_COUNT_X, 1.0f / NUMBER_COUNT_Y);
	SetPolygonSize(NUMBER_SIZE_X, NUMBER_SIZE_Y);
	SetPolygonPos(SECCHR_POS_X, TIMERROGO_POS_Y);
	SetPolygonUV((SEC % NUMBER_COUNT_X) / (float)NUMBER_COUNT_X,
				(SEC / NUMBER_COUNT_X) / (float)NUMBER_COUNT_Y);
	SetPolygonTexture(g_pTexture[TEX_TIMER]);
	DrawPolygon(pDC);

	
	sec = g_nTimer / 60;

	DrawNumber(XMFLOAT2(SECNUM_POS_X, TIMER_POS_Y),(unsigned)sec, SEC_CHRCNT);
	
	// 元に戻す
	SetPolygonColor(1.0f,1.0f,1.0f);
	SetPolygonUV(0.0f, 0.0f);
	SetPolygonFrameSize(1.0f, 1.0f);
}


//====================================================================================
//
//				タイム取得
//
//====================================================================================
int GetTimer(){
	return g_nTimer / 60;
}


//====================================================================================
//
//				リセット
//
//====================================================================================
void resetTimer() {
	g_nTimer = 0;
}