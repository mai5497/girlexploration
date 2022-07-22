//************************************************************************************
// 
// マップチップ管理[map.cpp]
// 編集者：伊地田真衣
// 
//************************************************************************************
//-------------------- インクルード部 --------------------
#include "Map.h"
#include "polygon.h"
#include "Texture.h"
#include "debugproc.h"
#include "Select.h"


//-------------------- 定数定義 --------------------
#define BG_POS_X		(0.0f)
#define BG_POS_Y		(0.0f)

#define MAP_COUNT_X		(6)
#define MAP_HEIGHT		(12)
#define MAP_WIDTH		(20)

#define UI_COUNT_X		(5)
#define UI_WIDTH		(140.0f)
#define UI_HEIGHT		(140.0f)
#define UI_DIFFERE		(UI_WIDTH - BG_WIDTH)

#define STAR_COUNT_X	(2)
#define MAX_STAR		(3)
#define STAR_WIDTH		(50.0f)
#define STAR_HEIGHT		(50.0f)
#define STAR_DIFFER		(STAR_WIDTH - BG_WIDTH)
#define STAR_POS_X		(0.0f - SCREEN_WIDTH / 2 + STAR_WIDTH * MAX_STAR + STAR_WIDTH / 2 )
#define STAR_POS_Y		(SCREEN_HEIGHT / 2 - STAR_HEIGHT / 2)

#define WIND_COUNT		(2)	// 分割数

enum TEX {
	MAP = 0,
	UI,
	STAR,
	WIND,
	UI_GOAL,

	MAX_TEXTURE
};


struct ANIME_PAT {
	int nFrame;	// 表示枠ナンバー
	int nCount;	// 表示フレーム数

};

//-------------------- グローバル変数定義 --------------------
static LPCWSTR g_pszTexFName[MAX_TEXTURE] = {
	L"data/texture/mapchip000.png",
	L"data/texture/mapchip001.png",
	L"data/texture/mapchip002.png",
	L"data/texture/wind1.png",
	L"data/texture/UI.png",
};

static ID3D11ShaderResourceView *g_pTexture[MAX_TEXTURE];

XMFLOAT2 g_pos;
XMFLOAT2 UIpos[UI_COUNT_X] = { XMFLOAT2(-340.0f,-165.0f),XMFLOAT2(-192.0f,-117.0f), XMFLOAT2(300.0f,-117.0f), XMFLOAT2(160.0f,-117.0f) };
XMFLOAT2 g_goalpos;
float	 g_fAngle;				// ゴール角度
static int g_nStarCnt;
static int g_nStageNum;

int mapchip[MAX_STAGE][12][20] =
{
	{
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,},
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,},
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,},
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,},
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 5, 0, 0, 6, 0, 0,},
	{ 0, 0, 0, 0, 0, 0, 0, 5, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,},
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 3, 3, 4,},
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,},
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,},
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,11, 0, 0, 0, 5, 0,},
	{ 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,},
	{ 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,},
	},
	{
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2,3,3,4,},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,},
	{0,0,0,0,0,0,0,0,0,0,0,0,2,3,4,0,0,0,0,0,},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,5,0,0,0,},
	{0,0,0,0,0,0,0,0,5,0,0,0,0,0,0,2,3,4,0,0,},
	{0,0,0,0,0,0,0,2,3,4,0,0,0,0,0,0,0,0,0,0,},
	{0,0,0,0,5,0,0,0,0,0,0,0,2,3,4,0,0,0,0,0,},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,},
	{1,1,1,0,0,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,},
	},

};


