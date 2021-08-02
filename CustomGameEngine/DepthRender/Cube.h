#pragma once
#include "Shape.h"
class Cube : public Shape
{
public:
	Cube();
	~Cube();

	void update(float windowW, float windowH);
	void initialize();
private:

	bool expanding = true;
	bool rotating = true;
	float offsetvalue = 0;
	Vector3D currscale = Vector3D(1, 1, 1);
};

