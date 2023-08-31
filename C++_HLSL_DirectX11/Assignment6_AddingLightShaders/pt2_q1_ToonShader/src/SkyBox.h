// MARY
// creating a SkyBox header and cpp file

#ifndef SKYBOX_H
#define SKYBOX_H

#include <d3d11.h>
#include "Vect.h"
#include "Align16.h"
#include "Matrix.h"

class Model;
struct ID3D11DeviceContext;
struct ID3D11Device;

class SkyBox : public Align16
{
private:
	Model* pSkyBox;

public:
	SkyBox(const SkyBox&) = delete;				// Copy constructor
	SkyBox(SkyBox&&) = delete;                    // Move constructor
	SkyBox& operator=(const SkyBox&) & = delete;  // Copy assignment operator
	SkyBox& operator=(SkyBox&&) & = delete;       // Move assignment operator


	SkyBox(ID3D11Device* dev, int scaleSize);		// only used constructor
	~SkyBox();										// destructor

	void Render(ID3D11DeviceContext* context);
};



#endif