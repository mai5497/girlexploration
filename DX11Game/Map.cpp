#include "Map.h"
#include "polygon.h"
#include "Texture.h"
#include "debugproc.h"
#include "Select.h"


// �}�N����`
#define BG_POS_X		(0.0f)
#define BG_POS_Y		(0.0f)

#define MAP_COUNT_X		(6)
#define MAP_HEIGHT		(12)
#define MAP_WIDTH		(20)

#define UI_COUNT_X		(5)
#define UI_WIDTH		(140.0f)
#define UI_HEIGHT		(140.0f)
#define UI_DIFFERE		(UI_WIDTH - BG_WIDTH)

#define STAR_COUNT_X	(2)
#define MAX_STAR		(3)
#define STAR_WIDTH		(50.0f)
#define STAR_HEIGHT		(50.0f)
#define STAR_DIFFER		(STAR_WIDTH - BG_WIDTH)
#define STAR_POS_X		(0.0f - SCREEN_WIDTH / 2 + STAR_WIDTH * MAX_STAR + STAR_WIDTH / 2 )
#define STAR_POS_Y		(SCREEN_HEIGHT / 2 - STAR_HEIGHT / 2)

enum TEX {
	MAP = 0,
	UI,
	STAR,

	MAX_TEXTURE
};



struct ANIME_PAT {
	int nFrame;	// �\���g�i���o�[
	int nCount;	// �\���t���[����

};

//�O���[�o���ϐ��錾
static LPCWSTR g_pszTexFName[MAX_TEXTURE] = {
	L"data/texture/mapchip000.png",
	L"data/texture/mapchip001.png",
	L"data/texture/mapchip002.png",
};

static ID3D11ShaderResourceView *g_pTexture[MAX_TEXTURE];

XMFLOAT2 g_pos;
XMFLOAT2 UIpos[UI_COUNT_X] = { XMFLOAT2(-340.0f,-165.0f),XMFLOAT2(-192.0f,-117.0f), XMFLOAT2(300.0f,-117.0f), XMFLOAT2(160.0f,-117.0f) };
XMFLOAT2 g_goalpos;
float	 g_fAngle;				// �S�[���p�x
static int g_nStarCnt;
static int g_nStageNum;

int mapchip[MAX_STAGE][12][20] =
{
	{
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,5,0,0,6,0,0,},
	{0,0,0,0,0,0,0,5,0,0,0,0,0,0,0,0,0,0,0,0,},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2,3,3,4,},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,5,0,},
	{0,0,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,},
	{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,},
	},
	{
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2,3,3,4,},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,},
	{0,0,0,0,0,0,0,0,0,0,0,0,2,3,4,0,0,0,0,0,},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,5,0,0,0,},
	{0,0,0,0,0,0,0,0,5,0,0,0,0,0,0,2,3,4,0,0,},
	{0,0,0,0,0,0,0,2,3,4,0,0,0,0,0,0,0,0,0,0,},
	{0,0,0,0,5,0,0,0,0,0,0,0,2,3,4,0,0,0,0,0,},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,},
	{1,1,1,0,0,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,},
	},

};



