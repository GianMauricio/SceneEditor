#pragma once
#include "Shape.h"
class Pyramid : public Shape
{
public:
	Pyramid();
	~Pyramid();

	void initialize();
	void update(float winW, float winH);
private:
};

