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
	float winH = rc.right - rc.left;
	float winW = rc.bottom - rc.top;
	GraphicsEngine::getInstance()->getImmediateDeviceContext()->setViewportSize(winW, winH);

	shape1.update(winW, winH);
	shape1.draw();

	m_swap_chain->present(true);
}

void AppWindow::onDestroy()
{
	Window::onDestroy();
	m_swap_chain->release();
	GraphicsEngine::getInstance()->release();
}

void AppWindow::initializeEngine()
{
	GraphicsEngine::getInstance()->initialize();
	EngineTime::initialize();
	m_swap_chain = GraphicsEngine::getInstance()->createSwapChain();

	RECT rc = this->getClientWindowRect();
	int width = rc.right - rc.left;
	int height = rc.bottom - rc.top;

	m_swap_chain->init(this->getWindowHandle(), width, height);
	shape1.initialize();

	shape1.setScale(Vector3D(0.1, 0.1, 0.1));
}
