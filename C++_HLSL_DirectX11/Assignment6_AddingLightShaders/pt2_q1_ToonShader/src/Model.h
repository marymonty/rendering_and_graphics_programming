#ifndef MODEL_H
#define MODEL_H

#include <d3d11.h>
#include "Vect.h"
#include "Align16.h"
#include "Matrix.h"



struct StandardVertex : public Align16
{
	Vect Pos;
	float u;    
	float v;
	Vect normal;
	Vect Color;

	void set(float _x, float _y, float _z,
		float _u = 0, float _v = 0,
		float _nx = 0, float _ny = 0, float _nz = 0,
		float _r = 1, float _g = 1, float _b = 1)
	{
		Pos = Vect(_x, _y, _z);
		u = _u;
		v = _v;
		normal = Vect(_nx, _ny, _nz, 0);
		Color = Vect(_r, _g, _b);
	}

	void set(float _x, float _y, float _z, float _u, float _v, const Vect& c)
	{
		Pos = Vect(_x, _y, _z);
		u = _u;
		v = _v;
		Color = c;
	}

	void set(float _x, float _y, float _z, float _u, float _v, const Vect& n, const Vect& c)
	{
		Pos = Vect(_x, _y, _z);
		u = _u;
		v = _v;
		normal = n;
		Color = c;
	}

	// MARY
	// adding a set that takes in pos as a vect
	void set(const Vect& posVect, float _u, float _v, const Vect& n)
	{
		Pos = posVect;
		u = _u;
		v = _v;
		normal = n;
	}

	void set(float _x, float _y, float _z, const Vect& c)
	{
		Pos = Vect(_x, _y, _z);
		u = 0;
		v = 0;
		Color = c;
	}

	void set(float _x, float _y, float _z, const Vect& n, const Vect& c)
	{
		Pos = Vect(_x, _y, _z);
		u = 0;
		v = 0;
		normal = n;
		Color = c;
	}

	void set(const Vect& p, const Vect& c)
	{
		Pos = p;
		Color = c;
	}
};

struct TriangleByIndex
{
	unsigned int v0;
	unsigned int v1;
	unsigned int v2;

	void set(int _v0, int _v1, int _v2)
	{
		v0 = _v0;
		v1 = _v1;
		v2 = _v2;
	}
};

class Model
{
private:
	// Model information
	TriangleByIndex *pTriList;
	StandardVertex* pStdVerts;
	int numVerts;
	int numTris;

	// GPU connections
	ID3D11Device*			mDevice;
	ID3D11Buffer*           mpVertexBuffer;
	ID3D11Buffer*           mpIndexBuffer;

	void privLoadDataToGPU();

public:
	Model(const Model&) = delete;				// Copy constructor
	Model(Model&&) = delete;                    // Move constructor
	Model& operator=(const Model&) & = delete;  // Copy assignment operator
	Model& operator=(Model&&) & = delete;       // Move assignment operator

	enum PreMadeModels {
		UnitBox,
		UnitBoxRepeatedTexture,
		UnitBoxSixFaceTexture,
		UnitPyramid,
		UnitPyramidRepeatedTexture,
		UnitSphere
	};

	Model(ID3D11Device* dev, StandardVertex *pVerts, int nverts, TriangleByIndex *ptlist, int ntri);
	Model(ID3D11Device* dev, PreMadeModels pm);

	virtual ~Model();

	void SetToContext(ID3D11DeviceContext* context);
	void Render(ID3D11DeviceContext* context);
};



#endif