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
	pShaderCol = new ShaderColor(md3dDevice);

	// MARY
	// use my homemade model
	pModel1 = new Model(md3dDevice, "../Assets/Models/blender_ice_cream1.azul");
	pModel2 = new Model(md3dDevice, Model::UnitBoxSixFaceTexture);

	// DEMO 1
	GraphObj1 = new GraphicObject_Color(pShaderCol, pModel1);
	GraphObj1->SetColor(Colors::Tan, 0);
	GraphObj1->SetColor(Colors::LightSeaGreen, 1);
	GraphObj1->SetColor(Colors::Red, 2);
	GraphObj1->SetColor(Colors::White, 3);

	GraphObj2 = new GraphicObject_Color(pShaderCol, pModel2);
	GraphObj2->SetColor(Colors::LightBlue);

	// Initialize the world matrix
	mWorld1 = Matrix(SCALE, .5f, .5f, .5f) * Matrix(TRANS, 0, 1, 0);
	mWorld2 = Matrix(SCALE, .5f, .5f, .5f) * Matrix(TRANS, 2, 1, 3);

	// MARY
	// set our new graphic object worlds
	GraphObj1->SetWorld(mWorld1);
	GraphObj2->SetWorld(mWorld2);



	// DEMO 2
	// initialize textures for other graphic objects
	pTex1 = new Texture(md3dDevice, L"../Assets/Textures/brick.tga");
	pTex2 = new Texture(md3dDevice, L"../Assets/Textures/Dice.tga");
	pTex3 = new Texture(md3dDevice, L"../Assets/Textures/Test512.tga");
	pTex4 = new Texture(md3dDevice, L"../Assets/Textures/CrateFace.tga");
	//our shaders and GraphicObjects
	pShaderTex = new ShaderTexture(md3dDevice);
	TexGO1 = new GraphicObject_Texture(pShaderTex, pModel1);
	TexGO2 = new GraphicObject_Texture(pShaderTex, pModel2);

	pShaderColLight = new ShaderColorLight(md3dDevice);
	LightGO1 = new GraphicObject_Light(pShaderColLight, pModel1);
	LightGO2 = new GraphicObject_Light(pShaderColLight, pModel2);

	pShaderTexLight = new ShaderColorLightTexture(md3dDevice);
	TexLight1 = new GraphicObject_TexLight(pShaderTexLight, pModel1);
	TexLight2 = new GraphicObject_TexLight(pShaderTexLight, pModel2);
	// setting their textures
	TexGO1->SetTexture(pTex1, 0);
	TexGO1->SetTexture(pTex2, 1);
	TexGO1->SetTexture(pTex4, 2);
	TexGO1->SetTexture(pTex3, 3);
	TexGO2->SetTexture(pTex4);

	LightGO1->SetMaterial(Colors::HotPink, Colors::HotPink, Vect(1, 1, 1, 100), 0);
	LightGO1->SetMaterial(Colors::Purple, Colors::Purple, Vect(1, 1, 1, 100), 1);
	LightGO1->SetMaterial(Colors::Gold, Colors::Gold, Vect(1, 1, 1, 100), 2);
	LightGO1->SetMaterial(Colors::LightBlue, Colors::LightBlue, Vect(1, 1, 1, 100), 3);
	LightGO2->SetMaterial(Colors::OldLace, Colors::OldLace, Vect(1, 1, 1, 100));

	TexLight1->SetTexture(pTex3, 0);
	TexLight1->SetTexture(pTex4, 1);
	TexLight1->SetTexture(pTex2, 2);
	TexLight1->SetTexture(pTex1, 3);
	TexLight2->SetTexture(pTex1);
	TexLight1->SetMaterial(Colors::White, Colors::White, Vect(1, 1, 1, 100));
	TexLight2->SetMaterial(Colors::White, Colors::White, Vect(1, 1, 1, 100));

	mWorld3 = Matrix(SCALE, .35f, .35f, .35f) * Matrix(TRANS, 1, 1, 0);
	mWorld4 = Matrix(SCALE, .35f, .35f, .35f) * Matrix(TRANS, 1, 4, 0);
	mWorld5 = Matrix(SCALE, .35f, .35f, .35f) * Matrix(TRANS, -1, 1, 0);
	mWorld6 = Matrix(SCALE, .35f, .35f, .35f) * Matrix(TRANS, -1, 4, 0);
	mWorld7 = Matrix(SCALE, .35f, .35f, .35f) * Matrix(TRANS, 2, 1, 0);
	mWorld8 = Matrix(SCALE, .35f, .35f, .35f) * Matrix(TRANS, 2, 4, 0);

	TexGO1->SetWorld(mWorld3);
	TexGO2->SetWorld(mWorld4);
	LightGO1->SetWorld(mWorld5);
	LightGO2->SetWorld(mWorld6);
	TexLight1->SetWorld(mWorld7);
	TexLight2->SetWorld(mWorld8);


	// Initialize the projection matrix
	mCam.setPerspective( 3.14159/3, mClientWidth / (float)mClientHeight, 1.0f, 1000.0f);
	mCam.setOrientAndPosition(Vect(0, 1, 0), Vect(0, 0, 0), Vect(0, 3, -5));

	mTimer.Reset();
}

