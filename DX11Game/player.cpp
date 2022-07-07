//************************************************************************************
// 
// プレイヤー[player.cpp]
// 編集者：伊地田真衣
// 
//************************************************************************************
//-------------------- インクルード部 --------------------
#include "player.h"
#include "polygon.h"
#include "Texture.h"
#include "debugproc.h"
#include "bullet.h"
#include "input.h"
#include "Collision.h"
#include "Map.h"
#include "Field.h"
#include "wind.h"
#include "Scene.h"
#include "clear.h"
#include "timer.h"


//-------------------- 定数定義 --------------------
#define PATH_PLAYERTEXTURE	(L"data/texture/player004.png")
#define PLAYER_POS_X		(-450.0f)
#define PLAYER_POS_Y		(-150.0f)
#define PLAYER_WIDTH		(112.0f)
#define PLAYER_HEIGHT		(112.0f)
#define PLAYER_COLLISION_W	(46.0f)
#define PLAYER_COLLISION_H	(112.0f)
#define PLAYER_SPEED_X		(3.0f)
#define PLAYER_SPEED_Y		(5.0f)
#define PLAYER_COUNT_X		(4)
#define PLAYER_COUNT_Y		(5)
#define GRAVITY				(0.2f)
#define GLIDERGRAVITY		(0.15f)


//-------------------- 構造体定義 --------------------
struct ANIME_PAT {
	int nFrame;	// 表示枠ナンバー
	int nCount;	// 表示フレーム数

};
//-------------------- グローバル変数定義 --------------------
static ANIME_PAT g_animePat[PLAYER_COUNT_Y + 1][PLAYER_COUNT_X + 1] = {
	{{ 0, 5},{-1,-1},{-1,-1},{-1,-1},{-1,-1}},
	{{ 4, 5},{ 5, 5},{ 6, 5},{-1,-1},{-1,-1}},
	{{ 8, 5},{ 9,10},{10, 5},{11,10},{-1,-1}},
	{{12, 5},{-1,-1},{-1,-1},{-1,-1},{-1,-1}},
	{{16, 7},{17, 2},{-1,-1},{-1,-1},{-1,-1}},
	{{-1,-1},{-1,-1},{-1,-1},{-1,-1},{-1,-1}},
};

static ID3D11ShaderResourceView *g_pTexture;
static XMFLOAT2 g_vPos;
static XMFLOAT2 g_oldPos;
XMFLOAT2 g_movepos;
static int g_nAnimeFrame;	// 表示枠ナンバー
static int g_nFrameCount;	// 表示フレーム数
static int g_nAnimPat;		// パターンナンバー
static int g_nDir;			// 方向（-1；左、1：右）
static int g_nWalk;			// 0:停止、1：移動 2:ダッシュ
static bool jumpFlg;
static bool g_landFlag;
static bool g_ClearFlg;

//-------------------- プロトタイプ宣言 --------------------
void PlayerCollision();

//====================================================================================
//
//	初期化
//
//====================================================================================
HRESULT	InitPlayer() {
	HRESULT hr = S_OK;
	ID3D11Device *pDevice = GetDevice();

	hr = CreateTextureFromFile(pDevice, PATH_PLAYERTEXTURE, &g_pTexture);
	if (FAILED(hr)) {
		return hr;
	}

	//変数初期化
	g_vPos.x = PLAYER_POS_X;
	g_vPos.y = PLAYER_POS_Y;
	g_oldPos = g_vPos;
	g_nAnimPat = 0;
	g_nDir = 1;
	g_nWalk = 0;
	g_nAnimeFrame = g_animePat[g_nWalk][g_nAnimPat].nFrame;
	g_nFrameCount = g_animePat[g_nWalk][g_nAnimPat].nCount;
	jumpFlg = false;
	g_landFlag = false;
	g_ClearFlg = false;

	return hr;
}

//====================================================================================
//
//	終了処理
//
//====================================================================================
void UninitPlayer() {
	// 背景テクスチャ開放
	SAFE_RELEASE(g_pTexture);
}

