//************************************************************************************
// 
// �I�����[Select.cpp]
// �ҏW�ҁF�ɒn�c�^��
// 
//************************************************************************************
//-------------------- �C���N���[�h�� --------------------
#include "Scene.h"
#include "Select.h"
#include "polygon.h"
#include "Texture.h"
#include "input.h"


//-------------------- �萔�}�N����` --------------------
#define PATH_SELECTTEXTURE	L"data/texture/bg000.png"
#define SELECT_POS_X			(0.0f)
#define SELECT_POS_Y			(0.0f)
#define SELECT_WIDTH			(SCREEN_WIDTH)
#define SELECT_HEIGHT		(SCREEN_HEIGHT)
//#define SELECT_ROGO_POS_X
//#define SELECT_ROGO_POS_Y
//#define SELECT_ROGO_WIDTH
//#define SELECT_ROGO_HEIGHT


//-------------------- �O���[�o���ϐ���` --------------------
static ID3D11ShaderResourceView* g_pTexture;
float g_posTexCoordSelect;
static int g_nStageNum;

//====================================================================================
//
//	������
//
//====================================================================================
HRESULT	InitSelect() {
	HRESULT hr = S_OK;
	ID3D11Device* pDevice = GetDevice();

	g_posTexCoordSelect = 0.0f;
	g_nStageNum = STAGE3;

	hr = CreateTextureFromFile(pDevice, PATH_SELECTTEXTURE, &g_pTexture);

	return hr;
}

//====================================================================================
//
//	�I������
//
//====================================================================================
void UninitSelect() {
	// �w�i�e�N�X�`���J��
	SAFE_RELEASE(g_pTexture);
}

//====================================================================================
//
//	�X�V
//
//====================================================================================
void UpdateSelect() {
	if (GetKeyRelease(VK_RETURN)) {	// �G���^�[�L�[�������ꂽ��
		SetScene(SCENE_GAME);
	}
}

//====================================================================================
//
//	�`��
//
//====================================================================================
void DrawSelect() {
	ID3D11DeviceContext* pDC = GetDeviceContext();

	SetPolygonSize(SELECT_WIDTH, SELECT_HEIGHT);
	SetPolygonPos(SELECT_POS_X, SELECT_POS_Y);
	SetPolygonUV(g_posTexCoordSelect, 0.0f);
	SetPolygonTexture(g_pTexture);
	DrawPolygon(pDC);

	SetPolygonUV(0.0f, 0.0f);
}

//====================================================================================
//
//				�X�e�[�W�ԍ��擾
//
//====================================================================================
int	GetStageNum() {
	return g_nStageNum;
}