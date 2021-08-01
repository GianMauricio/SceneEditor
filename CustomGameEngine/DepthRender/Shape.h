#pragma once
#include "Window.h"
#include "Vector3D.h"
#include "Matrix4x4.h"
#include "GraphicsEngine.h"
#include "SwapChain.h"
#include "DeviceContext.h"
#include "IndexBuffer.h"
#include "VertexBuffer.h"
#include "ConstantBuffer.h"
#include "VertexShader.h"
#include "PixelShader.h"
struct vertex
{
	Vector3D position;
	Vector3D color;
	Vector3D color1;
};


__declspec(align(16))
struct constant
{
	Matrix4x4 m_world;
	Matrix4x4 m_view;
	Matrix4x4 m_proj;
	unsigned int m_time;
};


class Shape
{
public:
	Shape();
	~Shape();

	void initialize();
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

