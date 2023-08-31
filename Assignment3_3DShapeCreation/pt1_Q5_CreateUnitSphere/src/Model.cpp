#include <assert.h>
#include "File.h"
#include "Model.h"
#include "ModelTools.h"
#include "d3dUtil.h"

Model::Model(ID3D11Device* dev, StandardVertex *pVerts, int nverts, TriangleByIndex *ptlist, int ntri)
{
	assert(nverts > 0);
	assert(ntri > 0);

	mDevice = dev;

	// Copy Data
	numVerts = nverts;
	pStdVerts = new StandardVertex[numVerts];
	for (int i = 0; i < numVerts; i++)
	{
		pStdVerts[i] = pVerts[i];
	}
	numTris = ntri;
	pTriList = new TriangleByIndex[numTris];
	for (int i = 0; i < numTris; i++)
	{
		pTriList[i] = ptlist[i];
	}

	privLoadDataToGPU();
}

Model::Model(ID3D11Device* dev, Model::PreMadeModels pm)
{
	mDevice = dev;
	pStdVerts = nullptr;
	pTriList = nullptr;
	numVerts = 0;
	numTris = 0;

	switch (pm)
	{
	case UnitBox:
		ModelTools::CreateUnitBox(pStdVerts, numVerts, pTriList, numTris);
		break;
	case UnitPyramid:
		ModelTools::CreateUnitPyramid(pStdVerts, numVerts, pTriList, numTris);
		break;
	case UnitSphere:
		ModelTools::CreateUnitSphere(12, 12, pStdVerts, numVerts, pTriList, numTris);
		break;
	default:
		assert(false && "Invalid option");
	}

	privLoadDataToGPU();
}

Model::~Model()
{
	delete[] pTriList;
	delete[] pStdVerts;

	ReleaseAndDeleteCOMobject(mpVertexBuffer);
	ReleaseAndDeleteCOMobject(mpIndexBuffer);
}

void  Model::privLoadDataToGPU()
{
	// Vertex buffer
	D3D11_BUFFER_DESC bd;
	ZeroMemory(&bd, sizeof(bd));
	bd.Usage = D3D11_USAGE_DEFAULT;
	bd.ByteWidth = sizeof(StandardVertex) * numVerts;
	bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	bd.CPUAccessFlags = 0;

	D3D11_SUBRESOURCE_DATA InitData;
	ZeroMemory(&InitData, sizeof(InitData));
	InitData.pSysMem = pStdVerts;
	HRESULT hr = mDevice->CreateBuffer(&bd, &InitData, &mpVertexBuffer);
	assert(SUCCEEDED(hr));

	// Index buffer
	bd.Usage = D3D11_USAGE_DEFAULT;
	bd.ByteWidth = sizeof(TriangleByIndex) * numTris;
	bd.BindFlags = D3D11_BIND_INDEX_BUFFER;
	bd.CPUAccessFlags = 0;
	InitData.pSysMem = pTriList;
	hr = mDevice->CreateBuffer(&bd, &InitData, &mpIndexBuffer);
	assert(SUCCEEDED(hr));

}

void Model::SetToContext(ID3D11DeviceContext* context)
{
	UINT stride = sizeof(StandardVertex);
	UINT offset = 0;
	context->IASetVertexBuffers(0, 1, &mpVertexBuffer, &stride, &offset);
	context->IASetIndexBuffer(mpIndexBuffer, DXGI_FORMAT_R32_UINT, 0);
	context->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
}

void Model::Render(ID3D11DeviceContext* context)
{
	context->DrawIndexed(numTris * 3, 0, 0);
}





