#include "DXApp.h"
#include <windows.h>
#include <sstream>
#include <assert.h>
#include "d3dUtil.h"

// needed to load shaders from file
#include <d3dcompiler.h>

#include "Model.h"
#include "ShaderColor.h"
#include "DirectXTex.h"
#include "Texture.h"
#include "FlatPlane.h"
#include "TerrainModel.h"
#include "GraphicObject_Color.h"
#include "ShaderTexture.h"
#include "GraphicObject_Texture.h"
// MARY - includes
#include "ShaderColorLight.h"
#include "GraphicObject_Light.h"
#include "ShaderColorLightTexture.h"
#include "GraphicObject_TexLight.h"

void DXApp::InitDemo()
{
	// MARY
	// use my homemade models
	pBurger = new Model(md3dDevice, "../Assets/Models/burger.azul");
	pCup = new Model(md3dDevice, "../Assets/Models/cup.azul");
	pDonut = new Model(md3dDevice, "../Assets/Models/donut.azul");
	pFork = new Model(md3dDevice, "../Assets/Models/fork.azul");
	pFries = new Model(md3dDevice, "../Assets/Models/fries.azul");
	pHand = new Model(md3dDevice, "../Assets/Models/hand.azul");
	pHotDog = new Model(md3dDevice, "../Assets/Models/hotdog.azul");
	pIceCream = new Model(md3dDevice, "../Assets/Models/iceCream.azul");
	pKnife = new Model(md3dDevice, "../Assets/Models/knife.azul");
	pPlate = new Model(md3dDevice, "../Assets/Models/plate.azul");
	pPerson1 = new Model(md3dDevice, "../Assets/Models/person1.azul");
	pPerson2 = new Model(md3dDevice, "../Assets/Models/person2.azul");

	// set the shader to our texture + light shader
	pShaderTexLight = new ShaderTexColMultiLight(md3dDevice);

	// create our graphic objects with our models
	BurgerGO = new GraphicObject_TexColMultiLight(pShaderTexLight, pBurger);
	CupGO = new GraphicObject_TexColMultiLight(pShaderTexLight, pCup);
	DonutGO = new GraphicObject_TexColMultiLight(pShaderTexLight, pDonut);
	ForkGO = new GraphicObject_TexColMultiLight(pShaderTexLight, pFork);
	FriesGO = new GraphicObject_TexColMultiLight(pShaderTexLight, pFries);
	HandGO = new GraphicObject_TexColMultiLight(pShaderTexLight, pHand);
	HotDogGO = new GraphicObject_TexColMultiLight(pShaderTexLight, pHotDog);
	IceCreamGO = new GraphicObject_TexColMultiLight(pShaderTexLight, pIceCream);
	KnifeGO = new GraphicObject_TexColMultiLight(pShaderTexLight, pKnife);
	PlateGO = new GraphicObject_TexColMultiLight(pShaderTexLight, pPlate);
	Person1GO = new GraphicObject_TexColMultiLight(pShaderTexLight, pPerson1);
	Person2GO = new GraphicObject_TexColMultiLight(pShaderTexLight, pPerson2);

	// Set the textures and materials for all Graphic Objects
	
	// BURGER
	pBurgerTex1 = new Texture(md3dDevice, L"../Assets/Textures/lettuce.tga");
	pBurgerTex2 = new Texture(md3dDevice, L"../Assets/Textures/burger_buns.tga");
	pBurgerTex3 = new Texture(md3dDevice, L"../Assets/Textures/burgers.tga");
	pBurgerTex4 = new Texture(md3dDevice, L"../Assets/Textures/tomato.tga");
	// setting BURGER textures
	BurgerGO->SetTexture(pBurgerTex1, 0);
	BurgerGO->SetTexture(pBurgerTex2, 1);
	BurgerGO->SetTexture(pBurgerTex3, 2);
	BurgerGO->SetTexture(pBurgerTex4, 3);
	BurgerGO->SetMaterial(Colors::White, Colors::White, Vect(0.45, 0.45, 0.45, 300));

	// CUP
	pCupTex1 = new Texture(md3dDevice, L"../Assets/Textures/cup.tga");
	pCupTex2 = new Texture(md3dDevice, L"../Assets/Textures/cup_lid.tga");
	pCupTex3 = new Texture(md3dDevice, L"../Assets/Textures/straw.tga");
	// setting CUP textures
	CupGO->SetTexture(pCupTex1, 0);
	CupGO->SetTexture(pCupTex2, 1);
	CupGO->SetTexture(pCupTex3, 2);
	CupGO->SetMaterial(Colors::White, Colors::White, Vect(0.65, 0.65, 0.65, 100), 0);
	CupGO->SetMaterial(Colors::White, Colors::White, Vect(0.9, 0.9, 0.9, 80), 1);
	CupGO->SetMaterial(Colors::White, Colors::White, Vect(0.8, 0.8, 0.8, 200), 2);

	// DONUT
	pDonutTex1 = new Texture(md3dDevice, L"../Assets/Textures/donut_swirl.tga");
	pDonutTex2 = new Texture(md3dDevice, L"../Assets/Textures/donut_icing.tga");
	pDonutTex3 = new Texture(md3dDevice, L"../Assets/Textures/donut.tga");
	// setting DONUT textures
	DonutGO->SetTexture(pDonutTex1, 0);
	DonutGO->SetTexture(pDonutTex2, 1);
	DonutGO->SetTexture(pDonutTex3, 2);
	DonutGO->SetMaterial(Colors::White, Colors::White, Vect(1, 1, 1, 100), 0);
	DonutGO->SetMaterial(Colors::White, Colors::White, Vect(1, 1, 1, 200), 1);
	DonutGO->SetMaterial(Colors::White, Colors::White, Vect(0.1, 0.1, 0.1, 200), 2);

	// FORK
	pForkTex1 = new Texture(md3dDevice, L"../Assets/Textures/utensil.tga");
	// setting FORK textures
	ForkGO->SetTexture(pForkTex1, 0);
	ForkGO->SetMaterial(Colors::White, Colors::White, Vect(1, 1, 1, 500));

	// FRIES
	pFriesTex1 = new Texture(md3dDevice, L"../Assets/Textures/fries.tga");
	pFriesTex2 = new Texture(md3dDevice, L"../Assets/Textures/fry_container.tga");
	// setting FRIES textures
	FriesGO->SetTexture(pFriesTex1, 0);
	FriesGO->SetTexture(pFriesTex2, 1);
	FriesGO->SetMaterial(Colors::White, Colors::White, Vect(0.5, 0.5, 0.5, 10), 0);
	FriesGO->SetMaterial(Colors::White, Colors::White, Vect(1, 1, 1, 100), 1);

	// HAND
	pHandTex1 = new Texture(md3dDevice, L"../Assets/Textures/hand_w_freckles.tga");
	pHandTex2 = new Texture(md3dDevice, L"../Assets/Textures/nails.tga");
	pHandTex3 = new Texture(md3dDevice, L"../Assets/Textures/ring.tga");
	pHandTex4 = new Texture(md3dDevice, L"../Assets/Textures/diamond.tga");
	// setting HAND textures
	HandGO->SetTexture(pHandTex1, 0);
	HandGO->SetTexture(pHandTex2, 1);
	HandGO->SetTexture(pHandTex3, 2);
	HandGO->SetTexture(pHandTex4, 3);
	HandGO->SetMaterial(Colors::White, Colors::White, Vect(0.05, 0.05, 0.05, 300), 0);
	HandGO->SetMaterial(Colors::Silver, Colors::White, Vect(1, 1, 1, 50), 1);
	HandGO->SetMaterial(Colors::White, Colors::White, Vect(0.75, 0.75, 0.75, 300), 2);
	HandGO->SetMaterial(Colors::LightSalmon, Colors::White, Vect(1, 1, 1, 50), 3);

	// HOTDOG
	pHotDogTex1 = new Texture(md3dDevice, L"../Assets/Textures/hotdog_bun.tga");
	pHotDogTex2 = new Texture(md3dDevice, L"../Assets/Textures/mustard.tga");
	pHotDogTex3 = new Texture(md3dDevice, L"../Assets/Textures/hotdog.tga");
	pHotDogTex4 = new Texture(md3dDevice, L"../Assets/Textures/pickles.tga");
	// setting HOTDOG textures
	HotDogGO->SetTexture(pHotDogTex1, 0);
	HotDogGO->SetTexture(pHotDogTex2, 1);
	HotDogGO->SetTexture(pHotDogTex3, 2);
	HotDogGO->SetTexture(pHotDogTex4, 3);
	HotDogGO->SetMaterial(Colors::White, Colors::White, Vect(0.1, 0.1, 0.1, 100), 0);
	HotDogGO->SetMaterial(Colors::White, Colors::White, Vect(0.8, 0.8, 0.8, 100), 1);
	HotDogGO->SetMaterial(Colors::White, Colors::White, Vect(0.55, 0.55, 0.55, 300), 2);
	HotDogGO->SetMaterial(Colors::White, Colors::White, Vect(0.75, 0.75, 0.75, 100), 3);

	// ICECREAM
	pIceCreamTex1 = new Texture(md3dDevice, L"../Assets/Textures/iceCream.tga");
	pIceCreamTex2 = new Texture(md3dDevice, L"../Assets/Textures/cone.tga");
	pIceCreamTex3 = new Texture(md3dDevice, L"../Assets/Textures/sprinkles.tga");
	// setting ICECREAM textures
	IceCreamGO->SetTexture(pIceCreamTex1, 0);
	IceCreamGO->SetTexture(pIceCreamTex2, 1);
	IceCreamGO->SetTexture(pIceCreamTex3, 2);
	IceCreamGO->SetMaterial(Colors::White, Colors::White, Vect(0.8, 0.8, 0.8, 100), 0);
	IceCreamGO->SetMaterial(Colors::White, Colors::White, Vect(0.3, 0.3, 0.3, 200), 1);
	IceCreamGO->SetMaterial(Colors::White, Colors::White, Vect(0.7, 0.7, 0.7, 200), 2);

	// KNIFE
	pKnifeTex1 = new Texture(md3dDevice, L"../Assets/Textures/utensil.tga");
	// setting KNIFE textures
	KnifeGO->SetTexture(pKnifeTex1, 0);
	KnifeGO->SetMaterial(Colors::Silver, Colors::White, Vect(1, 1, 1, 10));

	// PLATE
	pPlateTex1 = new Texture(md3dDevice, L"../Assets/Textures/plate.tga");
	// setting PLATE textures
	PlateGO->SetTexture(pPlateTex1, 0);
	PlateGO->SetMaterial(Colors::White, Colors::White, Vect(1, 1, 1, 90));

	// BLANKET
	pBlanketTex1 = new Texture(md3dDevice, L"../Assets/Textures/picnic_blanket.tga", D3D11_FILTER_MIN_MAG_MIP_LINEAR);
	pBlanket = new TerrainModel(md3dDevice, L"../Assets/Textures/MaryHM.tga", 150, 60, -3, 6, 6, pBlanketTex1, pShaderTexLight);

	// SKYBOX
	pShaderTex = new ShaderTexture(md3dDevice);
	pSkyBoxTex1 = new Texture(md3dDevice, L"../Assets/Textures/skybox_new.tga");
	pSkyBox = new SkyBox(md3dDevice, 400, pSkyBoxTex1, pShaderTex);

	// PERSON1
	pPerson1Tex1 = new Texture(md3dDevice, L"../Assets/Textures/scrunchie1.tga");
	pPerson1Tex2 = new Texture(md3dDevice, L"../Assets/Textures/hair1.tga");
	pPerson1Tex3 = new Texture(md3dDevice, L"../Assets/Textures/body1.tga");
	pPerson1Tex4 = new Texture(md3dDevice, L"../Assets/Textures/sunglasses1.tga");
	// setting PERSON1 textures
	Person1GO->SetTexture(pPerson1Tex1, 0);
	Person1GO->SetTexture(pPerson1Tex2, 1);
	Person1GO->SetTexture(pPerson1Tex3, 2);
	Person1GO->SetTexture(pPerson1Tex4, 3);
	Person1GO->SetMaterial(Colors::White, Colors::White, Vect(0.0, 0.0, 0.0, 100), 0);
	Person1GO->SetMaterial(Colors::White, Colors::White, Vect(0.8, 0.8, 0.8, 100), 1);
	Person1GO->SetMaterial(Colors::White, Colors::White, Vect(0.55, 0.55, 0.55, 70), 2);
	Person1GO->SetMaterial(Colors::White, Colors::White, Vect(1.0, 1.0, 1.0, 10), 3);

	// PERSON2
	pPerson2Tex1 = new Texture(md3dDevice, L"../Assets/Textures/scrunchie2.tga");
	pPerson2Tex2 = new Texture(md3dDevice, L"../Assets/Textures/hair2.tga");
	pPerson2Tex3 = new Texture(md3dDevice, L"../Assets/Textures/body2.tga");
	pPerson2Tex4 = new Texture(md3dDevice, L"../Assets/Textures/sunglasses2.tga");
	// setting PERSON2 textures
	Person2GO->SetTexture(pPerson2Tex1, 0);
	Person2GO->SetTexture(pPerson2Tex2, 1);
	Person2GO->SetTexture(pPerson2Tex3, 2);
	Person2GO->SetTexture(pPerson2Tex4, 3);
	Person2GO->SetMaterial(Colors::White, Colors::White, Vect(0.0, 0.0, 0.0, 100), 0);
	Person2GO->SetMaterial(Colors::White, Colors::White, Vect(0.8, 0.8, 0.8, 100), 1);
	Person2GO->SetMaterial(Colors::White, Colors::White, Vect(0.55, 0.55, 0.55, 70), 2);
	Person2GO->SetMaterial(Colors::White, Colors::White, Vect(1.0, 1.0, 1.0, 100), 3);


	// Initialize and set the world matrices for all Graphic Objects
	mBurgerWorld = Matrix(SCALE, 4.0f, 4.0f, 4.0f) * Matrix(TRANS, -60, -5.5, -34.6);
	BurgerGO->SetWorld(mBurgerWorld);
	mCupWorld = Matrix(SCALE, 5.0f, 4.2f, 5.0f) * Matrix(TRANS, 0, -12.5, -60);
	CupGO->SetWorld(mCupWorld);
	mDonutWorld = Matrix(SCALE, 3.6f, 3.6f, 3.6f) * Matrix(TRANS, 60, -10.5, -34.6);
	DonutGO->SetWorld(mDonutWorld);
	mFriesWorld = Matrix(SCALE, 4.3f, 4.3f, 4.3f) * Matrix(ROT_Y, 50) * Matrix(TRANS, 60, -5.5, 34.6);
	FriesGO->SetWorld(mFriesWorld);
	mHotDogWorld = Matrix(SCALE, 3.6f, 3.6f, 3.6f) * Matrix(ROT_Y, 10) * Matrix(TRANS, 0, -5.5, 60);
	HotDogGO->SetWorld(mHotDogWorld);
	mIceCreamWorld = Matrix(SCALE, 4.3f, 4.0f, 4.3f) * Matrix(TRANS, -60, -5.5, 34.6);
	IceCreamGO->SetWorld(mIceCreamWorld);

	mForkWorld = Matrix(SCALE, 3.5f, 3.5f, 3.5f) * Matrix(TRANS, 0, -9.0, 0);
	ForkGO->SetWorld(mForkWorld);
	mKnifeWorld = Matrix(SCALE, 3.5f, 3.5f, 3.5f) * Matrix(TRANS, 0, -8.0, 0);
	KnifeGO->SetWorld(mKnifeWorld);
	mPlateWorld = Matrix(SCALE, 3.5f, 3.5f, 3.5f) * Matrix(TRANS, 0, -10.5, 0);
	PlateGO->SetWorld(mPlateWorld);

	mHandWorld = Matrix(SCALE, 4.3f, 4.3f, 4.3f) * Matrix(TRANS, -60, 35, -34.6);
	HandGO->SetWorld(mHandWorld);

	mSkyWorld = (Matrix(IDENTITY) * Matrix(TRANS, 0, 100, 0));
	pSkyBox->SetWorld(mSkyWorld);

	mPerson1World = Matrix(SCALE, 5.8f, 5.8f, 5.8f) * Matrix(ROT_Y, -80) * Matrix(TRANS, -88, 0, 0);
	Person1GO->SetWorld(mPerson1World);
	mPerson2World = Matrix(SCALE, 5.8f, 5.8f, 5.8f) * Matrix(ROT_Y, 80) * Matrix(TRANS, 88, 0, 0);
	Person2GO->SetWorld(mPerson2World);


	// initialize positions for the point lights so they can move
	burgerPtLtPos = Vect(-60, 15, -34.6);
	cupPtLtPos = Vect(0, 15, -60);
	donutPtLtPos = Vect(60, 15, -34.6);
	friesPtLtPos = Vect(60, 15, 34.6);
	hotdogPtLtPos = Vect(0, 15, 60);
	iceCreamPtLtPos = Vect(-60, 15, 34.6);


	// Initialize the projection matrix
	mCam.setPerspective( 3.14159/3, mClientWidth / (float)mClientHeight, 1.0f, 1000.0f);
	mCam.setOrientAndPosition(Vect(0, 1, 0), Vect(0, 10, 0), Vect(20, 130, 150));

	mTimer.Reset();
}

