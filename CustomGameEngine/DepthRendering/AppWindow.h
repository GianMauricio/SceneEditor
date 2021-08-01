#pragma once
#include "Shape.h";
#include "Window.h"
#include "Text.h"
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
	Shape shape1;
	Shape shape2;
	Shape shape3;

	Text text;

	unsigned long m_old_time = 0;
	float m_delta_time = 0;
	float m_angle = 0;
};

