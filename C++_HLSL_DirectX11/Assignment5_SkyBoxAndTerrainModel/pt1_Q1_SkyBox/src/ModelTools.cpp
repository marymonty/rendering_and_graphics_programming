#include "ModelTools.h"
//#include "Enum.h"
//#include <math.h>
#include "Matrix.h"
#include <assert.h>
#include "Model.h"
#include "d3dUtil.h"


/// Creates the unit box centered at the origin
void ModelTools::CreateUnitBox(StandardVertex *&pVerts, int& nverts, TriangleByIndex *&pTriList, int& ntri)
{
	nverts = 8;
	pVerts = new StandardVertex[nverts];
	ntri = 12;
	pTriList = new TriangleByIndex[ntri];

	pVerts[0].set(-0.5f, -0.5f, -0.5f, Colors::Black);
	pVerts[1].set(-0.5f, +0.5f, -0.5f, Colors::Lime);
	pVerts[2].set(+0.5f, +0.5f, -0.5f, Colors::Yellow);
	pVerts[3].set(+0.5f, -0.5f, -0.5f, Colors::Red );
	pVerts[4].set(-0.5f, -0.5f, +0.5f, Colors::Blue);
	pVerts[5].set(-0.5f, +0.5f, +0.5f, Colors::Cyan);
	pVerts[6].set(+0.5f, +0.5f, +0.5f, Colors::White);
	pVerts[7].set(+0.5f, -0.5f, +0.5f, Colors::Magenta);

	// back face
	pTriList[0].set(0, 1, 2);
	pTriList[1].set(0, 2, 3);

	// front face
	pTriList[2].set(4, 6, 5);
	pTriList[3].set(4, 7, 6);

	// left face
	pTriList[4].set(4, 5, 1);
	pTriList[5].set(4, 1, 0);

	// right face
	pTriList[6].set(3, 2, 6);
	pTriList[7].set(3, 6, 7);

	// top face
	pTriList[8].set(1, 5, 6);
	pTriList[9].set(1, 6, 2);

	// bottom face
	pTriList[10].set(4, 0, 3);
	pTriList[11].set(4, 3, 7);
}

