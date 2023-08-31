// Mary
// TerrainModel.cpp 

#include "TerrainModel.h"
#include "Model.h"
#include "d3dUtil.h"
#include "DirectXTex.h"
#include <assert.h>


TerrainModel::TerrainModel(ID3D11Device* dev, LPCWSTR heightmapFile, float len, float maxheight, float ytrans, int RepeatU, int RepeatV, Texture* tex, ShaderTexColMultiLight* shader)
{
	pShader = shader;
	pTexture = tex;

	DirectX::ScratchImage scrtTex;
	HRESULT hr = LoadFromTGAFile(heightmapFile, nullptr, scrtTex);
	assert(SUCCEEDED(hr));

	const DirectX::Image* hgtmap = scrtTex.GetImage(0, 0, 0);
	assert(hgtmap->height == hgtmap->width);

	// hgtmap is an array of bytes for the image
	size_t side_sizet = hgtmap->height;	// the image should be square
	size_t pixel_width = 4;			// 4 bytes RGBA per pixel
	//uint8_t h_val = hgtmap->pixels[pixel_width * (5 * side + 3)]; // the 'R' byte of the pixel at (3,5)

	int side = static_cast<int>(side_sizet);

	// First, we can initialize the vertex buffer and index buffer
	// an NxN heightmap images will have N^2 total vertices (N rows of N columns)
	// and (N-1)^2 * 2 total triangles. 
	// N = the variable "side" found above, representing the texel length
	// of a side of the heightmap
	int nverts = (side * side);
	StandardVertex* pVerts = new StandardVertex[nverts];
	int ntri = (((side - 1) * (side - 1)) * 2);
	TriangleByIndex* pTriList = new TriangleByIndex[ntri];


	/********************** vertex buffer ************************/
	// since terrains are centered at the origin, a side length of 4 would mean
	// the side is from -2 to 2. We get the side length from len param (and all sides are same length)
	// each terrain vertex corresponds to one texel of the heightmap
	// we place the verts evenly spaced apart ( len / verts per side )
	float StartPos = 0 + (len / 2);
	float xCurrPos = 0 + (len / 2);
	float zCurrPos = 0 + (len / 2);
	float distBetweenVerts = (len / (side - 1));

	// RepeatU and RepeatV are how many times the texture should be repeated
	// (independent of the heightmap dimensions)
	// We are using a wrap filter, and dividing the verts up based on how many
	// times the UV repeats
	float start = 0;
	float currU = start;
	float currV = start;
	float uVertDist = (RepeatU / static_cast<float>(side - 1));
	float vVertDist = (RepeatV / static_cast<float>(side - 1));
	// loop iterators
	int i = 0;
	int j = 0;
	int k = 0;
	while (i < side)
	{
		// the i value = the z value, incrementing i means we are moving to the next row
		xCurrPos = StartPos;
		currU = start;
		k = 0;
		while (j < (side * (i + 1)))
		{
			// the k value = the x value, incrementing k means we move to the next column

			// calculate the pixel height in findPixelHeight function
			float pixelHeight = findPixelHeight(side, k, i, pixel_width, maxheight, hgtmap);

			// we also need to add the ytrans value to every vert
			// I initially set all normals to just be the positive Y axis, the field vertices
			// will get correctly set in the next step
			pVerts[j].set(xCurrPos, pixelHeight + ytrans, zCurrPos, currU, currV, 0, 1, 0);
			xCurrPos -= distBetweenVerts;
			currU += uVertDist;
			j++;
			k++;
		}
		currV += vVertDist;
		zCurrPos -= distBetweenVerts;
		i++;
	}


	/******************* Calculate Normals **********************/
	// since we have a normal.set() function, we can set the normals 
	// we can also ignore the edges (and therefore edge cases) and just 
	// calculate normals of verts that all have 6 triangle faces (uses a helper method findVertNorm)
	i = 1;
	j = 1;
	k = 1;
	Vect norm;
	while (i < side - 1)
	{
		j = 1;
		while (j < side - 1)
		{
			k = i * side + j;
			// findVertNorm calculates the normal of the vert accounting for the 6
			// connected tri faces
			norm = findVertNorm(pVerts, k, side);
			pVerts[k].normal.set(norm);
			j++;
		}
		i++;
	}



	/***************** index buffer ******************/
	i = 0;
	j = 0;
	int indexCount = 0;
	// per row, there are (N-1)*2 triangles
	// we only loop through UP TO (NOT including) the last row
	// below is a visual of the first two rows of a 4x4 terrain
	//	0 _____ 1 _____ 2 _____ 3
	//	|       |       |       |
	//	|       |       |       |
	//	4 _____ 5 _____ 6 _____ 7
	// the traingles would be: (0, 4, 1), (1, 4, 5), (1, 5, 2), (2, 5, 6),
	//							(2, 6, 3), (3, 6, 7)
	// OR (j, j+side, j+1), (j+1, j+side, j+1+side), j++
	//		(j, j+side, j+1), (j+1, j+side, j+1+side), j++ repeated
	while (i < (side - 1))
	{
		while (indexCount < (((side - 1) * 2) * (i + 1)))
		{
			pTriList[indexCount].set(j, j + side, j + 1);
			pTriList[indexCount + 1].set(j + 1, j + side, j + 1 + side);
			indexCount += 2;
			j++;
		}
		// we need to increment j here because we dont reuse the last vert
		// in the row, we need to move onto the start of the next row vert 
		j++;
		i++;
	}

	pModTerrain = new Model(dev, pVerts, nverts, pTriList, ntri);

	delete[] pVerts;
	delete[] pTriList;

}