void DXApp::UpdateScene()
{
	mHandWorld *= Matrix(ROT_Y, -0.01);
	HandGO->SetWorld(mHandWorld);

	burgerPtLtPos *= Matrix(ROT_Y, 0.002);
	cupPtLtPos *= Matrix(ROT_Y, 0.002);
	donutPtLtPos *= Matrix(ROT_Y, 0.002);
	friesPtLtPos *= Matrix(ROT_Y, 0.002);
	hotdogPtLtPos *= Matrix(ROT_Y, 0.002);
	iceCreamPtLtPos *= Matrix(ROT_Y, 0.002);

	float camSpeed = 0.4f;
	if (GetKeyState('W') & 0x08000)
	{
		mCam.TranslateFwdBack(camSpeed);
	}
	else if (GetKeyState('S') & 0x08000)
	{
		mCam.TranslateFwdBack(-camSpeed);
	}

	if (GetKeyState('A') & 0x08000)
	{
		mCam.TranslateLeftRight(-camSpeed);
	}
	else if (GetKeyState('D') & 0x08000)
	{
		mCam.TranslateLeftRight(camSpeed);
	}

	float rotSpeed = 0.05f;
	if (GetKeyState(VK_LEFT) & 0x08000)
	{
		mCam.TurnLeftRight(rotSpeed);
	}
	else if (GetKeyState(VK_RIGHT) & 0x08000)
	{
		mCam.TurnLeftRight(-rotSpeed);
	}

	if (GetKeyState(VK_UP) & 0x08000)
	{
		mCam.TiltUpDown(rotSpeed);
	}
	else if (GetKeyState(VK_DOWN) & 0x08000)
	{
		mCam.TiltUpDown(-rotSpeed);
	}

	mCam.updateCamera();
}