HRESULT	InitMap() {
	HRESULT hr = S_OK;
	ID3D11Device *pDevice = GetDevice();

	g_pos.x = 0.0f;
	g_pos.y = 0.0f;
	g_goalpos.x = 380.0f;
	g_goalpos.y = 80.0f;
	g_nStarCnt = MAX_STAR;
	g_nStageNum = GetStageNum();

	for (int i = 0; i < MAX_TEXTURE; i++) {
		hr = CreateTextureFromFile(pDevice, g_pszTexFName[i], &g_pTexture[i]);
		if (FAILED(hr)) {
			return hr;
		}
	}

	return hr;

}
void	UninitMap() {
	// �e�N�X�`���J��
	for (int i = 0; i < MAX_TEXTURE; i++) {
		SAFE_RELEASE(g_pTexture[i]);
	}

}
void	UpdateMap() {
	// �p�x�̕ύX
	g_fAngle += 1.0f;
	if (g_fAngle >= 180.0f) {
		g_fAngle -= 360;
	}
}
void	DrawMap() {
	ID3D11DeviceContext *pDC = GetDeviceContext();


	for (int i = 0; i < MAP_HEIGHT; i++) {
		for (int j = 0; j < MAP_WIDTH; j++) {
			g_pos.x = (float)(j * BG_WIDTH - SCREEN_WIDTH / 2 + BG_WIDTH / 2);
			g_pos.y = -1.0f * (i * BG_HEIGHT - SCREEN_HEIGHT / 2 );
			if (mapchip[g_nStageNum][i][j] == 6) {
				// �S�[���̕`��
				SetPolygonSize(UI_WIDTH, UI_HEIGHT);
				SetPolygonFrameSize(1.0f / UI_COUNT_X, 1.0f);
				SetPolygonTexture(g_pTexture[UI]);
				SetPolygonPos(g_pos.x + UI_DIFFERE / 2, g_pos.y);
				SetPolygonUV((4 % UI_COUNT_X) / (float)UI_COUNT_X, 0.0f);
				SetPolygonAngle(g_fAngle);
				DrawPolygon(pDC);
				continue;
			}
			// �}�b�v�̕`��
			SetPolygonSize(BG_WIDTH, BG_HEIGHT);
			SetPolygonFrameSize(1.0f / MAP_COUNT_X, 1.0f);
			SetPolygonTexture(g_pTexture[MAP]);
			SetPolygonUV((mapchip[g_nStageNum][i][j] % MAP_COUNT_X) / (float)MAP_COUNT_X,0.0f);
			SetPolygonPos(g_pos.x,g_pos.y);
			SetPolygonAngle(0.0f);
			DrawPolygon(pDC);
		}
	}

	// UI�̕`��
	SetPolygonSize(UI_WIDTH, UI_HEIGHT);
	SetPolygonFrameSize(1.0f / UI_COUNT_X, 1.0f);
	SetPolygonTexture(g_pTexture[UI]);
	for (int i = 0; i < UI_COUNT_X - 1; i++) {
		SetPolygonPos(UIpos[i].x, UIpos[i].y);
		SetPolygonUV((i % UI_COUNT_X) / (float)UI_COUNT_X, 0.0f);
		SetPolygonAngle(0.0f);
		DrawPolygon(pDC);
	}


	// �X�^�[�R�C���i�����j�擾�`��
	SetPolygonSize(STAR_WIDTH, STAR_HEIGHT);
	SetPolygonFrameSize(1.0f / STAR_COUNT_X, 1.0f);
	SetPolygonTexture(g_pTexture[STAR]);
	SetPolygonAngle(0.0f);
	for (int i = MAX_STAR; i > 0; i--) {
		SetPolygonPos(STAR_POS_X - i * STAR_WIDTH,STAR_POS_Y);
		if (i > g_nStarCnt) {
			SetPolygonUV((1 % STAR_COUNT_X) / (float)STAR_COUNT_X, 0.0f);
		} else {
			SetPolygonUV((0 % STAR_COUNT_X) / (float)STAR_COUNT_X, 0.0f);
		}
		DrawPolygon(pDC);
	}


	// ���ɖ߂�
	SetPolygonAngle(0.0f);
	SetPolygonFrameSize(1.0f, 1.0f);
	SetPolygonUV(0.0f, 0.0f);
}


// �}�b�v�̎擾
int* GetMap() {
	return &mapchip[g_nStageNum][0][0];
}

// �S�[���ʒu�擾
XMFLOAT2 GetGoalpos() {
	return g_goalpos;
}

// �S�[���T�C�Y�擾
XMFLOAT2 GetGoalsize() {
	XMFLOAT2 goalsize;
	goalsize.x = UI_WIDTH / 4;
	goalsize.y = UI_HEIGHT / 4;
	
	return goalsize;
}

void DestroyFruit(int* fruit){
	*fruit = 0;
	g_nStarCnt--;
}