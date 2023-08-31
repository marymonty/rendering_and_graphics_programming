// GraphicObject_Light


#ifndef _GraphicObject_Light
#define _GraphicObject_Light

#include "GraphicObject_Base.h"
#include "Vect.h"
// MARY
// include Shader Color Light shader
#include "ShaderColorLight.h"


class GraphicObject_Light : public GraphicObject_Base
{
friend class ShaderColorLight;

public:
	GraphicObject_Light(const GraphicObject_Light&) = delete;				 // Copy constructor
	GraphicObject_Light(GraphicObject_Light&&) = default;                    // Move constructor
	GraphicObject_Light& operator=(const GraphicObject_Light&) & = default;  // Copy assignment operator
	GraphicObject_Light& operator=(GraphicObject_Light&&) & = default;       // Move assignment operator
	GraphicObject_Light() = delete;

	~GraphicObject_Light();

	// constructor only takes the shader and model
	GraphicObject_Light(ShaderColorLight* shader, Model* mod);

	// set functions for world matrix, material
	void SetWorld(const Matrix& m);
	void SetMaterial(Vect am, Vect dif, Vect sp);
	virtual void Render() override;


private:
	ShaderColorLight*				pShader;
	Vect							matAmb;
	Vect							matDif;
	Vect							matSp;
	Matrix							World;

};

#endif _GraphicObject_Light
