#include "GraphicObject_Color.h"
#include "Model.h"
#include "ShaderColor.h"
#include <assert.h>

GraphicObject_Color::GraphicObject_Color(ShaderColor* shader,  Model* mod)
{
	SetModel(mod );
	pShader = shader;

	Color = Vect(1, 1, 1);
	World = Matrix(IDENTITY);
}

GraphicObject_Color::~GraphicObject_Color()
{

}

void GraphicObject_Color::SetColor(const Vect& col) 
{
	Color = col;
}

void GraphicObject_Color::SetWorld(const Matrix& m) 
{ 
	World = m;
}

void GraphicObject_Color::Render()
{
	pShader->SendWorldColor(World, Color);
	pModel->SetToContext(pShader->GetContext());
	pModel->Render(pShader->GetContext());
}