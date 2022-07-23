//************************************************************************************
// 
// �v���C���[[player.cpp]
// �ҏW�ҁF�ɒn�c�^��
// 
//************************************************************************************
//-------------------- �C���N���[�h�� --------------------
#include "player.h"
#include "polygon.h"
#include "Texture.h"
#include "debugproc.h"
#include "bullet.h"
#include "input.h"
#include "Collision.h"
#include "Map.h"
#include "Field.h"
#include "Scene.h"
#include "clear.h"
#include "timer.h"


//-------------------- �萔��` --------------------
#define PATH_PLAYERTEXTURE	(L"data/texture/player004.png") // �e�N�X�`���p�X
#define PLAYER_POS_X		(-450.0f)						// �v���C���[�������W
#define PLAYER_POS_Y		(-150.0f)
#define PLAYER_WIDTH		(112.0f)						// �v���C���[�傫��
#define PLAYER_HEIGHT		(112.0f)
#define PLAYER_COLLISION_W	(46.0f)							// �����蔻�艡��
#define PLAYER_COLLISION_H	(112.0f)						// �����蔻�荂�� 
#define PLAYER_SPEED_X		(3.0f)							// �c�ړ��X�s�[�h
#define PLAYER_SPEED_Y		(5.0f)							// ���ړ��X�s�[�h
#define PLAYER_COUNT_X		(4)								// ��������
#define PLAYER_COUNT_Y		(5)								// �c������
#define GRAVITY				(0.2f)							// �d��
#define GLIDERGRAVITY		(0.15f)							// ���󒆂̏d��
#define WINDSPEED			(5.0f)							// ���㏸�X�s�[�h


//-------------------- �\���̒�` --------------------
struct ANIME_PAT {
	int nFrame;	// �\���g�i���o�[
	int nCount;	// �\���t���[����

};
//-------------------- �O���[�o���ϐ���` --------------------
static ANIME_PAT g_animePat[PLAYER_COUNT_Y + 1][PLAYER_COUNT_X + 1] = {
	{{ 0, 5},{-1,-1},{-1,-1},{-1,-1},{-1,-1}},
	{{ 4, 5},{ 5, 5},{ 6, 5},{-1,-1},{-1,-1}},
	{{ 8, 5},{ 9,10},{10, 5},{11,10},{-1,-1}},
	{{12, 5},{-1,-1},{-1,-1},{-1,-1},{-1,-1}},
	{{16, 7},{17, 2},{-1,-1},{-1,-1},{-1,-1}},
	{{-1,-1},{-1,-1},{-1,-1},{-1,-1},{-1,-1}},
};

static ID3D11ShaderResourceView *g_pTexture;
static XMFLOAT2 g_vPos;
static XMFLOAT2 g_oldPos;
XMFLOAT2 g_movepos;
static int g_nAnimeFrame;	// �\���g�i���o�[
static int g_nFrameCount;	// �\���t���[����
static int g_nAnimPat;		// �p�^�[���i���o�[
static int g_nDir;			// �����i-1�G���A1�F�E�j
static int g_nWalk;			// 0:��~�A1�F�ړ� 2:�_�b�V��
static bool jumpFlg;
static bool g_landFlag;
static bool g_ClearFlg;

//-------------------- �v���g�^�C�v�錾 --------------------
void PlayerCollision();

//====================================================================================
//
//	������
//
//====================================================================================
HRESULT	InitPlayer() {
	HRESULT hr = S_OK;
	ID3D11Device *pDevice = GetDevice();

	hr = CreateTextureFromFile(pDevice, PATH_PLAYERTEXTURE, &g_pTexture);
	if (FAILED(hr)) {
		return hr;
	}

	//�ϐ�������
	g_vPos.x = PLAYER_POS_X;
	g_vPos.y = PLAYER_POS_Y;
	g_oldPos = g_vPos;
	g_nAnimPat = 0;
	g_nDir = 1;
	g_nWalk = 0;
	g_nAnimeFrame = g_animePat[g_nWalk][g_nAnimPat].nFrame;
	g_nFrameCount = g_animePat[g_nWalk][g_nAnimPat].nCount;
	jumpFlg = false;
	g_landFlag = false;
	g_ClearFlg = false;

	return hr;
}

//====================================================================================
//
//	�I������
//
//====================================================================================
void UninitPlayer() {
	// �w�i�e�N�X�`���J��
	SAFE_RELEASE(g_pTexture);
}

//====================================================================================
//
//	�X�V
//
//====================================================================================
void	UpdatePlayer() {
	//�ړ�
	g_nWalk = 0;		
	g_nDir = 1;
	g_movepos.x = 0.0f;

	// ���ړ�
	if(GetKeyPress(VK_A)){
		g_nWalk = 1;
		g_nDir = -1;//��
		g_movepos.x = -PLAYER_SPEED_X;
	}
	// �E�ړ�
	if (GetKeyPress(VK_D)) {
		g_nWalk = 1;
		g_nDir = 1;//�E
		g_movepos.x = PLAYER_SPEED_X;
	}
	// �W�����v
	if (jumpFlg == false && GetKeyPress(VK_SPACE) && g_nWalk != 4) {
		g_nWalk = 3;
		g_nDir = 1;	// g_nDir�Ŕ��]�����邽�߁A���̌����ɂ��Ă���
		g_movepos.y = PLAYER_SPEED_Y;
		jumpFlg = true;
		g_landFlag = false;
	}

	// �W�����v��
	if (jumpFlg) {
		g_nWalk = 3;
		if (GetKeyPress(VK_SHIFT)) {
			g_nWalk = 4;
			g_movepos.y += GLIDERGRAVITY;
		}
	}

	g_movepos.y -= GRAVITY;

	g_oldPos = g_vPos;

	g_vPos.x += g_movepos.x;
	g_vPos.y += g_movepos.y;

	// �A�j���[�V�����X�V
	--g_nFrameCount;
	if (g_nFrameCount <= 0) {
		++g_nAnimPat;
		g_nAnimeFrame = g_animePat[g_nWalk][g_nAnimPat].nFrame;
		if (g_nAnimeFrame < 0) {
			g_nAnimPat = 0;
			g_nAnimeFrame = g_animePat[g_nWalk][g_nAnimPat].nFrame;
		} 
		g_nFrameCount =	g_animePat[g_nWalk][g_nAnimPat].nCount;
	}

	PlayerCollision();

	if (g_ClearFlg) {
		// �N���A�X�V����
		UpdateClear();
	}

	// �f�o�b�O�p������\��
	PrintDebugProc("*** Player ***\n");
	PrintDebugProc("g_pTexture(%s)\n", (g_pTexture) ? "OK" : "NG");
	PrintDebugProc("g_vPos={%.0f,%.0f}\n", g_vPos.x, g_vPos.y);
	PrintDebugProc("\n");
}

