#include "ModelTools.h"
//#include "Enum.h"
//#include <math.h>
#include "Matrix.h"
#include <assert.h>
#include "Model.h"
#include "d3dUtil.h"


// MARY
// adding normals to all our models


/// Creates the unit box centered at the origin
void ModelTools::CreateUnitBox(StandardVertex *&pVerts, int& nverts, TriangleByIndex *&pTriList, int& ntri)
{
	nverts = 8;
	pVerts = new StandardVertex[nverts];
	ntri = 12;
	pTriList = new TriangleByIndex[ntri];

	// MARY
	// we need to duplicate vertices to set the correct normal for each face's vertices
	// copy from create unit box six face texture

	// Forward
	int vind = 0;
	int tind = 0;
	pVerts[vind].set(0.5f, 0.5f, 0.5f, 1, 0, 0, 0, 1);
	pVerts[vind + 1].set(-0.5f, 0.5f, 0.5f, 0, 0, 0, 0, 1);
	pVerts[vind + 2].set(-0.5f, -0.5f, 0.5f, 0, 1, 0, 0, 1);
	pVerts[vind + 3].set(0.5f, -0.5f, 0.5f, 1, 1, 0, 0, 1);
	pTriList[tind].set(vind, vind + 1, vind + 2);
	pTriList[tind + 1].set(vind, vind + 2, vind + 3);

	// Back
	vind += 4;
	tind += 2;
	pVerts[vind].set(0.5f, 0.5f, -0.5f, 0, 0, 0, 0, -1);
	pVerts[vind + 1].set(-0.5f, 0.5f, -0.5f, 1, 0, 0, 0, -1);
	pVerts[vind + 2].set(-0.5f, -0.5f, -0.5f, 1, 1, 0, 0, -1);
	pVerts[vind + 3].set(0.5f, -0.5f, -0.5f, 0, 1, 0, 0, -1);
	pTriList[tind].set(vind + 2, vind + 1, vind);
	pTriList[tind + 1].set(vind + 3, vind + 2, vind);

	// Left
	vind += 4;
	tind += 2;
	pVerts[vind].set(0.5f, 0.5f, -0.5f, 1, 0, 1, 0, 0);
	pVerts[vind + 1].set(0.5f, 0.5f, 0.5f, 0, 0, 1, 0, 0);
	pVerts[vind + 2].set(0.5f, -0.5f, 0.5f, 0, 1, 1, 0, 0);
	pVerts[vind + 3].set(0.5f, -0.5f, -0.5f, 1, 1, 1, 0, 0);
	pTriList[tind].set(vind, vind + 1, vind + 2);
	pTriList[tind + 1].set(vind, vind + 2, vind + 3);

	// Right
	vind += 4;
	tind += 2;
	pVerts[vind].set(-0.5f, 0.5f, 0.5f, 1, 0, -1, 0, 0);
	pVerts[vind + 1].set(-0.5f, 0.5f, -0.5f, 0, 0, -1, 0, 0);
	pVerts[vind + 2].set(-0.5f, -0.5f, -0.5f, 0, 1, -1, 0, 0);
	pVerts[vind + 3].set(-0.5f, -0.5f, 0.5f, 1, 1, -1, 0, 0);
	pTriList[tind].set(vind, vind + 1, vind + 2);
	pTriList[tind + 1].set(vind, vind + 2, vind + 3);

	// Top
	vind += 4;
	tind += 2;
	pVerts[vind].set(0.5f, 0.5f, -0.5f, 1, 0, 0, 1, 0);
	pVerts[vind + 1].set(-0.5f, 0.5f, -0.5f, 0, 0, 0, 1, 0);
	pVerts[vind + 2].set(-0.5f, 0.5f, 0.5f, 0, 1, 0, 1, 0);
	pVerts[vind + 3].set(0.5f, 0.5f, 0.5f, 1, 1, 0, 1, 0);
	pTriList[tind].set(vind, vind + 1, vind + 2);
	pTriList[tind + 1].set(vind, vind + 2, vind + 3);

	// Bottom
	vind += 4;
	tind += 2;
	pVerts[vind].set(0.5f, -0.5f, 0.5f, 1, 0, 0, -1, 0);
	pVerts[vind + 1].set(-0.5f, -0.5f, 0.5f, 0, 0, 0, -1, 0);
	pVerts[vind + 2].set(-0.5f, -0.5f, -0.5f, 0, 1, 0, -1, 0);
	pVerts[vind + 3].set(0.5f, -0.5f, -0.5f, 1, 1, 0, -1, 0);
	pTriList[tind].set(vind, vind + 1, vind + 2);
	pTriList[tind + 1].set(vind, vind + 2, vind + 3);
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
	pVerts[vind].set(0.5f, 0.5f, 0.5f, 1, 0, 0, 0, 1 );
	pVerts[vind + 1].set(-0.5f, 0.5f, 0.5f, 0, 0, 0, 0, 1);
	pVerts[vind + 2].set(-0.5f, -0.5f, 0.5f, 0, 1, 0, 0, 1);
	pVerts[vind + 3].set(0.5f, -0.5f, 0.5f, 1, 1, 0, 0, 1);
	pTriList[tind].set(vind, vind + 1, vind + 2);
	pTriList[tind + 1].set(vind, vind + 2, vind + 3);

	// Back
	vind += 4;
	tind += 2;
	pVerts[vind].set(0.5f, 0.5f, -0.5f, 0, 0, 0, 0, -1);
	pVerts[vind + 1].set(-0.5f, 0.5f, -0.5f, 1, 0, 0, 0, -1);
	pVerts[vind + 2].set(-0.5f, -0.5f, -0.5f, 1, 1, 0, 0, -1);
	pVerts[vind + 3].set(0.5f, -0.5f, -0.5f, 0, 1, 0, 0, -1);
	pTriList[tind].set(vind + 2, vind + 1, vind);
	pTriList[tind + 1].set(vind + 3, vind + 2, vind);

	// Left
	vind += 4;
	tind += 2;
	pVerts[vind].set(0.5f, 0.5f, -0.5f, 1, 0, 1, 0, 0);
	pVerts[vind + 1].set(0.5f, 0.5f, 0.5f, 0, 0, 1, 0, 0);
	pVerts[vind + 2].set(0.5f, -0.5f, 0.5f, 0, 1, 1, 0, 0);
	pVerts[vind + 3].set(0.5f, -0.5f, -0.5f, 1, 1, 1, 0, 0);
	pTriList[tind].set(vind, vind + 1, vind + 2);
	pTriList[tind + 1].set(vind, vind + 2, vind + 3);

	// Right
	vind += 4;
	tind += 2;
	pVerts[vind].set(-0.5f, 0.5f, 0.5f, 1, 0, -1, 0, 0);
	pVerts[vind + 1].set(-0.5f, 0.5f, -0.5f, 0, 0, -1, 0, 0);
	pVerts[vind + 2].set(-0.5f, -0.5f, -0.5f, 0, 1, -1, 0, 0);
	pVerts[vind + 3].set(-0.5f, -0.5f, 0.5f, 1, 1, -1, 0, 0);
	pTriList[tind].set(vind, vind + 1, vind + 2);
	pTriList[tind + 1].set(vind, vind + 2, vind + 3);

	// Top
	vind += 4;
	tind += 2;
	pVerts[vind].set(0.5f, 0.5f, -0.5f, 1, 0, 0, 1, 0);
	pVerts[vind + 1].set(-0.5f, 0.5f, -0.5f, 0, 0, 0, 1, 0);
	pVerts[vind + 2].set(-0.5f, 0.5f, 0.5f, 0, 1, 0, 1, 0);
	pVerts[vind + 3].set(0.5f, 0.5f, 0.5f, 1, 1, 0, 1, 0);
	pTriList[tind].set(vind, vind + 1, vind + 2);
	pTriList[tind + 1].set(vind, vind + 2, vind + 3);

	// Bottom
	vind += 4;
	tind += 2;
	pVerts[vind].set(0.5f, -0.5f, 0.5f, 1, 0, 0, -1, 0);
	pVerts[vind + 1].set(-0.5f, -0.5f, 0.5f, 0, 0, 0, -1, 0);
	pVerts[vind + 2].set(-0.5f, -0.5f, -0.5f, 0, 1, 0, -1, 0);
	pVerts[vind + 3].set(0.5f, -0.5f, -0.5f, 1, 1, 0, -1, 0);
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


	// MARY
	// add normals
	// the normals are aligned to whatever axis is perpendicular to the face of the vertex
	// so for forward, our normals are pointing perpendicular out of our forward face, which points
	// directly forward along the positive Z axis (0, 0, 1)
	// for right face, our normals point perpendicular out of our right face, which points 
	// in the negative x direction (-1, 0, 0), etc

	// Setting up faces
	// Forward
	int vind = 0;
	int tind = 0;
	// (0, .375), (0, .625), (.25, .375), (.25, .625) 
	pVerts[vind].set(0.5f, 0.5f, 0.5f, 0.25f, 0.625f, 0, 0, 1);
	pVerts[vind + 1].set(-0.5f, 0.5f, 0.5f, 0.25f, 0.375f, 0, 0, 1);
	pVerts[vind + 2].set(-0.5f, -0.5f, 0.5f, 0, 0.375f, 0, 0, 1);
	pVerts[vind + 3].set(0.5f, -0.5f, 0.5f, 0, 0.625f, 0, 0, 1);
	pTriList[tind].set(vind, vind + 1, vind + 2);
	pTriList[tind + 1].set(vind, vind + 2, vind + 3);

	// Back
	vind += 4;
	tind += 2;
	// (.5, .375), (.5, .625), (.75, .375), (.75, .375)
	pVerts[vind].set(0.5f, 0.5f, -0.5f, 0.5f, 0.625f, 0, 0, -1);
	pVerts[vind + 1].set(-0.5f, 0.5f, -0.5f, 0.5f, 0.375f, 0, 0, -1);
	pVerts[vind + 2].set(-0.5f, -0.5f, -0.5f, 0.75f, 0.375f, 0, 0, -1);
	pVerts[vind + 3].set(0.5f, -0.5f, -0.5f, 0.75f, 0.625f, 0, 0, -1);
	pTriList[tind].set(vind + 2, vind + 1, vind);
	pTriList[tind + 1].set(vind + 3, vind + 2, vind);

	// right
	vind += 4;
	tind += 2;
	// (.25, .125), (.5, .125), (.25, .375), (.5, .375)
	pVerts[vind].set(0.5f, 0.5f, -0.5f, 0.5f, 0.625f, -1, 0, 0);
	pVerts[vind + 1].set(0.5f, 0.5f, 0.5f, 0.25f, 0.625f, -1, 0, 0);
	pVerts[vind + 2].set(0.5f, -0.5f, 0.5f, 0.25f, 0.875f, -1, 0, 0);
	pVerts[vind + 3].set(0.5f, -0.5f, -0.5f, 0.5f, 0.875f, -1, 0, 0);
	pTriList[tind].set(vind, vind + 1, vind + 2);
	pTriList[tind + 1].set(vind, vind + 2, vind + 3);

	// left
	vind += 4;
	tind += 2;
	// (.25, .625), (.5, .625), (.25, .875), (.5, .875)
	pVerts[vind].set(-0.5f, 0.5f, 0.5f, 0.25f, 0.375f, 1, 0, 0);
	pVerts[vind + 1].set(-0.5f, 0.5f, -0.5f, 0.5f, 0.375f, 1, 0, 0);
	pVerts[vind + 2].set(-0.5f, -0.5f, -0.5f, 0.5f, 0.125f, 1, 0, 0);
	pVerts[vind + 3].set(-0.5f, -0.5f, 0.5f, 0.25f, 0.125f, 1, 0, 0);
	pTriList[tind].set(vind, vind + 1, vind + 2);
	pTriList[tind + 1].set(vind, vind + 2, vind + 3);

	// Top
	vind += 4;
	tind += 2;
	// (.25, .375), (.5, .375), (.25, .625), (.5, .625)
	pVerts[vind].set(0.5f, 0.5f, -0.5f, 0.5f, 0.625f, 0, 1, 0);
	pVerts[vind + 1].set(-0.5f, 0.5f, -0.5f, 0.5f, 0.375f, 0, 1, 0);
	pVerts[vind + 2].set(-0.5f, 0.5f, 0.5f, 0.25f, 0.375f, 0, 1, 0);
	pVerts[vind + 3].set(0.5f, 0.5f, 0.5f, 0.25f, 0.625f, 0, 1, 0);
	pTriList[tind].set(vind, vind + 1, vind + 2);
	pTriList[tind + 1].set(vind, vind + 2, vind + 3);

	// Bottom
	vind += 4;
	tind += 2;
	// (.75, .375), (1, .375), (.75, .625), (1, .625)
	pVerts[vind].set(0.5f, -0.5f, 0.5f, 1, 0.625f, 0, -1, 0);
	pVerts[vind + 1].set(-0.5f, -0.5f, 0.5f, 1, 0.375f, 0, -1, 0);
	pVerts[vind + 2].set(-0.5f, -0.5f, -0.5f, 0.75f, 0.375f, 0, -1, 0);
	pVerts[vind + 3].set(0.5f, -0.5f, -0.5f, 0.75f, 0.625f, 0, -1, 0);
	pTriList[tind].set(vind, vind + 1, vind + 2);
	pTriList[tind + 1].set(vind, vind + 2, vind + 3);
}