void DXApp::UpdateScene()
{
	mWorld2 *= Matrix(ROT_Y, 0.03);
	//TexLight2->SetWorld(mWorld2);
	GraphObj2->SetWorld(mWorld2);

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

	// Plane/box display
	
	// MARY
	// change to our color shaders then render our colored graphic objects
	pShaderCol->SetToContext(md3dImmediateContext);
	pShaderCol->SendCamMatrices(mCam.getViewMatrix(), mCam.getProjMatrix());

	// --- Render Object #1;
	GraphObj1->Render();

	// --- Render Object #2
	GraphObj2->Render();

	// set the shaders to context and render the other graphic objects
	pShaderTex->SetToContext(md3dImmediateContext);
	pShaderTex->SendCamMatrices(mCam.getViewMatrix(), mCam.getProjMatrix());
	TexGO1->Render();
	TexGO2->Render();

	pShaderColLight->SetToContext(md3dImmediateContext);
	pShaderColLight->SendCamMatrices(mCam.getViewMatrix(), mCam.getProjMatrix());
	// We need to set the Lights
	pShaderColLight->SetDirectionalLightParameters(Vect(-1, 1, -2).getNorm(),
		.1 * Vect(1, 1, 1), .5 * Vect(1, 1, 1), Vect(1, 1, 1));
	pShaderColLight->SetPointLightParameters(Vect(0, 1, -3), 100, .2 * Vect(0, 1, 0),
		.1 * Vect(1, 1, 1), 2 * Vect(1, 1, 1), 1 * Vect(1, 1, 1));
	pShaderColLight->SetSpotLightParameters(Vect(1, 1, -4), 4000, .5 * Vect(1, 0, 0),
		-Vect(1, 1, -4).getNorm(), 50, .2 * Vect(1, 1, 1), 3 * Vect(1, 1, 1), 1 * Vect(1, 1, 1, 150));
	Vect eyepos;
	mCam.getPos(eyepos);
	pShaderColLight->SendLightParameters(eyepos);
	LightGO1->Render();
	LightGO2->Render();

	pShaderTexLight->SetToContext(md3dImmediateContext);
	pShaderTexLight->SendCamMatrices(mCam.getViewMatrix(), mCam.getProjMatrix());
	// We need to set the Lights
	pShaderTexLight->SetDirectionalLightParameters(Vect(-1, -1, 1).getNorm(),
		.1 * Vect(1, 1, 1), .5 * Vect(1, 1, 1), Vect(1, 1, 1));
	pShaderTexLight->SetPointLightParameters(Vect(-2, 1, 0), 100, .2 * Vect(0, 1, 0),
		.1 * Vect(1, 1, 1), 2 * Vect(1, 1, 1), 1 * Vect(1, 1, 1));
	pShaderTexLight->SetSpotLightParameters(Vect(1, 0, -4), 4000, .5 * Vect(1, 0, 0),
		-Vect(1, 0, -4).getNorm(), 50, .2 * Vect(1, 1, 1), 3 * Vect(1, 1, 1), 1 * Vect(1, 1, 1, 150));
	mCam.getPos(eyepos);
	pShaderTexLight->SendLightParameters(eyepos);
	TexLight1->Render();
	TexLight2->Render();

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
	delete pModel1;
	delete pModel2;
	delete pShaderCol;
	delete pShaderTex;
	delete pShaderColLight;
	delete pShaderTexLight;

	delete GraphObj1;
	delete GraphObj2;

	delete TexLight1;
	delete TexLight2;
	delete pTex1;
	delete pTex2;
	delete pTex3;
	delete pTex4;

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