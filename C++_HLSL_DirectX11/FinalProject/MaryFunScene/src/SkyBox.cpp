#include <assert.h>
#include "File.h"
#include "SkyBox.h"
#include "d3dUtil.h"
#include "Model.h"

SkyBox::SkyBox(ID3D11Device* dev, int scaleSize, Texture* tex, ShaderTexture* shader)
{
	pTexture = tex;
	pShader = shader;

	// same verts and tris as all other cubes in the ModelTools class
	int nverts = 24;
	StandardVertex* pStdVerts = new StandardVertex[nverts];
	int ntri = 12;
	TriangleByIndex* pTriList = new TriangleByIndex[ntri];


	// for the skybox, our faces are inverted (facing inward)
	// so we need to switch the windings
	// also the normals face inward (which means they are uneffected by
	// outside light (which is the proper interaction)

	//*
	// Setting up faces
	// Forward
	int vind = 0;
	int tind = 0;
	// (.5, .25), (.5, .5), (.75, .25), (.75, .5)
	pStdVerts[vind].set(0.5f * scaleSize, 0.5f * scaleSize, 0.5f * scaleSize, 0.75f, 0.25f, 0, 0, -1);
	pStdVerts[vind + 1].set(-0.5f * scaleSize, 0.5f * scaleSize, 0.5f * scaleSize, 0.5f, 0.25f, 0, 0, -1);
	pStdVerts[vind + 2].set(-0.5f * scaleSize, -0.5f * scaleSize, 0.5f * scaleSize, 0.5f, 0.5f, 0, 0, -1);
	pStdVerts[vind + 3].set(0.5f * scaleSize, -0.5f * scaleSize, 0.5f * scaleSize, 0.75f, 0.5f, 0, 0, -1);
	pTriList[tind].set(vind+2, vind + 1, vind);
	pTriList[tind + 1].set(vind + 3, vind + 2, vind);

	// Back
	vind += 4;
	tind += 2;
	// (0, .25), (0, .5), (.25, .25), (.25, .5)
	pStdVerts[vind].set(0.5f * scaleSize, 0.5f * scaleSize, -0.5f * scaleSize, 0.005f, 0.252f, 0, 0, 1);
	pStdVerts[vind + 1].set(-0.5f * scaleSize, 0.5f * scaleSize, -0.5f * scaleSize, 0.255f, 0.252f, 0, 0, 1);
	pStdVerts[vind + 2].set(-0.5f * scaleSize, -0.5f * scaleSize, -0.5f * scaleSize, 0.255f, 0.498f, 0, 0, 1);
	pStdVerts[vind + 3].set(0.5f * scaleSize, -0.5f * scaleSize, -0.5f * scaleSize, 0.005f, 0.498f, 0, 0, 1);
	pTriList[tind].set(vind, vind + 1, vind + 2);
	pTriList[tind + 1].set(vind, vind + 2, vind + 3);

	// right
	vind += 4;
	tind += 2;
	// (.75, .25), (.75, .5), (1, .25), (1, .5)
	pStdVerts[vind].set(0.5f * scaleSize, 0.5f * scaleSize, -0.5f * scaleSize, 1.0f, 0.252f, 1, 0, 0);
	pStdVerts[vind + 1].set(0.5f * scaleSize, 0.5f * scaleSize, 0.5f * scaleSize, 0.75f, 0.252f, 1, 0, 0);
	pStdVerts[vind + 2].set(0.5f * scaleSize, -0.5f * scaleSize, 0.5f * scaleSize, 0.75f, 0.498f, 1, 0, 0);
	pStdVerts[vind + 3].set(0.5f * scaleSize, -0.5f * scaleSize, -0.5f * scaleSize, 1.0f, 0.498f, 1, 0, 0);
	pTriList[tind].set(vind + 2, vind + 1, vind);
	pTriList[tind + 1].set(vind + 3, vind + 2, vind);

	// left
	vind += 4;
	tind += 2;
	// (.25, .25), (.25, .5), (.5, .25), (.5, .5)
	pStdVerts[vind].set(-0.5f * scaleSize, 0.5f * scaleSize, 0.5f * scaleSize, 0.5f, 0.252f, -1, 0, 0);
	pStdVerts[vind + 1].set(-0.5f * scaleSize, 0.5f * scaleSize, -0.5f * scaleSize, 0.25f, 0.252f, -1, 0, 0);
	pStdVerts[vind + 2].set(-0.5f * scaleSize, -0.5f * scaleSize, -0.5f * scaleSize, 0.25f, 0.498f, -1, 0, 0);
	pStdVerts[vind + 3].set(-0.5f * scaleSize, -0.5f * scaleSize, 0.5f * scaleSize, 0.5f, 0.498f, -1, 0, 0);
	pTriList[tind].set(vind + 2, vind + 1, vind);
	pTriList[tind + 1].set(vind + 3, vind + 2, vind);

	// Top
	vind += 4;
	tind += 2;
	// (.5, 0), (.5, .25), (.75, 0), (.75, .25)
	pStdVerts[vind].set(0.5f * scaleSize, 0.5f * scaleSize, -0.5f * scaleSize, 0.748f, 0.002f, 0, -1, 0);
	pStdVerts[vind + 1].set(-0.5f * scaleSize, 0.5f * scaleSize, -0.5f * scaleSize, 0.502f, 0.002f, 0, -1, 0);
	pStdVerts[vind + 2].set(-0.5f * scaleSize, 0.5f * scaleSize, 0.5f * scaleSize, 0.502f, 0.248f, 0, -1, 0);
	pStdVerts[vind + 3].set(0.5f * scaleSize, 0.5f * scaleSize, 0.5f * scaleSize, 0.748f, 0.248f, 0, -1, 0);
	pTriList[tind].set(vind + 2, vind + 1, vind);
	pTriList[tind + 1].set(vind + 3, vind + 2, vind);

	// Bottom
	vind += 4;
	tind += 2;
	// (.5, .5), (.5, .75), (.75, .5), (.75, .75)
	pStdVerts[vind].set(0.5f * scaleSize, -0.5f * scaleSize, 0.5f * scaleSize, 0.748f, 0.502f, 0, 1, 0);
	pStdVerts[vind + 1].set(-0.5f * scaleSize, -0.5f * scaleSize, 0.5f * scaleSize, 0.502f, 0.502f, 0, 1, 0);
	pStdVerts[vind + 2].set(-0.5f * scaleSize, -0.5f * scaleSize, -0.5f * scaleSize, 0.502f, 0.748f, 0, 1, 0);
	pStdVerts[vind + 3].set(0.5f * scaleSize, -0.5f * scaleSize, -0.5f * scaleSize, 0.748f, 0.748f, 0, 1, 0);
	pTriList[tind].set(vind + 2, vind + 1, vind);
	pTriList[tind + 1].set(vind + 3, vind + 2, vind);
	//*/

	pSkyBox = new Model(dev, pStdVerts, nverts, pTriList, ntri);

	delete[] pStdVerts;
	delete[] pTriList;
}

SkyBox::~SkyBox()
{
	delete pSkyBox;
}


void SkyBox::SetTexture(Texture* tex)
{
	pTexture = tex;
}

void SkyBox::SetWorld(Matrix w)
{
	mWorld = w;
}

void SkyBox::Render(ID3D11DeviceContext* context)
{
	// utilizing the Model class SetToContext and Render functions
	pShader->SetToContext(context);
	pShader->SetTextureResourceAndSampler(pTexture);
	pShader->SendWorld(mWorld);
	pSkyBox->SetToContext(context);
	pSkyBox->Render(context);
}




