#ifndef __MAP_H__
#define __MAP_H__

#include "main.h"

#define MAP_HEIGHT		(12)
#define MAP_WIDTH		(20)
#define BG_WIDTH		(48)
#define BG_HEIGHT		(48)


//===========================
//
//	プロトタイプ宣言
//
//===========================
HRESULT	InitMap();	// 初期化
void	UninitMap();	// 終了
void	UpdateMap();	// 更新
void	DrawMap();	// 描画

int*	GetMap();
XMFLOAT2 GetGoalpos();
XMFLOAT2 GetGoalsize();
void DestroyFruit(int* fruit);


#endif // !__MAP_H__

