#include "AppWindow.h"
#include <Windows.h>
#include <iostream>
AppWindow* AppWindow::sharedInstance = NULL;

AppWindow::AppWindow()
{
	//std::cout << "Create called" << std::endl;
	Window::onCreate();
}


AppWindow::~AppWindow()
{
}

AppWindow* AppWindow::getInstance()
{
	return sharedInstance;
}

void AppWindow::initialize()
{
	sharedInstance = new AppWindow();
}

void AppWindow::onCreate()
{
	Window::onCreate();
}

void AppWindow::onUpdate()
{
	Window::onUpdate();
	GraphicsEngine::getInstance()->getImmediateDeviceContext()->clearRenderTargetColor(this->m_swap_chain, 0, 0.3f, 0.4f, 1);
	RECT rc = this->getClientWindowRect();
	GraphicsEngine::getInstance()->getImmediateDeviceContext()->setViewportSize(rc.right - rc.left, rc.bottom - rc.top);

	//Animation starts here
	//Time calculations
	unsigned long new_time = 0;

	if (m_old_time) 
	{
		new_time = ::GetTickCount() - m_old_time;
	}

	m_delta_time = new_time / 1000.0f;
	m_old_time = ::GetTickCount();

	m_angle += 1.57f*m_delta_time;
	constant cc;
	cc.m_angle = m_angle;

	//Shape 1 draw
	this->shape1.getCB()->update(GraphicsEngine::getInstance()->getImmediateDeviceContext(), &cc);
	this->shape2.getCB()->update(GraphicsEngine::getInstance()->getImmediateDeviceContext(), &cc);
	this->shape3.getCB()->update(GraphicsEngine::getInstance()->getImmediateDeviceContext(), &cc);
	shape1.draw();
	shape2.draw();
	shape3.draw();

	m_swap_chain->present(true);
}

void AppWindow::onDestroy()
{
	Window::onDestroy();
	this->shape1.destroy();
	m_swap_chain->release();
	GraphicsEngine::getInstance()->release();
}

void AppWindow::initializeEngine()
{
	GraphicsEngine::initialize();
	GraphicsEngine* gEngine = GraphicsEngine::getInstance();
	m_swap_chain = GraphicsEngine::getInstance()->createSwapChain();

	RECT rc = this->getClientWindowRect();
	int width = rc.right - rc.left;
	int height = rc.bottom - rc.top;

	m_swap_chain->init(this->getWindowHandle(), width, height);

	//initialize shape data
	//TODO: Shape color
	vec3 shape1Pos = { 0.5, 0.5, 0.0 };
	vec3 shape1Scale = { 1, 1, 1 };
	shape1.initialize(shape1Pos, shape1Scale);

	vec3 shape2Pos = { -0.5, -0.5, 0.0 };
	vec3 shape2Scale = { 1, 1, 1 };
	shape2.initialize(shape2Pos, shape2Scale);

	vec3 shape3Pos = { -0.5, 0.5, 0.0 };
	vec3 shape3Scale = { 1.5, 1.5, 1.5 };
	shape3.initialize(shape3Pos, shape3Scale);
}
