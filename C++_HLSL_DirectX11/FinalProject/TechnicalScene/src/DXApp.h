// DXApp
// Andre Berthiaume, June 2016
// Note: DX 11 SDK https://www.microsoft.com/en-us/download/details.aspx?id=6812
// Note on weird stuff with swap chain (1s and 2s) https://msdn.microsoft.com/en-us/library/windows/desktop/jj863687(v=vs.85).aspx

#ifndef _DXApp
#define _DXApp

#include <d3d11.h>
#include "d3dUtil.h"
#include "Align16.h"
#include "GameTimer.h"
#include <string>

// New includes for demo
#include "Vect.h"
#include "Matrix.h"
#include "Camera.h"
#include "ShaderColor.h"
#include "ShaderColorLight.h"

//MARY
#include "ShaderTexture.h";
#include "GraphicObject_Texture.h"
#include "GraphicObject_Light.h"
#include "ShaderColorLightTexture.h"
#include "GraphicObject_TexLight.h"
#include "SkyBox.h"
#include "ShaderTexColMultiLight.h"
#include "GraphicObject_TexColMultiLight.h"
#include "ShaderColorMultiLight.h"


class Model;
class Texture;
class FlatPlane;
class TerrainModel;
class GraphicObject_Color;
class ShaderTexture;
class GraphicObject_Texture;

class DXApp : public Align16
{
private:	
	// Main window handle
	HWND      mhMainWnd;

	Vect BackgroundColor;
	int SyncInterval = 1;  // 1 for sync to refresh rate, 0 for no sync

	// DX application elements
	ID3D11Device* md3dDevice;					// Connects to the graphics card
	ID3D11DeviceContext* md3dImmediateContext;	// Settings for the GPU to use
	IDXGISwapChain* mSwapChain;					// image buffers used for rendering
	ID3D11RenderTargetView* mRenderTargetView;	// Where to send rendring operations (typically: points to one of the swap buffers)
	ID3D11DepthStencilView* mpDepthStencilView; // Needed to force depth-buffer operations

	GameTimer mTimer;
	std::string mMainWndCaption;
	int mClientWidth;
	int mClientHeight;

	void InitDirect3D();
	void InitDemo();
	void UpdateScene();
	void DrawScene();
	void CalculateFrameStats();

	// Shader loading utility. SHould be moved elsewhere later...
	HRESULT CompileShaderFromFile(WCHAR* szFileName, LPCSTR szEntryPoint, LPCSTR szShaderModel, ID3DBlob** ppBlobOut);

	// Debug utility
	void ReportLiveDXObjects();

	// Demo specific additions
	Camera mCam;

	// utilizing all shaders
	ShaderColor* pShaderCol;
	ShaderColorLight* pShaderColLight;
	ShaderColorMultiLight* pShaderColMultiLight;
	ShaderTexture* pShaderTex;
	ShaderColorLightTexture* pShaderColLightTex;
	ShaderTexColMultiLight* pShaderTexColMultiLight;

	// create a graphic object for each shader
	GraphicObject_Color* ColorGO1;
	GraphicObject_Color* ColorGO2;
	GraphicObject_Color* ColorGO3;
	GraphicObject_Color* ColorGO4;
	GraphicObject_Color* ColorGO5;
	GraphicObject_Color* ColorGO6;
	GraphicObject_Texture* TexGO1;
	GraphicObject_Texture* TexGO2;
	GraphicObject_Texture* TexGO3;
	GraphicObject_Texture* TexGO4;
	GraphicObject_Texture* TexGO5;
	GraphicObject_Light* LightGO1;
	GraphicObject_Light* LightGO2;
	//GraphicObject_Light* LightGO3;
	GraphicObject_Light* LightGO4;
	GraphicObject_Light* LightGO5;
	GraphicObject_Light* LightGO6;
	GraphicObject_TexLight* TexLightGO1;
	GraphicObject_TexLight* TexLightGO2;
	GraphicObject_TexLight* TexLightGO3;
	GraphicObject_TexLight* TexLightGO4;
	GraphicObject_TexLight* TexLightGO5;
	GraphicObject_TexColMultiLight* TexColMultiLightGO1;
	GraphicObject_TexColMultiLight* TexColMultiLightGO2;
	GraphicObject_TexColMultiLight* TexColMultiLightGO3;
	GraphicObject_TexColMultiLight* TexColMultiLightGO4;
	GraphicObject_TexColMultiLight* TexColMultiLightGO5;

	// create a model for each graphic object
	Model* pUnitBoxRepTex;
	Model* pUnitBoxSixTex;
	Model* pUnitSphere;
	Model* pUnitTexSphere;
	Model* pUnitPyrRepTex;
	Model* pHotDog;

	// also create our Terrain, Flat plane and SkyBox models
	TerrainModel* pTerrain;
	FlatPlane* pPlane;
	SkyBox* pSkyBox;

	// create a texture for the models / meshes that need them
	Texture* pTexTex1;
	Texture* pTexTex2;
	Texture* pTexTex3;
	Texture* pTexTex4;
	Texture* pTexTex5;
	Texture* pTexTex6;
	Texture* pTexTex7;
	Texture* pTexTex8;
	Texture* pTexLightTex1;
	Texture* pTexLightTex2;
	Texture* pTexLightTex3;
	Texture* pTexLightTex4;
	Texture* pTexLightTex5;
	Texture* pTexLightTex6;
	Texture* pTexLightTex7;
	Texture* pTexLightTex8;
	Texture* pTexColMultiLightTex1;
	Texture* pTexColMultiLightTex2;
	Texture* pTexColMultiLightTex3;
	Texture* pTexColMultiLightTex4;
	Texture* pTexColMultiLightTex5;
	Texture* pTexColMultiLightTex6;
	Texture* pTexColMultiLightTex7;
	Texture* pTexColMultiLightTex8;
	Texture* pTerrainTex;
	Texture* pSkyBoxTex;

	// create world matrices for each object
	Matrix mColWorld1;
	Matrix mColWorld2;
	Matrix mColWorld3;
	Matrix mColWorld4;
	Matrix mColWorld5;
	Matrix mColWorld6;
	Matrix mTexWorld1;
	Matrix mTexWorld2;
	Matrix mTexWorld3;
	Matrix mTexWorld4;
	Matrix mTexWorld5;
	Matrix mLightWorld1;
	Matrix mLightWorld2;
	//Matrix mLightWorld3;
	Matrix mLightWorld4;
	Matrix mLightWorld5;
	Matrix mLightWorld6;
	Matrix mTexLightWorld1;
	Matrix mTexLightWorld2;
	Matrix mTexLightWorld3;
	Matrix mTexLightWorld4;
	Matrix mTexLightWorld5;
	Matrix mTexColMultiLightWorld1;
	Matrix mTexColMultiLightWorld2;
	Matrix mTexColMultiLightWorld3;
	Matrix mTexColMultiLightWorld4;
	Matrix mTexColMultiLightWorld5;
	Matrix mPlaneWorld;
	Matrix mSkyBoxWorld;

	Vect lightPos1;
	Vect lightPos2;
	Vect lightPos3;
	Vect lightPos4;
	Vect lightPos5;
	Vect lightPos6;


public:
	DXApp(HWND hwnd);
	virtual ~DXApp();
	
	void FrameTick();

	// overrides for handling mouse input.
	void OnMouseDown(WPARAM btnState, int xval, int yval);
	void OnMouseUp(WPARAM btnState, int xval, int yval);
	void OnMouseMove(WPARAM btnState, int xval, int yval);
	void OnMouseWheel(short delta);


};

#endif _DXApp