// GraphicObject_TexLight
// this class is the same as GraphicObject_Light
// just with an added Texture* private data member and the 
// setTexture method

#ifndef _GraphicObject_TexLight
#define _GraphicObject_TexLight

#include "GraphicObject_Base.h"
#include "Vect.h"
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

	// set functions for world matrix, texture, material, and all color params
	// add mesh specific setTexture and setMaterial functions
	void SetWorld(const Matrix& m);
	void SetTexture(Texture* tex);
	void SetTexture(Texture* tex, int meshnum);
	void SetMaterial(Vect am, Vect dif, Vect sp);
	void SetMaterial(Vect am, Vect dif, Vect sp, int meshnum);
	virtual void Render() override;


private:
	// make the texture and material vects into arrays to store multiple
	ShaderColorLightTexture*		pShader;
	Texture**						pTextureArr;
	Vect*							matAmbArr;
	Vect*							matDifArr;
	Vect*							matSpArr;
	Matrix							World;

};

#endif _GraphicObject_TexLight
