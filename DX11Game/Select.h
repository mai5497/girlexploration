#ifndef __SELECT_H__
#define __SELECT_H__

#include "main.h"

enum STAGE {
	STAGE1 = 0,
	STAGE2,
	STAGE3,

	MAX_STAGE
};

//===========================
//
//	プロトタイプ宣言
//
//===========================
HRESULT	InitSelect();	// 初期化
void	UninitSelect();	// 終了
void	UpdateSelect();	// 更新
void	DrawSelect();	// 描画

int		GetStageNum();	// ステージ番号取得

#endif // !__SELECT_H__
