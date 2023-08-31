// ShaderColorMultiLight

// Implementing the ability to use multiple lights in the shader

#ifndef _ShaderColorMultiLight
#define _ShaderColorMultiLight

#include "ShaderBase.h"
#include "Matrix.h"

struct ID3D11Buffer;
struct ID3D11Device;

class ShaderColorMultiLight : public ShaderBase
{

public:
	ShaderColorMultiLight(const ShaderColorMultiLight&) = delete;				 // Copy constructor
	ShaderColorMultiLight(ShaderColorMultiLight&&) = default;                    // Move constructor
	ShaderColorMultiLight& operator=(const ShaderColorMultiLight&) & = default;  // Copy assignment operator
	ShaderColorMultiLight& operator=(ShaderColorMultiLight&&) & = default;       // Move assignment operator
	~ShaderColorMultiLight();		  							         // Destructor

	ShaderColorMultiLight(ID3D11Device* device);

	virtual void SetToContext(ID3D11DeviceContext* devcon) override;

	// give the user the ability to specify and not specify the light parameters (if none is specified, only apply to the 0th light)
	void SetDirectionalLightParameters(const Vect& dir, const Vect& amb = Vect(1, 1, 1), const Vect& dif = Vect(1, 1, 1), const Vect& sp = Vect(1, 1, 1));
	void SetPointLightParameters(int index, const Vect& pos, float r, const Vect& att, const Vect& amb = Vect(1, 1, 1), const Vect& dif = Vect(1, 1, 1), const Vect& sp = Vect(1, 1, 1));
	void SetPointLightParameters(const Vect& pos, float r, const Vect& att, const Vect& amb = Vect(1, 1, 1), const Vect& dif = Vect(1, 1, 1), const Vect& sp = Vect(1, 1, 1));
	void SetSpotLightParameters(int index, const Vect& pos, float r, const Vect& att, const Vect& dir, float spotExp, const Vect& amb = Vect(1, 1, 1), const Vect& dif = Vect(1, 1, 1), const Vect& sp = Vect(1, 1, 1));
	void SetSpotLightParameters(const Vect& pos, float r, const Vect& att, const Vect& dir, float spotExp, const Vect& amb = Vect(1, 1, 1), const Vect& dif = Vect(1, 1, 1), const Vect& sp = Vect(1, 1, 1));
	void SendFogParameters(float start = 0, float range = 0, const Vect& color = Vect(1, 1, 1));

	void SendCamMatrices(const Matrix& view, const Matrix& proj);
	void SendLightParameters(const Vect& eyepos);
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

	SpotLight SpotLightData[8];

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

	struct Data_LightParams
	{
		DirectionalLight DirLight;
		PointLight PntLight[8];
		SpotLight SptLight[8];
		Vect EyePosWorld;
	};

	ID3D11Buffer*  mpBufferLightParams;

};

#endif _ShaderColorMultiLight

