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
	
	/*
	//Initialize cube shapes
	for (int i = 0; i < 50; i++) {
		Shape* temp = new Cube();

		//Make not null exception
		temp->initialize();

		//make each shape small so that it doesn't eat the screen
		temp->setScale(Vector3D(1.5, 1.5, 1.5));

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

		curr->setPosition(Vector3D(0, -1, 0));
	}
	*/

	//Make plane
	plane = new Plane3D();
	plane->initialize();
	plane->setPosition(Vector3D(0.0, -1.0, 0.0));
	plane->setScale(Vector3D(7, 0.01, 7));
	shape_list.push_back(plane);

	Cube* newCube1 = new Cube();
	newCube1->initialize();
	newCube1->setScale(Vector3D(0.75, 0.75, 0.75));
	newCube1->setPosition(Vector3D(-1.0, 0.9, 0.0));
	shape_list.push_back(newCube1);

	Cube* newCube2 = new Cube();
	newCube2->initialize();
	newCube2->setScale(Vector3D(0.75, 0.75, 0.75));
	newCube2->setPosition(Vector3D(-2.5, 2.0, 0.0));
	shape_list.push_back(newCube2);

	Cube* newCube3 = new Cube();
	newCube3->initialize();
	newCube3->setScale(Vector3D(0.75, 0.75, 0.75));
	newCube3->setPosition(Vector3D(-2.5, 3.0, -4.0));
	shape_list.push_back(newCube3);

	//pyramid = new Pyramid();
	//pyramid->initialize();
	//pyramid->setPosition(Vector3D(2.0, 0, 0));
	//shape_list.push_back(pyramid);
}