// implementing CreatUnitPyramid constructor
// creates a 4 sided pyramid centered on the origin with height, width, and depth equal to 1
void ModelTools::CreateUnitPyramid(StandardVertex*& pVerts, int& nverts, TriangleByIndex*& pTriList, int& ntri)
{
	nverts = 16;
	pVerts = new StandardVertex[nverts];
	ntri = 6;
	pTriList = new TriangleByIndex[ntri];

	// MARY
	// need to duplicate verts for differing normals
	// the vertex normal is equal to the normal of the face, which is found
	// using the three verts of the face

	// back face
	int vertInd = 0;
	int triInd = 0;
	// set( vert X, vert Y, vert Z, u, v)
	Vect norm = normalizePyramidSides(Vect(0.0f, 1.0f, 0.0f), Vect(1.0f, -1.0f, -1.0f), Vect(-1.0f, -1.0f, -1.0f));
	pVerts[vertInd].set(0.0f, 1.0f, 0.0f, 0.5f, 0, norm.X(), norm.Y(), norm.Z());
	pVerts[vertInd + 1].set(1.0f, -1.0f, -1.0f, 0, 1, norm.X(), norm.Y(), norm.Z());
	pVerts[vertInd + 2].set(-1.0f, -1.0f, -1.0f, 1, 1, norm.X(), norm.Y(), norm.Z());
	pTriList[triInd].set(vertInd, vertInd + 1, vertInd + 2);

	// front face
	vertInd += 3;
	triInd += 1;
	norm = normalizePyramidSides(Vect(0.0f, 1.0f, 0.0f), Vect(-1.0f, -1.0f, 1.0f), Vect(1.0f, -1.0f, 1.0f));
	pVerts[vertInd].set(0.0f, 1.0f, 0.0f, 0.5f, 0, norm.X(), norm.Y(), norm.Z());
	pVerts[vertInd + 1].set(-1.0f, -1.0f, 1.0f, 0, 1, norm.X(), norm.Y(), norm.Z());
	pVerts[vertInd + 2].set(1.0f, -1.0f, 1.0f, 1, 1, norm.X(), norm.Y(), norm.Z());
	pTriList[triInd].set(vertInd, vertInd + 1, vertInd + 2);

	// left face
	vertInd += 3;
	triInd += 1;
	norm = normalizePyramidSides(Vect(0.0f, 1.0f, 0.0f), Vect(+1.0f, -1.0f, +1.0f), Vect(+1.0f, -1.0f, -1.0f));
	pVerts[vertInd].set(0.0f, 1.0f, 0.0f, 0.5f, 0, norm.X(), norm.Y(), norm.Z());
	pVerts[vertInd + 1].set(+1.0f, -1.0f, +1.0f, 0, 1, norm.X(), norm.Y(), norm.Z());
	pVerts[vertInd + 2].set(+1.0f, -1.0f, -1.0f, 1, 1, norm.X(), norm.Y(), norm.Z());
	pTriList[triInd].set(vertInd, vertInd + 1, vertInd + 2);

	// right face
	vertInd += 3;
	triInd += 1;
	norm = normalizePyramidSides(Vect(0.0f, 1.0f, 0.0f), Vect(-1.0f, -1.0f, -1.0f), Vect(-1.0f, -1.0f, +1.0f));
	pVerts[vertInd].set(0.0f, 1.0f, 0.0f, 0.5f, 0, norm.X(), norm.Y(), norm.Z());
	pVerts[vertInd + 1].set(-1.0f, -1.0f, -1.0f, 0, 1, norm.X(), norm.Y(), norm.Z());
	pVerts[vertInd + 2].set(-1.0f, -1.0f, +1.0f, 1, 1, norm.X(), norm.Y(), norm.Z());
	pTriList[triInd].set(vertInd, vertInd + 1, vertInd + 2);

	// bottom square
	vertInd += 3;
	triInd += 1;
	pVerts[vertInd].set(-1.0f, -1.0f, -1.0f, 0, 0, 0, -1, 0);
	pVerts[vertInd + 1].set(+1.0f, -1.0f, -1.0f, 0, 1, 0, -1, 0);
	pVerts[vertInd + 2].set(+1.0f, -1.0f, +1.0f, 1, 1, 0, -1, 0);
	pVerts[vertInd + 3].set(-1.0f, -1.0f, +1.0f, 1, 0, 0, -1, 0);
	pTriList[triInd].set(vertInd, vertInd + 1, vertInd + 2);
	pTriList[triInd + 1].set(vertInd, vertInd + 2, vertInd + 3);
}

