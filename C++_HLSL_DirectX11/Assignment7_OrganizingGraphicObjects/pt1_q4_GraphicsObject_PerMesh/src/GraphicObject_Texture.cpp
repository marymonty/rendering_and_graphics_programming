#include "GraphicObject_Texture.h"
#include "Model.h"
#include "ShaderTexture.h"
#include <assert.h>

GraphicObject_Texture::GraphicObject_Texture(ShaderTexture* shaderTex, Model* mod)
{
	SetModel(mod);
	pShader = shaderTex;
	World = Matrix(IDENTITY);

	// MARY
	// since we set the texture elsewhere, there is no need to loop through the
	// different meshes in this constructor, but we do need to create the new texture
	// array of pointers
	int n = mod->GetMeshCount();
	pTextureArr = new Texture*[n];

}

// MARY
// delete the pointer pointer array
GraphicObject_Texture::~GraphicObject_Texture()
{
	delete[] pTextureArr;
}

// MARY
// this is now the SetTexture method that will assign all meshes the same texture
void GraphicObject_Texture::SetTexture(Texture* tex)
{
	int i = 0;
	while (i < this->pModel->GetMeshCount())
	{
		// assign all pointers in our Texture pointer array tex texture
		pTextureArr[i] = tex;
		i++;
	}

}

// MARY
// with specified meshnum param, we just set that meshnum to the param tex
void GraphicObject_Texture::SetTexture(Texture* tex, int meshnum)
{
	// assert that the meshnum is a valid mesh num
	assert(pModel->ValidMeshNum(meshnum));
	pTextureArr[meshnum] = tex;
}

void GraphicObject_Texture::SetWorld(const Matrix& m)
{
	World = m;
}

// Render
// we now need to account for rendering possibly different textures with each mesh
void GraphicObject_Texture::Render()
{
	// set the model to context since this is consistent over all meshes
	pModel->SetToContext(pShader->GetContext());

	int i = 0;
	while (i < pModel->GetMeshCount())
	{
		pShader->SendWorld(World);
		// need to specify the texture we are setting with the texture array
		pShader->SetTextureResourceAndSampler(pTextureArr[i]);
		// render each mesh individually with RenderMesh call
		pModel->RenderMesh(pShader->GetContext(), i);
		i++;
	}
}