void DXApp::DrawScene()
{
	md3dImmediateContext->ClearRenderTargetView(mRenderTargetView, VasA(BackgroundColor));
	md3dImmediateContext->ClearDepthStencilView(mpDepthStencilView, D3D11_CLEAR_DEPTH, 1.0f, 0);
	
	// set the shaders to context and render the graphic objects
	pShaderTexLight->SetToContext(md3dImmediateContext);
	pShaderTexLight->SendCamMatrices(mCam.getViewMatrix(), mCam.getProjMatrix());
	// We need to set the Lights
	pShaderTexLight->SetDirectionalLightParameters(Vect(-1, -1, 0).getNorm(),
		0.3 * Vect(1, 1, 1), 1 * Vect(1, 1, 1), Vect(1, 1, 1));
	// burger point light
	pShaderTexLight->SetPointLightParameters(1, burgerPtLtPos, 6.5, .4 * Vect(0, 1, 0),
		.3 * Colors::Red, 1 * Colors::Red, 0.3 * Colors::Red);
	// cup point light
	pShaderTexLight->SetPointLightParameters(2, cupPtLtPos, 6.5, .4 * Vect(0, 1, 0),
		.3 * Colors::Teal, 1 * Colors::Teal, 0.3 * Colors::Teal);
	// donut point light
	pShaderTexLight->SetPointLightParameters(3, donutPtLtPos, 6.5, .4 * Vect(0, 1, 0),
		.3 * Colors::HotPink, 1 * Colors::HotPink, 0.3 * Colors::HotPink);
	// fries point light
	pShaderTexLight->SetPointLightParameters(4, friesPtLtPos, 6.5, .4 * Vect(0, 1, 0),
		.3 * Colors::Yellow, 1 * Colors::Yellow, 0.3 * Colors::Yellow);
	// hotdog point light
	pShaderTexLight->SetPointLightParameters(5, hotdogPtLtPos, 6.5, .4 * Vect(0, 1, 0),
		.3 * Colors::Green, 1 * Colors::Green, 0.3 * Colors::Green);
	// ice cream point light
	pShaderTexLight->SetPointLightParameters(6, iceCreamPtLtPos, 6.5, .4 * Vect(0, 1, 0),
		.3 * Colors::DarkViolet, 1 * Colors::DarkViolet, 0.3 * Colors::DarkViolet);
	// plate point light
	pShaderTexLight->SetPointLightParameters(7, Vect(0, 0, 0), 7.5, .4 * Vect(0, 1, 0),
		.5 * Vect(1, 1, 1), 1 * Vect(1, 1, 1), 1 * Vect(1, 1, 1));
	Vect eyepos;
	mCam.getPos(eyepos);
	pShaderTexLight->SendLightParameters(eyepos);
	
	BurgerGO->Render();
	CupGO->Render();
	DonutGO->Render();
	ForkGO->Render();
	FriesGO->Render();
	HandGO->Render();
	HotDogGO->Render();
	IceCreamGO->Render();
	KnifeGO->Render();
	PlateGO->Render();
	Person1GO->Render();
	Person2GO->Render();

	pBlanket->Render(md3dImmediateContext);

	pShaderTex->SetToContext(md3dImmediateContext);
	pShaderTex->SendCamMatrices(mCam.getViewMatrix(), mCam.getProjMatrix());
	pSkyBox->Render(md3dImmediateContext);
	

	// Switches the display to show the now-finished back-buffer
	mSwapChain->Present(SyncInterval, 0);
}


