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
//	�v���g�^�C�v�錾
//
//===========================
HRESULT	InitSelect();	// ������
void	UninitSelect();	// �I��
void	UpdateSelect();	// �X�V
void	DrawSelect();	// �`��

int		GetStageNum();	// �X�e�[�W�ԍ��擾

#endif // !__SELECT_H__
