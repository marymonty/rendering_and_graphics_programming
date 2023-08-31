// GraphicObject_Light
// Andre Berthiaume, July 2016

#ifndef _GraphicObject_Light
#define _GraphicObject_Light

#include "GraphicObject_Base.h"
#include "Vect.h"
// MARY
// include Shader Color Light shader
#include "ShaderColorLight.h"

// inlcude our needed structs
struct Material;
struct PhongADS;


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
	// include secondary functions for set's that include the meshnum param to apply a material 
	// to specific meshes only
	void SetWorld(const Matrix& m);
	void SetMaterial(Vect am, Vect dif, Vect sp);
	void SetMaterial(Vect am, Vect dif, Vect sp, int meshnum);	
	virtual void Render() override;


private:
	ShaderColorLight*				pShader;
	// MARY
	// these Vects for Ambient, diffuse, and specular are now arrays
	Vect*							matAmbArr;
	Vect*							matDifArr;
	Vect*							matSpArr;
	Matrix							World;

};

#endif _GraphicObject_Light
