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

	pVerts[0].set(-0.5f, -0.5f, -0.5f,  Colors::Yellow);			// Colors::Black);
	pVerts[1].set(-0.5f, +0.5f, -0.5f,	Colors::Yellow);			// Colors::Lime);
	pVerts[2].set(+0.5f, +0.5f, -0.5f,	Colors::Yellow);			// Colors::Yellow);	
	pVerts[3].set(+0.5f, -0.5f, -0.5f,	Colors::Yellow);			// Colors::Red );
	pVerts[4].set(-0.5f, -0.5f, +0.5f,	Colors::Yellow);			// Colors::Blue);
	pVerts[5].set(-0.5f, +0.5f, +0.5f,	Colors::Yellow);			// Colors::Cyan);
	pVerts[6].set(+0.5f, +0.5f, +0.5f,	Colors::Yellow);			// Colors::White);
	pVerts[7].set(+0.5f, -0.5f, +0.5f,	Colors::Yellow);			// Colors::Magenta);

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


// CreateUnitSphere constructor
// creates a sphere of radius 1 with vslice vertical bands and hslice horizontal bands on the sphere
void ModelTools::CreateUnitSphere(int vslice, int hslice, StandardVertex*& pVerts, int& nverts, TriangleByIndex*& pTriList, int& ntri)
{
	// find the initial curve (from 0,1 to 0,-1) and plot the points
	// then just rotate the normal vector around the Y axis some amount
	// and draw the curve over and over to make all the verts


	// number of vertices calculated 
	// always top and bottom stand alone verts (0,1) (0,-1) plus hslice verts per row * vslice rows
	// so, nverts = 2 + (hslice * vslice)
	nverts = 2 + (hslice * vslice);
	pVerts = new StandardVertex[nverts];
	// number of triangles calculated
	// triangles connected to stand alone top and bottom verts are equal to number of horizontal 
	// slices = (top + bottom)*hslice then triangles in squares covering the rest of the sphere are
	// ((vslice - 1) * hslice) * 2, with (vslice-1)*hslice giving us the number of squares
	// so together, there are (2*hslice) + (((vslice - 1) * hslice) *2) triangles total
	ntri = (2*hslice) + (((vslice - 1) * hslice) * 2);
	pTriList = new TriangleByIndex[ntri];

	// I have three separate loops to construct the verts of the sphere
	// the first loop starts at the top of the sphere and creates the top point,
	// then creates the first row circle of verts to get the correct windings of tris

	// the second loop goes through the whole body of the sphere, where we can think of
	// all quads being made

	// the third loop goes through the bottom of the sphere and creates the bottom point
	// and the last row circle of verts to wind





















	// create the first curve by going from top point to bottom point
	// we can follow the unit circle, start at rad pi/2 and move counter clockwise to 3pi/2. 
	float radVal = (3.14159265 / 2);
	float radIncrementVal = (3.14159265 / (vslice + 1));
	
	// go through to create the first curve (includes the top and bottom points)
	int i = 0;
	while (i < (vslice + 2))
	{
		pVerts[i].set(cosf(radVal), sinf(radVal), 0.0f, Colors::White);
		radVal += radIncrementVal;
		i++;
	}

	// now we have to redraw this curve (hslice - 1) more times
	// each time rotating around the Y axis 










	// first create the top vert
	pVerts[0].set(0.0f, 1.0f, 0.0f, Colors::White);
	// since our starting point is at 0,1,0 our starting X radian value is pi/2
	float sphereRadVal = (3.14159265 / 2);
	// using a unit vect (of length 1) we calculate where the next vertex
	// should go by starting at the top (0, 1, 0) and moving south by a radian 
	// of pi / (vslice + 1) along a unit circle (moving south by cos(rad) and sin(rad))
	// we then need to 
	float radIncrementVal = (3.14159265 / (vslice + 1));
	
	float circleRadVal;
	float circleIncrementVal = (3.14159265 / hslice);
	int i = 1;
	int j = 0;
	while (i < nverts-1)
	{
		// we are moving counterclockwise towards 3pi / 2
		sphereRadVal += radIncrementVal;
		// each increment of radVal, we need to make a circle on this Y plane in space
		// the circle is spaced out evenly using (pi / hslice)
		pVerts[i].set(cosf(sphereRadVal), sinf(sphereRadVal), 0.0f, Colors::White);
		circleRadVal = sphereRadVal;
		while (j < hslice)
		{

		}
		

		i++;
	}
	pVerts[i].set(0.0f, -1.0f, 0.0f, Colors::White);






	// I am using the parameterization of a sphere as
	// P(U,V) = (sin(U)cos(V), sin(U)sin(V), cos(U))
	// where U is the angle between the positive x-axis and the projection
	// the point in space makes onto the xy plane
	// and V is the angle between the positive z-axis and the line from the 
	// origin to the point in space


}
