#include "AppWindow.h"

//Define custon vector3
struct vec3
{
	float x, y, z;
};

//Define custom vertex
struct vertex
{
	vec3 position;
	vec3 color;
};

AppWindow::AppWindow()
{
}

AppWindow::~AppWindow()
{
}

void AppWindow::onCreate()
{
	//Base class functions
	Window::onCreate();
	GraphicsEngine::get()->init();
	m_swap_chain=GraphicsEngine::get()->createSwapChain();

	RECT rc = this->getClientWindowRect();
	m_swap_chain->init(this->m_hwnd, rc.right - rc.left, rc.bottom - rc.top);

	//All vertices to draw
	//Rainbow Rectangle (The Pride flag lol) 
	vertex RainbowRect[] = 
	{
		//X - Y - Z, R - G - B
		//Red Stripe
		{-0.5f, 0.9f, 0.0f,  1, 0, 0}, //Upper Left Corner
		{0.5f, 0.9f, 0.0f,  1, 0, 0}, //Upper Right Corner
		{-0.5f, 0.8f, 0.0f,  1, 0, 0}, //Lower Left Corner
		{0.5f, 0.8f, 0.0f,  1, 0, 0}, //Lower Right Corner

		//Orange Stripe
		{-0.5f, 0.8f, 0.0f,  1, 0.6, 0}, //Upper Left Corner
		{0.5f, 0.8f, 0.0f,  1, 0.6, 0}, //Upper Right Corner
		{-0.5f, 0.7f, 0.0f,  1, 0.6, 0}, //Lower Left Corner
		{0.5f, 0.7f, 0.0f,  1, 0.6, 0}, //Lower Right Corner

		//Yellow Stripe
		{-0.5f, 0.7f, 0.0f,  1, 1, 0}, //Upper Left Corner
		{0.5f, 0.7f, 0.0f,  1, 1, 0}, //Upper Right Corner
		{-0.5f, 0.6f, 0.0f,  1, 1, 0}, //Lower Left Corner
		{0.5f, 0.6f, 0.0f,  1, 1, 0}, //Lower Right Corner

		//Green Stripe
		{-0.5f, 0.6f, 0.0f,  0, 1, 0}, //Upper Left Corner
		{0.5f, 0.6f, 0.0f,  0, 1, 0}, //Upper Right Corner
		{-0.5f, 0.5f, 0.0f,  0, 1, 0}, //Lower Left Corner
		{0.5f, 0.5f, 0.0f,  0, 1, 0}, //Lower Right Corner

		//Blue Stripe
		{-0.5f, 0.5f, 0.0f,  0, 0, 1}, //Upper Left Corner
		{0.5f, 0.5f, 0.0f,  0, 0, 1}, //Upper Right Corner
		{-0.5f, 0.4f, 0.0f,  0, 0, 1}, //Lower Left Corner
		{0.5f, 0.4f, 0.0f,  0, 0, 1}, //Lower Right Corner

		//Purple Stripe
		{-0.5f, 0.4f, 0.0f,  1, 0, 1}, //Upper Left Corner
		{0.5f, 0.4f, 0.0f,  1, 0, 1}, //Upper Right Corner
		{-0.5f, 0.3f, 0.0f,  1, 0, 1}, //Lower Left Corner
		{0.5f, 0.3f, 0.0f,  1, 0, 1}, //Lower Right Corner
	};

	//Green Rectangle
	vertex GreenRect[] =
	{
		{-0.5f, 0.2f, 0.0f,  0, 1, 0}, //Upper Left Corner
		{0.5f, 0.2f, 0.0f,  0, 1, 0}, //Upper Right Corner
		{-0.5f, -0.2f, 0.0f,  0, 1, 0}, //Lower Left Corner
		{0.5f, -0.2f, 0.0f,  0, 1, 0}, //Lower Right Corner
	};

	//This one is complicated, Rainbow Triangle
	vertex RTCore[] =
	{
		//X - Y - Z, R - G - B
		//Red Stripe
		{-0.5f, -0.3f, 0.0f,  1, 0, 0}, //Upper Left Corner
		{0.5f, -0.3f, 0.0f,  1, 0, 0}, //Upper Right Corner
		{-0.5f, -0.4f, 0.0f,  1, 0, 0}, //Lower Left Corner
		{0.5f, -0.4f, 0.0f,  1, 0, 0}, //Lower Right Corner

		//Orange Stripe
		{-0.5f, -0.4f, 0.0f,  1, 0.6, 0}, //Upper Left Corner
		{0.5f, -0.4f, 0.0f,  1, 0.6, 0}, //Upper Right Corner
		{-0.5f, -0.5f, 0.0f,  1, 0.6, 0}, //Lower Left Corner
		{0.5f, -0.5f, 0.0f,  1, 0.6, 0}, //Lower Right Corner

		//Yellow Stripe
		{-0.5f, -0.5f, 0.0f,  1, 1, 0}, //Upper Left Corner
		{0.5f, -0.5f, 0.0f,  1, 1, 0}, //Upper Right Corner
		{-0.5f, -0.6f, 0.0f,  1, 1, 0}, //Lower Left Corner
		{0.5f, -0.6f, 0.0f,  1, 1, 0}, //Lower Right Corner

		//Green Stripe
		{-0.5f, -0.6f, 0.0f,  0, 1, 0}, //Upper Left Corner
		{0.5f, -0.6f, 0.0f,  0, 1, 0}, //Upper Right Corner
		{-0.5f, -0.7f, 0.0f,  0, 1, 0}, //Lower Left Corner
		{0.5f, -0.7f, 0.0f,  0, 1, 0}, //Lower Right Corner

		//Blue Stripe
		{-0.5f, -0.7f, 0.0f,  0, 0, 1}, //Upper Left Corner
		{0.5f, -0.7f, 0.0f,  0, 0, 1}, //Upper Right Corner
		{-0.5f, -0.8f, 0.0f,  0, 0, 1}, //Lower Left Corner
		{0.5f, -0.8f, 0.0f,  0, 0, 1}, //Lower Right Corner

		//Purple Stripe
		{-0.5f, -0.8f, 0.0f,  1, 0, 1}, //Upper Left Corner
		{0.5f, -0.8f, 0.0f,  1, 0, 1}, //Upper Right Corner
		{-0.5f, -0.9f, 0.0f,  1, 0, 1}, //Lower Left Corner
		{0.5f, -0.9f, 0.0f,  1, 0, 1}, //Lower Right Corner
	};

	vertex RTLeftMask[] = {
		{-0.5f, -0.3f, 0.0f,  0, 0.3, 0.4}, //Upper Left Corner
		{ 0.0f, -0.3f, 0.0f,  0, 0.3, 0.4}, //Upper Right Corner --> Make right-er
		{-0.5f, -0.9f, 0.0f,  0, 0.3, 0.4}, //Lower Left Corner
		{-0.2f, -0.9f, 0.0f,  0, 0.3, 0.4}, //Lower Right Corner
	};

	vertex RTRightMask[] = {
		{0.0f, -0.3f, 0.0f,  0, 0.3, 0.4}, //Upper Left Corner --> Make left-er
		{0.5f, -0.3f, 0.0f,  0, 0.3, 0.4}, //Upper Right Corner 
		{0.2f, -0.9f, 0.0f,  0, 0.3, 0.4}, //Lower Left Corner
		{0.5f, -0.9f, 0.0f,  0, 0.3, 0.4}, //Lower Right Corner
	};

	//Create Vertex buffers
	vb_RR=GraphicsEngine::get()->createVertexBuffer();
	UINT size_listRR = ARRAYSIZE(RainbowRect);

	vb_GR = GraphicsEngine::get()->createVertexBuffer();
	UINT size_listRG = ARRAYSIZE(GreenRect);

	vb_RTC = GraphicsEngine::get()->createVertexBuffer();
	UINT size_listRTC = ARRAYSIZE(RTCore);

	vb_RTLM = GraphicsEngine::get()->createVertexBuffer();
	UINT size_listRTLM = ARRAYSIZE(RTLeftMask);

	vb_RTRM = GraphicsEngine::get()->createVertexBuffer();
	UINT size_listRTRM = ARRAYSIZE(RTRightMask);

	//Parse and compile vertex shader
	void* shader_byte_code = nullptr;
	size_t size_shader = 0;
	GraphicsEngine::get()->compileVertexShader(L"VertexShader.hlsl", "vsmain", &shader_byte_code, &size_shader);
	m_vs=GraphicsEngine::get()->createVertexShader(shader_byte_code, size_shader);

	//Load vertices into their respective buffers with the shader data
	vb_RR->load(RainbowRect, sizeof(vertex), size_listRR, shader_byte_code, size_shader);
	vb_GR->load(GreenRect, sizeof(vertex), size_listRG, shader_byte_code, size_shader);
	vb_RTC->load(RTCore, sizeof(vertex), size_listRTC, shader_byte_code, size_shader);
	vb_RTLM->load(RTLeftMask, sizeof(vertex), size_listRTC, shader_byte_code, size_shader);
	vb_RTRM->load(RTRightMask, sizeof(vertex), size_listRTC, shader_byte_code, size_shader);

	//Release vertex shader
	GraphicsEngine::get()->releaseCompiledShader();

	//Parse and compile pixel shader
	GraphicsEngine::get()->compilePixelShader(L"PixelShader.hlsl", "psmain", &shader_byte_code, &size_shader);
	m_ps = GraphicsEngine::get()->createPixelShader(shader_byte_code, size_shader);

	//Release pixel shader
	GraphicsEngine::get()->releaseCompiledShader();
}

