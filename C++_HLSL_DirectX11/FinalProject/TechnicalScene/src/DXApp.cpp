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
	// First, create all shaders
	pShaderCol = new ShaderColor(md3dDevice);
	pShaderTex = new ShaderTexture(md3dDevice);
	//pShaderColLight = new ShaderColorLight(md3dDevice);
	pShaderColMultiLight = new ShaderColorMultiLight(md3dDevice);
	pShaderColLightTex = new ShaderColorLightTexture(md3dDevice);
	pShaderTexColMultiLight = new ShaderTexColMultiLight(md3dDevice);

	// next create all models
	pUnitBoxRepTex = new Model(md3dDevice, Model::UnitBoxRepeatedTexture);
	pUnitBoxSixTex = new Model(md3dDevice, Model::UnitBoxSixFaceTexture);
	pUnitSphere = new Model(md3dDevice, Model::UnitSphere);
	pUnitTexSphere = new Model(md3dDevice, Model::UnitTexSphere);
	pUnitPyrRepTex = new Model(md3dDevice, Model::UnitPyramidRepeatedTexture);
	pHotDog = new Model(md3dDevice, "../Assets/Models/hotdog.azul");

	// create our graphic objects with our models for each shader
	ColorGO1 = new GraphicObject_Color(pShaderCol, pUnitBoxRepTex);
	ColorGO2 = new GraphicObject_Color(pShaderCol, pUnitBoxSixTex);
	ColorGO3 = new GraphicObject_Color(pShaderCol, pUnitSphere);
	ColorGO4 = new GraphicObject_Color(pShaderCol, pUnitTexSphere);
	ColorGO5 = new GraphicObject_Color(pShaderCol, pUnitPyrRepTex);
	ColorGO6 = new GraphicObject_Color(pShaderCol, pHotDog);

	TexGO1 = new GraphicObject_Texture(pShaderTex, pUnitBoxRepTex);
	TexGO2 = new GraphicObject_Texture(pShaderTex, pUnitBoxSixTex);
	TexGO3 = new GraphicObject_Texture(pShaderTex, pUnitTexSphere);
	TexGO4 = new GraphicObject_Texture(pShaderTex, pUnitPyrRepTex);
	TexGO5 = new GraphicObject_Texture(pShaderTex, pHotDog);

	LightGO1 = new GraphicObject_Light(pShaderColMultiLight, pUnitBoxRepTex);
	LightGO2 = new GraphicObject_Light(pShaderColMultiLight, pUnitBoxSixTex);
	LightGO4 = new GraphicObject_Light(pShaderColMultiLight, pUnitTexSphere);
	LightGO5 = new GraphicObject_Light(pShaderColMultiLight, pUnitPyrRepTex);
	LightGO6 = new GraphicObject_Light(pShaderColMultiLight, pHotDog);

	TexLightGO1 = new GraphicObject_TexLight(pShaderColLightTex, pUnitBoxRepTex);
	TexLightGO2 = new GraphicObject_TexLight(pShaderColLightTex, pUnitBoxSixTex);
	TexLightGO3 = new GraphicObject_TexLight(pShaderColLightTex, pUnitTexSphere);
	TexLightGO4 = new GraphicObject_TexLight(pShaderColLightTex, pUnitPyrRepTex);
	TexLightGO5 = new GraphicObject_TexLight(pShaderColLightTex, pHotDog);

	TexColMultiLightGO1 = new GraphicObject_TexColMultiLight(pShaderTexColMultiLight, pUnitBoxRepTex);
	TexColMultiLightGO2 = new GraphicObject_TexColMultiLight(pShaderTexColMultiLight, pUnitBoxSixTex);
	TexColMultiLightGO3 = new GraphicObject_TexColMultiLight(pShaderTexColMultiLight, pUnitTexSphere);
	TexColMultiLightGO4 = new GraphicObject_TexColMultiLight(pShaderTexColMultiLight, pUnitPyrRepTex);
	TexColMultiLightGO5 = new GraphicObject_TexColMultiLight(pShaderTexColMultiLight, pHotDog);

	// Set the textures and materials for all Graphic Objects
	ColorGO1->SetColor(Colors::Red);
	ColorGO2->SetColor(Colors::Orange);
	ColorGO3->SetColor(Colors::Lime);
	ColorGO4->SetColor(Colors::Green);
	ColorGO5->SetColor(Colors::CornflowerBlue);
	ColorGO6->SetColor(Colors::Purple, 0);
	ColorGO6->SetColor(Colors::LightPink, 1);
	ColorGO6->SetColor(Colors::HotPink, 2);
	ColorGO6->SetColor(Colors::Indigo, 3);

	pTexTex1 = new Texture(md3dDevice, L"../Assets/Textures/CrateFace.tga");
	TexGO1->SetTexture(pTexTex1);
	pTexTex2 = new Texture(md3dDevice, L"../Assets/Textures/Dice.tga");
	TexGO2->SetTexture(pTexTex2);
	pTexTex3 = new Texture(md3dDevice, L"../Assets/Textures/squareWorld.tga");
	TexGO3->SetTexture(pTexTex3);
	pTexTex4 = new Texture(md3dDevice, L"../Assets/Textures/AlignmentTest.tga");
	TexGO4->SetTexture(pTexTex4);
	pTexTex5 = new Texture(md3dDevice, L"../Assets/Textures/hotdog_bun.tga");
	TexGO5->SetTexture(pTexTex5, 0);
	pTexTex6 = new Texture(md3dDevice, L"../Assets/Textures/mustard.tga");
	TexGO5->SetTexture(pTexTex6, 1);
	pTexTex7 = new Texture(md3dDevice, L"../Assets/Textures/hotdog.tga");
	TexGO5->SetTexture(pTexTex7, 2);
	pTexTex8 = new Texture(md3dDevice, L"../Assets/Textures/pickles.tga");
	TexGO5->SetTexture(pTexTex8, 3);

	LightGO1->SetMaterial(Colors::Indigo, Colors::Indigo, Vect(0.1, 0.1, 0.1, 10));
	LightGO2->SetMaterial(Colors::CornflowerBlue, Colors::CornflowerBlue, Vect(0.3, 0.3, 0.3, 30));
	LightGO4->SetMaterial(Colors::Yellow, Colors::Yellow, Vect(0.8, 0.8, 0.8, 80));
	LightGO5->SetMaterial(Colors::Orange, Colors::Orange, Vect(1, 1, 1, 100));
	LightGO6->SetMaterial(Colors::Red, Colors::Red, Vect(1, 1, 1, 100), 0);
	LightGO6->SetMaterial(Colors::Firebrick, Colors::Firebrick, Vect(0.3, 0.3, 0.3, 100), 1);
	LightGO6->SetMaterial(Colors::HotPink, Colors::HotPink, Vect(0.7, 0.7, 0.7, 100), 2);
	LightGO6->SetMaterial(Colors::Magenta, Colors::Magenta, Vect(1, 1, 1, 100), 3);

	pTexLightTex1 = new Texture(md3dDevice, L"../Assets/Textures/CrateFace.tga");
	TexLightGO1->SetTexture(pTexLightTex1);
	TexLightGO1->SetMaterial(Colors::White, Colors::White, Vect(1, 1, 1, 100));
	pTexLightTex2 = new Texture(md3dDevice, L"../Assets/Textures/CubeFaces.tga");
	TexLightGO2->SetTexture(pTexLightTex2);
	TexLightGO2->SetMaterial(Colors::White, Colors::White, Vect(1, 1, 1, 100));
	pTexLightTex3 = new Texture(md3dDevice, L"../Assets/Textures/squareWorld.tga");
	TexLightGO3->SetTexture(pTexLightTex3);
	TexLightGO3->SetMaterial(Colors::White, Colors::White, Vect(1, 1, 1, 100));
	pTexLightTex4 = new Texture(md3dDevice, L"../Assets/Textures/AlignmentTest.tga");
	TexLightGO4->SetTexture(pTexLightTex4);
	TexLightGO4->SetMaterial(Colors::White, Colors::White, Vect(1, 1, 1, 100));
	pTexLightTex5 = new Texture(md3dDevice, L"../Assets/Textures/hotdog_bun.tga");
	pTexLightTex6 = new Texture(md3dDevice, L"../Assets/Textures/mustard.tga");
	pTexLightTex7 = new Texture(md3dDevice, L"../Assets/Textures/hotdog.tga");
	pTexLightTex8 = new Texture(md3dDevice, L"../Assets/Textures/pickles.tga");
	TexLightGO5->SetTexture(pTexLightTex5, 0);
	TexLightGO5->SetTexture(pTexLightTex6, 1);
	TexLightGO5->SetTexture(pTexLightTex7, 2);
	TexLightGO5->SetTexture(pTexLightTex8, 3);
	TexLightGO5->SetMaterial(Colors::Brown, Colors::White, Vect(1, 1, 1, 100), 0);
	TexLightGO5->SetMaterial(Colors::Gold, Colors::White, Vect(1, 1, 1, 100), 1);
	TexLightGO5->SetMaterial(Colors::DeepPink, Colors::White, Vect(1, 1, 1, 100), 2);
	TexLightGO5->SetMaterial(Colors::Green, Colors::White, Vect(1, 1, 1, 100), 3);


	pTexColMultiLightTex1 = new Texture(md3dDevice, L"../Assets/Textures/CrateFace.tga");
	TexColMultiLightGO1->SetTexture(pTexColMultiLightTex1);
	TexColMultiLightGO1->SetMaterial(Colors::White, Colors::White, Vect(1, 1, 1, 100));
	pTexColMultiLightTex2 = new Texture(md3dDevice, L"../Assets/Textures/Dice.tga");
	TexColMultiLightGO2->SetTexture(pTexColMultiLightTex2);
	TexColMultiLightGO2->SetMaterial(Colors::White, Colors::White, Vect(1, 1, 1, 100));
	pTexColMultiLightTex3 = new Texture(md3dDevice, L"../Assets/Textures/squareWorld.tga");
	TexColMultiLightGO3->SetTexture(pTexColMultiLightTex3);
	TexColMultiLightGO3->SetMaterial(Colors::White, Colors::White, Vect(1, 1, 1, 100));
	pTexColMultiLightTex4 = new Texture(md3dDevice, L"../Assets/Textures/AlignmentTest.tga");
	TexColMultiLightGO4->SetTexture(pTexColMultiLightTex4);
	TexColMultiLightGO4->SetMaterial(Colors::White, Colors::White, Vect(1, 1, 1, 100));
	pTexColMultiLightTex5 = new Texture(md3dDevice, L"../Assets/Textures/hotdog_bun.tga");
	pTexColMultiLightTex6 = new Texture(md3dDevice, L"../Assets/Textures/mustard.tga");
	pTexColMultiLightTex7 = new Texture(md3dDevice, L"../Assets/Textures/hotdog.tga");
	pTexColMultiLightTex8 = new Texture(md3dDevice, L"../Assets/Textures/pickles.tga");
	TexColMultiLightGO5->SetTexture(pTexColMultiLightTex5, 0);
	TexColMultiLightGO5->SetTexture(pTexColMultiLightTex6, 1);
	TexColMultiLightGO5->SetTexture(pTexColMultiLightTex7, 2);
	TexColMultiLightGO5->SetTexture(pTexColMultiLightTex8, 3);
	TexColMultiLightGO5->SetMaterial(Colors::White, Colors::White, Vect(0.1, 0.1, 0.1, 100), 0);
	TexColMultiLightGO5->SetMaterial(Colors::White, Colors::White, Vect(0.8, 0.8, 0.8, 100), 1);
	TexColMultiLightGO5->SetMaterial(Colors::White, Colors::White, Vect(0.55, 0.55, 0.55, 300), 2);
	TexColMultiLightGO5->SetMaterial(Colors::White, Colors::White, Vect(0.75, 0.75, 0.75, 100), 3);

	// terrain
	pTerrainTex = new Texture(md3dDevice, L"../Assets/Textures/sandgrass.tga", D3D11_FILTER_MIN_MAG_MIP_LINEAR);
	pTerrain = new TerrainModel(md3dDevice, L"../Assets/Textures/MaryHM.tga", 3500, 300, -300, 30, 30, pTerrainTex, pShaderTexColMultiLight);
	// flat plane
	pPlane = new FlatPlane(md3dDevice, 100, 1, 1);
	// skybox
	//pSkyBoxTex = new Texture(md3dDevice, L"../Assets/Textures/skybox.tga");
	//pSkyBox = new SkyBox(md3dDevice, 400, pSkyBoxTex, pShaderTex);



	// Initialize and set the world matrices for all Graphic Objects
		// create world matrices for each object
	mColWorld1 = Matrix(SCALE, 4.0f, 4.0f, 4.0f) * Matrix(TRANS, 100, 150, 0);
	ColorGO1->SetWorld(mColWorld1);
	mColWorld2 = Matrix(SCALE, 4.0f, 4.0f, 4.0f) * Matrix(TRANS, 100, 140, 0);
	ColorGO2->SetWorld(mColWorld2);
	mColWorld3 = Matrix(SCALE, 4.0f, 4.0f, 4.0f) * Matrix(TRANS, 100, 130, 0);
	ColorGO3->SetWorld(mColWorld3);
	mColWorld4 = Matrix(SCALE, 4.0f, 4.0f, 4.0f) * Matrix(TRANS, 100, 120, 0);
	ColorGO4->SetWorld(mColWorld4);
	mColWorld5 = Matrix(SCALE, 4.0f, 4.0f, 4.0f) * Matrix(TRANS, 100, 110, 0);
	ColorGO5->SetWorld(mColWorld5);
	mColWorld6 = Matrix(SCALE, 1.0f, 1.0f, 1.0f) * Matrix(TRANS, 100, 100, 0);
	ColorGO6->SetWorld(mColWorld6);

	mTexWorld1 = Matrix(SCALE, 4.0f, 4.0f, 4.0f) * Matrix(TRANS, 110, 140, 0);
	TexGO1->SetWorld(mTexWorld1);
	mTexWorld2 = Matrix(SCALE, 4.0f, 4.0f, 4.0f) * Matrix(TRANS, 110, 130, 0);
	TexGO2->SetWorld(mTexWorld2);
	mTexWorld3 = Matrix(SCALE, 4.0f, 4.0f, 4.0f) * Matrix(TRANS, 110, 120, 0);
	TexGO3->SetWorld(mTexWorld3);
	mTexWorld4 = Matrix(SCALE, 4.0f, 4.0f, 4.0f) * Matrix(TRANS, 110, 110, 0);
	TexGO4->SetWorld(mTexWorld4);
	mTexWorld5 = Matrix(SCALE, 1.0f, 1.0f, 1.0f) * Matrix(TRANS, 110, 100, 0);
	TexGO5->SetWorld(mTexWorld5);

	mLightWorld1 = Matrix(SCALE, 4.0f, 4.0f, 4.0f) * Matrix(TRANS, 120, 140, 0);
	LightGO1->SetWorld(mLightWorld1);
	mLightWorld2 = Matrix(SCALE, 4.0f, 4.0f, 4.0f) * Matrix(TRANS, 120, 130, 0);
	LightGO2->SetWorld(mLightWorld2);
	mLightWorld4 = Matrix(SCALE, 4.0f, 4.0f, 4.0f) * Matrix(TRANS, 120, 120, 0);
	LightGO4->SetWorld(mLightWorld4);
	mLightWorld5 = Matrix(SCALE, 4.0f, 4.0f, 4.0f) * Matrix(TRANS, 120, 110, 0);
	LightGO5->SetWorld(mLightWorld5);
	mLightWorld6 = Matrix(SCALE, 1.0f, 1.0f, 1.0f) * Matrix(TRANS, 120, 100, 0);
	LightGO6->SetWorld(mLightWorld6);

	mTexLightWorld1 = Matrix(SCALE, 4.0f, 4.0f, 4.0f) * Matrix(TRANS, 130, 140, 0);
	TexLightGO1->SetWorld(mTexLightWorld1);
	mTexLightWorld2 = Matrix(SCALE, 4.0f, 4.0f, 4.0f) * Matrix(TRANS, 130, 130, 0);
	TexLightGO2->SetWorld(mTexLightWorld2);
	mTexLightWorld3 = Matrix(SCALE, 4.0f, 4.0f, 4.0f) * Matrix(TRANS, 130, 120, 0);
	TexLightGO3->SetWorld(mTexLightWorld3);
	mTexLightWorld4 = Matrix(SCALE, 4.0f, 4.0f, 4.0f) * Matrix(TRANS, 130, 110, 0);
	TexLightGO4->SetWorld(mTexLightWorld4);
	mTexLightWorld5 = Matrix(SCALE, 1.0f, 1.0f, 1.0f) * Matrix(TRANS, 130, 100, 0);
	TexLightGO5->SetWorld(mTexLightWorld5);

	mTexColMultiLightWorld1 = Matrix(SCALE, 4.0f, 4.0f, 4.0f) * Matrix(TRANS, 140, 140, 0);
	TexColMultiLightGO1->SetWorld(mTexColMultiLightWorld1);
	mTexColMultiLightWorld2 = Matrix(SCALE, 4.0f, 4.0f, 4.0f) * Matrix(TRANS, 140, 130, 0);
	TexColMultiLightGO2->SetWorld(mTexColMultiLightWorld2);
	mTexColMultiLightWorld3 = Matrix(SCALE, 4.0f, 4.0f, 4.0f) * Matrix(TRANS, 140, 120, 0);
	TexColMultiLightGO3->SetWorld(mTexColMultiLightWorld3);
	mTexColMultiLightWorld4 = Matrix(SCALE, 4.0f, 4.0f, 4.0f) * Matrix(TRANS, 140, 110, 0);
	TexColMultiLightGO4->SetWorld(mTexColMultiLightWorld4);
	mTexColMultiLightWorld5 = Matrix(SCALE, 1.0f, 1.0f, 1.0f) * Matrix(TRANS, 140, 100, 0);
	TexColMultiLightGO5->SetWorld(mTexColMultiLightWorld5);
	
	
	mPlaneWorld = Matrix(SCALE, 1.0f, 1.0f, 1.0f) * Matrix(ROT_X, 3.1415 / 2) * Matrix(TRANS, 120, 120, -50);
	//mSkyBoxWorld = Matrix(IDENTITY) * Matrix(TRANS, 0, 100, 0);
	//pSkyBox->SetWorld(mSkyBoxWorld);


	lightPos1 = Vect(120, 140, 10);
	lightPos2 = Vect(120, -140, 10);
	lightPos3 = Vect(130, 140, 10);
	lightPos4 = Vect(140, 140, 10);
	lightPos5 = Vect(170, -140, 10);
	lightPos6 = Vect(130, 140, 10);



	// Initialize the projection matrix
	mCam.setPerspective( 3.14159/3, mClientWidth / (float)mClientHeight, 1.0f, 1000.0f);
	mCam.setOrientAndPosition(Vect(0, 1, 0), Vect(120, 120, 0), Vect(120, 125, 80));

	mTimer.Reset();
}

