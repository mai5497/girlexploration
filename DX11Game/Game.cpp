//************************************************************************************
// 
// �Q�[������[Game.cpp]
// �ҏW�ҁF�ɒn�c�^��
// 
//************************************************************************************
//-------------------- �C���N���[�h�� --------------------
#include "Scene.h"
#include "Game.h"
#include "polygon.h"
#include "Texture.h"
#include "input.h"
#include "bg.h"
#include "player.h"
#include "Map.h"
//#include "wind.h"
#include "timer.h"
#include "clear.h"



//====================================================================================
//
//	������
//
//====================================================================================
HRESULT	InitGame() {
	HRESULT hr = S_OK;

	// �w�i������
	hr = InitBG();
	if (FAILED(hr)) {
		MessageBox(GetMainWnd(), _T("�w�i���������s"), NULL, MB_OK);
		return hr;
	}

	// �v���C���[������
	hr = InitPlayer();
	if (FAILED(hr)) {
		MessageBox(GetMainWnd(), _T("�v���C���[���������s"), NULL, MB_OK);
		return hr;
	}

	// �}�b�v�`�b�v������
	hr = InitMap();
	if (FAILED(hr)) {
		MessageBox(GetMainWnd(), _T("�}�b�v�`�b�v���������s"), NULL, MB_OK);
		return hr;
	}

	// ��������
	//hr = InitWind();
	//if (FAILED(hr)) {
	//	MessageBox(GetMainWnd(), _T("�����������s"), NULL, MB_OK);
	//	return hr;
	//}

	// �^�C�}�[������
	hr = InitTimer();
	if (FAILED(hr)) {
		MessageBox(GetMainWnd(), _T("�^�C�}�[���������s"), NULL, MB_OK);
		return hr;
	}

	// �N���A������
	hr = InitClear();
	if (FAILED(hr)) {
		MessageBox(GetMainWnd(), _T("�N���A���������s"), NULL, MB_OK);
		return hr;
	}

	return hr;
}

//====================================================================================
//
//	�I������
//
//====================================================================================
void UninitGame() {
	// �w�i�I������
	UninitBG();

	// �}�b�v�`�b�v�I������
	UninitMap();

	// �v���C���[�I������
	UninitPlayer();

	// ���̏I������
	//UninitWind();

	// �^�C�}�[�I������
	UninitTimer();

	// �N���A�I������
	UninitClear();

}

//====================================================================================
//
//	�X�V
//
//====================================================================================
void	UpdateGame() {
	// �w�i�X�V
	UpdateBG();

	// �}�b�v�`�b�v�`��X�V
	UpdateMap();

	// ���X�V
	//UpdateWind();

	// �v���C���[�X�V
	UpdatePlayer();

	// �^�C�}�[�X�V����
	UpdateTimer();

}

//====================================================================================
//
//	�`��
//
//====================================================================================
void DrawGame() {

	// �w�i�`��
	DrawBG();

	// �}�b�v�`�b�v�`��
	DrawMap();

	// ���`��
	//DrawWind();

	// �^�C�}�[�`��
	DrawTimer();

	// �v���C���[�`��
	DrawPlayer();
}