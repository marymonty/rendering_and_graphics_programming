// GraphicObject_TexLight
// this class is the same as GraphicObject_Light
// just with an added Texture* private data member and the 
// setTexture method

#ifndef _GraphicObject_TexLight
#define _GraphicObject_TexLight

#include "GraphicObject_Base.h"
#include "Vect.h"
// MARY
// include Shader Color Light shader
#include "ShaderColorLightTexture.h"


class GraphicObject_TexLight : public GraphicObject_Base
{
friend class ShaderColorLightTexture;

public:
	GraphicObject_TexLight(const GraphicObject_TexLight&) = delete;				 // Copy constructor
	GraphicObject_TexLight(GraphicObject_TexLight&&) = default;                    // Move constructor
	GraphicObject_TexLight& operator=(const GraphicObject_TexLight&) & = default;  // Copy assignment operator
	GraphicObject_TexLight& operator=(GraphicObject_TexLight&&) & = default;       // Move assignment operator
	GraphicObject_TexLight() = delete;

	~GraphicObject_TexLight();

	// constructor only takes the shader and model
	GraphicObject_TexLight(ShaderColorLightTexture* shader, Model* mod);

	// set functions for world matrix, texture, and material
	void SetWorld(const Matrix& m);
	void SetTexture(Texture* tex);
	void SetMaterial(Vect am, Vect dif, Vect sp);
	virtual void Render() override;


private:
	ShaderColorLightTexture*		pShader;
	Texture*						pTexture;
	Vect							matAmb;
	Vect							matDif;
	Vect							matSp;
	Matrix							World;

};

#endif _GraphicObject_TexLight
