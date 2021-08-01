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

	//Core functions
	void initialize();
	void draw();
	void update(float windowW, float windowH);
	void destroy();

	//Get functions
	VertexBuffer* getVB();
	ConstantBuffer* getCB();
	VertexShader* getVS();
	PixelShader* getPS();

	//Set functions
	void setPosition(Vector3D newPos);
	void setScale(Vector3D newScale);

private:
	VertexBuffer* m_vb;
	VertexShader* m_vs;
	IndexBuffer* m_ib;
	PixelShader* m_ps;
	ConstantBuffer* m_cb;

	Vector3D position;
	Vector3D scale;

	float m_delta_pos;
	float m_delta_scale;
	float m_delta_rot;
};

