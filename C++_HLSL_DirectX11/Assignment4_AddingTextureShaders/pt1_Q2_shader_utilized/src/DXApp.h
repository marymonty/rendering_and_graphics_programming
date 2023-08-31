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
// MARY
// include the header file for our new shader
#include "ColorSelected3DOptimized.h"

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

	// Debug utility
	void ReportLiveDXObjects();


	Camera mCam;
	// MARY
	// create our world matrices
	Matrix mWorld1;	
	Matrix mWorld2;	
	Matrix mWorld3;	
	Matrix mWorld4;	
	Matrix mWorld5;	
	// MARY
	// adding a matrix for View * Projection
	//Matrix ViewProjMat;

	Model* boxModel;
	Model* pyramidModel;
	// have our shader pointer be of the correct type - ColorSelected3DOptimized
	ColorSelected3DOptimized* pShColor;

	Vect MousePos;		// gimmicky mouse control
	float mTheta;
	float mPhi;
	float mRadius;

	
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