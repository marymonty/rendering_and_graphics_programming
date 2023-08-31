// GraphicObject_TexColMultiLight
// this class is the same as GraphicObject_TexLight
// just with multi light capabilities

#ifndef _GraphicObject_TexColMultiLight
#define _GraphicObject_TexColMultiLight

#include "GraphicObject_Base.h"
#include "Vect.h"
#include "ShaderTexColMultiLight.h"


class GraphicObject_TexColMultiLight : public GraphicObject_Base
{
friend class ShaderColorLightTexture;

public:
	GraphicObject_TexColMultiLight(const GraphicObject_TexColMultiLight&) = delete;				 // Copy constructor
	GraphicObject_TexColMultiLight(GraphicObject_TexColMultiLight&&) = default;                    // Move constructor
	GraphicObject_TexColMultiLight& operator=(const GraphicObject_TexColMultiLight&) & = default;  // Copy assignment operator
	GraphicObject_TexColMultiLight& operator=(GraphicObject_TexColMultiLight&&) & = default;       // Move assignment operator
	GraphicObject_TexColMultiLight() = delete;

	~GraphicObject_TexColMultiLight();

	// constructor only takes the shader and model
	GraphicObject_TexColMultiLight(ShaderTexColMultiLight* shader, Model* mod);

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
	ShaderTexColMultiLight*			pShader;
	Texture**						pTextureArr;
	Vect*							matAmbArr;
	Vect*							matDifArr;
	Vect*							matSpArr;
	Matrix							World;

};

#endif _GraphicObject_TexColMultiLight
