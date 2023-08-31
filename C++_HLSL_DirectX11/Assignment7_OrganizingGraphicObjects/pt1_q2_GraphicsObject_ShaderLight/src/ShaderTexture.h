// ShaderTexture
// derived from the ShaderBase class

#ifndef _ShaderTexture
#define _ShaderTexture

#include "ShaderBase.h"
#include "Matrix.h"
#include "Texture.h"

// adding the structs of the buffer and device COM objects
struct ID3D11Buffer;
struct ID3D11Device;

class ShaderTexture : public ShaderBase
{
public:
	ShaderTexture(ID3D11Device* device);
	~ShaderTexture();

	virtual void SetToContext(ID3D11DeviceContext* devcon) override;

	void SetTextureResourceAndSampler(Texture* tex);
	void SendCamMatrices(const Matrix& view, const Matrix& proj);
	void SendWorld(const Matrix& world);

private:
	// Constant Buffers
	// gotten from the Texture hlsl file
	// CamMatrices stores the View and projection matrices
	struct CamMatrices
	{
		Matrix View;
		Matrix Projection;
	};

	ID3D11Buffer* mpCamBuff;

	// WorldData stores the World matrix
	struct WorldData
	{
		Matrix World;
	};

	ID3D11Buffer* mpWorldBuff;
};


#endif _ShaderTexture