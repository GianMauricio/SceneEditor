#pragma once
#include "Window.h"
#include "GraphicsEngine.h"
#include "SwapChain.h"
#include "DeviceContext.h"
#include "VertexBuffer.h"
#include "ConstantBuffer.h"
#include "VertexShader.h"
#include "PixelShader.h"

struct vec3
{
	float x, y, z;
};

struct vertex
{
	vec3 position;
	vec3 position1;
	vec3 color;
	vec3 color1;
};

__declspec(align(16))
struct constant
{
	float m_angle;
};


class Shape
{
public:
	Shape();
	~Shape();

	void initialize(vec3 position, vec3 scale, vec3 color);
	void initialize(vec3 position1, vec3 position2, vec3 scale1, vec3 scale2, vec3 color1, vec3 color2);
	void initializeDemoShape();
	void draw();
	void update(constant cc);
	void destroy();
	VertexBuffer* getVB();
	ConstantBuffer* getCB();
	VertexShader* getVS();
	PixelShader* getPS();

private:
	VertexBuffer* m_vb;
	VertexShader* m_vs;
	PixelShader* m_ps;
	ConstantBuffer* m_cb;

	unsigned long m_old_time = 0;
	float m_delta_time = 0;
	float m_angle = 0;
};

