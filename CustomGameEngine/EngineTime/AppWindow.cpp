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
	if (accelerating) {
		elapsedTime += EngineTime::getDeltaTime();
	}

	else {
		elapsedTime -= EngineTime::getDeltaTime();
	}

	if (elapsedTime > 7.5f) {
		accelerating = false;
	}

	else if(elapsedTime < 0.0f){
		accelerating = true;
	}

	m_angle += 0.05f * elapsedTime;

	//std::cout << m_angle << std::endl;
	constant cc;
	cc.m_angle = m_angle;

	//Shape update
	this->shape1.update(cc);
	shape1.draw();

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
	EngineTime::initialize();
	GraphicsEngine* gEngine = GraphicsEngine::getInstance();
	m_swap_chain = GraphicsEngine::getInstance()->createSwapChain();

	RECT rc = this->getClientWindowRect();
	int width = rc.right - rc.left;
	int height = rc.bottom - rc.top;

	m_swap_chain->init(this->getWindowHandle(), width, height);

	//initialize demo shape data
	shape1.initializeDemoShape();
}