void ModelTools::CreateUnitBoxRepTexture(StandardVertex *&pVerts, int& nverts, TriangleByIndex *&pTriList, int& ntri)
{
	nverts = 24;
	pVerts = new StandardVertex[nverts];
	ntri = 12;
	pTriList = new TriangleByIndex[ntri];



	// Setting up faces
	// Forward
	int vind = 0;
	int tind = 0;
	pVerts[vind].set(0.5f, 0.5f, 0.5f, 1, 0);
	pVerts[vind + 1].set(-0.5f, 0.5f, 0.5f, 0, 0);
	pVerts[vind + 2].set(-0.5f, -0.5f, 0.5f, 0, 1);
	pVerts[vind + 3].set(0.5f, -0.5f, 0.5f, 1, 1);
	pTriList[tind].set(vind, vind + 1, vind + 2);
	pTriList[tind + 1].set(vind, vind + 2, vind + 3);

	// Back
	vind += 4;
	tind += 2;
	//*
	pVerts[vind].set(0.5f, 0.5f, -0.5f, 0, 0);
	pVerts[vind + 1].set(-0.5f, 0.5f, -0.5f, 1, 0);
	pVerts[vind + 2].set(-0.5f, -0.5f, -0.5f, 1, 1);
	pVerts[vind + 3].set(0.5f, -0.5f, -0.5f, 0, 1);
	pTriList[tind].set(vind + 2, vind + 1, vind);
	pTriList[tind + 1].set(vind + 3, vind + 2, vind);

	// Left
	vind += 4;
	tind += 2;
	pVerts[vind].set(0.5f, 0.5f, -0.5f, 1, 0);
	pVerts[vind + 1].set(0.5f, 0.5f, 0.5f, 0, 0);
	pVerts[vind + 2].set(0.5f, -0.5f, 0.5f, 0, 1);
	pVerts[vind + 3].set(0.5f, -0.5f, -0.5f, 1, 1);
	pTriList[tind].set(vind, vind + 1, vind + 2);
	pTriList[tind + 1].set(vind, vind + 2, vind + 3);

	// Right
	vind += 4;
	tind += 2;
	pVerts[vind].set(-0.5f, 0.5f, 0.5f, 1, 0);
	pVerts[vind + 1].set(-0.5f, 0.5f, -0.5f, 0, 0);
	pVerts[vind + 2].set(-0.5f, -0.5f, -0.5f, 0, 1);
	pVerts[vind + 3].set(-0.5f, -0.5f, 0.5f, 1, 1);
	pTriList[tind].set(vind, vind + 1, vind + 2);
	pTriList[tind + 1].set(vind, vind + 2, vind + 3);

	// Top
	vind += 4;
	tind += 2;
	pVerts[vind].set(0.5f, 0.5f, -0.5f, 1, 0);
	pVerts[vind + 1].set(-0.5f, 0.5f, -0.5f, 0, 0);
	pVerts[vind + 2].set(-0.5f, 0.5f, 0.5f, 0, 1);
	pVerts[vind + 3].set(0.5f, 0.5f, 0.5f, 1, 1);
	pTriList[tind].set(vind, vind + 1, vind + 2);
	pTriList[tind + 1].set(vind, vind + 2, vind + 3);

	// Bottom
	vind += 4;
	tind += 2;
	pVerts[vind].set(0.5f, -0.5f, 0.5f, 1, 0);
	pVerts[vind + 1].set(-0.5f, -0.5f, 0.5f, 0, 0);
	pVerts[vind + 2].set(-0.5f, -0.5f, -0.5f, 0, 1);
	pVerts[vind + 3].set(0.5f, -0.5f, -0.5f, 1, 1);
	pTriList[tind].set(vind, vind + 1, vind + 2);
	pTriList[tind + 1].set(vind, vind + 2, vind + 3);
}


