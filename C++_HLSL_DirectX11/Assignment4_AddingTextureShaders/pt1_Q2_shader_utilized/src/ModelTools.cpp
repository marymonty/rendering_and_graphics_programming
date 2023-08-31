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

