#ifndef _TerrainModel
#define _TerrainModel

#include "Matrix.h"
#include <tuple>
#include <d3d11.h>
#include "DirectXTex.h"

class Model;
struct ID3D11DeviceContext;
struct ID3D11Device;

class TerrainModel 
{

private:


public:
	TerrainModel(ID3D11Device* dev, LPCWSTR heightmapFile, int RepeatU, int RepeatV);

	void Render(ID3D11DeviceContext* context);

};



#endif _TerrainModel