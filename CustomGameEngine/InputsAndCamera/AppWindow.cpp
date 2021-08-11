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
	InputSystem::getInstance()->addListener(this);
	InputSystem::getInstance()->showCursor(false);
}

void AppWindow::onUpdate()
{
	//Update the window
	Window::onUpdate();

	//Update the input listeners
	InputSystem::getInstance()->update();

	//Clear the current render
	GraphicsEngine::getInstance()->getImmediateDeviceContext()->clearRenderTargetColor(this->m_swap_chain, 0, 0.3f, 0.4f, 1);
	RECT rc = this->getClientWindowRect();
	float winH = rc.bottom - rc.top;
	float winW = rc.right - rc.left; 
	GraphicsEngine::getInstance()->getImmediateDeviceContext()->setViewportSize(winW, winH);

	//Update camera
	CameraList::getInstance()->update();

	//Draw and update all shapes
	for (Shape* curr : shape_list) {
		//Update shapes
		curr->update(winW, winH);
		curr->draw();
	}

	m_swap_chain->present(true);
}

void AppWindow::onDestroy()
{
	Window::onDestroy();
	//TODO:Release the shape list
	m_swap_chain->release();
	//TODO:Release the pixel and vertex shaders
	GraphicsEngine::getInstance()->release();
}

void AppWindow::onFocus()
{
	InputSystem::getInstance()->addListener(this);
	//InputSystem::getInstance()->addListener(CameraList::getInstance()->getCamera());
}

void AppWindow::onKillFocus()
{
	InputSystem::getInstance()->removeListener(this);
	//InputSystem::getInstance()->removeListener(CameraList::getInstance()->getCamera());
}

void AppWindow::onKeyDown(int key)
{
	//This works because chars have an implicit integer value attached to them
	switch (key) 
	{
		case 'P':
			for (Shape* shape : shape_list) {
				shape->setViewPers(true);
			}

			/*std::cout << "Rightwards: " << m_rightward << std::endl;
			std::cout << "Forwards: " << m_forward << std::endl;
			std::cout << "RotX: " << m_rot_x << std::endl;
			std::cout << "RotY: " << m_rot_y << std::endl;*/
			break;

		case 'O':
			for (Shape* shape : shape_list) {
				shape->setViewPers(false);
			}
			break;

		default:
			//std::cout << "Key not implemented; key code is: " << key << std::endl;
			break;
	}
}

void AppWindow::onKeyUp(int key)
{
}

void AppWindow::onMouseMove(const Point& mouse_pos)
{
}

void AppWindow::onLeftMouseDown(const Point& mouse_pos)
{
}

void AppWindow::onLeftMouseUp(const Point& mouse_pos)
{
}

void AppWindow::onRightMouseDown(const Point& mouse_pos)
{
}

void AppWindow::onRightMouseUp(const Point& mouse_pos)
{
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
	
	CameraList::initialize(width, height);

	m_swap_chain->init(this->getWindowHandle(), width, height);
	
	/*
	for (int i = 0; i < 20; i++) {
		Shape* temp = new Cube();

		//Make not null exception
		temp->initialize();

		//make each shape small so that it doesn't eat the screen
		temp->setScale(Vector3D(1.0, 1.0, 1.0));

		//add new shape to list
		shape_list.push_back(temp);
	}
	

	//Randomize the position of all Cubes
	for (Shape* curr : shape_list) {
		//Create 2 random numbers for x and z
		float x = -4.0f + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (8.0)));
		float y = -4.0f + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (8.0)));
		float z = -2.0f + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (2.0)));

		Vector3D randPos = Vector3D(x, y, z);

		curr->setPosition(randPos);
	}
	*/
	//Make cube
	Shape* temp = new Cube();

	//Make not null exception
	temp->initialize();

	//make each shape small so that it doesn't eat the screen
	temp->setScale(Vector3D(1.0, 1.0, 1.0));
	temp->setPosition(Vector3D(0.0, 0.0, 0.0));

	//add new shape to list
	shape_list.push_back(temp);

	//Make plane
	Shape* plane = new Plane3D();
	plane->initialize();
	plane->setPosition(Vector3D(0.0, 0.0, 0.0));
	plane->setScale(Vector3D(10, 0.01, 10));
	shape_list.push_back(plane);
}