DXApp::DXApp(HWND hwnd)
{
	assert(hwnd);
	mhMainWnd = hwnd;

	BackgroundColor = Colors::MidnightBlue;

	md3dDevice = nullptr;
	md3dImmediateContext = nullptr;
	mSwapChain = nullptr;
	mRenderTargetView = nullptr;

	// Get window data through the window handle
	RECT rc;
	BOOL err = GetClientRect(mhMainWnd, &rc);  // Seriously MS: Redifining BOOL as int? Confusing much?
	assert(err);

	// get width/hight
	mClientWidth = rc.right - rc.left;
	mClientHeight = rc.bottom - rc.top;

	// Get window caption
	const int MAX_LABEL_LENGTH = 100; // probably overkill...
	CHAR str[MAX_LABEL_LENGTH];
	GetWindowText(mhMainWnd, str, MAX_LABEL_LENGTH);
	mMainWndCaption = str;

	// Initialize DX11
	this->InitDirect3D();

	// Demo initialization
	this->InitDemo();
}

DXApp::~DXApp()
{
	delete pShaderTexLight;
	delete pShaderTex;

	delete BurgerGO;
	delete CupGO;
	delete DonutGO;
	delete ForkGO;
	delete FriesGO;
	delete HandGO;
	delete HotDogGO;
	delete IceCreamGO;
	delete KnifeGO;
	delete PlateGO;
	delete Person1GO;
	delete Person2GO;

	delete pBurger;
	delete pCup;
	delete pDonut;
	delete pFork;
	delete pFries;
	delete pHand;
	delete pHotDog;
	delete pIceCream;
	delete pKnife;
	delete pPlate;
	delete pPerson1;
	delete pPerson2;
	delete pBlanket;
	delete pSkyBox;

	delete pBurgerTex1;
	delete pBurgerTex2;
	delete pBurgerTex3;
	delete pBurgerTex4;
	delete pCupTex1;
	delete pCupTex2;
	delete pCupTex3;
	delete pDonutTex1;
	delete pDonutTex2;
	delete pDonutTex3;
	delete pForkTex1;
	delete pFriesTex1;
	delete pFriesTex2;
	delete pHandTex1;
	delete pHandTex2;
	delete pHandTex3;
	delete pHandTex4;
	delete pHotDogTex1;
	delete pHotDogTex2;
	delete pHotDogTex3;
	delete pHotDogTex4;
	delete pIceCreamTex1;
	delete pIceCreamTex2;
	delete pIceCreamTex3;
	delete pKnifeTex1;
	delete pPlateTex1;
	delete pBlanketTex1;
	delete pSkyBoxTex1;

	delete pPerson1Tex1;
	delete pPerson1Tex2;
	delete pPerson1Tex3;
	delete pPerson1Tex4;
	delete pPerson2Tex1;
	delete pPerson2Tex2;
	delete pPerson2Tex3;
	delete pPerson2Tex4;


	ReleaseAndDeleteCOMobject(mRenderTargetView);
	ReleaseAndDeleteCOMobject(mpDepthStencilView);
	ReleaseAndDeleteCOMobject(mSwapChain);
	ReleaseAndDeleteCOMobject(md3dImmediateContext);

	// Must be done BEFORE the device is released
	ReportLiveDXObjects();		// See http://masterkenth.com/directx-leak-debugging/

	ReleaseAndDeleteCOMobject(md3dDevice);
}

