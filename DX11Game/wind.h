#ifndef __WIND_H__
#define __WIND_H__

#include "main.h"

//===========================
//
//	�萔��`
//
//===========================
#define WIND_WIDTH			(96.0f / 2)	// �T�C�Y��
#define WIND_HEIGHT			(192.0f)// �T�C�Y�c
#define WINDSPEED			(10.0f)


//===========================
//
//	�v���g�^�C�v�錾
//
//===========================
HRESULT	InitWind();		// ������
void	UninitWind();	// �I��
void	UpdateWind();	// �X�V
void	DrawWind();		// �`��

XMFLOAT2 GetWindPos();	// �����W�擾

#endif // !__WIND_H__

