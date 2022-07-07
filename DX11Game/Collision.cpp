//************************************************************************************
// 
// 当たり判定[Collision.cpp]
// 編集者：伊地田真衣
// 
//************************************************************************************
//-------------------- インクルード部 --------------------
#include "Collision.h"

//====================================================================================
//
//				当たり判定
//
//====================================================================================
bool CheckCollisionRect(XMFLOAT2 Rect1Size, XMFLOAT2 Rect2Size, XMFLOAT2 Rect1Pos, XMFLOAT2 Rect2Pos) {
	XMFLOAT2 halfSize1 = XMFLOAT2(Rect1Size.x / 2.0f, Rect1Size.y / 2.0f);
	XMFLOAT2 halfSize2 = XMFLOAT2(Rect2Size.x / 2.0f, Rect2Size.y / 2.0f);

	if (Rect2Pos.x - halfSize2.x < Rect1Pos.x + halfSize1.x &&
		Rect1Pos.x - halfSize1.x < Rect2Pos.x + halfSize2.x) {
		if (Rect2Pos.y - halfSize2.y < Rect1Pos.y + halfSize1.y &&
			Rect1Pos.y - halfSize1.y < Rect2Pos.y + halfSize2.y) {
			return true;
		}
	}
	return false;
}
