// ���l�\��
#include "number.h"
#include "Texture.h"
#include "polygon.h"

// �萔��`
#define PATH_NUMBERTEXTURE	L"data/texture/number000.png"


// �O���[�o���ϐ���`
static ID3D11ShaderResourceView *g_pTexture;


// ����������
HRESULT InitNumber() {
	HRESULT hr = S_OK;
	ID3D11Device *pDevice = GetDevice();

	hr = CreateTextureFromFile(pDevice, PATH_NUMBERTEXTURE, &g_pTexture);
	return hr;
}


// �I������
void UninitNumber() {
	// �e�N�X�`���J��
	SAFE_RELEASE(g_pTexture);
}



void DrawNumber(XMFLOAT2 vPos,unsigned uNumber,int nWidth,float fSizeX,float fSizeY) {
	ID3D11DeviceContext *pDC = GetDeviceContext();
	SetPolygonColor(1.0f,1.0f, 1.0f);
	SetPolygonSize(fSizeX, fSizeY);
	SetPolygonTexture(g_pTexture);
	SetPolygonFrameSize(1.0f / NUMBER_COUNT_X, 1.0f / NUMBER_COUNT_Y);
	//�@
	vPos.x += (nWidth - 0.5f) * fSizeX;
	vPos.y -= fSizeY * 0.5f;
	//�D
	for (; nWidth > 0 ;--nWidth) {
		//�A
		unsigned n = uNumber % 10;
		SetPolygonPos(vPos.x, vPos.y);
		SetPolygonUV((n % NUMBER_COUNT_X) / (float)NUMBER_COUNT_X,
					 (n / NUMBER_COUNT_X) / (float)NUMBER_COUNT_Y);
		DrawPolygon(pDC);
		//�B
		uNumber /= 10;
		//�C
		vPos.x -= fSizeX;
	}
	//���ɖ߂�
	SetPolygonFrameSize(1.0f, 1.0f);
	SetPolygonUV(0.0f, 0.0f);
}

