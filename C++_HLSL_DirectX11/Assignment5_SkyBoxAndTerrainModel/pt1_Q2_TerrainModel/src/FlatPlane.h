// FlatPlane.h
// Berthiaume Jan 2017

#ifndef _FlatPlane
#define _FlatPlane

#include "Matrix.h"

class Model;
struct ID3D11DeviceContext;
struct ID3D11Device;

class FlatPlane : public Align16
{
private:
	Model * pPlane;

public:
	FlatPlane(const FlatPlane&) = delete;				// Copy constructor
	FlatPlane(Model&&) = delete;						// Move constructor
	FlatPlane& operator=(const FlatPlane&) & = delete;  // Copy assignment operator
	FlatPlane& operator=(FlatPlane&&) & = delete;       // Move assignment operator
	~FlatPlane();

	FlatPlane(ID3D11Device* dev, float len, float urep, float vrep);

	void Render(ID3D11DeviceContext* context);

};

#endif _FlatPlane
