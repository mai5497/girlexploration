#ifndef __SCENE_H__
#define __SCENE_H__

#include "main.h"

enum EScene {
	SCENE_NONE = 0,	// ���ݒ�
	SCENE_TITLE,	// �^�C�g�����
	SCENE_MODE,		// ���[�h�I�����
	SCENE_GAME,		// �Q�[�����

	MAX_SCENE		// �V�[������
};

HRESULT InitScene();			// ������
void UninitScene();				// �I������
void UpdateScene();				// �X�V
void DrawScene();				// �`��

void SetScene(EScene Escene);	// �؂�ւ�
int GetScene();					// �V�[���ԍ��Ԃ�

#endif
