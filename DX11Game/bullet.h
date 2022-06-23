//弾
#pragma once
#include "main.h"

//===========================
//
//	プロトタイプ宣言
//
//===========================
HRESULT	InitBullet();	// 初期化
void	UninitBullet();	// 終了
void	UpdateBullet();	// 更新
void	DrawBullet();	// 描画
int	FireBullet(XMFLOAT2 vPos, int nDir);	//発射