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

	// all of our models will use the texture + color + multi light shader
	ShaderTexColMultiLight* pShaderTexLight;
	// skybox just uses texture shader though
	ShaderTexture* pShaderTex;

	// create a graphic object for each object
	GraphicObject_TexColMultiLight* BurgerGO;
	GraphicObject_TexColMultiLight* CupGO;
	GraphicObject_TexColMultiLight* DonutGO;
	GraphicObject_TexColMultiLight* ForkGO;
	GraphicObject_TexColMultiLight* FriesGO;
	GraphicObject_TexColMultiLight* HandGO;
	GraphicObject_TexColMultiLight* HotDogGO;
	GraphicObject_TexColMultiLight* IceCreamGO;
	GraphicObject_TexColMultiLight* KnifeGO;
	GraphicObject_TexColMultiLight* PlateGO;
	GraphicObject_TexColMultiLight* BlanketGO;
	GraphicObject_TexColMultiLight* Person1GO;
	GraphicObject_TexColMultiLight* Person2GO;


	// create a model for each model I have
	Model* pBurger;
	Model* pCup;
	Model* pDonut;
	Model* pFork;
	Model* pFries;
	Model* pHand;
	Model* pHotDog;
	Model* pIceCream;
	Model* pKnife;
	Model* pPlate;
	Model* pPerson1;
	Model* pPerson2;
	TerrainModel* pBlanket;
	SkyBox* pSkyBox;

	// create a texture for each mesh in each model
	Texture* pBurgerTex1;
	Texture* pBurgerTex2;
	Texture* pBurgerTex3;
	Texture* pBurgerTex4;
	Texture* pCupTex1;
	Texture* pCupTex2;
	Texture* pCupTex3;
	Texture* pDonutTex1;
	Texture* pDonutTex2;
	Texture* pDonutTex3;
	Texture* pForkTex1;
	Texture* pFriesTex1;
	Texture* pFriesTex2;
	Texture* pFriesTex3;
	Texture* pHandTex1;
	Texture* pHandTex2;
	Texture* pHandTex3;
	Texture* pHandTex4;
	Texture* pHotDogTex1;
	Texture* pHotDogTex2;
	Texture* pHotDogTex3;
	Texture* pHotDogTex4;
	Texture* pIceCreamTex1;
	Texture* pIceCreamTex2;
	Texture* pIceCreamTex3;
	Texture* pKnifeTex1;
	Texture* pPlateTex1;
	Texture* pBlanketTex1;
	Texture* pSkyBoxTex1;
	Texture* pPerson1Tex1;
	Texture* pPerson1Tex2;
	Texture* pPerson1Tex3;
	Texture* pPerson1Tex4;
	Texture* pPerson2Tex1;
	Texture* pPerson2Tex2;
	Texture* pPerson2Tex3;
	Texture* pPerson2Tex4;

	// create world matrices for each object
	Matrix mBurgerWorld;
	Matrix mCupWorld;
	Matrix mDonutWorld;
	Matrix mForkWorld;
	Matrix mFriesWorld;
	Matrix mHandWorld;
	Matrix mHotDogWorld;
	Matrix mIceCreamWorld;
	Matrix mKnifeWorld;
	Matrix mPlateWorld;
	Matrix mBlanketWorld;
	Matrix mPerson1World;
	Matrix mPerson2World;
	Matrix mSkyWorld;

	Vect burgerPtLtPos;
	Vect cupPtLtPos;
	Vect donutPtLtPos;
	Vect friesPtLtPos;
	Vect hotdogPtLtPos;
	Vect iceCreamPtLtPos;




	/*
ShaderColor*			pShaderCol;

ShaderColorLight*		pShaderColLight;
GraphicObject_Color*	GraphObj1;
GraphicObject_Color*	GraphObj2;
GraphicObject_Texture*  TexGO1;
GraphicObject_Texture*  TexGO2;
GraphicObject_Light*	LightGO1;
GraphicObject_Light*	LightGO2;
*/




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