void DXApp::UpdateScene()
{
	// move lights
	lightPos1 *= Matrix(ROT_Z, 0.01);
	lightPos2 *= Matrix(ROT_Z, 0.01);
	lightPos3 *= Matrix(ROT_Z, 0.01);
	lightPos4 *= Matrix(ROT_Z, 0.01);
	lightPos5 *= Matrix(ROT_Z, 0.01);
	lightPos6 *= Matrix(ROT_Z, 0.01);


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
	
	// set the shader, and render the objects
	// Color shaded objects
	pShaderCol->SetToContext(md3dImmediateContext);
	pShaderCol->SendCamMatrices(mCam.getViewMatrix(), mCam.getProjMatrix());
	ColorGO1->Render();
	ColorGO2->Render();
	ColorGO3->Render();
	ColorGO4->Render();
	ColorGO5->Render();
	ColorGO6->Render();

	// Textured Objects
	pShaderTex->SetToContext(md3dImmediateContext);
	pShaderTex->SendCamMatrices(mCam.getViewMatrix(), mCam.getProjMatrix());
	TexGO1->Render();
	TexGO2->Render();
	TexGO3->Render();
	TexGO4->Render();
	TexGO5->Render();
	//pSkyBox->Render(md3dImmediateContext);

	// Multi Light Colored Objects
	pShaderColMultiLight->SetToContext(md3dImmediateContext);
	pShaderColMultiLight->SendCamMatrices(mCam.getViewMatrix(), mCam.getProjMatrix());
	pShaderColMultiLight->SetDirectionalLightParameters(Vect(1, 0, -1).getNorm(),
		0.5 * Vect(1, 1, 1), 1 * Vect(1, 1, 1), Vect(1, 1, 1));
	pShaderColMultiLight->SetPointLightParameters(0, lightPos1, 35, .4 * Vect(0, 1, 0),
		0.5 * Colors::Red, 1 * Colors::Red, 0.3 * Colors::Red);
	pShaderColMultiLight->SetPointLightParameters(1, lightPos2, 35, .4 * Vect(0, 1, 0),
		0.5 * Colors::CornflowerBlue, 1 * Colors::CornflowerBlue, 0.3 * Colors::CornflowerBlue);
	Vect eyepos;
	mCam.getPos(eyepos);
	pShaderColMultiLight->SendLightParameters(eyepos);
	pShaderColMultiLight->SendWorldAndMaterial(mPlaneWorld, Colors::Yellow, 1 * Colors::Yellow, Vect(.7, .7, .7, 100));
	// FOG
	//pShaderColMultiLight->SendFogParameters(10, 35, Colors::HotPink);
	pPlane->Render(md3dImmediateContext);
	LightGO1->Render();
	LightGO2->Render();
	LightGO4->Render();
	LightGO5->Render();
	LightGO6->Render();
	
	// Color Lit Textured Objects 
	pShaderColLightTex->SetToContext(md3dImmediateContext);
	pShaderColLightTex->SendCamMatrices(mCam.getViewMatrix(), mCam.getProjMatrix());
	pShaderColLightTex->SetDirectionalLightParameters(Vect(1, 0, -1).getNorm(),
		0.5 * Vect(1, 1, 1), 1 * Vect(1, 1, 1), Vect(1, 1, 1));
	pShaderColLightTex->SetPointLightParameters(lightPos3, 15, .4 * Vect(0, 1, 0),
		0.5 * Colors::LightSeaGreen, 1 * Colors::LightSeaGreen, 0.3 * Colors::LightSeaGreen);
	mCam.getPos(eyepos);
	pShaderColLightTex->SendLightParameters(eyepos);
	TexLightGO1->Render();
	TexLightGO2->Render();
	TexLightGO3->Render();
	TexLightGO4->Render();
	TexLightGO5->Render();

	// Colored, Textured, and Multi Lit objects
	pShaderTexColMultiLight->SetToContext(md3dImmediateContext);
	pShaderTexColMultiLight->SendCamMatrices(mCam.getViewMatrix(), mCam.getProjMatrix());
	pShaderTexColMultiLight->SetDirectionalLightParameters(Vect(1, 0, -1).getNorm(),
		0.5 * Vect(1, 1, 1), 1 * Vect(1, 1, 1), Vect(1, 1, 1));
	pShaderTexColMultiLight->SetPointLightParameters(0, lightPos4, 15, .4 * Vect(0, 1, 0),
		0.5 * Colors::Orange, 1 * Colors::Orange, 0.3 * Colors::Orange);
	pShaderTexColMultiLight->SetPointLightParameters(1, lightPos5, 15, .4 * Vect(0, 1, 0),
		0.5 * Colors::Maroon, 1 * Colors::Maroon, 0.3 * Colors::Maroon);
	pShaderTexColMultiLight->SetPointLightParameters(2, lightPos6, 15, .4 * Vect(0, 1, 0),
		0.5 * Colors::RosyBrown, 1 * Colors::RosyBrown, 0.3 * Colors::RosyBrown);
	mCam.getPos(eyepos);
	pShaderTexColMultiLight->SendLightParameters(eyepos);
	TexColMultiLightGO1->Render();
	TexColMultiLightGO2->Render();
	TexColMultiLightGO3->Render();
	TexColMultiLightGO4->Render();
	TexColMultiLightGO5->Render();
	pTerrain->Render(md3dImmediateContext);

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
	// delete our shaders
	delete pShaderCol;
	delete pShaderColMultiLight;
	delete pShaderTex;
	delete pShaderColLightTex;
	delete pShaderTexColMultiLight;

	// delete our graphic objects 
	delete ColorGO1;
	delete ColorGO2;
	delete ColorGO3;
	delete ColorGO4;
	delete ColorGO5;
	delete ColorGO6;
	delete TexGO1;
	delete TexGO2;
	delete TexGO3;
	delete TexGO4;
	delete TexGO5;
	delete LightGO1;
	delete LightGO2;
	delete LightGO4;
	delete LightGO5;
	delete LightGO6;
	delete TexLightGO1;
	delete TexLightGO2;
	delete TexLightGO3;
	delete TexLightGO4;
	delete TexLightGO5;
	delete TexColMultiLightGO1;
	delete TexColMultiLightGO2;
	delete TexColMultiLightGO3;
	delete TexColMultiLightGO4;
	delete TexColMultiLightGO5;

	// delete out models 
	delete pUnitBoxRepTex;
	delete pUnitBoxSixTex;
	delete pUnitSphere;
	delete pUnitTexSphere;
	delete pUnitPyrRepTex;
	delete pHotDog;

	// delete our Terrain, Flat plane and SkyBox models
	delete pTerrain;
	delete pPlane;
	//delete pSkyBox;

	// delete textures
	delete pTexTex1;
	delete pTexTex2;
	delete pTexTex3;
	delete pTexTex4;
	delete pTexTex5;
	delete pTexTex6;
	delete pTexTex7;
	delete pTexTex8;
	delete pTexLightTex1;
	delete pTexLightTex2;
	delete pTexLightTex3;
	delete pTexLightTex4;
	delete pTexLightTex5;
	delete pTexLightTex6;
	delete pTexLightTex7;
	delete pTexLightTex8;
	delete pTexColMultiLightTex1;
	delete pTexColMultiLightTex2;
	delete pTexColMultiLightTex3;
	delete pTexColMultiLightTex4;
	delete pTexColMultiLightTex5;
	delete pTexColMultiLightTex6;
	delete pTexColMultiLightTex7;
	delete pTexColMultiLightTex8;
	delete pTerrainTex;
	//delete pSkyBoxTex;
	

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