#include "FlatPlane.h"
#include "Model.h"
#include "d3dUtil.h"

FlatPlane::FlatPlane(ID3D11Device* dev, float len, float urep, float vrep)
{
	int nverts = 4;
	StandardVertex* pVerts = new StandardVertex[nverts];

	int ntri = 2;
	TriangleByIndex* pTriList = new TriangleByIndex[ntri];

	pVerts[0].set(-0.5f * len, 0, -0.5f * len, urep, vrep, Colors::Black);
	pVerts[1].set(-0.5f * len, 0, 0.5f * len, urep, 0, Colors::Blue);
	pVerts[2].set(0.5f * len, 0, 0.5f * len, 0, 0, Colors::Magenta);
	pVerts[3].set(0.5f * len, 0, -0.5f * len, 0, vrep, Colors::Red);

	pTriList[0].set(0, 1, 2);
	pTriList[1].set(0, 2, 3);

	pPlane = new Model(dev, pVerts, nverts, pTriList, ntri);

	delete[] pVerts;
	delete[] pTriList;
}

FlatPlane::~FlatPlane()
{
	delete pPlane;
}

void FlatPlane::Render(ID3D11DeviceContext* context)
{
	pPlane->SetToContext(context);
	pPlane->Render(context);
}