//�e
#pragma once
#include "main.h"

//===========================
//
//	�v���g�^�C�v�錾
//
//===========================
HRESULT	InitBullet();	// ������
void	UninitBullet();	// �I��
void	UpdateBullet();	// �X�V
void	DrawBullet();	// �`��
int	FireBullet(XMFLOAT2 vPos, int nDir);	//����