// See http://masterkenth.com/directx-leak-debugging/
void DXApp::ReportLiveDXObjects()
{
#ifdef _DEBUG
	HRESULT hr = S_OK;

	// Now we set up the Debug interface, to be queried on shutdown
	ID3D11Debug* debugDev;
	hr = md3dDevice->QueryInterface(__uuidof(ID3D11Debug), reinterpret_cast<void**>(&debugDev));

	debugDev->ReportLiveDeviceObjects(D3D11_RLDO_DETAIL);
	ReleaseAndDeleteCOMobject(debugDev);
#endif
}

void DXApp::InitDirect3D()
{
	HRESULT hr = S_OK;

	UINT createDeviceFlags = 0;
#ifdef _DEBUG
	createDeviceFlags |= D3D11_CREATE_DEVICE_DEBUG;
#endif

	// This is a *greatly* simplified process to create a DX device and context:
	// We force the use of DX11 feature level since that's what CDM labs are limited to.
	// For real-life applications would need to test what's the best feature level and act accordingly
	hr = D3D11CreateDevice(nullptr, D3D_DRIVER_TYPE_HARDWARE, nullptr, createDeviceFlags, nullptr, 0, D3D11_SDK_VERSION, &md3dDevice, nullptr, &md3dImmediateContext);
	assert(SUCCEEDED(hr));

	// Now we obtain the associated DXGIfactory1 with our device 
	// Many steps...
	IDXGIDevice* dxgiDevice = nullptr;
	hr = md3dDevice->QueryInterface(__uuidof(IDXGIDevice), reinterpret_cast<void**>(&dxgiDevice));
	assert(SUCCEEDED(hr));

	IDXGIAdapter* adapter = nullptr;
	hr = dxgiDevice->GetAdapter(&adapter);
	assert(SUCCEEDED(hr));

	IDXGIFactory1* dxgiFactory1 = nullptr;
	hr = adapter->GetParent(__uuidof(IDXGIFactory1), reinterpret_cast<void**>(&dxgiFactory1));
	assert(SUCCEEDED(hr));
	// See also note on weird stuff with factories and swap chains (1s and 2s)
	// https://msdn.microsoft.com/en-us/library/windows/desktop/jj863687(v=vs.85).aspx

	// We are done with these now...
	ReleaseAndDeleteCOMobject(adapter);
	ReleaseAndDeleteCOMobject(dxgiDevice);

	// Controls MSAA option:
	// - 4x count level garanteed for all DX11 
	// - MUST be the same for depth buffer!
	// - We _need_ to work with the depth buffer because reasons... (see below)
	DXGI_SAMPLE_DESC sampDesc;
	sampDesc.Count = 1;
	sampDesc.Quality = static_cast<UINT>(D3D11_CENTER_MULTISAMPLE_PATTERN);  // MS: what's with the type mismtach?

	DXGI_MODE_DESC buffdesc;				// https://msdn.microsoft.com/en-us/library/windows/desktop/bb173064(v=vs.85).aspx
	ZeroMemory(&buffdesc, sizeof(buffdesc));
	buffdesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;

	// Next we create a swap chain. 
	// Useful thread: http://stackoverflow.com/questions/27270504/directx-creating-the-swapchain
	// Note that this is for a DirectX 11.0: in a real app, we should test the feature levels and act accordingly

	DXGI_SWAP_CHAIN_DESC sd;				// See MSDN: https://msdn.microsoft.com/en-us/library/windows/desktop/bb173075(v=vs.85).aspx
	ZeroMemory(&sd, sizeof(sd));
	sd.BufferCount = 2;						// Much confusion about this number... see http://www.gamedev.net/topic/633807-swap-chain-buffer-count/
	sd.BufferDesc = buffdesc;
	sd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	sd.OutputWindow = mhMainWnd;
	sd.SampleDesc = sampDesc;
	sd.Windowed = TRUE;

	hr = dxgiFactory1->CreateSwapChain(md3dDevice, &sd, &mSwapChain);
	assert(SUCCEEDED(hr));
	ReleaseAndDeleteCOMobject(dxgiFactory1);

	// Create a render target view		https://msdn.microsoft.com/en-us/library/windows/desktop/ff476582(v=vs.85).aspx
	ID3D11Texture2D* pBackBuffer = nullptr;
	hr = mSwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), reinterpret_cast<void**>(&pBackBuffer));
	assert(SUCCEEDED(hr));;

	hr = md3dDevice->CreateRenderTargetView(pBackBuffer, nullptr, &mRenderTargetView);
	ReleaseAndDeleteCOMobject(pBackBuffer);
	assert(SUCCEEDED(hr));

	/**********************************************************/

	// First we fix what it means for triangles to be front facing.
	// Requires setting a whole new rasterizer state
	//*
	D3D11_RASTERIZER_DESC rd;
	rd.FillMode = D3D11_FILL_SOLID;  // Also: D3D11_FILL_WIREFRAME
	rd.CullMode = D3D11_CULL_BACK;
	rd.FrontCounterClockwise = true; // true for RH forward facing
	rd.DepthBias = 0;
	rd.SlopeScaledDepthBias = 0.0f;
	rd.DepthBiasClamp = 0.0f;
	rd.DepthClipEnable = true;
	rd.ScissorEnable = false;
	rd.MultisampleEnable = true;  // Does not in fact turn on/off multisample: https://msdn.microsoft.com/en-us/library/windows/desktop/ff476198(v=vs.85).aspx
	rd.AntialiasedLineEnable = true;

	ID3D11RasterizerState* rs;
	md3dDevice->CreateRasterizerState(&rd, &rs);

	md3dImmediateContext->RSSetState(rs);
	ReleaseAndDeleteCOMobject(rs); // we can release this resource since we won't be changing it any further
	//*/

	// We must turn on the abilty to process depth during rendering.
	// Done through depth stencils (see https://msdn.microsoft.com/en-us/library/windows/desktop/bb205074(v=vs.85).aspx)
	// Below is a simplified version
	//*
	D3D11_TEXTURE2D_DESC descDepth;
	descDepth.Width = mClientWidth;
	descDepth.Height = mClientHeight;
	descDepth.MipLevels = 1;
	descDepth.ArraySize = 1;
	descDepth.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
	descDepth.SampleDesc = sampDesc;
	descDepth.Usage = D3D11_USAGE_DEFAULT;
	descDepth.BindFlags = D3D11_BIND_DEPTH_STENCIL;
	descDepth.CPUAccessFlags = 0;
	descDepth.MiscFlags = 0;

	ID3D11Texture2D* pDepthStencil;
	hr = md3dDevice->CreateTexture2D(&descDepth, NULL, &pDepthStencil);
	assert(SUCCEEDED(hr));

	// Create the depth stencil view
	D3D11_DEPTH_STENCIL_VIEW_DESC descDSV;
	ZeroMemory(&descDSV, sizeof(descDSV));
	descDSV.Format = descDepth.Format;
	descDSV.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2DMS;
	descDSV.Texture2D.MipSlice = 0;;

	hr = md3dDevice->CreateDepthStencilView(pDepthStencil, &descDSV, &mpDepthStencilView);
	assert(SUCCEEDED(hr));
	ReleaseAndDeleteCOMobject(pDepthStencil);
	//*/

	/**********************************************************/

	//md3dImmediateContext->OMSetRenderTargets(1, &mRenderTargetView, nullptr);  // to use without depth stencil
	md3dImmediateContext->OMSetRenderTargets(1, &mRenderTargetView, mpDepthStencilView);

	// Setup the viewport
	D3D11_VIEWPORT vp;
	vp.Width = (FLOAT)mClientWidth;
	vp.Height = (FLOAT)mClientHeight;
	vp.MinDepth = 0.0f;
	vp.MaxDepth = 1.0f;
	vp.TopLeftX = 0;
	vp.TopLeftY = 0;
	md3dImmediateContext->RSSetViewports(1, &vp);
}

