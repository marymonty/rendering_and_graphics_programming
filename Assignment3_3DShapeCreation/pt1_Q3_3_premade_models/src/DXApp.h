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

class Model;

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
	ID3D11VertexShader*     mpVertexShader;
	ID3D11PixelShader*      mpPixelShader;
	ID3D11InputLayout*      mpVertexLayout;

	//ID3D11Buffer*           mpVertexBuffer;
	//ID3D11Buffer*           mpIndexBuffer;

	Camera mCam;
	Matrix mWorld;
	// MARY
	// need other world matrices for rendering
	Matrix mWorld2;
	Matrix mWorld3;

	Model* unitCubeModel;
	// MARY
	// need another model
	Model* unitPyramidModel;

	Vect MousePos;		// gimmicky mouse control
	float mTheta;
	float mPhi;
	float mRadius;

	//ID3D11Buffer* mpcbWVPBuffer;

	//struct WVPmatrices
	//{
	//	Matrix mWorld;
	//	Matrix mView;
	//	Matrix mProjection;
	//};

	// MARY
	// Need to match the context buffer's to the 
	// ColorSelected3D context buffers
	// mpcbViewProjBuffer contains the view matrix and projection matrix
	// since these matrices only need to be updated when the camera moves
	ID3D11Buffer* mpcbViewProjBuffer;

	struct ViewProjData
	{
		Matrix mView;
		Matrix mProjection;
	};

	// mpcbWorldColorBuffer contains the world matrix and the object color
	// since these matrices need to be updated with each separate cube render
	ID3D11Buffer* mpcbWorldColorBuffer;

	struct WorldColorData
	{
		Matrix mWorld;
		Vect Color;
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