//====================================================================================
//
//				初期化
//
//====================================================================================
HRESULT	InitMap() {
	HRESULT hr = S_OK;
	ID3D11Device *pDevice = GetDevice();

	g_pos.x = 0.0f;
	g_pos.y = 0.0f;
	g_goalpos.x = 380.0f;
	g_goalpos.y = 80.0f;
	g_nStarCnt = MAX_STAR;
	g_nStageNum = GetStageNum();

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
void	UninitMap() {
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
void	UpdateMap() {
	// ゴールの角度の変更
	g_fAngle += 1.0f;
	if (g_fAngle >= 180.0f) {
		g_fAngle -= 360;
	}
}

//====================================================================================
//
//				描画
//
//====================================================================================
void	DrawMap() {
	ID3D11DeviceContext *pDC = GetDeviceContext();


	for (int i = 0; i < MAP_HEIGHT; i++) {
		for (int j = 0; j < MAP_WIDTH; j++) {
			g_pos.x = (float)(j * BG_WIDTH - SCREEN_WIDTH / 2 + BG_WIDTH / 2);
			g_pos.y = -1.0f * (i * BG_HEIGHT - SCREEN_HEIGHT / 2 );
			if (mapchip[g_nStageNum][i][j] == 6) {
				// ゴールの描画
				SetPolygonSize(UI_WIDTH, UI_HEIGHT);
				SetPolygonFrameSize(1.0f / UI_COUNT_X, 1.0f);
				SetPolygonTexture(g_pTexture[UI]);
				SetPolygonPos(g_pos.x + UI_DIFFERE / 2, g_pos.y);
				SetPolygonUV((4 % UI_COUNT_X) / (float)UI_COUNT_X, 0.0f);
				SetPolygonAngle(g_fAngle);
				DrawPolygon(pDC);
				continue;
			}

			//--- UI描画 ---
			if (6 < mapchip[g_nStageNum][i][j] && mapchip[g_nStageNum][i][j] < 11) {

				//g_sizeMAP = MakeFloat2(UI_WIDTH, UI_HEIGHT);
				//g_sizeTexCoordMAP = MakeFloat2(1.0f / UI_COUNT_X, 1.0f);
				//g_posTexCoordMAP = MakeFloat2(((mapchip[g_nStageNum][i][j] - 7 % UI_COUNT_X) / (float)UI_COUNT_X), 0.0f);
				//DrawSpriteQuad(MakeFloat3(g_posMAP.x, g_posMAP.y - UI_DIFFERE / 2, 0.0f), g_sizeMAP, g_colorMAP, g_TextureMAP[UI], g_posTexCoordMAP, g_sizeTexCoordMAP, 0);		//四角形描画関数
				continue;
			}

			//--- 風描画 ---
			if (mapchip[g_nStageNum][i][j] == 11) {
				SetPolygonSize(WIND_WIDTH, WIND_HEIGHT);
				SetPolygonFrameSize(1.0f / WIND_COUNT, 1.0f);
				SetPolygonPos(g_pos.x, g_pos.y + WIND_HEIGHT / 2);
				SetPolygonUV(1.0f / WIND_COUNT, 0.0f);
				SetPolygonTexture(g_pTexture[WIND]);
				DrawPolygon(pDC);
				continue;
			}

			// マップの描画
			SetPolygonSize(BG_WIDTH, BG_HEIGHT);
			SetPolygonFrameSize(1.0f / MAP_COUNT_X, 1.0f);
			SetPolygonTexture(g_pTexture[MAP]);
			SetPolygonUV((mapchip[g_nStageNum][i][j] % MAP_COUNT_X) / (float)MAP_COUNT_X,0.0f);
			SetPolygonPos(g_pos.x,g_pos.y);
			SetPolygonAngle(0.0f);
			DrawPolygon(pDC);
		}
	}

	// UIの描画
	SetPolygonSize(UI_WIDTH, UI_HEIGHT);
	SetPolygonFrameSize(1.0f / UI_COUNT_X, 1.0f);
	SetPolygonTexture(g_pTexture[UI]);
	for (int i = 0; i < UI_COUNT_X - 1; i++) {
		SetPolygonPos(UIpos[i].x, UIpos[i].y);
		SetPolygonUV((i % UI_COUNT_X) / (float)UI_COUNT_X, 0.0f);
		SetPolygonAngle(0.0f);
		DrawPolygon(pDC);
	}


	// スターコイン（仮名）取得描画
	SetPolygonSize(STAR_WIDTH, STAR_HEIGHT);
	SetPolygonFrameSize(1.0f / STAR_COUNT_X, 1.0f);
	SetPolygonTexture(g_pTexture[STAR]);
	SetPolygonAngle(0.0f);
	for (int i = MAX_STAR; i > 0; i--) {
		SetPolygonPos(STAR_POS_X - i * STAR_WIDTH,STAR_POS_Y);
		if (i > g_nStarCnt) {
			SetPolygonUV((1 % STAR_COUNT_X) / (float)STAR_COUNT_X, 0.0f);
		} else {
			SetPolygonUV((0 % STAR_COUNT_X) / (float)STAR_COUNT_X, 0.0f);
		}
		DrawPolygon(pDC);
	}


	// 元に戻す
	SetPolygonAngle(0.0f);
	SetPolygonFrameSize(1.0f, 1.0f);
	SetPolygonUV(0.0f, 0.0f);
}


//====================================================================================
//
//				マップの取得
//
//====================================================================================
int* GetMap() {
	return &mapchip[g_nStageNum][0][0];
}

//====================================================================================
//
//				ゴール位置取得
//
//====================================================================================
XMFLOAT2 GetGoalpos() {
	return g_goalpos;
}

//====================================================================================
//
//				ゴールサイズ取得
//
//====================================================================================
XMFLOAT2 GetGoalsize() {
	XMFLOAT2 goalsize;
	goalsize.x = UI_WIDTH / 4;
	goalsize.y = UI_HEIGHT / 4;
	
	return goalsize;
}


//====================================================================================
//
//				フルーツ消す処理
//
//====================================================================================
void DestroyFruit(int* fruit){
	*fruit = 0;
	g_nStarCnt--;
}