// MARY
// CreateUnitPyramidTexture
void ModelTools::CreateUnitPyramidRepTexture(StandardVertex*& pVerts, int& nverts, TriangleByIndex*& pTriList, int& ntri)
{
	// 3 verts per upper triangle - no repeating verts for UV texture
	// 4 triangles + 1 square (which has 4 verts) in the pyramid
	nverts = 16;
	pVerts = new StandardVertex[nverts];
	ntri = 6;
	pTriList = new TriangleByIndex[ntri];


	// back face
	int vertInd = 0;
	int triInd = 0;
	// set( vert X, vert Y, vert Z, u, v)
	Vect norm = normalizePyramidSides(Vect(0.0f, 1.0f, 0.0f), Vect(1.0f, -1.0f, -1.0f), Vect(-1.0f, -1.0f, -1.0f));
	pVerts[vertInd].set(0.0f, 1.0f, 0.0f, 0.5f, 0, norm, Colors::White);
	pVerts[vertInd + 1].set(1.0f, -1.0f, -1.0f, 0, 1, norm, Colors::White);
	pVerts[vertInd + 2].set(-1.0f, -1.0f, -1.0f, 1, 1, norm, Colors::White);
	pTriList[triInd].set(vertInd, vertInd + 1, vertInd + 2);

	// front face
	vertInd += 3;
	triInd += 1;
	norm = normalizePyramidSides(Vect(0.0f, 1.0f, 0.0f), Vect(-1.0f, -1.0f, 1.0f), Vect(1.0f, -1.0f, 1.0f));
	pVerts[vertInd].set(0.0f, 1.0f, 0.0f, 0.5f, 0, norm, Colors::White);
	pVerts[vertInd + 1].set(-1.0f, -1.0f, 1.0f, 0, 1, norm, Colors::White);
	pVerts[vertInd + 2].set(1.0f, -1.0f, 1.0f, 1, 1, norm, Colors::White);
	pTriList[triInd].set(vertInd, vertInd + 1, vertInd + 2);

	// left face
	vertInd += 3;
	triInd += 1;
	norm = normalizePyramidSides(Vect(0.0f, 1.0f, 0.0f), Vect(+1.0f, -1.0f, +1.0f), Vect(+1.0f, -1.0f, -1.0f));
	pVerts[vertInd].set(0.0f, 1.0f, 0.0f, 0.5f, 0, norm, Colors::White);
	pVerts[vertInd + 1].set(+1.0f, -1.0f, +1.0f, 0, 1, norm, Colors::White);
	pVerts[vertInd + 2].set(+1.0f, -1.0f, -1.0f, 1, 1, norm, Colors::White);
	pTriList[triInd].set(vertInd, vertInd + 1, vertInd + 2);

	// right face
	vertInd += 3;
	triInd += 1;
	norm = normalizePyramidSides(Vect(0.0f, 1.0f, 0.0f), Vect(-1.0f, -1.0f, -1.0f), Vect(-1.0f, -1.0f, +1.0f));
	pVerts[vertInd].set(0.0f, 1.0f, 0.0f, 0.5f, 0, norm, Colors::White);
	pVerts[vertInd + 1].set(-1.0f, -1.0f, -1.0f, 0, 1, norm, Colors::White);
	pVerts[vertInd + 2].set(-1.0f, -1.0f, +1.0f, 1, 1, norm, Colors::White);
	pTriList[triInd].set(vertInd, vertInd + 1, vertInd + 2);

	// bottom square
	vertInd += 3;
	triInd += 1;
	norm = Vect(0, -1, 0);
	pVerts[vertInd].set(-1.0f, -1.0f, -1.0f, 0, 0, norm, Colors::White);
	pVerts[vertInd + 1].set(+1.0f, -1.0f, -1.0f, 0, 1, norm, Colors::White);
	pVerts[vertInd + 2].set(+1.0f, -1.0f, +1.0f, 1, 1, norm, Colors::White);
	pVerts[vertInd + 3].set(-1.0f, -1.0f, +1.0f, 1, 0, norm, Colors::White);
	pTriList[triInd].set(vertInd, vertInd + 1, vertInd + 2);
	pTriList[triInd + 1].set(vertInd, vertInd + 2, vertInd + 3);
}



// for the sphere, the normals are just the points themselves



// normalizePyramidSides
// function takes in the verts of a face of the pyramid
// and computes the two vectors that lie on the traingles edges, u and v
// then calculates the face normal with u cross v / the magnitude of u cross v
// where magnitude is found with sqrt(x^2 + y^2 + z^2)
Vect normalizePyramidSides(Vect v0, Vect v1, Vect v2)
{
	Vect u = v1 - v0;
	Vect v = v2 - v0;

	Vect uCrossV = u.cross(v);
	return uCrossV.norm();
}