#pragma once
#include "Shape.h"
class Cube : public Shape
{
public:
	Cube();
	~Cube();

	void initialize();
private:

	float offsetvalue = 0;
	Vector3D currscale = Vector3D(1, 1, 1);
};

