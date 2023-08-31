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
	pVerts[vind].set(0.5f, 0.5f, -0.5f, 0, 0);
	pVerts[vind + 1].set(-0.5f, 0.5f, -0.5f, 1, 0);
	pVerts[vind + 2].set(-0.5f, -0.5f, -0.5f, 1, 1);
	pVerts[vind + 3].set(0.5f, -0.5f, -0.5f, 0, 1);
	/*  
	// used to demo texture address modes
	pVerts[vind].set(0.5f, 0.5f, -0.5f, -3, -3);
	pVerts[vind + 1].set(-0.5f, 0.5f, -0.5f, 3, -3);
	pVerts[vind + 2].set(-0.5f, -0.5f, -0.5f, 3, 3);
	pVerts[vind + 3].set(0.5f, -0.5f, -0.5f, -3, 3);
	//*/
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


// CreatUnitPyramid constructor
// creates a 4 sided pyramid centered on the origin with height, width, and depth equal to 1
void ModelTools::CreateUnitPyramid(StandardVertex*& pVerts, int& nverts, TriangleByIndex*& pTriList, int& ntri)
{
	// 5 verts - bottom square and top point
	nverts = 5;
	pVerts = new StandardVertex[nverts];
	// 6 triangles - two for bottom square, four to make up the sides
	ntri = 6;
	pTriList = new TriangleByIndex[ntri];

	pVerts[0].set(0.0f, 1.0f, 0.0f, Colors::White);			//lime
	pVerts[1].set(-1.0f, -1.0f, -1.0f, Colors::White);		//black
	pVerts[2].set(+1.0f, -1.0f, -1.0f, Colors::White);		//red
	pVerts[3].set(+1.0f, -1.0f, +1.0f, Colors::White);		//magenta
	pVerts[4].set(-1.0f, -1.0f, +1.0f, Colors::White);		//blue

	// back face
	pTriList[0].set(0, 2, 1);

	// front face
	pTriList[1].set(0, 4, 3);

	// left face
	pTriList[2].set(0, 3, 2);

	// right face
	pTriList[3].set(0, 1, 4);

	// bottom square faces
	pTriList[4].set(1, 2, 3);
	pTriList[5].set(1, 3, 4);
}


// CreateUnitPyramidRepTexture
void ModelTools::CreateUnitPyramidRepTexture(StandardVertex*& pVerts, int& nverts, TriangleByIndex*& pTriList, int& ntri)
{
	// 3 verts per upper triangle - no repeating verts for UV texture
	// 4 triangles + 1 square (which has 4 verts) in the pyramid
	nverts = 16;
	pVerts = new StandardVertex[nverts];
	ntri = 6;
	pTriList = new TriangleByIndex[ntri];



	// Setting up faces
	// back face
	int vertInd = 0;
	int triInd = 0;
	// set( vert X, vert Y, vert Z, u, v)
	pVerts[vertInd].set(0.0f, 1.0f, 0.0f, 0.5f, 0);
	pVerts[vertInd + 1].set(1.0f, -1.0f, -1.0f, 0, 1);
	pVerts[vertInd + 2].set(-1.0f, -1.0f, -1.0f, 1, 1);
	pTriList[triInd].set(vertInd, vertInd + 1, vertInd + 2);

	// front face
	vertInd += 3;
	triInd += 1;
	pVerts[vertInd].set(0.0f, 1.0f, 0.0f, 0.5f, 0);
	pVerts[vertInd + 1].set(-1.0f, -1.0f, 1.0f, 0, 1);
	pVerts[vertInd + 2].set(1.0f, -1.0f, 1.0f, 1, 1);
	pTriList[triInd].set(vertInd, vertInd + 1, vertInd + 2);

	// left face
	vertInd += 3;
	triInd += 1;
	pVerts[vertInd].set(0.0f, 1.0f, 0.0f, 0.5f, 0);
	pVerts[vertInd + 1].set(+1.0f, -1.0f, +1.0f, 0, 1);
	pVerts[vertInd + 2].set(+1.0f, -1.0f, -1.0f, 1, 1);
	pTriList[triInd].set(vertInd, vertInd + 1, vertInd + 2);

	// right face
	vertInd += 3;
	triInd += 1;
	pVerts[vertInd].set(0.0f, 1.0f, 0.0f, 0.5f, 0);
	pVerts[vertInd + 1].set(-1.0f, -1.0f, -1.0f, 0, 1);
	pVerts[vertInd + 2].set(-1.0f, -1.0f, +1.0f, 1, 1);
	pTriList[triInd].set(vertInd, vertInd + 1, vertInd + 2);

	// bottom square
	vertInd += 3;
	triInd += 1;
	pVerts[vertInd].set(-1.0f, -1.0f, -1.0f, 0, 0);
	pVerts[vertInd + 1].set(+1.0f, -1.0f, -1.0f, 0, 1);
	pVerts[vertInd + 2].set(+1.0f, -1.0f, +1.0f, 1, 1);
	pVerts[vertInd + 3].set(-1.0f, -1.0f, +1.0f, 1, 0);
	pTriList[triInd].set(vertInd, vertInd + 1, vertInd + 2);
	pTriList[triInd + 1].set(vertInd, vertInd + 2, vertInd + 3);
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