// findPixelHeight 
// calculates the pixel height
// in coordinate terms, our vertices are located at (k, i), which means (col, row)
// so for example if these are our first two rows:
//	0 _____ 1 _____ 2 _____ 3
//	|       |       |       |
//	|       |       |       |
//	4 _____ 5 _____ 6 _____ 7
// and we are looking to get to 6, we need (2, 1) for the second col and first row
// first we find the hight of the terrain vertex by using the hgtmap byte array
// h_val is a value between [0, 255], or the greyscale value of the texel
// we need to find that equal value within our range of [0, maxheight]
// we do that by using (maxheight * h_val) / 255
float TerrainModel::findPixelHeight(int side, int k, int i, size_t pixel_width, float maxheight, const DirectX::Image* hgtmap)
{
	float h_val = hgtmap->pixels[texelIndex(side, k, i, pixel_width)]; // the 'R' byte of the pixel at (k,i)
	return (maxheight * h_val) / 255.0f;
}


// texelIndex
// helper function to find the location in the byte array of our (i, j) index
int TerrainModel::texelIndex(int side, int i, int j, size_t pixelWidth) const
{
	return pixelWidth * (j * side + i);
}


// calcTriNorm
// a helper function to the helper funtion findVertNorm
// this calcTriNorm calculates an individual triangles norm based on side vectors
Vect TerrainModel::calcTriNorm(Vect v0, Vect v1, Vect v2)
{
	Vect u = v1 - v0;
	Vect v = v2 - v0;
	Vect uCrossV = u.cross(v);
	return uCrossV.norm();
}


// findVertNorm
// below is a visual of the first three rows of a 4x4 terrain
//	0 _____ 1 _____ 2 _____ 3
//	|       |       |       |
//	|       |       |       |
//	4 _____ 5 _____ 6 _____ 7
//	|       |       |       |
//	|       |       |       |
//	8 _____ 9 _____ 10_____ 11
// so at vertex 5, we need to look at triangle (1, 4, 5), (1, 5, 2), (2, 5, 6)
//		(4, 8, 5), (5, 8, 9), (5, 9, 6)
// programatically, if j = 5, that would be:
//	(j - side, j - 1, j), (j - side, j, j - side + 1), (j - side + 1, j, j + 1)
//	(j - 1, j + side - 1, j), (j, j + side - 1, j + side), (j, j + side, j + 1) 
// j++
Vect TerrainModel::findVertNorm(StandardVertex* pVerts, int j, int side)
{
	// call calcTriNorm on each triangle figured out above
	// then add all those triangle normals together to get the final vert normal
	// then normalize it
	Vect norm = (calcTriNorm(pVerts[j - side].Pos, pVerts[j - 1].Pos, pVerts[j].Pos) +
					calcTriNorm(pVerts[j - side].Pos, pVerts[j].Pos, pVerts[j - side + 1].Pos) +
					calcTriNorm(pVerts[j - side + 1].Pos, pVerts[j].Pos, pVerts[j + 1].Pos) +
					calcTriNorm(pVerts[j - 1].Pos, pVerts[j + side - 1].Pos, pVerts[j].Pos) +
					calcTriNorm(pVerts[j].Pos, pVerts[j + side - 1].Pos, pVerts[j + side].Pos) +
					calcTriNorm(pVerts[j].Pos, pVerts[j + side].Pos, pVerts[j + 1].Pos)).norm();
	return norm;
}

void TerrainModel::SetTexture(Texture* tex)
{
	pTexture = tex;
}


// Render needs to set the terrain to context
// and draw it!
void TerrainModel::Render(ID3D11DeviceContext* context)
{
	pShader->SetToContext(context);
	pShader->SetTextureResourceAndSampler(pTexture);
	pModTerrain->SetToContext(context);
	pModTerrain->Render(context);
}

TerrainModel::~TerrainModel()
{
	delete pModTerrain;
}