void DXApp::CalculateFrameStats()
{
	// Code computes the average frames per second, and also the 
	// average time it takes to render one frame.  These stats 
	// are appended to the window caption bar.

	static int frameCnt = 0;
	static float timeElapsed = 0.0f;

	frameCnt++;

	// Compute averages over one second period.
	if ((mTimer.TotalTime() - timeElapsed) >= 1.0f)
	{
		float fps = (float)frameCnt; // fps = frameCnt / 1
		float mspf = 1000.0f / fps;

		std::ostringstream outs;
		outs.precision(6);
		outs << mMainWndCaption << "    "
			<< "FPS: " << fps << "    "
			<< "Frame Time: " << mspf << " (ms)";
		SetWindowText(mhMainWnd, outs.str().c_str());

		// Reset for next average.
		frameCnt = 0;
		timeElapsed += 1.0f;
	}
}

void DXApp::FrameTick()
{
	mTimer.Tick();
	CalculateFrameStats();

	this->UpdateScene();
	this->DrawScene();
}

void DXApp::OnMouseDown(WPARAM btnState, int xval, int yval)
{
	UNREFERENCED_PARAMETER(btnState);
	UNREFERENCED_PARAMETER(xval);
	UNREFERENCED_PARAMETER(yval);
}

void DXApp::OnMouseUp(WPARAM btnState, int xval, int yval)
{
	UNREFERENCED_PARAMETER(btnState);
	UNREFERENCED_PARAMETER(xval);
	UNREFERENCED_PARAMETER(yval);
}

