// ShaderTexColMultiLight
// Mary Montgomery
// this shader is almost identical to the ShaderColorLightTexture shader
// this one just accounts for multiple lights stored in an array

#ifndef _ShaderTexColMultiLight
#define _ShaderTexColMultiLight

#include "ShaderBase.h"
#include "Matrix.h"
#include "Texture.h"

struct ID3D11Buffer;
struct ID3D11Device;

class ShaderTexColMultiLight : public ShaderBase
{

public:

	ShaderTexColMultiLight(ID3D11Device* device);			// only constructor needed
	~ShaderTexColMultiLight();		  						// Destructor

	virtual void SetToContext(ID3D11DeviceContext* devcon) override;

	// texture specific methods
	void SetTextureResourceAndSampler(Texture* tex);

	// lighting specific methods allowing for light specification or not
	void SetDirectionalLightParameters(const Vect& dir, const Vect& amb = Vect(1, 1, 1), const Vect& dif = Vect(1, 1, 1), const Vect& sp = Vect(1, 1, 1));
	void SetPointLightParameters(int index, const Vect& pos, float r, const Vect& att, const Vect& amb = Vect(1, 1, 1), const Vect& dif = Vect(1, 1, 1), const Vect& sp = Vect(1, 1, 1));
	void SetPointLightParameters(const Vect& pos, float r, const Vect& att, const Vect& amb = Vect(1, 1, 1), const Vect& dif = Vect(1, 1, 1), const Vect& sp = Vect(1, 1, 1));
	void SetSpotLightParameters(int index, const Vect& pos, float r, const Vect& att, const Vect& dir, float spotExp, const Vect& amb = Vect(1, 1, 1), const Vect& dif = Vect(1, 1, 1), const Vect& sp = Vect(1, 1, 1));
	void SetSpotLightParameters(const Vect& pos, float r, const Vect& att, const Vect& dir, float spotExp, const Vect& amb = Vect(1, 1, 1), const Vect& dif = Vect(1, 1, 1), const Vect& sp = Vect(1, 1, 1));
	void SendLightParameters(const Vect& eyepos);
	// adding methods for setting and sending fog parameters
	void SendFogParameters(float start = 0, float range = 0, const Vect& color = Vect(1, 1, 1));

	// overlapping methods
	void SendCamMatrices(const Matrix& view, const Matrix& proj);
	void SendWorldAndMaterial(const Matrix& world, const Vect& amb = Vect(.5f, .5f, .5f), const Vect& dif = Vect(.5f, .5f, .5f), const Vect& sp = Vect(.5f, .5f, .5f));

private:
	// Fog constant buffer
	struct CBFog
	{
		float fogStart;
		float fogRange;
		Vect fogColor;
		bool fogShowing = false;
	};
	ID3D11Buffer* mpFogBuff;


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
	// array of point lights - I'm having up to 8 point lights
	PointLight PointLightData[8];

	struct SpotLight
	{
		PhongADS Light;
		Vect Position;
		Vect Attenuation;
		Vect Direction;
		float SpotExp;
		float Range;
	};
	// array of spot lights - I'm having up to 8 spot lights
	SpotLight SpotLightData[8];

	struct Data_LightParams
	{
		DirectionalLight DirLight;
		// create the arrays of lights
		PointLight PntLight[8];
		SpotLight SptLight[8];
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

#endif _ShaderTexColMultiLight

