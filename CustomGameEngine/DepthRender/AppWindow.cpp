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
	float winH = rc.bottom - rc.top;
	float winW = rc.right - rc.left; 
	GraphicsEngine::getInstance()->getImmediateDeviceContext()->setViewportSize(winW, winH);

	plane->update(winW, winH);
	plane->draw();

	//Draw and update all shapes
	for (Shape* curr : shape_list) {
		curr->update(winW, winH);
		curr->draw();
	}

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
	//make stuff truly random
	srand(time(NULL));
	GraphicsEngine::getInstance()->initialize();
	EngineTime::initialize();
	m_swap_chain = GraphicsEngine::getInstance()->createSwapChain();

	RECT rc = this->getClientWindowRect();
	int width = rc.right - rc.left;
	int height = rc.bottom - rc.top;

	m_swap_chain->init(this->getWindowHandle(), width, height);
	
	//Initialize cube shapes
	for (int i = 0; i < 100; i++) {
		Shape* temp = new Cube();

		//Make not null exception
		temp->initialize();

		//make each shape small so that it doesn't eat the screen
		temp->setScale(Vector3D(0.2, 0.2, 0.2));

		//add new shape to list
		shape_list.push_back(temp);
	}

	//Randomize the position of all shapes
	for (Shape* curr : shape_list) {
		//Create 3 random numbers for x, y and z
		float x = -4.0f + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (8.0)));
		float y = -3.0f + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (6.0)));
		float z = -4.0f + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (8.0)));

		Vector3D randPos = Vector3D(x, y, z);


		curr->setPosition(randPos);
	}

	//Make plane
	plane = new Plane3D();
	plane->initialize();
	plane->setPosition(Vector3D(0.2, 0.0, 0));
	plane->setScale(Vector3D(5, 0.01, 5));
}
