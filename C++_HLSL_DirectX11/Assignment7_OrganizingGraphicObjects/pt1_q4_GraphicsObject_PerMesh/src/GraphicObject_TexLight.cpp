#include "GraphicObject_TexLight.h"
#include "Model.h"
#include "ShaderColorLightTexture.h"
#include <assert.h>

GraphicObject_TexLight::GraphicObject_TexLight(ShaderColorLightTexture* shader,  Model* mod)
{
	SetModel(mod );
	pShader = shader;
	World = Matrix(IDENTITY);

	// MARY
	// create the texture and material arrays
	int n = mod->GetMeshCount();
	pTextureArr = new Texture * [n];
	matAmbArr = new Vect[n];
	matDifArr = new Vect[n];
	matSpArr = new Vect[n];
}

// delete all arrays
GraphicObject_TexLight::~GraphicObject_TexLight()
{
	delete[] pTextureArr;
	delete[] matAmbArr;
	delete[] matDifArr;
	delete[] matSpArr;
}

void GraphicObject_TexLight::SetWorld(const Matrix& m) 
{ 
	World = m;
}


// MARY
// this is now the SetTexture method that will assign all meshes the same texture
void GraphicObject_TexLight::SetTexture(Texture* tex)
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
void GraphicObject_TexLight::SetTexture(Texture* tex, int meshnum)
{
	// assert that the meshnum is a valid mesh num
	assert(pModel->ValidMeshNum(meshnum));
	pTextureArr[meshnum] = tex;
}


// set the Material vects, same material for all meshes since no mesh was specified
void GraphicObject_TexLight::SetMaterial(Vect am, Vect dif, Vect sp)
{
	int i = 0;
	while (i < pModel->GetMeshCount())
	{
		matAmbArr[i] = am;
		matDifArr[i] = dif;
		matSpArr[i] = sp;
		i++;
	}
}

// set the Material vectsfor the specified mesh only
void GraphicObject_TexLight::SetMaterial(Vect am, Vect dif, Vect sp, int meshnum)
{
	// assert the meshnum is valid
	assert(pModel->ValidMeshNum(meshnum));
	matAmbArr[meshnum] = am;
	matDifArr[meshnum] = dif;
	matSpArr[meshnum] = sp;
}


// render each mesh separately
void GraphicObject_TexLight::Render()
{
	// model set to context is consistent through all meshes
	pModel->SetToContext(pShader->GetContext());
	int i = 0;
	while (i < pModel->GetMeshCount())
	{
		pShader->SendWorldAndMaterial(World, matAmbArr[i], matDifArr[i], matSpArr[i]);
		pShader->SetTextureResourceAndSampler(pTextureArr[i]);
		pModel->RenderMesh(pShader->GetContext(), i);
		i++;
	}
}