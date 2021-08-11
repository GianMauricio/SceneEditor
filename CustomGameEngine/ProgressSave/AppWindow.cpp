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

	//Draw and update all shapes
	for (Shape* curr : shape_list) {
		//Set new world params
		curr->setPerspective(m_forward, m_rightward);
		curr->setRotX(m_rot_x);
		curr->setRotY(m_rot_y);
		curr->setZoomFactor(m_scale_cube);

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
}

void AppWindow::onKillFocus()
{
	InputSystem::getInstance()->removeListener(this);
}

void AppWindow::onKeyDown(int key)
{
	//This works because chars have an implicit integer value attached to them
	switch (key) 
	{
		case 'W':
			m_forward = 1.0f;
			break;

		case 'S':
			m_forward = -1.0f;
			break;

		case 'A':
			m_rightward = -1.0f;
			break;

		case 'D':
			m_rightward = 1.0f;
			break;

		default:
			std::cout << "Key not implemented; key code is: " << key << std::endl;
			break;
	}
}

void AppWindow::onKeyUp(int key)
{
	m_forward = 0.0f;
	m_rightward = 0.0f;
}

void AppWindow::onMouseMove(const Point& mouse_pos)
{
	//std::cout << "mouse moved" << std::endl;
	int width = (this->getClientWindowRect().right - this->getClientWindowRect().left);
	int height = (this->getClientWindowRect().bottom - this->getClientWindowRect().top);

	m_rot_x += (mouse_pos.m_y - (height / 2.0f)) * EngineTime::getDeltaTime() * 0.1f;
	m_rot_y += (mouse_pos.m_x - (width / 2.0f)) * EngineTime::getDeltaTime() * 0.1f;

	InputSystem::getInstance()->setCursorPosition(Point((int)(width / 2.0f), (int)(height / 2.0f)));
}

void AppWindow::onLeftMouseDown(const Point& mouse_pos)
{
	//std::cout << "mouse 1 down" << std::endl;
	m_scale_cube = 0.5f;
}

void AppWindow::onLeftMouseUp(const Point& mouse_pos)
{
	//std::cout << "mouse 1 up" << std::endl;
	m_scale_cube = 1.0f;
}

void AppWindow::onRightMouseDown(const Point& mouse_pos)
{
	//std::cout << "mouse 2 down" << std::endl;
	m_scale_cube = 2.0f;
}

void AppWindow::onRightMouseUp(const Point& mouse_pos)
{
	//std::cout << "mouse 2 up" << std::endl;
	m_scale_cube = 1.0f;
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
		float z = -4.0f + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (8.0)));

		Vector3D randPos = Vector3D(x, 1.0f, z);

		curr->setPosition(randPos);
	}

	//Make plane
	Shape* plane = new Plane3D();
	plane->initialize();
	plane->setPosition(Vector3D(0.0, 0.75, 0.0));
	plane->setScale(Vector3D(10, 0.01, 10));
	shape_list.push_back(plane);
}