// CreateUnitBoxSixFaceTexture
// textures a box using an unwrapped UV map
void ModelTools::CreateUnitBoxSixFaceTexture(StandardVertex*& pVerts, int& nverts, TriangleByIndex*& pTriList, int& ntri)
{
	// the only difference between this code and the repeated texture code
	// is the UV coordinates in the pVerts set functions
	nverts = 24;
	pVerts = new StandardVertex[nverts];
	ntri = 12;
	pTriList = new TriangleByIndex[ntri];


	// Setting up faces
	// Forward
	int vind = 0;
	int tind = 0;
	// (0, .375), (0, .625), (.25, .375), (.25, .625) 
	pVerts[vind].set(0.5f, 0.5f, 0.5f, 0.25f, 0.625f);	
	pVerts[vind + 1].set(-0.5f, 0.5f, 0.5f, 0.25f, 0.375f);
	pVerts[vind + 2].set(-0.5f, -0.5f, 0.5f, 0, 0.375f);
	pVerts[vind + 3].set(0.5f, -0.5f, 0.5f, 0, 0.625f);
	pTriList[tind].set(vind, vind + 1, vind + 2);
	pTriList[tind + 1].set(vind, vind + 2, vind + 3);

	// Back
	vind += 4;
	tind += 2;
	// (.5, .375), (.5, .625), (.75, .375), (.75, .375)
	pVerts[vind].set(0.5f, 0.5f, -0.5f, 0.5f, 0.625f);
	pVerts[vind + 1].set(-0.5f, 0.5f, -0.5f, 0.5f, 0.375f);	
	pVerts[vind + 2].set(-0.5f, -0.5f, -0.5f, 0.75f, 0.375f);
	pVerts[vind + 3].set(0.5f, -0.5f, -0.5f, 0.75f, 0.625f);
	pTriList[tind].set(vind + 2, vind + 1, vind);
	pTriList[tind + 1].set(vind + 3, vind + 2, vind);

	// right
	vind += 4;
	tind += 2;
	// (.25, .125), (.5, .125), (.25, .375), (.5, .375)
	pVerts[vind].set(0.5f, 0.5f, -0.5f, 0.5f, 0.625f);		
	pVerts[vind + 1].set(0.5f, 0.5f, 0.5f, 0.25f, 0.625f);
	pVerts[vind + 2].set(0.5f, -0.5f, 0.5f, 0.25f, 0.875f);
	pVerts[vind + 3].set(0.5f, -0.5f, -0.5f, 0.5f, 0.875f);
	pTriList[tind].set(vind, vind + 1, vind + 2);
	pTriList[tind + 1].set(vind, vind + 2, vind + 3);

	// left
	vind += 4;
	tind += 2;
	// (.25, .625), (.5, .625), (.25, .875), (.5, .875)
	pVerts[vind].set(-0.5f, 0.5f, 0.5f, 0.25f, 0.375f);
	pVerts[vind + 1].set(-0.5f, 0.5f, -0.5f, 0.5f, 0.375f);
	pVerts[vind + 2].set(-0.5f, -0.5f, -0.5f, 0.5f, 0.125f);
	pVerts[vind + 3].set(-0.5f, -0.5f, 0.5f, 0.25f, 0.125f);
	pTriList[tind].set(vind, vind + 1, vind + 2);
	pTriList[tind + 1].set(vind, vind + 2, vind + 3);

	// Top
	vind += 4;
	tind += 2;
	// (.25, .375), (.5, .375), (.25, .625), (.5, .625)
	pVerts[vind].set(0.5f, 0.5f, -0.5f, 0.5f, 0.625f);
	pVerts[vind + 1].set(-0.5f, 0.5f, -0.5f, 0.5f, 0.375f);
	pVerts[vind + 2].set(-0.5f, 0.5f, 0.5f, 0.25f, 0.375f);
	pVerts[vind + 3].set(0.5f, 0.5f, 0.5f, 0.25f, 0.625f);
	pTriList[tind].set(vind, vind + 1, vind + 2);
	pTriList[tind + 1].set(vind, vind + 2, vind + 3);

	// Bottom
	vind += 4;
	tind += 2;
	// (.75, .375), (1, .375), (.75, .625), (1, .625)
	pVerts[vind].set(0.5f, -0.5f, 0.5f, 1, 0.625f);
	pVerts[vind + 1].set(-0.5f, -0.5f, 0.5f, 1, 0.375f);
	pVerts[vind + 2].set(-0.5f, -0.5f, -0.5f, 0.75f, 0.375f);
	pVerts[vind + 3].set(0.5f, -0.5f, -0.5f, 0.75f, 0.625f);
	pTriList[tind].set(vind, vind + 1, vind + 2);
	pTriList[tind + 1].set(vind, vind + 2, vind + 3);
}



