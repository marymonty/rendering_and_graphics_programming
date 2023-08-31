#include "DXApp.h"
#include <windows.h>
#include <sstream>
#include <assert.h>
#include "d3dUtil.h"

// needed to load shaders from file
#include <d3dcompiler.h>

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
	mpVertexBuffer = nullptr;

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
	ReleaseAndDeleteCOMobject(mpVertexShader);
	ReleaseAndDeleteCOMobject(mpPixelShader);
	ReleaseAndDeleteCOMobject(mpVertexLayout);
	ReleaseAndDeleteCOMobject(mpVertexBuffer);
	ReleaseAndDeleteCOMobject(mpIndexBuffer)

	ReleaseAndDeleteCOMobject(mRenderTargetView);
	ReleaseAndDeleteCOMobject(mSwapChain);
	ReleaseAndDeleteCOMobject(md3dImmediateContext);
	ReleaseAndDeleteCOMobject(md3dDevice);
}

void DXApp::InitDirect3D()
{
	HRESULT hr = S_OK;
	
	UINT createDeviceFlags = 0;
#ifdef _DEBUG
	createDeviceFlags |= D3D11_CREATE_DEVICE_DEBUG;
#endif

	// This is a *greatly* simplified process to create a DX device and context:
	// We force the use of DX11 feature.
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
	// keep FillMode as FILL_SOLID for the Star problem

	rd.FillMode = D3D11_FILL_SOLID;  // Also: D3D11_FILL_WIREFRAME
	rd.CullMode = D3D11_CULL_BACK;
	rd.FrontCounterClockwise = true; // true for RH standard forward facing
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
	/**********************************************************/

	md3dImmediateContext->OMSetRenderTargets(1, &mRenderTargetView, nullptr);

	// Setup the viewport
	D3D11_VIEWPORT vp;
	vp.Width =  (FLOAT)mClientWidth;
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
	if( (mTimer.TotalTime() - timeElapsed) >= 1.0f )
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

void DXApp::InitDemo()
{
	HRESULT hr = S_OK;

	// Compile the vertex shader
	ID3DBlob* pVSBlob = nullptr;
	hr = CompileShaderFromFile(L"../Assets/Shaders/SimpleColor.hlsl", "VS", "vs_4_0", &pVSBlob);
	if (FAILED(hr))
	{
		MessageBox(nullptr, "Problem compiling the VERTEX shader", "Error", MB_OK);
		assert(!FAILED(hr));
	}

	// Create the vertex shader
	hr = md3dDevice->CreateVertexShader(pVSBlob->GetBufferPointer(), pVSBlob->GetBufferSize(), nullptr, &mpVertexShader);
	assert(!FAILED(hr));

	// Define the input layout
	D3D11_INPUT_ELEMENT_DESC layout[] =
	{
		{ "POSITION", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
	};
	UINT numElements = ARRAYSIZE(layout);

	// Create the input layout
	hr = md3dDevice->CreateInputLayout(layout, numElements, pVSBlob->GetBufferPointer(), pVSBlob->GetBufferSize(), &mpVertexLayout);
	ReleaseAndDeleteCOMobject(pVSBlob);
	assert(!FAILED(hr));

	// Set the input layout
	md3dImmediateContext->IASetInputLayout(mpVertexLayout);

	// Compile the pixel shader
	ID3DBlob* pPSBlob = nullptr;
	hr = CompileShaderFromFile(L"../Assets/Shaders/SimpleColor.hlsl", "PS", "ps_4_0", &pPSBlob);
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

	// Create vertex buffer
	
	// MARY 
	// we create the array of Vects (vertices) here
	// do not repeat vertices used twice (the bottom two verts of 
	//		the north facing triangle of the star are the same two verts
	//		of the bottom of the south facing triangle) 
	Vect vertices[] =
		{
			// Star Pattern contains four separate triangles
			// north pointing, south pointing, east pointing, and west pointing triangles
			
			// north pointing triangle
			Vect(0.0f, 0.75f, 0),	// Top 
			Vect(0.25f, 0.0f, 0),	// Bottom right 
			Vect(-0.25f, 0.0f, 0),	// Bottom left 

			//south pointing triangle
			Vect(0.0f, -0.75f, 0),	// Top
			//Bottom left and right vertices are the same as north pointing 

			// east pointing triangle
			Vect(0.75f, 0.0f, 0),	// Top
			Vect(0.0f, 0.25f, 0),	// Bottom left
			Vect(0.0f, -0.25f, 0),	// Bottom right

			// west pointing traingle
			Vect(-0.75f, 0.0f, 0),	// Top
			//Bottom left and right verts are the same as east pointing

		};

	D3D11_BUFFER_DESC bd;
	ZeroMemory(&bd, sizeof(bd));
	bd.Usage = D3D11_USAGE_DEFAULT;
	// MARY 
	// the sizeof(Vect) needs to be multiplied by the number of vertices
	// in the vertice array, which in our case is 8
	bd.ByteWidth = sizeof(Vect) * 8;	// size of verts * num of verts
	bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	bd.CPUAccessFlags = 0;	// zero means the cpu shall not have read nor write access to this buffer. There is no enum label for that, oddly...

	D3D11_SUBRESOURCE_DATA InitData;
	ZeroMemory(&InitData, sizeof(InitData));
	InitData.pSysMem = vertices;
	hr = md3dDevice->CreateBuffer(&bd, &InitData, &mpVertexBuffer);
	assert(SUCCEEDED(hr));

	// Set vertex buffer
	UINT stride = sizeof(Vect);
	UINT offset = 0;
	md3dImmediateContext->IASetVertexBuffers(0, 1, &mpVertexBuffer, &stride, &offset);

	// Create index buffer (watch your winding!!!)
	
	// MARY
	// remember to list the vertices in counter clockwise order!
	WORD indices[] = 
		{
			// create the triangles using the index of the vertex 
			// in the vertices array

			0, 2, 1,	// north pointing
			3, 1, 2,	// south pointing
			4, 5, 6,	// east pointing
			7, 6, 5		// west pointing

		};

	bd.Usage = D3D11_USAGE_DEFAULT;

	// MARY
	// ByteWidth is sizeof(WORD) * number of vertices per triangle * number of triangles
	// so there are 3 verts per triangle, and 4 total triangles
	bd.ByteWidth = sizeof(WORD) * 3 * 4;
	bd.BindFlags = D3D11_BIND_INDEX_BUFFER;
	bd.CPUAccessFlags = 0;

	InitData.pSysMem = indices;
	hr = md3dDevice->CreateBuffer(&bd, &InitData, &mpIndexBuffer);
	assert(SUCCEEDED(hr));

	// Set primitive topology
	md3dImmediateContext->IASetIndexBuffer(mpIndexBuffer, DXGI_FORMAT_R16_UINT, 0);
	md3dImmediateContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

	// Set the shader as active for context
	md3dImmediateContext->VSSetShader(mpVertexShader, nullptr, 0);
	md3dImmediateContext->PSSetShader(mpPixelShader, nullptr, 0);

	mTimer.Reset();
}

void DXApp::UpdateScene()
{
	// nothing for now
}

void DXApp::DrawScene()
{	
	// Clear the back buffer
	md3dImmediateContext->ClearRenderTargetView(mRenderTargetView, VasA(BackgroundColor) );

	// Build the next frame to display
	
	// MARY 
	// DrawIndexed first param is the index count, which is found by multiplying 
	// the number of indices per triangle, with the total number of triangles (3 * 4)
	md3dImmediateContext->DrawIndexed(3 * 4, 0, 0); 
	
	// Switches the display to show the now-finished back-buffer
	mSwapChain->Present(SyncInterval, 0);
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