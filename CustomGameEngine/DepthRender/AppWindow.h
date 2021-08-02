#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <vector>

#include "Cube.h";
#include "Plane3D.h"
#include "IndexBuffer.h"
#include "EngineTime.h"
#include "Window.h"
#include "GraphicsEngine.h"
#include "SwapChain.h"
#include "DeviceContext.h"
#include "VertexBuffer.h"
#include "ConstantBuffer.h"
#include "VertexShader.h"
#include "PixelShader.h"

class AppWindow: public Window
{
public:
	static AppWindow* getInstance();
	static void initialize();

	// Inherited via Window
	virtual void onCreate() override;
	virtual void onUpdate() override;
	virtual void onDestroy() override;

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

	bool accelerating = true;
	float elapsedTime = 0;
	float m_angle = 0;
};

