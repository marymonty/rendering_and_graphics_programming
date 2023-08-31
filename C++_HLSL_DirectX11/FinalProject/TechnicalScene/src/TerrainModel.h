// Mary Montgomery
// TerrainModel creates a terrain height map out of a greyscale tga image

/*	Final updates to TerrainModel:
*		constructor now takes pointers to the terrain texture and shader that we store in the terrainModel object
*/


#ifndef _TerrainModel
#define _TerrainModel

#include "Matrix.h"
#include <tuple>
#include <d3d11.h>
#include "DirectXTex.h"
#include "Model.h"
#include "Texture.h"
#include "ShaderTexColMultiLight.h"

class Model;
struct ID3D11DeviceContext;
struct ID3D11Device;

class TerrainModel : public Align16
{

private:
	Model* pModTerrain;
	Texture* pTexture;
	ShaderTexColMultiLight* pShader;

public:
	// constructor and destructor
	TerrainModel(ID3D11Device* dev, LPCWSTR heightmapFile, float len, float maxheight, float ytrans, int RepeatU, int RepeatV, Texture* tex, ShaderTexColMultiLight* shader);
	~TerrainModel();

	// helper functions
	float findPixelHeight(int side, int k, int i, size_t pixel_width, float maxheight, const DirectX::Image* hgtmap);
	int texelIndex(int side, int i, int j, size_t pixelWidth) const;

	Vect findVertNorm(StandardVertex* pVerts, int k, int side);
	Vect calcTriNorm(Vect v0, Vect v1, Vect v2);

	// new set functions
	void SetTexture(Texture* tex);

	// render function
	void Render(ID3D11DeviceContext* context);

};




#endif _TerrainModel