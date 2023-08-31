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

	// duplicate vertices to set the correct normal for each face's vertices

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


// CreatUnitPyramid constructor
// creates a 4 sided pyramid centered on the origin with height, width, and depth equal to 1
void ModelTools::CreateUnitPyramid(StandardVertex*& pVerts, int& nverts, TriangleByIndex*& pTriList, int& ntri)
{
	nverts = 16;
	pVerts = new StandardVertex[nverts];
	ntri = 6;
	pTriList = new TriangleByIndex[ntri];

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



// CreateUnitSphere
// creates a sphere of radius 1 with vslice vertical bands and hslice horizontal bands on the sphere
void ModelTools::CreateUnitSphere(int vslice, int hslice, StandardVertex*& pVerts, int& nverts, TriangleByIndex*& pTriList, int& ntri)
{
	// if the sphere has 3 verticle slices, it has 4 rows - 2 are top and bottom points, 2 are central rows
	// that have horizontal slice number of verts in them
	// number of vertices calculated 
	// always top and bottom stand alone verts (0,1) (0,-1) plus (hslice verts per row - 1) * vslice rows
	// so, nverts = 2 + (hslice * vslice)
	nverts = 2 + ((hslice - 1) * vslice);
	pVerts = new StandardVertex[nverts];
	// number of triangles calculated
	// triangles connected to stand alone top and bottom verts are equal to number of horizontal 
	// slices = (top + bottom)*vslice then triangles in squares covering the rest of the sphere are
	// ((vslice * 2) * (hslice-2), with vslice*2 giving us tris per row * hslice-2 rows,
	// so together, there are (2*hslice) + (((vslice * 2) * (hslice - 2) triangles total
	ntri = (2 * vslice) + ((vslice * 2) * (hslice - 2));
	pTriList = new TriangleByIndex[ntri];

	// find the verticle and horizontal increment radians 
	// for each vertical increment, we will loop through a horizontal circle
	// vertically though we only move through a hemisphere
	// so mathematically, horizontally we are going the diameter, which is 2*pi*r, which in our
	// case is just 2pi, divided by the number of horizontal slices, and vertically we are going
	// half that distance, so 1*pi, divided by the number of verticle slices
	float verticleInc = 3.14159 / vslice;
	float horizontalInc = 6.2831853 / hslice;

	// also to remember, the normals of the verts are just the points themselves
	
	// we can set our top vertex at 0, 1, 0
	pVerts[0].set(0.0f, 1.0f, 0.0f, 0.5f, 1.0f, 0.0f, 1.0f, 0.0f);

	// loop through to create the vertex buffer
	//      0
	//   1 2 3 4
	//   5 6 7 8
	//		9
	// to get from the top of the circle, row 1, we need to traverse by horizontal
	// rows to get to row 2 (going vertically from 0 would lead us nowhere - there is nothing 
	// vertically beside 0). So our outer for loop has to be horizontal row by row, and the 
	// inner loop traverses each row by vertically moving vert to vert within the row
	// we can start at horizontal row 1 since we already made our first row (top point)
	int i = 1;
	int j = 0;
	int index = 1;
	float x;
	float y;
	float z;
	Vect norm;
	float currULength = 0.0f;
	float uLengthDiff = 1 / static_cast<float>(hslice);
	float currVHeight = 1.0f;
	float vHeightDiff = 1 / static_cast<float>(vslice);
	while (i < hslice)
	{
		j = 0;
		currULength = 0;
		while (index <= (vslice * i))
		{
			// to figure out our x, y, and z values we know our verticle position is the
			// horizontal row we are in (i) * the verticle increment value to get our current
			// verticle position. For horizontal position we take the verticle column we are in
			// (j) and multiply by the horizontal increment value to get our horizontal position.
			// we then combine those values using different multiplications of sin and cos
			// based on a formula for finding position in 3D where x = r * cos(s) * sin(t), 
			// y = r* cos(t), and z = r * sin(s) * sin(t) where s = the angle around the Y axis (horizontal) and 
			// t is the height angle measured down (verticle) from the Y axis. Our r is just 1 so we can ignore it!

			x = cosf(horizontalInc * j) * sinf(i * verticleInc);
			y = cosf(i * verticleInc);
			z = sinf(horizontalInc * j) * sinf(i * verticleInc);
			norm = Vect(x, y, z);
			// make sure we normalize our norm
			norm.norm();
			// k is just keeping a running counter of what vert we are currently on
			pVerts[index].set(x, y, z, currULength, currVHeight, norm, Colors::White);
			currULength += uLengthDiff;
			j++;
			index++;
		}
		currVHeight -= vHeightDiff;
		i++;
	}
	// the final horizontal row is just the bottom point so we can set that below
	//pVerts[nverts - 1].set(0.0f, -1.0f, 0.0f, 0.0f, 0.5f, 0.0f, -1.0f, 0.0f);
	pVerts[index].set(0.0f, -1.0f, 0.0f, 0.5f, 0.0f, 0.0f, -1.0f, 0.0f);


	// we can split the sphere into three parts - the first row, the middle bulk, and the last row.
	// the first and last rows make particular triangles, but the middle bulk is the same as the terrain
	// with creating tris from quads. 
	// visual of first row if we have 4 verticle columns
	//				  0				
	//			1	2	3	4
	// keeping in mind that the first and last two are also beside one another
	// the triangle pattern would be (1, 2, 0) (2, 3, 0), (3, 4, 0), (4, 1, 0)
	// or in our case (k, k+1, 0th vert), (k+1, k+2, 0), (k+2, k+3, 0), (k+3, k-vslice+1, 0) 
	// for the bulk rows we would have
	//			1	2	3	4
	//			5	6	7	8
	// tri pattern is: (1, 5, 2), (2, 5, 6), (2, 6, 3), (3, 6, 7), (3, 7, 4), (4, 7, 8), 
	//		(4, 8, 1), (1, 8, 5)
	// these last two tris follow a different pattern - (k-vslice, k, k-(vslice*2)+1), 
	//		(k-(vslice*2)+1, k, k-vslice+1)
	// the last rows lets say are
	//			5	6	7	8
	//				  9
	// these tris would be: (5, 9, 6), (6, 9, 7), (7, 9, 8), (8, 9, 5)
	// or (k, lastVert, k+1), (k+1, lastVert, k+2), (k+2, lastVert, k+3), (k+3, lastVert, k)
	i = 0;
	j = 0;
	index = 0;
	while (i < hslice)
	{
		// j is always the start of the horizontal row vert number
		j = (i * vslice) + 1;
		if (i == hslice - 1)
		{
			// we need to repeat the last horizontal row to get the bottom triangles
			j -= vslice;
		}
		while (j <= (vslice * (i + 1)))
		{
			// I have three separate conditions to construct the tris of the sphere
			// the first starts at the top of the sphere and creates those top tris
			// since they are not quads, just tris, so we need the correct winding
			if (i == 0)
			{
				// we are at the top row of the sphere, so lets make some triangles
				// the last tri is different
				if (j == (vslice * (i + 1)))
				{
					pTriList[index].set(j, j - vslice + 1, 0);
				}
				else
				{
					pTriList[index].set(j, j + 1, 0);
				}
			}

			// the second condition goes through the bottom of the sphere and creates the bottom tris
			// since this also creates tris only
			else if (i == (hslice - 1))
			{
				
				// we are at the bottom row of the sphere so lets make some triangles
				if (j == (vslice * (i)))
				{
					pTriList[index].set(j, nverts - 1, j - vslice + 1);
					// we need to exit the loop
					j += vslice;
				}
				else
				{
					pTriList[index].set(j, nverts - 1, j + 1);
				}
			}

			// the third condition goes through the whole body of the sphere, where we can think of
			// all quads being made
			else 
			{
				// we are in the middle of the sphere so lets make some split quads
				// the last quad made has a different pattern
				if (j == (vslice * (i + 1)))
				{
					pTriList[index].set(j - vslice, j, j - (vslice*2) + 1);
					pTriList[index + 1].set(j - (vslice*2) + 1, j, j - vslice + 1);
				}
				else
				{
					pTriList[index].set(j - vslice, j, j - vslice + 1);
					pTriList[index + 1].set(j - vslice + 1, j, j + 1);
				}
				index++;
			}
			j++;
			index++;
		}
		i++;
	}
}


// CreateUnitTexSphere
// this changes the UnitSphere code by calculating UVs, duplicating vertices (top and bottom and end of row)
void ModelTools::CreateUnitTexSphere(int vslice, int hslice, StandardVertex*& pVerts, int& nverts, TriangleByIndex*& pTriList, int& ntri)
{
	// verts = vslice verts for top and bottom row, vslice + 1 verts for all middle rows so
	// (vslice * 2) + ((vslice+1)*(hslice-1))
	nverts = (vslice*2) + ((vslice+1) * (hslice-1));
	pVerts = new StandardVertex[nverts];
	// tris = vslice tris for top and bottom rows, vslice*2 for all middle rows so
	// (vslice*2) + ((vslice*2)*(hslice-2))
	ntri = (2 * vslice) + ((vslice * 2) * (hslice - 2));
	pTriList = new TriangleByIndex[ntri];

	float verticleInc = 3.14159 / vslice;
	float horizontalInc = 6.2831853 / hslice;

	// also to remember, the normals of the verts are just the points themselves

	int i = 0;
	int j = 0;
	int k = 1;
	int index = 0;
	float x;
	float y;
	float z;
	Vect norm;
	float currULength = 0.0f;
	float uLengthDiff = 1 / static_cast<float>(vslice);
	float currVHeight = 1.0f;
	float vHeightDiff = 1 / static_cast<float>(hslice);
	while (i <= hslice)
	{
		j = 0;
		currULength = 0;
		k = 1;
		while (k <= (vslice +1))
		{
			// top and bottom rows both just map to their respective 0, 1, 0 or 0, -1, 0 position
			if (i == 0 || i == (hslice))
			{
				if (k == (vslice + 1))
				{
					// dont go through this last loop to make another end vert 
					// (top and bottom rows only have vslice verts, not an extra end vert)
					k += 2;
					break;
				}
				else
				{
					x = 0.0f;
					if (i == 0)
					{
						y = 1.0f;
					}
					else
					{
						y = -1.0f;
					}
					z = 0.0f;
					norm = Vect(x, y, z);
					norm.norm();
					pVerts[index].set(x, y, z, currULength, currVHeight, norm, Colors::White);
				}
			}
			else
			{
				// we are in a middle vert row so we have an extra vslice + 1 vert at the end of each row
				// we also need to calculate our position in space (not 0, 1, 0 anymore)
				x = cosf(horizontalInc * j) * sinf((i+1) * verticleInc);
				y = cosf((i+1) * verticleInc);
				z = sinf(horizontalInc * j) * sinf((i+1) * verticleInc);
				norm = Vect(x, y, z);
				// make sure we normalize our norm
				norm.norm();
				// index is just keeping a running counter of what vert we are currently on
				pVerts[index].set(x, y, z, currULength, currVHeight, norm, Colors::White);
			}
			currULength += uLengthDiff;
			j++;
			index++;
			k++;
		}
		currVHeight -= vHeightDiff;
		i++;
	}

	i = 0;
	j = 0;
	index = 0;
	while (i < hslice)
	{
		// j is always the start of the horizontal row vert number
		j = (i * vslice);
		while (j < (vslice * (i + 1)))
		{
			// I have three separate conditions to construct the tris of the sphere
			// the first starts at the top of the sphere and creates those top tris
			// since they are not quads, just tris, so we need the correct winding
			if (i == 0)
			{
				// we are at the top row of the sphere, so lets make some triangles
				pTriList[index].set(j, j + vslice, j + vslice + 1);
			}

			// the second condition goes through the bottom of the sphere and creates the bottom tris
			// since this also creates tris only
			else if (i == (hslice - 1))
			{
				pTriList[index].set(j, j + vslice + 1, j + 1);
			}

			// the third condition goes through the whole body of the sphere, where we can think of
			// all quads being made
			else
			{
				// we are in the middle of the sphere so lets make some split quads
				pTriList[index].set(j, j + vslice + 1, j + 1);
				pTriList[index + 1].set(j + vslice + 1, j + vslice + 2, j + 1);
				index++;
			}
			j++;
			index++;
		}
		i++;
	}
}
