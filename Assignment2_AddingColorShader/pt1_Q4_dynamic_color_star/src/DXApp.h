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

	// Demo specific additions
	ID3D11VertexShader*     mpVertexShader;
	ID3D11PixelShader*      mpPixelShader;
	ID3D11InputLayout*      mpVertexLayout;

	ID3D11Buffer*           mpVertexBuffer;
	ID3D11Buffer*           mpIndexBuffer;
	// MARY
	// We need to create a Constant Buffer for the dynamic color
	// Constant Buffer
	ID3D11Buffer*			mpcbColor;

	// Vertex structure

	// MARY
	// changing the vertex structure from { Pos, Color } where Color is a Vect,
	// to { Pos, ColorNum } where ColorNum is an int
	// this int will allow us to dynmaically change the color of our vertices
	struct SimpleVertex
	{
		Vect Pos;
		int ColorNum;
	};

	// MARY
	// create the Constant Buffer Structure
	// this is the array of color vects that can be referenced using SimpleVertex's ColorNum
	struct CBColor
	{
		Vect col[2];
	};
	
public:
	DXApp(HWND hwnd);
	virtual ~DXApp();
	
	void FrameTick();

	// overrides for handling mouse input.
	void OnMouseDown(WPARAM btnState, int xval, int yval);
	void OnMouseUp(WPARAM btnState, int xval, int yval);
	void OnMouseMove(WPARAM btnState, int xval, int yval);


};

#endif _DXApp