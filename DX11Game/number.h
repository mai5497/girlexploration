// ���l�\��
#pragma once

#include "main.h"

//�萔��`
#define NUMBER_SIZE_X	(40.0f)		// ������
#define NUMBER_SIZE_Y	(70.0f)		// ��������

#define NUMBER_COUNT_X	10
#define NUMBER_COUNT_Y	2


//�֐��v���g�^�C�v
HRESULT InitNumber();
void UninitNumber();
//void UpdateNumber();	����͒�`���Ȃ�
void DrawNumber(XMFLOAT2 vPos,					// �\���ʒu�i����j
				unsigned nNumber,				// �\�����l
				int nWidth,						// �\������
				float fSizeX = NUMBER_SIZE_X,	// ������
				float fSizeY = NUMBER_SIZE_Y);	// ��������