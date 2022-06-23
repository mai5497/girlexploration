//----- �C���N���[�h�� -----
#include "Scene.h"
#include "title.h"
#include "Game.h"
#include "Select.h"

//----- �O���[�o���ϐ� -----
static EScene g_eScene = SCENE_NONE;

//------------------------------------------------------------------------------------
//
//				������
//
//------------------------------------------------------------------------------------
HRESULT InitScene() {
	HRESULT hr = S_OK;

	SetScene(SCENE_TITLE);	// �ŏ��̓^�C�g�����

	return hr;
}


//------------------------------------------------------------------------------------
//
//				�I��
//
//------------------------------------------------------------------------------------
void UninitScene() {
	SetScene(SCENE_NONE);	// ���݂̉�ʂ��I��
}

//------------------------------------------------------------------------------------
//
//				�X�V
//
//------------------------------------------------------------------------------------
void UpdateScene() {
	switch (g_eScene) {
	case SCENE_TITLE:	// �^�C�g�����
		UpdateTitle();
		break;
	case SCENE_MODE:	// ���[�h�I��
		UpdateSelect();
		break;
	case SCENE_GAME:	// �Q�[�����
		UpdateGame();
		break;
	default:
		break;
	}
}

//------------------------------------------------------------------------------------
//
//				�`��
//
//------------------------------------------------------------------------------------
void DrawScene() {
	switch (g_eScene) {
	case SCENE_TITLE:	// �^�C�g�����
		DrawTitle();
		break;
	case SCENE_MODE:	// ���[�h�I��
		DrawSelect();
		break;
	case SCENE_GAME:	// �Q�[�����
		DrawGame();
		break;
	default:
		break;
	}

}


//------------------------------------------------------------------------------------
//
//				�؂�ւ�
//
//------------------------------------------------------------------------------------
void SetScene(EScene eScene) {
	// ���݂̉�ʂ��I��
	switch (g_eScene) {
	case SCENE_TITLE:		// �^�C�g�����
		UninitTitle();
		break;
	case SCENE_MODE:	// ���[�h�I��
		UninitSelect();
		break;
	case SCENE_GAME:		// �Q�[�����
		UninitGame();
		break;
	default:
		break;

	}
	// ��ʂ����ւ�
	g_eScene = eScene;
	// ���̉�ʂ�������
	switch (g_eScene) {
	case SCENE_TITLE:		// �^�C�g�����
		InitTitle();
		break;
	case SCENE_MODE:	// ���[�h�I��
		InitSelect();
		break;
	case SCENE_GAME:		// �Q�[�����
		InitGame();
		break;
	default:
		break;
	}
}

//------------------------------------------------------------------------------------
//
//				�V�[���ԍ��擾
//
//------------------------------------------------------------------------------------
int GetScene() {
	return g_eScene;
}