// CreateSkyBox
// textures a box using an unwrapped SkyBox UV map
void ModelTools::CreateSkyBoxTexture(StandardVertex*& pVerts, int& nverts, TriangleByIndex*& pTriList, int& ntri)
{
	// same verts and tris as all other cubes
	nverts = 24;
	pVerts = new StandardVertex[nverts];
	ntri = 12;
	pTriList = new TriangleByIndex[ntri];


	// all of these need to be inverted so the textures face
	// the inside of the box I think

	//*
	// Setting up faces
	// Forward
	int vind = 0;
	int tind = 0;
	// (.25, .33), (.25, .66), (.5, .33), (.5, .66) 
	pVerts[vind].set(0.5f, 0.5f, 0.5f, 0.5f, 0.33f);
	pVerts[vind + 1].set(-0.5f, 0.5f, 0.5f, 0.25f, 0.33f);
	pVerts[vind + 2].set(-0.5f, -0.5f, 0.5f, 0.25f, 0.66f);
	pVerts[vind + 3].set(0.5f, -0.5f, 0.5f, 0.5, 0.66f);
	pTriList[tind].set(vind, vind + 1, vind + 2);
	pTriList[tind + 1].set(vind, vind + 2, vind + 3);

	// Back
	vind += 4;
	tind += 2;
	// (.75, .33), (.75, .66), (1, .33), (1, .66)
	pVerts[vind].set(0.5f, 0.5f, -0.5f, 0.75f, 0.33f);
	pVerts[vind + 1].set(-0.5f, 0.5f, -0.5f, 1, 0.33f);
	pVerts[vind + 2].set(-0.5f, -0.5f, -0.5f, 1, 0.66f);
	pVerts[vind + 3].set(0.5f, -0.5f, -0.5f, 0.75f, 0.66f);
	pTriList[tind].set(vind + 2, vind + 1, vind);
	pTriList[tind + 1].set(vind + 3, vind + 2, vind);

	// right
	vind += 4;
	tind += 2;
	// (.5, .33), (.5, .66), (.75, .33), (.75, .66)
	// prob not (0, .33), (0, .66), (.25, .33), (.25, .66)
	pVerts[vind].set(0.5f, 0.5f, -0.5f, 0.75f, 0.33f);
	pVerts[vind + 1].set(0.5f, 0.5f, 0.5f, 0.5f, 0.33f);
	pVerts[vind + 2].set(0.5f, -0.5f, 0.5f, 0.5f, 0.66f);
	pVerts[vind + 3].set(0.5f, -0.5f, -0.5f, 0.75f, 0.66f);
	pTriList[tind].set(vind, vind + 1, vind + 2);
	pTriList[tind + 1].set(vind, vind + 2, vind + 3);

	// left
	vind += 4;
	tind += 2;
	// (0, .33), (0, .66), (.25, .33), (.25, .66)
	pVerts[vind].set(-0.5f, 0.5f, 0.5f, 0.25f, 0.33f);
	pVerts[vind + 1].set(-0.5f, 0.5f, -0.5f, 0, 0.33f);
	pVerts[vind + 2].set(-0.5f, -0.5f, -0.5f, 0, 0.66f);
	pVerts[vind + 3].set(-0.5f, -0.5f, 0.5f, 0.25f, 0.66f);
	pTriList[tind].set(vind, vind + 1, vind + 2);
	pTriList[tind + 1].set(vind, vind + 2, vind + 3);

	// Top
	vind += 4;
	tind += 2;
	// (.25, 0), (.25, .33), (.5, 0), (.5, .33)
	pVerts[vind].set(0.5f, 0.5f, -0.5f, 0.5f, 0.33f);
	pVerts[vind + 1].set(-0.5f, 0.5f, -0.5f, 0.5f, 0);
	pVerts[vind + 2].set(-0.5f, 0.5f, 0.5f, 0.25f, 0);
	pVerts[vind + 3].set(0.5f, 0.5f, 0.5f, 0.25f, 0.33f);
	pTriList[tind].set(vind, vind + 1, vind + 2);
	pTriList[tind + 1].set(vind, vind + 2, vind + 3);

	// Bottom
	vind += 4;
	tind += 2;
	// (.25, .66), (.25, 1), (.5, .66), (.5, 1)
	pVerts[vind].set(0.5f, -0.5f, 0.5f, 0.5f, 0.66f);
	pVerts[vind + 1].set(-0.5f, -0.5f, 0.5f, 0.25f, 0.66f);
	pVerts[vind + 2].set(-0.5f, -0.5f, -0.5f, 0.25f, 1);
	pVerts[vind + 3].set(0.5f, -0.5f, -0.5f, 0.5f, 1);
	pTriList[tind].set(vind, vind + 1, vind + 2);
	pTriList[tind + 1].set(vind, vind + 2, vind + 3);
	//*/
}
