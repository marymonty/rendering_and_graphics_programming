#include "GraphicObject_Light.h"
#include "Model.h"
#include "ShaderColorLight.h"
#include <assert.h>

GraphicObject_Light::GraphicObject_Light(ShaderColorMultiLight* shader,  Model* mod)
{
	SetModel(mod );
	pShader = shader;
	World = Matrix(IDENTITY);

	// MARY
	// since we set the lighting elsewhere, there is no need to loop through the
	// different meshes in this constructor, but we do need to create the new Vect
	// arrays for ambient, diffuse, and specular
	int n = mod->GetMeshCount();
	matAmbArr = new Vect[n];
	matDifArr = new Vect[n];
	matSpArr = new Vect[n];
}

// MARY
// delete the pointer arrays
GraphicObject_Light::~GraphicObject_Light()
{
	delete[] matAmbArr;
	delete[] matDifArr;
	delete[] matSpArr;
}

void GraphicObject_Light::SetWorld(const Matrix& m) 
{ 
	World = m;
}

// set the Material vects, same material for all meshes since no mesh was specified
void GraphicObject_Light::SetMaterial(Vect am, Vect dif, Vect sp)
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
void GraphicObject_Light::SetMaterial(Vect am, Vect dif, Vect sp, int meshnum)
{
	// assert the meshnum is valid
	assert(pModel->ValidMeshNum(meshnum));
	matAmbArr[meshnum] = am;
	matDifArr[meshnum] = dif;
	matSpArr[meshnum] = sp;
}


// render one mesh at a time
void GraphicObject_Light::Render()
{
	// set model to context since that is consistent over all meshes
	pModel->SetToContext(pShader->GetContext());

	int i = 0;
	while (i < pModel->GetMeshCount())
	{
		pShader->SendWorldAndMaterial(World, matAmbArr[i], matDifArr[i], matSpArr[i]);
		pModel->RenderMesh(pShader->GetContext(), i);
		i++;
	}
}