#include "wind.h"
#include "polygon.h"
#include "Texture.h"

#define PATH_WINDTEXTURE	(L"data/texture/wind1.png")


//�O���[�o���ϐ��錾
static ID3D11ShaderResourceView* g_pTexture;
float g_posTexCoordWind;
XMFLOAT2 g_posWind;


//===================
//
//	������
//
//===================
HRESULT	InitWind() {
	HRESULT hr = S_OK;
	ID3D11Device* pDevice = GetDevice();

	g_posTexCoordWind = 0.0f;
	g_posWind.x = 70.0f;
	g_posWind.y = -90.0f;

	hr = CreateTextureFromFile(pDevice, PATH_WINDTEXTURE, &g_pTexture);

	return hr;
}

//===================
//
//	�I��
//
//===================
void UninitWind() {
	// �w�i�e�N�X�`���J��
	SAFE_RELEASE(g_pTexture);
}

//===================
//
//	�X�V
//
//===================
void UpdateWind() {


}

//===================
//
//	�`��
//
//===================
void	DrawWind() {
	ID3D11DeviceContext* pDC = GetDeviceContext();

	SetPolygonSize(WIND_WIDTH, WIND_HEIGHT);
	SetPolygonPos(g_posWind.x,g_posWind.y);
	SetPolygonUV(1.0f / 2, 0.0f);
	SetPolygonColor(1.0f, 1.0f, 1.0f);
	SetPolygonTexture(g_pTexture);
	DrawPolygon(pDC);

	SetPolygonUV(0.0f, 0.0f);
	SetPolygonColor(1.0f, 1.0f, 1.0f);
}



//===================
//
//	���W�擾
//
//===================
XMFLOAT2 GetWindPos() {
	return g_posWind;
}