//====================================================================================
//
//	�`��
//
//====================================================================================
void DrawPlayer() {
	ID3D11DeviceContext *pDC = GetDeviceContext();

	SetPolygonSize(PLAYER_WIDTH, PLAYER_HEIGHT);
	SetPolygonPos(g_vPos.x, g_vPos.y);
	SetPolygonTexture(g_pTexture);
	SetPolygonFrameSize(1.0f / PLAYER_COUNT_X , 1.0f /PLAYER_COUNT_Y );
	SetPolygonUV((g_nAnimeFrame % PLAYER_COUNT_X) / (float)PLAYER_COUNT_X,
				 (g_nAnimeFrame / PLAYER_COUNT_X) / (float)PLAYER_COUNT_Y);
	//SetPolygonReversal();
	DrawPolygon(pDC);

	if (g_ClearFlg) {
		DrawClear();
	}

	//���ɖ߂�
	UnSetPolygonReversal();
	SetPolygonFrameSize(1.0f,1.0f);
	SetPolygonUV(0.0f,0.0f);
}

//====================================================================================
//
//				�����蔻��
//
//====================================================================================
void PlayerCollision() {
	XMFLOAT2 checkPos = XMFLOAT2(0.0f, 0.0f);

	//----- �}�b�v�����蔻�� -----
	int *map = GetMap();
	for (int i = 0; i < MAP_HEIGHT; i++) {
		for (int j = 0; j < MAP_WIDTH; j++, ++map) {
			if (*map == 0) {	// �`��Ȃ�
				continue;
			}
			if (6 < *map && *map < 11) {	//UI
				continue;
			}
			checkPos.x = (float)(j * BG_WIDTH - SCREEN_WIDTH / 2 + BG_WIDTH / 2);
			checkPos.y = (float)-(i * BG_HEIGHT - SCREEN_HEIGHT / 2);

			if (*map == 5 && !g_ClearFlg) { // �N���A�t���O����������X�^�[�R�C�����Ȃ�����
				if (CheckCollisionRect(XMFLOAT2(PLAYER_COLLISION_W, PLAYER_COLLISION_H), XMFLOAT2(BG_WIDTH, BG_HEIGHT), g_vPos, checkPos)) {
					DestroyFruit(map);
				}
				continue;
			}
			if (*map == 6 /* && !g_GameoverFlg */) {	// �S�[��
				//----- �S�[�������蔻�� -----
				checkPos = GetGoalpos();
				if (CheckCollisionRect(XMFLOAT2(PLAYER_COLLISION_W, PLAYER_COLLISION_H), GetGoalsize(), g_vPos, checkPos)) {
					g_ClearFlg = true;	// �N���A�t���O���Ă�
					if (GetKeyRelease(VK_RETURN)) {
						SetScene(SCENE_MODE);
					}
					continue;
				}
			}
			if (*map == 11) {	// ��
				//----- �������蔻�� -----
				if (CheckCollisionRect(XMFLOAT2(PLAYER_COLLISION_W, PLAYER_COLLISION_H), XMFLOAT2(WIND_WIDTH, WIND_HEIGHT), g_vPos, checkPos)) {
					if (g_nWalk != 4) {
						continue;
					}
					g_movepos.y = WINDSPEED;
				}
			}
			if (CheckCollisionRectX(XMFLOAT2(PLAYER_COLLISION_W, PLAYER_COLLISION_H), XMFLOAT2(BG_WIDTH, BG_HEIGHT), g_vPos, checkPos)) {
				//----- ����ɒ��n -----
				if (g_oldPos.y - (PLAYER_HEIGHT / 2.0f) >= checkPos.y + (BG_HEIGHT / 2.0f) &&
					checkPos.y + (BG_HEIGHT / 2.0f) >= g_vPos.y - (PLAYER_HEIGHT / 2.0f)) {
					g_movepos.y = 0.0f;
					g_vPos.y = checkPos.y + PLAYER_HEIGHT / 2.0f + BG_HEIGHT / 2.0f;
					jumpFlg = false;
					g_landFlag = true;
				}
				//----- �u���b�N�ɓ����Ԃ��� -----
				if (g_oldPos.y + (PLAYER_HEIGHT / 2.0f) <= checkPos.y - (BG_HEIGHT / 2.0f)
					&& checkPos.y - (BG_HEIGHT / 2.0f) <= g_vPos.y + (PLAYER_HEIGHT / 2.0f)) {
					g_vPos.y = checkPos.y - PLAYER_HEIGHT / 2.0f - BG_HEIGHT / 2.0f;
					g_movepos.y = 0.0f;
				}
			}
		}
	}
}