void DXApp::OnMouseMove(WPARAM btnState, int xval, int yval)
{
	UNREFERENCED_PARAMETER(btnState);
	UNREFERENCED_PARAMETER(xval);
	UNREFERENCED_PARAMETER(yval);
}

void  DXApp::OnMouseWheel(short delta)
{
	UNREFERENCED_PARAMETER(delta);
}


// Shader loading utility. Will be moved elsewhere later...
// Needs to be moved. Requires
HRESULT DXApp::CompileShaderFromFile(WCHAR* szFileName, LPCSTR szEntryPoint, LPCSTR szShaderModel, ID3DBlob** ppBlobOut)
{
	HRESULT hr = S_OK;

	DWORD dwShaderFlags = D3DCOMPILE_ENABLE_STRICTNESS;
#ifdef _DEBUG
	// Set the D3DCOMPILE_DEBUG flag to embed debug information in the shaders.
	// Setting this flag improves the shader debugging experience, but still allows 
	// the shaders to be optimized and to run exactly the way they will run in 
	// the release configuration of this program.
	dwShaderFlags |= D3DCOMPILE_DEBUG;

	// Disable optimizations to further improve shader debugging
	dwShaderFlags |= D3DCOMPILE_SKIP_OPTIMIZATION;
#endif

	ID3DBlob* pErrorBlob = nullptr;
	hr = D3DCompileFromFile(szFileName, nullptr, nullptr, szEntryPoint, szShaderModel, dwShaderFlags, 0, ppBlobOut, &pErrorBlob);
	if (FAILED(hr))
	{
		if (pErrorBlob)
		{
			OutputDebugStringA(reinterpret_cast<const char*>(pErrorBlob->GetBufferPointer()));
			pErrorBlob->Release();
		}
		return hr;
	}
	if (pErrorBlob) pErrorBlob->Release();

	return S_OK;
}