#include "GraphicObject_Light.h"
#include "Model.h"
#include "ShaderColorLight.h"
#include <assert.h>

GraphicObject_Light::GraphicObject_Light(ShaderColorLight* shader,  Model* mod)
{
	SetModel(mod );
	pShader = shader;
	World = Matrix(IDENTITY);
}

GraphicObject_Light::~GraphicObject_Light()
{

}

void GraphicObject_Light::SetWorld(const Matrix& m) 
{ 
	World = m;
}

// set the Material vects
void GraphicObject_Light::SetMaterial(Vect am, Vect dif, Vect sp)
{
	matAmb = am;
	matDif = dif;
	matSp = sp;
}

void GraphicObject_Light::Render()
{
	pShader->SendWorldAndMaterial(World, matAmb, matDif, matSp);
	pModel->SetToContext(pShader->GetContext());
	pModel->Render(pShader->GetContext());
}