void AppWindow::onUpdate()
{
	Window::onUpdate();

	//CLEAR THE RENDER TARGET 
	GraphicsEngine::get()->getImmediateDeviceContext()->clearRenderTargetColor(this->m_swap_chain,
		0, 0.3f,0.4f, 1);

	//SET VIEWPORT OF RENDER TARGET IN WHICH WE HAVE TO DRAW
	RECT rc = this->getClientWindowRect();
	GraphicsEngine::get()->getImmediateDeviceContext()->setViewportSize(rc.right - rc.left, rc.bottom - rc.top);

	//SET DEFAULT SHADER IN THE GRAPHICS PIPELINE TO BE ABLE TO DRAW
	GraphicsEngine::get()->getImmediateDeviceContext()->setVertexShader(m_vs);
	GraphicsEngine::get()->getImmediateDeviceContext()->setPixelShader(m_ps);

	//Rainbow rect
	GraphicsEngine::get()->getImmediateDeviceContext()->setVertexBuffer(vb_RR);
	GraphicsEngine::get()->getImmediateDeviceContext()->drawTriangleStrip(vb_RR->getSizeVertexList(), 0);

	//Green Rect
	GraphicsEngine::get()->getImmediateDeviceContext()->setVertexBuffer(vb_GR);
	GraphicsEngine::get()->getImmediateDeviceContext()->drawTriangleStrip(vb_GR->getSizeVertexList(), 0);

	//Rainbow triangle
	GraphicsEngine::get()->getImmediateDeviceContext()->setVertexBuffer(vb_RTC);
	GraphicsEngine::get()->getImmediateDeviceContext()->drawTriangleStrip(vb_RTC->getSizeVertexList(), 0);

	//RT Left Mask
	GraphicsEngine::get()->getImmediateDeviceContext()->setVertexBuffer(vb_RTLM);
	GraphicsEngine::get()->getImmediateDeviceContext()->drawTriangleStrip(vb_RTLM->getSizeVertexList(), 0);

	//RT Right Mask
	GraphicsEngine::get()->getImmediateDeviceContext()->setVertexBuffer(vb_RTRM);
	GraphicsEngine::get()->getImmediateDeviceContext()->drawTriangleStrip(vb_RTRM->getSizeVertexList(), 0);

	m_swap_chain->present(true);
}

void AppWindow::onDestroy()
{
	Window::onDestroy();
	vb_RR->release();
	vb_GR->release();
	m_swap_chain->release();
	m_vs->release();
	m_ps->release();
	GraphicsEngine::get()->release();
}
