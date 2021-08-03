#pragma once
#include "Shape.h"
class Plane3D : public Shape
{
public:
	Plane3D();
	~Plane3D();

	void initialize();
	void update(float windowW, float windowH);
private:
};

