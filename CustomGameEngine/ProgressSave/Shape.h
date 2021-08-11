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

enum Type {CUBE, PLANE, PYRAMID, NONE};

class Shape
{
public:
	Shape();
	~Shape();

	//Core functions
	virtual void initialize() = 0;
	void draw();
	virtual void update(float windowW, float windowH) = 0;
	void destroy();

	//Get functions
	VertexBuffer* getVB();
	ConstantBuffer* getCB();
	VertexShader* getVS();
	PixelShader* getPS();

	//Set functions
	void setPosition(Vector3D newPos);
	void setScale(Vector3D newScale);

	void setRotX(float newRot);
	void setRotY(float newRot);
	void setZoomFactor(float newZoom);
	void setPerspective(float newForward, float newRightward);

protected:
	VertexBuffer* m_vb;
	VertexShader* m_vs;
	IndexBuffer* m_ib;
	PixelShader* m_ps;
	ConstantBuffer* m_cb;

	Vector3D position;
	Vector3D scale;
	Vector3D rotation_vals; /*Use this as float container*/

	float m_delta_pos;
	float m_delta_scale;
	float m_delta_rot;

	//Camera values
	float m_rot_x = 0.0f;
	float m_rot_y = 0.0f;

	float m_scale_cube = 1;
	float m_forward = 0.0f;
	float m_rightward = 0.0f;

	//Fucking preserve this shit for the love of god, if this thing dies we all die with it
	Matrix4x4 m_world_cam;

	Type type = Type::NONE;
};

