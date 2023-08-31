#include "GraphicObject_TexLight.h"
#include "Model.h"
#include "ShaderColorLightTexture.h"
#include <assert.h>

GraphicObject_TexLight::GraphicObject_TexLight(ShaderColorLightTexture* shader,  Model* mod)
{
	SetModel(mod );
	pShader = shader;
	World = Matrix(IDENTITY);
}

GraphicObject_TexLight::~GraphicObject_TexLight()
{

}

void GraphicObject_TexLight::SetWorld(const Matrix& m) 
{ 
	World = m;
}


void GraphicObject_TexLight::SetTexture(Texture* tex)
{
	pTexture = tex;
}


// set the Material vects
void GraphicObject_TexLight::SetMaterial(Vect am, Vect dif, Vect sp)
{
	matAmb = am;
	matDif = dif;
	matSp = sp;
}


void GraphicObject_TexLight::Render()
{
	pShader->SendWorldAndMaterial(World, matAmb, matDif, matSp);
	pShader->SetTextureResourceAndSampler(pTexture);
	pModel->SetToContext(pShader->GetContext());
	pModel->Render(pShader->GetContext());
}