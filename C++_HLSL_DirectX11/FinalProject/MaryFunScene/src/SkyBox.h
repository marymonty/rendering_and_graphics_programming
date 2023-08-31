// MARY
// creating a SkyBox header and cpp file

/*	Final updates to SkyBox:
*		constructor now takes pointers to the skybox texture and shader that we store in the skybox object
*		we have a SetWorld function to set and store the skybox world for easier rendering
*/

#ifndef SKYBOX_H
#define SKYBOX_H

#include <d3d11.h>
#include "Vect.h"
#include "Align16.h"
#include "Matrix.h"
#include "Texture.h"
#include "ShaderTexture.h"

class Model;
struct ID3D11DeviceContext;
struct ID3D11Device;

class SkyBox : public Align16
{
private:
	Model* pSkyBox;
	Texture* pTexture;
	ShaderTexture* pShader;
	Matrix mWorld;

public:
	SkyBox(const SkyBox&) = delete;				// Copy constructor
	SkyBox(SkyBox&&) = delete;                    // Move constructor
	SkyBox& operator=(const SkyBox&) & = delete;  // Copy assignment operator
	SkyBox& operator=(SkyBox&&) & = delete;       // Move assignment operator


	SkyBox(ID3D11Device* dev, int scaleSize, Texture* tex, ShaderTexture* shader);		// only used constructor
	~SkyBox();										// destructor

	// new set functions
	void SetTexture(Texture* tex);
	void SetWorld(Matrix w);

	void Render(ID3D11DeviceContext* context);
};



#endif