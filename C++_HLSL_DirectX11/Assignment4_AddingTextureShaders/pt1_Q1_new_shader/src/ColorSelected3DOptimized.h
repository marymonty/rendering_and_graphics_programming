// MARY
// ColorSelected3DOptimized shader class
// Derived from the ShaderBase base class

#ifndef _ColorSelected3DOptimized
#define _ColorSelected3DOptimized

#include "ShaderBase.h"
#include "Matrix.h"

struct ID3D11Buffer;
struct ID3D11Device;

class ColorSelected3DOptimized : public ShaderBase
{
private:
	// we have one constant buffer that now stores the
	// World*View*Projection matrix and the selected Color
	struct Data_WVPColor
	{
		Matrix WVP;
		Vect Color;
	};
	// pointer to our constant buffer
	ID3D11Buffer*           mpBuffWVPColor;

public:
	// define the big four (plus) just to delete or default them to optimize a bit
	ColorSelected3DOptimized(const ColorSelected3DOptimized&) = delete;					// Copy constructor
	ColorSelected3DOptimized(ColorSelected3DOptimized&&) = default;                    // Move constructor
	ColorSelected3DOptimized& operator=(const ColorSelected3DOptimized&) & = default;  // Copy assignment operator
	ColorSelected3DOptimized& operator=(ColorSelected3DOptimized&&) & = default;       // Move assignment operator
	~ColorSelected3DOptimized();		  												// Destructor

	ColorSelected3DOptimized(ID3D11Device* device);

	virtual void SetToContext(ID3D11DeviceContext* devcon) override;

	void SendWVPColor(const Matrix& wvp, const Vect& col);
};

#endif _ColorSelected3DOptimized
