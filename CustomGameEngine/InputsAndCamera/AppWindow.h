#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <vector>

#include "Cube.h";
#include "Pyramid.h"
#include "Plane3D.h"
#include "IndexBuffer.h"
#include "EngineTime.h"
#include "Window.h"
#include "InputListener.h"
#include "InputSystem.h"
#include "GraphicsEngine.h"
#include "SwapChain.h"
#include "DeviceContext.h"
#include "VertexBuffer.h"
#include "ConstantBuffer.h"
#include "VertexShader.h"
#include "PixelShader.h"

class AppWindow: public Window, public InputListener
{
public:
	static AppWindow* getInstance();
	static void initialize();

	// Inherited via Window
	virtual void onCreate() override;
	virtual void onUpdate() override;
	virtual void onDestroy() override;
	virtual void onFocus() override;
	virtual void onKillFocus() override;

	//Inherited via InputListener
	void onKeyDown(int key);
	void onKeyUp(int key);

	void onMouseMove(const Point& mouse_pos);
	void onLeftMouseDown(const Point& mouse_pos);
	void onLeftMouseUp(const Point& mouse_pos);
	void onRightMouseDown(const Point& mouse_pos);
	void onRightMouseUp(const Point& mouse_pos);

	//Exclusive functions
	void initializeEngine();
	
private:
	AppWindow();
	~AppWindow();
	AppWindow(AppWindow const&) {};
	AppWindow& operator = (AppWindow const&) {};
	static AppWindow* sharedInstance;

	SwapChain * m_swap_chain;
	std::vector<Shape*> shape_list;

	Shape* plane;
	Shape* pyramid;

//Temp shit
private:
	VertexBuffer* m_vb;
	VertexShader* m_vs;
	PixelShader* m_ps;
	ConstantBuffer* m_cb;
	IndexBuffer* m_ib;
private:
	long m_old_delta;
	long m_new_delta;
	float m_delta_time;

	float m_delta_pos;
	float m_delta_scale;
	float m_delta_rot;

	float m_rot_x = 0.0f;
	float m_rot_y = 0.0f;

	float m_scale_cube = 1;
	float m_forward = 0.0f;
	float m_rightward = 0.0f;
	Matrix4x4 m_world_cam;
};

