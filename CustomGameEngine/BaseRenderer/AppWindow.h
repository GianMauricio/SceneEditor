#pragma once
#include "Window.h"
#include "GraphicsEngine.h"
#include "SwapChain.h"
#include "DeviceContext.h"
#include "VertexBuffer.h"
#include "VertexShader.h"
#include "PixelShader.h"

class AppWindow: public Window
{
public:
	AppWindow();
	~AppWindow();

	// Inherited via Window
	virtual void onCreate() override;
	virtual void onUpdate() override;
	virtual void onDestroy() override;
private:
	SwapChain * m_swap_chain;
	VertexBuffer* vb_RS;
	VertexBuffer* vb_RR;
	VertexBuffer* vb_GR;
	VertexBuffer* vb_RTC;
	VertexBuffer* vb_RTLM;
	VertexBuffer* vb_RTRM;
	VertexShader* m_vs;
	PixelShader* m_ps;
};

