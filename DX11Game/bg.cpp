// �w�i�`��
#include "bg.h"
#include "polygon.h"
#include "Texture.h"


// �}�N����`
#define PATH_BGTEXTURE	L"data/texture/bg000.png"
#define BG_POS_X		0.0f
#define BG_POS_Y		0.0f
#define BG_WIDTH		SCREEN_WIDTH
#define BG_HEIGHT		SCREEN_HEIGHT

//�O���[�o���ϐ��錾
static ID3D11ShaderResourceView *g_pTexture;
float g_posTexCoordBG;

//===================
//
//	������
//
//===================
HRESULT	InitBG() {
	HRESULT hr = S_OK;
	ID3D11Device *pDevice = GetDevice();

	g_posTexCoordBG = 0.0f;

	hr = CreateTextureFromFile(pDevice, PATH_BGTEXTURE, &g_pTexture);

	return hr;
}

//===================
//
//	�I������
//
//===================
void UninitBG() {
	// �w�i�e�N�X�`���J��
	SAFE_RELEASE(g_pTexture);
}

//===================
//
//	�X�V
//
//===================
void	UpdateBG() {
	//�Ȃɂ����Ȃ��F�j
}

//===================
//
//	�`��
//
//===================
void DrawBG() {
	ID3D11DeviceContext *pDC = GetDeviceContext();

	SetPolygonSize(BG_WIDTH, BG_HEIGHT);
	SetPolygonPos(BG_POS_X, BG_POS_Y);
	SetPolygonUV(g_posTexCoordBG, 0.0f);
	SetPolygonTexture(g_pTexture);
	DrawPolygon(pDC);

	SetPolygonUV(0.0f, 0.0f);
}

void AddBGTexCoord(float add) {
	g_posTexCoordBG += add;
}