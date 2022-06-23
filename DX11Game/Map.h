#ifndef __MAP_H__
#define __MAP_H__

#include "main.h"

#define MAP_HEIGHT		(12)
#define MAP_WIDTH		(20)
#define BG_WIDTH		(48)
#define BG_HEIGHT		(48)


//===========================
//
//	�v���g�^�C�v�錾
//
//===========================
HRESULT	InitMap();	// ������
void	UninitMap();	// �I��
void	UpdateMap();	// �X�V
void	DrawMap();	// �`��

int*	GetMap();
XMFLOAT2 GetGoalpos();
XMFLOAT2 GetGoalsize();
void DestroyFruit(int* fruit);


#endif // !__MAP_H__

