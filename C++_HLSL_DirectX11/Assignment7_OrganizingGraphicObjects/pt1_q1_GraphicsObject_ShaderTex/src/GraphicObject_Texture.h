// GraphicObject_Texture
// Mary Montgomery, march 2023
// very similar to the GraphicObject_Color class, just instead of our Color
// private data member and associated setColor function we have a texture and a
// setTexture function

#ifndef _GraphicObject_Texture
#define _GraphicObject_Texture

#include "GraphicObject_Base.h"
#include "Vect.h"
// MARY
// have to include the shader texture class
#include "ShaderTexture.h"

class GraphicObject_Texture : public GraphicObject_Base
{
friend class ShaderTexture;

public:
	GraphicObject_Texture(const GraphicObject_Texture&) = delete;				 // Copy constructor
	GraphicObject_Texture(GraphicObject_Texture&&) = default;                    // Move constructor
	GraphicObject_Texture& operator=(const GraphicObject_Texture&) & = default;  // Copy assignment operator
	GraphicObject_Texture& operator=(GraphicObject_Texture&&) & = default;       // Move assignment operator
	~GraphicObject_Texture();		  											 // Destructor

	GraphicObject_Texture() = delete;

	void SetTexture(Texture* tex);
	void SetWorld(const Matrix& m);
	virtual void Render() override;

	GraphicObject_Texture(ShaderTexture* shaderTex, Model* mod);

private:
	// MARY
	// need a pointer to a Texture
	Texture*						pTexture;
	ShaderTexture*					pShader;
	Matrix							World;

};

#endif _GraphicObject_Texture
