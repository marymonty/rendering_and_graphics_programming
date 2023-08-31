#include "TerrainModel.h"
#include "Model.h"
#include "d3dUtil.h"
#include "DirectXTex.h"
#include <assert.h>


//TerrainModel::TerrainModel(ID3D11Device* dev, LPCWSTR heightmapFile, int RepeatU, int RepeatV)
//{
//	DirectX::ScratchImage scrtTex;
//	HRESULT hr = LoadFromTGAFile(heightmapFile, nullptr, scrtTex);
//	assert(SUCCEEDED(hr));
//
//	const DirectX::Image* hgtmap = scrtTex.GetImage(0, 0, 0);
//	assert(hgtmap->height == hgtmap->width );
//
//	size_t side = hgtmap->height;	// the image should be square
//	size_t pixel_width = 4;			// 4 bytes RGBA per pixel
//	uint8_t h_val = hgtmap->pixels[ pixel_width * (5 * side + 3) ]; // the 'R' byte of the pixel at (3,5)
//
//
//	// ** much work to add below **
//
//	
//}
//
//void TerrainModel::Render(ID3D11DeviceContext* context)
//{
//	// ?
//}