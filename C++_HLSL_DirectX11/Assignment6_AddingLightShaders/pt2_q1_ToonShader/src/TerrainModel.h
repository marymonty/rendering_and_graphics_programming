#ifndef _TerrainModel
#define _TerrainModel

#include "Matrix.h"
#include <tuple>
#include <d3d11.h>
#include "DirectXTex.h"
#include "Model.h"

class Model;
struct ID3D11DeviceContext;
struct ID3D11Device;

class TerrainModel : public Align16
{

private:
	Model* pModTerrain;

public:
	// constructor and destructor
	TerrainModel(ID3D11Device* dev, LPCWSTR heightmapFile, float len, float maxheight, float ytrans, int RepeatU, int RepeatV);
	~TerrainModel();

	// helper functions
	float findPixelHeight(int side, int k, int i, size_t pixel_width, float maxheight, const DirectX::Image* hgtmap);
	int texelIndex(int side, int i, int j, size_t pixelWidth) const;
	// normal helper functions
	Vect findVertNorm(StandardVertex* pVerts, int k, int side);
	Vect calcTriNorm(Vect v0, Vect v1, Vect v2);

	// render function
	void Render(ID3D11DeviceContext* context);

};




#endif _TerrainModel