//************************************************************************************
// 
// メイン[main.h]
// 編集者：伊地田真衣
// 
//************************************************************************************
#ifndef __MAIN_H__
#define __MAIN_H__

//-------------------- インクルード部 --------------------
#include <windows.h>
#include <tchar.h>
#include <mmsystem.h>
#include <d3d11.h>
#include <DirectXMath.h>
#include <stdio.h>
#include <stdlib.h>
#include "resource.h"

// 本来はヘッダに書かない方が良い
using namespace DirectX;

//-------------------- 定数マクロ定義 --------------------
#ifndef SAFE_RELEASE
#define SAFE_RELEASE(x) {if(x){(x)->Release();x=nullptr;}}
#endif
#ifndef SAFE_DELETE
#define SAFE_DELETE(x) {if(x){delete(x);x=nullptr;}}
#endif
#ifndef SAFE_DELETE_ARRAY
#define SAFE_DELETE_ARRAY(x) {if(x){delete[](x);x=nullptr;}}
#endif

#define SCREEN_WIDTH	(960)				// ウインドウの幅
#define SCREEN_HEIGHT	(576)				// ウインドウの高さ
#define SCREEN_CENTER_X	(SCREEN_WIDTH/2)	// ウインドウの中心Ｘ座標
#define SCREEN_CENTER_Y	(SCREEN_HEIGHT/2)	// ウインドウの中心Ｙ座標

#define	NUM_VERTEX		(4)					// 頂点数
#define	NUM_POLYGON		(2)					// ポリゴン数

#define FRAME_RATE		(60)				//フレームレート６０

enum EBlendState {
	BS_NONE = 0,	// 半透明合成なし
	BS_ALPHABLEND,	// 半透明合成
	BS_ADDITIVE,	// 加算合成
	BS_SUBTRACTION,	// 減算合成

	MAX_BLENDSTATE
};

//-------------------- 構造体定義 --------------------
// 頂点フォーマット( 頂点座標[2D] / 反射光 / テクスチャ座標 )
typedef struct {
	XMFLOAT3 vtx;		// 頂点座標
	XMFLOAT4 diffuse;	// 拡散反射光
	XMFLOAT2 tex;		// テクスチャ座標
} VERTEX_2D;

//-------------------- プロトタイプ宣言 --------------------
HWND GetMainWnd();
HINSTANCE GetInstance();
ID3D11Device* GetDevice();
ID3D11DeviceContext* GetDeviceContext();
void SetBlendState(int nBlendState);

#endif