//====================================================================================
//
//	更新
//
//====================================================================================
void	UpdatePlayer() {
	//移動
	g_nWalk = 0;		
	g_nDir = 1;
	g_movepos.x = 0.0f;

	// 左移動
	if(GetKeyPress(VK_A)){
		g_nWalk = 1;
		g_nDir = -1;//左
		g_movepos.x = -PLAYER_SPEED_X;
	}
	// 右移動
	if (GetKeyPress(VK_D)) {
		g_nWalk = 1;
		g_nDir = 1;//右
		g_movepos.x = PLAYER_SPEED_X;
	}
	// ジャンプ
	if (jumpFlg == false && GetKeyPress(VK_W)) {
		g_nWalk = 3;
		g_nDir = 1;	// g_nDirで反転させるため、正の向きにしておく
		g_movepos.y = PLAYER_SPEED_Y;
		jumpFlg = true;
	}

	// ジャンプ中
	if (jumpFlg) {
		g_nWalk = 3;
		if (GetKeyPress(VK_SHIFT)) {
			g_nWalk = 4;
			g_movepos.y += GLIDERGRAVITY;
		}
	}

	g_movepos.y -= GRAVITY;

	g_oldPos = g_vPos;

	g_vPos.x += g_movepos.x;
	g_vPos.y += g_movepos.y;

	// アニメーション更新
	--g_nFrameCount;
	if (g_nFrameCount <= 0) {
		++g_nAnimPat;
		g_nAnimeFrame = g_animePat[g_nWalk][g_nAnimPat].nFrame;
		if (g_nAnimeFrame < 0) {
			g_nAnimPat = 0;
			g_nAnimeFrame = g_animePat[g_nWalk][g_nAnimPat].nFrame;
		} 
		g_nFrameCount =	g_animePat[g_nWalk][g_nAnimPat].nCount;
	}

	PlayerCollision();

	if (g_ClearFlg) {
		// クリア更新処理
		UpdateClear();
	}

	// デバッグ用文字列表示
	PrintDebugProc("*** Player ***\n");
	PrintDebugProc("g_pTexture(%s)\n", (g_pTexture) ? "OK" : "NG");
	PrintDebugProc("g_vPos={%.0f,%.0f}\n", g_vPos.x, g_vPos.y);
	PrintDebugProc("\n");
}

//====================================================================================
//
//	描画
//
//====================================================================================
void DrawPlayer() {
	ID3D11DeviceContext *pDC = GetDeviceContext();

	SetPolygonSize(PLAYER_WIDTH, PLAYER_HEIGHT);
	SetPolygonPos(g_vPos.x, g_vPos.y);
	SetPolygonTexture(g_pTexture);
	SetPolygonFrameSize(1.0f / PLAYER_COUNT_X , 1.0f /PLAYER_COUNT_Y );
	SetPolygonUV((g_nAnimeFrame % PLAYER_COUNT_X) / (float)PLAYER_COUNT_X,
				 (g_nAnimeFrame / PLAYER_COUNT_X) / (float)PLAYER_COUNT_Y);
	DrawPolygon(pDC);

	if (g_ClearFlg) {
		DrawClear();
	}

	//元に戻す
	SetPolygonFrameSize(1.0f,1.0f);
	SetPolygonUV(0.0f,0.0f);
}

//====================================================================================
//
//				当たり判定
//
//====================================================================================
void PlayerCollision() {
	XMFLOAT2 checkPos = XMFLOAT2(0.0f, 0.0f);

	//----- マップ当たり判定 -----
	int *map = GetMap();
	for (int i = 0; i < MAP_HEIGHT; i++) {
		for (int j = 0; j < MAP_WIDTH; j++, ++map) {
			if (*map == 0) {	// 描画なし
				continue;
			}
			if (*map == 6) {	// ゴール
				continue;
			}
			checkPos.x = (float)(j * BG_WIDTH - SCREEN_WIDTH / 2 + BG_WIDTH / 2);
			checkPos.y = (float)-(i * BG_HEIGHT - SCREEN_HEIGHT / 2);

			if (CheckCollisionRect(XMFLOAT2(PLAYER_COLLISION_W, PLAYER_COLLISION_H), XMFLOAT2(BG_WIDTH, BG_HEIGHT), g_vPos, checkPos)) {
				if (*map == 5 && !g_ClearFlg) { // クリアフラグがたったらスターコイン取れなくする
					DestroyFruit(map);
					continue;
				}
				if (g_vPos.y < g_oldPos.y) { // 落下
					g_movepos.y = 0.0f;
					g_vPos.y = checkPos.y + PLAYER_HEIGHT / 2.0f + BG_HEIGHT / 2.0f;
					jumpFlg = false;
					g_landFlag = true;
				}
				if (g_vPos.y > g_oldPos.y) { // 上昇
					g_vPos.y = checkPos.y - BG_HEIGHT / 2.0f - PLAYER_HEIGHT / 2.0f;
					g_movepos.y = 0.0f;
				} 
			}
		}

	}

	//----- 風当たり判定 -----
	checkPos = GetWindPos();
	if (CheckCollisionRect(XMFLOAT2(PLAYER_COLLISION_W, PLAYER_COLLISION_H), XMFLOAT2(WIND_WIDTH, WIND_HEIGHT), g_vPos, checkPos)) {
		if (g_nWalk != 4){
			return;
		}
		g_movepos.y = WINDSPEED;
	}

	//----- ゴール当たり判定 -----
	checkPos = GetGoalpos();
	if (CheckCollisionRect(XMFLOAT2(PLAYER_COLLISION_W, PLAYER_COLLISION_H), GetGoalsize(), g_vPos, checkPos)) {
		g_ClearFlg = true;	// クリアフラグ立てる
		if (GetKeyRelease(VK_RETURN)) {
			SetScene(SCENE_MODE);
			return;
		}
	}
}

