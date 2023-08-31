#include "GraphicObject_Texture.h"
#include "Model.h"
// MARY
// include the texture class
#include "ShaderTexture.h"
#include <assert.h>

GraphicObject_Texture::GraphicObject_Texture(ShaderTexture* shaderTex, Model* mod)
{
	// MARY
	// set the shader
	SetModel(mod);
	pShader = shaderTex;
	World = Matrix(IDENTITY);
}

GraphicObject_Texture::~GraphicObject_Texture()
{

}

void GraphicObject_Texture::SetTexture(Texture* tex)
{
	pTexture = tex;
}

void GraphicObject_Texture::SetWorld(const Matrix& m)
{
	World = m;
}

// Render
// we need to send the world to the shader, set the shader texture
// then set the model to context and call Model class's render function
void GraphicObject_Texture::Render()
{
	pShader->SendWorld(World);
	pShader->SetTextureResourceAndSampler(pTexture);
	pModel->SetToContext(pShader->GetContext());
	pModel->Render(pShader->GetContext());
}