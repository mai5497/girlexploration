//************************************************************************************
// 
// ����Ǘ�[Field.cpp]
// �ҏW�ҁF�ɒn�c�^��
// ���g�p�Ȃ�����
//************************************************************************************
//-------------------- �C���N���[�h�� --------------------
#include "Field.h"
#include "polygon.h"
#include "Texture.h"

//-------------------- �萔��` --------------------
#define PATH_BGTEXTURE	L"data/texture/kabe.png"
#define KABE_POS_X		0.0f
#define KABE_POS_Y		0.0f
#define KABE_WIDTH		100
#define KABE_HEIGHT		100

//-------------------- �\���̒�` --------------------
struct Field{
	XMFLOAT2 fieldPos;
};

//-------------------- �O���[�o���ϐ� --------------------
Field g_field[3];
static ID3D11ShaderResourceView *g_pTexture;


//====================================================================================
//
//				������
//
//====================================================================================
HRESULT InitField() {
	HRESULT hr = S_OK;
	ID3D11Device *pDevice = GetDevice();

	hr = CreateTextureFromFile(pDevice, PATH_BGTEXTURE, &g_pTexture);
	g_field[0].fieldPos.x = 100.0f;
	g_field[0].fieldPos.y = 100.0f;

	g_field[1].fieldPos.x = 200.0f;
	g_field[1].fieldPos.y = 200.0f;

	g_field[2].fieldPos.x = 300.0f;
	g_field[2].fieldPos.y = 300.0f;

	

	return hr;

}

//====================================================================================
//
//				�I��
//
//====================================================================================
void UninitField() {
	// �e�N�X�`���J��
	SAFE_RELEASE(g_pTexture);

}

//====================================================================================
//
//				�X�V
//
//====================================================================================
void UpdateField() {

}

//====================================================================================
//
//				�`��
//
//====================================================================================
void DrawField() {
	ID3D11DeviceContext *pDC = GetDeviceContext();

	SetPolygonSize(KABE_WIDTH, KABE_HEIGHT);
	for (int i = 0; i < 1; i++) {
		SetPolygonPos(g_field[i].fieldPos.x, g_field[i].fieldPos.y);
		SetPolygonTexture(g_pTexture);
		DrawPolygon(pDC);
	}
}


//====================================================================================
//
//				�ǉ�
//
//====================================================================================
void AddFieldPos(float add) {
	for (int i = 0; i < 1; i++) {
		g_field[i].fieldPos.x += add;
	}
}

