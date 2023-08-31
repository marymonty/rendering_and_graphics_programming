// ShaderTextureMultiLight
// Mary Montgomery
// this shader is almost identical to the ShaderColorLightTexture shader
// just has some constant buffer light differences

#ifndef _ShaderTextureMultiLight
#define _ShaderTextureMultiLight

#include "ShaderBase.h"
#include "Matrix.h"
#include "Texture.h"

struct ID3D11Buffer;
struct ID3D11Device;

class ShaderTextureMultiLight : public ShaderBase
{

public:

	ShaderTextureMultiLight(ID3D11Device* device);			// only constructor needed
	~ShaderTextureMultiLight();		  						// Destructor

	virtual void SetToContext(ID3D11DeviceContext* devcon) override;

	// texture specific methods
	void SetTextureResourceAndSampler(Texture* tex);

	// lighting specific methods
	void SetDirectionalLightParameters(const Vect& dir, const Vect& amb = Vect(1, 1, 1), const Vect& dif = Vect(1, 1, 1), const Vect& sp = Vect(1, 1, 1));
	void SetPointLightParameters(int index, const Vect& pos, float r, const Vect& att, const Vect& amb = Vect(1, 1, 1), const Vect& dif = Vect(1, 1, 1), const Vect& sp = Vect(1, 1, 1));
	void SetSpotLightParameters(int index, const Vect& pos, float r, const Vect& att, const Vect& dir, float spotExp, const Vect& amb = Vect(1, 1, 1), const Vect& dif = Vect(1, 1, 1), const Vect& sp = Vect(1, 1, 1));
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
	// MARY
	// create the PointLightData array
	PointLight PointLightData[3];

	struct SpotLight
	{
		PhongADS Light;
		Vect Position;
		Vect Attenuation;
		Vect Direction;
		float SpotExp;
		float Range;
	};
	// MARY
	// create the SpotLightData array
	SpotLight SpotLightData[3];

	struct Data_LightParams
	{
		DirectionalLight DirLight;
		// MARY
		// creating arrays of PointLights and SpotLights
		PointLight PntLight[3];
		SpotLight SptLight[3];
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

#endif _ShaderTextureMultiLight

