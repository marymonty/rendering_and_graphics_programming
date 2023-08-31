#include "DXApp.h"
#include <windows.h>
#include <sstream>
#include <assert.h>
#include "d3dUtil.h"

// needed to load shaders from file
#include <d3dcompiler.h>

#include "Model.h"

DXApp::DXApp(HWND hwnd)
{
	assert(hwnd);
	mhMainWnd = hwnd;

	BackgroundColor = Colors::MidnightBlue;

	md3dDevice = nullptr;
	md3dImmediateContext = nullptr;
	mSwapChain = nullptr;
	mRenderTargetView = nullptr;

	mpVertexShader = nullptr;
	mpPixelShader = nullptr;
	mpVertexLayout = nullptr;
	//mpVertexBuffer = nullptr;
	//mpIndexBuffer = nullptr;

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

void DXApp::InitDemo()
{
	HRESULT hr = S_OK;

	// MARY
	// create BOTH of our vertex shaders in Init
	// ColorSelected3D Shader
	// Compile the vertex shader
	ID3DBlob* pVSBlob = nullptr;
	hr = CompileShaderFromFile(L"../Assets/Shaders/ColorSelected3D.hlsl", "VS", "vs_4_0", &pVSBlob);
	if (FAILED(hr))
	{
		MessageBox(nullptr,
			"Problem compiling the VERTEX shader", "Error", MB_OK);
		assert(!FAILED(hr));
	}
	// Create the ColorSelected3D vertex shader
	hr = md3dDevice->CreateVertexShader(pVSBlob->GetBufferPointer(), pVSBlob->GetBufferSize(), nullptr, &mpVertexShader);
	assert(!FAILED(hr));

	// SimpleColor3D Shader
	// Compile the vertex shader
	ID3DBlob* pVSBlobSC = nullptr;
	hr = CompileShaderFromFile(L"../Assets/Shaders/SimpleColor3D.hlsl", "VS", "vs_4_0", &pVSBlobSC);
	if (FAILED(hr))
	{
		MessageBox(nullptr,
			"Problem compiling the VERTEX shader", "Error", MB_OK);
		assert(!FAILED(hr));
	}
	// Create the ColorSelected3D vertex shader
	hr = md3dDevice->CreateVertexShader(pVSBlobSC->GetBufferPointer(), pVSBlobSC->GetBufferSize(), nullptr, &mpVertexShader2);
	assert(!FAILED(hr));

	// Define the input layout
	D3D11_INPUT_ELEMENT_DESC layout[] =
	{
		{ "POSITION", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "COLOR", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT , D3D11_INPUT_PER_VERTEX_DATA, 0 }
	};
	UINT numElements = ARRAYSIZE(layout);

	// Create the input layouts for both vertex shaders
	hr = md3dDevice->CreateInputLayout(layout, numElements, pVSBlob->GetBufferPointer(), pVSBlob->GetBufferSize(), &mpVertexLayout);
	assert(!FAILED(hr));
	hr = md3dDevice->CreateInputLayout(layout, numElements, pVSBlobSC->GetBufferPointer(), pVSBlobSC->GetBufferSize(), &mpVertexLayout2);
	assert(!FAILED(hr));
	ReleaseAndDeleteCOMobject(pVSBlob);
	ReleaseAndDeleteCOMobject(pVSBlobSC);
	// Set the input layout
	md3dImmediateContext->IASetInputLayout(mpVertexLayout);


	// MARY
	// create BOTH of our pixel shaders in Init
	// ColorSelected3D Shader
	// Compile the pixel shader
	ID3DBlob* pPSBlob = nullptr;
	hr = CompileShaderFromFile(L"../Assets/Shaders/ColorSelected3D.hlsl", "PS", "ps_4_0", &pPSBlob);
	if (FAILED(hr))
	{
		MessageBox(nullptr,
			"Problem compiling the PIXEL shader", "Error", MB_OK);
		assert(!FAILED(hr));
	}
	// Create the pixel shader
	hr = md3dDevice->CreatePixelShader(pPSBlob->GetBufferPointer(), pPSBlob->GetBufferSize(), nullptr, &mpPixelShader);
	ReleaseAndDeleteCOMobject(pPSBlob);
	assert(!FAILED(hr));

	// SimpleColor3D Shader
	// Compile the pixel shader
	ID3DBlob* pPSBlobSC = nullptr;
	hr = CompileShaderFromFile(L"../Assets/Shaders/SimpleColor3D.hlsl", "PS", "ps_4_0", &pPSBlobSC);
	if (FAILED(hr))
	{
		MessageBox(nullptr,
			"Problem compiling the PIXEL shader", "Error", MB_OK);
		assert(!FAILED(hr));
	}
	// Create the pixel shader
	hr = md3dDevice->CreatePixelShader(pPSBlobSC->GetBufferPointer(), pPSBlobSC->GetBufferSize(), nullptr, &mpPixelShader2);
	ReleaseAndDeleteCOMobject(pPSBlobSC);
	assert(!FAILED(hr));

	// vertex and index buffers are all handeled in the Model class

	// constructing Models
	unitCubeModel = new Model(md3dDevice, Model::PreMadeModels::UnitBox);
	unitPyramidModel = new Model(md3dDevice, Model::PreMadeModels::UnitPyramid);
	   
	// Set the shader as active for context
	//md3dImmediateContext->VSSetShader(mpVertexShader, nullptr, 0);
	//md3dImmediateContext->PSSetShader(mpPixelShader, nullptr, 0);
	

	// MARY
	// create the two separate constant buffers needed for the ColorSelected3D shader file
	// ViewProjData and WorldColorData buffers
	// First, the view and projection matrix buffer
	D3D11_BUFFER_DESC bd;
	ZeroMemory(&bd, sizeof(bd));
	bd.Usage = D3D11_USAGE_DEFAULT;
	bd.ByteWidth = sizeof(ViewProjData);
	bd.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	bd.CPUAccessFlags = 0;

	hr = md3dDevice->CreateBuffer(&bd, nullptr, &mpcbViewProjBuffer);
	assert(SUCCEEDED(hr));

	// Second, the world matrix and color buffer
	bd.Usage = D3D11_USAGE_DEFAULT;
	bd.ByteWidth = sizeof(WorldColorData);
	bd.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	bd.CPUAccessFlags = 0;

	hr = md3dDevice->CreateBuffer(&bd, nullptr, &mpcbWorldColorBuffer);
	assert(SUCCEEDED(hr));


	// create the constant buffer needed for SimpleColor3D shader in init
	bd.Usage = D3D11_USAGE_DEFAULT;
	bd.ByteWidth = sizeof(WVPmatrices);
	bd.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	bd.CPUAccessFlags = 0;

	hr = md3dDevice->CreateBuffer(&bd, nullptr, &mpcbWVPBuffer);
	assert(SUCCEEDED(hr));

	// Connect the buffers to the render pipeline
	//md3dImmediateContext->VSSetConstantBuffers(0, 1, &mpcbViewProjBuffer);
	//md3dImmediateContext->VSSetConstantBuffers(1, 1, &mpcbWorldColorBuffer);


	// Initialize the worldmat
	mWorld1 = Matrix(IDENTITY);
	// MARY
	// we need multiple World matrices so the rendered objects are displayed
	// in multiple origins (i.e. the rendered objects are not all displayed overlapping)
	mWorld2 = Matrix(SCALE, .5f, .5f, .5f) * Matrix(TRANS, 2, 1, 3);
	mWorld3 = Matrix(SCALE, .5f, .5f, .5f) * Matrix(TRANS, -2, 1, 3);
	mWorld4 = Matrix(SCALE, .5f, .5f, .5f) * Matrix(TRANS, 0, 2, 3);

	// Initialize the projection matrix
	mCam.setPerspective(45, mClientWidth / (float)mClientHeight, 1.0f, 1000.0f);

	// Initialize gimmicky mouse control values
	mTheta = 0;
	mPhi = 3.1415f / 8;
	mRadius = 5;

	mTimer.Reset();
}

void DXApp::UpdateScene()
{
	//mWorld *= Matrix(ROT_Y, .0001f);  // Simple slow rotation about y axis

	// Build the view matrix using gimmicky trick
	Vect target = Vect(0, 0, 0, 0);
	Vect up = Vect(0, 1, 0, 0);
	Vect pos = Vect(0, 0, -mRadius) * Matrix(ROT_Y, mTheta) * Matrix(ROT_X, mPhi);
	mCam.setOrientAndPosition(up, target, pos);

	mCam.updateCamera();
}

void DXApp::DrawScene()
{
	// Clear the back buffer
	md3dImmediateContext->ClearRenderTargetView(mRenderTargetView, VasA(BackgroundColor));
	// Clear the depth stencil;
	md3dImmediateContext->ClearDepthStencilView(mpDepthStencilView, D3D11_CLEAR_DEPTH, 1.0f, 0);


	// We are initially using the ColorSelected3D shader, so we need to 
	// update our VS, PS, input layout, and constant buffer accordingly
	md3dImmediateContext->VSSetShader(mpVertexShader, nullptr, 0);
	md3dImmediateContext->PSSetShader(mpPixelShader, nullptr, 0);
	md3dImmediateContext->IASetInputLayout(mpVertexLayout);
	md3dImmediateContext->VSSetConstantBuffers(0, 1, &mpcbViewProjBuffer);
	md3dImmediateContext->VSSetConstantBuffers(1, 1, &mpcbWorldColorBuffer);

	// ColorSelected3D shader has two constant buffers, so set them before rendering
	// update buffer with cam data, only send the camera view and projection matrices once
	ViewProjData vpdata;
	vpdata.mView = mCam.getViewMatrix();
	vpdata.mProjection = mCam.getProjMatrix();
	md3dImmediateContext->UpdateSubresource(mpcbViewProjBuffer, 0, nullptr, &vpdata, 0, 0);

	// update buffer with instance data of world matrix and color
	WorldColorData wcdata;
	wcdata.mWorld = mWorld1;
	wcdata.Color = Colors::HotPink;
	md3dImmediateContext->UpdateSubresource(mpcbWorldColorBuffer, 0, nullptr, &wcdata, 0, 0);
	// make sure we will be rendering a cube by calling SetToContext
	// which binds the vertex and index buffers and primitaive topology to the input assembler stage
	unitCubeModel->SetToContext(md3dImmediateContext);
	// Render Object #1
	unitCubeModel->Render(md3dImmediateContext);

	// for object 2 (unit Pyramid) using ColorSelected 3D shader we need to update
	// instance data of world matrix and color
	wcdata.mWorld = mWorld2;
	wcdata.Color = Colors::LightGreen;
	md3dImmediateContext->UpdateSubresource(mpcbWorldColorBuffer, 0, nullptr, &wcdata, 0, 0);
	// make sure we will be rendering a pyramid by calling SetToContext
	// which binds the vertex and index buffers and primitaive topology to the input assembler stage
	unitPyramidModel->SetToContext(md3dImmediateContext);
	// Render Object #2
	unitPyramidModel->Render(md3dImmediateContext);



	// here we are switching to the SimpleColor3D shader, so we need to 
	// update our VS, PS, input layout, and constant buffer
	md3dImmediateContext->VSSetShader(mpVertexShader2, nullptr, 0);
	md3dImmediateContext->PSSetShader(mpPixelShader2, nullptr, 0);
	md3dImmediateContext->IASetInputLayout(mpVertexLayout2);
	md3dImmediateContext->VSSetConstantBuffers(0, 1, &mpcbWVPBuffer);

	// now our constant buffer is WVPmatrices, all data needs to be updated every instance
	WVPmatrices wvpdata;
	wvpdata.mWorld = mWorld3;
	wvpdata.mView = mCam.getViewMatrix();
	wvpdata.mProjection = mCam.getProjMatrix();
	md3dImmediateContext->UpdateSubresource(mpcbWVPBuffer, 0, nullptr, &wvpdata, 0, 0);
	// context is already set to the Pyramid so the correct buffers and topology is bound
	// Render Object #3
	unitPyramidModel->Render(md3dImmediateContext);

	// render another cube by updating the constant buffer
	wvpdata.mWorld = mWorld4;
	wvpdata.mView = mCam.getViewMatrix();
	wvpdata.mProjection = mCam.getProjMatrix();
	md3dImmediateContext->UpdateSubresource(mpcbWVPBuffer, 0, nullptr, &wvpdata, 0, 0);
	// we are switching back to rendering a cube so we need another SetToContext call 
	// to bind the vertex and index buffers and primitaive topology of the cube to the input assembler stage
	unitCubeModel->SetToContext(md3dImmediateContext);
	// Render Object #4
	unitCubeModel->Render(md3dImmediateContext);


	// simpleColor3D shader does not specify a color so we are using the model's default color


	// Switches the display to show the now-finished back-buffer
	mSwapChain->Present(SyncInterval, 0);
}

DXApp::~DXApp()
{
	ReleaseAndDeleteCOMobject(mpVertexShader);
	ReleaseAndDeleteCOMobject(mpPixelShader);
	ReleaseAndDeleteCOMobject(mpVertexLayout);

	delete unitCubeModel;
	// MARY
	// need to clean up my resources
	delete unitPyramidModel;


	// Not needed anymore: handled by Model
	//ReleaseAndDeleteCOMobject(mpVertexBuffer);
	//ReleaseAndDeleteCOMobject(mpIndexBuffer);
	
	// MARY
	// we have new constant buffers to release
	ReleaseAndDeleteCOMobject(mpcbWVPBuffer);
	ReleaseAndDeleteCOMobject(mpcbViewProjBuffer);
	ReleaseAndDeleteCOMobject(mpcbWorldColorBuffer);

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
	// MARY
	// make the fill wireframe
	rd.FillMode = D3D11_FILL_WIREFRAME;  // Also: D3D11_FILL_SOLID
	rd.CullMode = D3D11_CULL_BACK;
	rd.FrontCounterClockwise = true; // true for RH forward facing
	rd.DepthBias = 0;
	rd.SlopeScaledDepthBias = 0.0f;
	rd.DepthBiasClamp = 0.0f;
	rd.DepthClipEnable = true;
	rd.ScissorEnable = false;
	rd.MultisampleEnable = true;  // Does not in fact turn on/off multisample: https://msdn.microsoft.com/en-us/library/windows/desktop/ff476198(v=vs.85).aspx
	rd.AntialiasedLineEnable = false;

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
	// Gimmicky mouse control
	if (btnState & MK_LBUTTON)
	{
		MousePos[x] = static_cast<float>(xval);
		MousePos[y] = static_cast<float>(yval);
	}
}

void DXApp::OnMouseUp(WPARAM btnState, int xval, int yval)
{
	UNREFERENCED_PARAMETER(btnState);
	UNREFERENCED_PARAMETER(xval);
	UNREFERENCED_PARAMETER(yval);
}

void DXApp::OnMouseMove(WPARAM btnState, int xval, int yval)
{
	// Gimmicky mouse control
	if (btnState & MK_LBUTTON)
	{
		float dx = 0.01f*(MousePos[x] - xval);
		float dy = 0.01f*(MousePos[y] - yval);

		// Update angles based on input to orbit camera around box.
		mTheta += dx;
		mPhi -= dy;

		static float verticalMax = MATH_PI2 - 0.2f;

		if (mPhi > verticalMax)
			mPhi = verticalMax;
		else if (mPhi < -verticalMax)
			mPhi = -verticalMax;
	}

	MousePos[x] = static_cast<float>(xval);
	MousePos[y] = static_cast<float>(yval);
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