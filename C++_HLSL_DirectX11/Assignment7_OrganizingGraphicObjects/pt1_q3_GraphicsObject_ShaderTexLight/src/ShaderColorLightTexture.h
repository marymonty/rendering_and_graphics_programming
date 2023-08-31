// ShaderColorLightTexture
// Mary Montgomery
// this shader is almost identical to the ShaderColorLight shader
// this one just accounts for Texture through the SetTextureResourceAndSampler method

#ifndef _ShaderColorLightTexture
#define _ShaderColorLightTexture

#include "ShaderBase.h"
#include "Matrix.h"
#include "Texture.h"

struct ID3D11Buffer;
struct ID3D11Device;

class ShaderColorLightTexture : public ShaderBase
{

public:

	ShaderColorLightTexture(ID3D11Device* device);			// only constructor needed
	~ShaderColorLightTexture();		  						// Destructor

	virtual void SetToContext(ID3D11DeviceContext* devcon) override;

	// texture specific methods
	void SetTextureResourceAndSampler(Texture* tex);

	// lighting specific methods
	void SetDirectionalLightParameters(const Vect& dir, const Vect& amb = Vect(1, 1, 1), const Vect& dif = Vect(1, 1, 1), const Vect& sp = Vect(1, 1, 1));
	void SetPointLightParameters(const Vect& pos, float r, const Vect& att, const Vect& amb = Vect(1, 1, 1), const Vect& dif = Vect(1, 1, 1), const Vect& sp = Vect(1, 1, 1));
	void SetSpotLightParameters(const Vect& pos, float r, const Vect& att, const Vect& dir, float spotExp, const Vect& amb = Vect(1, 1, 1), const Vect& dif = Vect(1, 1, 1), const Vect& sp = Vect(1, 1, 1));
	void SendLightParameters(const Vect& eyepos);

	// overlapping methods
	void SendCamMatrices(const Matrix& view, const Matrix& proj);
	void SendWorldAndMaterial(const Matrix& world, const Vect& amb = Vect(.5f, .5f, .5f), const Vect& dif = Vect(.5f, .5f, .5f), const Vect& sp = Vect(.5f, .5f, .5f));

private:
	// Texture constant buffers would just be the cam matrices and world data
	// which are contained in lighting constant buffers

	struct Material
	{
		Vect Ambient;
		Vect Diffuse;
		Vect Specular;
	};
	struct PhongADS
	{
		Vect Ambient;
		Vect Diffuse;
		Vect Specular;
	};


	// LIGHT TYPES

	struct DirectionalLight
	{
		PhongADS Light;
		Vect Direction;
	};
	DirectionalLight DirLightData;

	struct PointLight
	{
		PhongADS Light;
		Vect Position;
		Vect Attenuation;
		float Range;
	};
	PointLight PointLightData;

	struct SpotLight
	{
		PhongADS Light;
		Vect Position;
		Vect Attenuation;
		Vect Direction;
		float SpotExp;
		float Range;
	};
	SpotLight SpotLightData;

	struct Data_LightParams
	{
		DirectionalLight DirLight;
		PointLight PntLight;
		SpotLight SptLight;
		Vect EyePosWorld;
	};

	ID3D11Buffer* mpBufferLightParams;


	// Cam, World, and Matrial Buffers
	struct CamMatrices
	{
		Matrix View;
		Matrix Projection;
	};

	ID3D11Buffer*  mpBufferCamMatrices;

	struct Data_WorldAndMaterial
	{
		Matrix World;
		Matrix WorlInv;
		Material Mat;
	};

	ID3D11Buffer*	mpBuffWordAndMaterial;

};

#endif _ShaderColorLightTexture

