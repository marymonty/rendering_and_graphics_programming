// GraphicObject_Texture
// Mary Montgomery, march 2023

#ifndef _GraphicObject_Texture
#define _GraphicObject_Texture

#include "GraphicObject_Base.h"
#include "Vect.h"
#include "ShaderTexture.h"

class GraphicObject_Texture : public GraphicObject_Base
{
	friend class ShaderTexture;

public:
	GraphicObject_Texture(const GraphicObject_Texture&) = delete;				 // Copy constructor
	GraphicObject_Texture(GraphicObject_Texture&&) = default;                    // Move constructor
	GraphicObject_Texture& operator=(const GraphicObject_Texture&) = default;  // Copy assignment operator
	GraphicObject_Texture& operator=(GraphicObject_Texture&&) = default;       // Move assignment operator
	~GraphicObject_Texture();		  											 // Destructor

	GraphicObject_Texture() = delete;

	// MARY
	// adding a second SetTexture method with a meshnum param
	void SetTexture(Texture* tex);
	void SetTexture(Texture* tex, int meshnum);
	void SetWorld(const Matrix& m);
	virtual void Render() override;

	GraphicObject_Texture(ShaderTexture* shaderTex, Model* mod);

private:
	// MARY
	// need a pointer to a pointer to a Texture (to have multiple textures)
	Texture**						pTextureArr;
	ShaderTexture*					pShader;
	Matrix							World;

};

#endif _GraphicObject_Texture
