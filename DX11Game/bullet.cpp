//************************************************************************************
// 
// �e[main.cpp]
// �ҏW�ҁF�ɒn�c�^��
// ���g�p����
//************************************************************************************
//-------------------- �C���N���[�h�� --------------------
#include "bullet.h"
#include "Texture.h"
#include "polygon.h"


//-------------------- �萔��` --------------------
#define PATH_BULLETTEXTURE L"data/texture/player000.png"
#define BULLET_WIDTH 64
#define BULLET_HEIGHT 64
#define BULLET_SPEED 12.0f
#define BULLET_COUNT_X 4
#define BULLET_COUNT_Y 4
#define BULLET_FRAME 3
#define MAX_BULLET 100

//-------------------- �\���̒�` --------------------
struct BULLET {
	XMFLOAT2 vPos; // �ʒu
	XMFLOAT2 vVel; // ���x
};

//-------------------- �O���[�o���ϐ� --------------------
static ID3D11ShaderResourceView* g_pTexture;
static BULLET g_bullet[MAX_BULLET];// �e���
static int g_nBullet;// �g�p���e��


//====================================================================================
//
//				������
//
//====================================================================================
HRESULT InitBullet()
{
	HRESULT hr = S_OK;
	ID3D11Device* pDevice = GetDevice();
	// �e�N�X�`���Ǎ�
	hr = CreateTextureFromFile(
		pDevice,
		PATH_BULLETTEXTURE,
		&g_pTexture);
	if (FAILED(hr)) {
		return hr;
	}
	// ������
	g_nBullet = 0;
	return hr;
}


//====================================================================================
//
//				�I������
//
//====================================================================================
void UninitBullet()
{
	// �e�N�X�`�����
	SAFE_RELEASE(g_pTexture);
}


//====================================================================================
//
//				�X�V
//
//====================================================================================
void UpdateBullet()
{
	for (int i = g_nBullet - 1; i >= 0; --i) {
		BULLET* pBullet = &g_bullet[i];
		// �ړ�
		pBullet->vPos.x += pBullet->vVel.x;
		pBullet->vPos.y += pBullet->vVel.y;
		// ��ʊO�ɏo�������
		if (pBullet->vPos.x <
			(SCREEN_WIDTH + BULLET_WIDTH) * -0.5f ||
			pBullet->vPos.x >
			(SCREEN_WIDTH + BULLET_WIDTH) * 0.5f ||
			pBullet->vPos.y <
			(SCREEN_HEIGHT + BULLET_HEIGHT) * -0.5f ||
			pBullet->vPos.y >
			(SCREEN_HEIGHT + BULLET_HEIGHT) * 0.5f) {
			--g_nBullet;
			*pBullet = g_bullet[g_nBullet];
			continue;
		} // TODO: �����蔻��
	}
}

//====================================================================================
//
//				�`��
//
//====================================================================================
void DrawBullet()
{
	ID3D11DeviceContext* pDC = GetDeviceContext();
	SetPolygonSize(BULLET_WIDTH, BULLET_HEIGHT);
	SetPolygonTexture(g_pTexture);
	SetPolygonFrameSize(1.0f / BULLET_COUNT_X,
		1.0f / BULLET_COUNT_Y);
	SetPolygonUV((BULLET_FRAME % BULLET_COUNT_X) /
		(float)BULLET_COUNT_X,
		(BULLET_FRAME / BULLET_COUNT_X) /
		(float)BULLET_COUNT_Y);
	BULLET* pBullet = g_bullet;
	for (int i = 0; i < g_nBullet; ++i, ++pBullet) {
		SetPolygonPos(pBullet->vPos.x,pBullet->vPos.y);
		DrawPolygon(pDC);
	} SetPolygonUV(0.0f, 0.0f);
	SetPolygonFrameSize(1.0f, 1.0f);
}

//====================================================================================
//
//				����
// 
//====================================================================================
int FireBullet(XMFLOAT2 vPos, int nDir)
{
	if (g_nBullet < MAX_BULLET) {
		BULLET* pBullet = &g_bullet[g_nBullet];
		pBullet->vPos = vPos;
		switch (nDir) {
		case 0://��
			pBullet->vVel.x = 0.0f;
			pBullet->vVel.y = -BULLET_SPEED;
			break;
		case 1://��
			pBullet->vVel.x = -BULLET_SPEED;
			pBullet->vVel.y = 0.0f;
			break;
		case 2://�E
			pBullet->vVel.x = BULLET_SPEED;
			pBullet->vVel.y = 0.0f;
			break;
		case 3://��
			pBullet->vVel.x = 0.0f;
			pBullet->vVel.y = BULLET_SPEED;
			break;
		} 
		++g_nBullet;
		return g_nBullet;
	} return 0;
}