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
};

