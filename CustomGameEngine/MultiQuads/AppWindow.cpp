#include "AppWindow.h"
#include <Windows.h>

AppWindow* AppWindow::sharedInstance = NULL;

struct vec3
{
	float x, y, z;
};

struct vertex
{
	vec3 position;
	vec3 position1;
	vec3 color;
	vec3 color1;
};


__declspec(align(16))
struct constant
{
	float m_angle;
};


AppWindow::AppWindow()
{
}


AppWindow::~AppWindow()
{
}

AppWindow* AppWindow::getInstance()
{
	if (sharedInstance == NULL)
	{
		sharedInstance = new AppWindow();
	}

	return sharedInstance;
}

void AppWindow::initialize()
{
	sharedInstance = new AppWindow();
}

void AppWindow::onCreate()
{
	Window::onCreate();
	GraphicsEngine::getInstance()->init();
}

void AppWindow::onUpdate()
{
	Window::onUpdate();
	GraphicsEngine::getInstance()->getImmediateDeviceContext()->clearRenderTargetColor(this->m_swap_chain, 0, 0.3f, 0.4f, 1);
	RECT rc = this->getClientWindowRect();
	GraphicsEngine::getInstance()->getImmediateDeviceContext()->setViewportSize(rc.right - rc.left, rc.bottom - rc.top);

	//Animation starts here
	//Time calculations
	unsigned long new_time = 0;

	if (m_old_time) 
	{
		new_time = ::GetTickCount() - m_old_time;
	}

	m_delta_time = new_time / 1000.0f;
	m_old_time = ::GetTickCount();

	m_angle += 1.57f*m_delta_time;
	constant cc;
	cc.m_angle = m_angle;

	m_cb->update(GraphicsEngine::getInstance()->getImmediateDeviceContext(), &cc);

	GraphicsEngine::getInstance()->getImmediateDeviceContext()->setConstantBuffer(m_vs, m_cb);
	GraphicsEngine::getInstance()->getImmediateDeviceContext()->setConstantBuffer(m_ps, m_cb);

	GraphicsEngine::getInstance()->getImmediateDeviceContext()->setVertexShader(m_vs);
	GraphicsEngine::getInstance()->getImmediateDeviceContext()->setPixelShader(m_ps);


	GraphicsEngine::getInstance()->getImmediateDeviceContext()->setVertexBuffer(m_vb);

	GraphicsEngine::getInstance()->getImmediateDeviceContext()->drawTriangleStrip(m_vb->getSizeVertexList(), 0);
	m_swap_chain->present(true);
}

void AppWindow::onDestroy()
{
	Window::onDestroy();
	m_vb->release();
	m_swap_chain->release();
	m_vs->release();
	m_ps->release();
	GraphicsEngine::getInstance()->release();
}

void AppWindow::initializeEngine()
{
	GraphicsEngine::initialize();
	GraphicsEngine* gEngine = GraphicsEngine::getInstance();
	m_swap_chain = GraphicsEngine::getInstance()->createSwapChain();

	RECT rc = this->getClientWindowRect();
	int width = rc.right - rc.left;
	int height = rc.bottom - rc.top;

	m_swap_chain->init(this->getWindowHandle(), width, height); //Redundant
	
	void* shader_byte_code = nullptr;
	size_t size_shader = 0;

	//Vertices
	gEngine->compileVertexShader(L"VertexShader.hlsl", "vsmain", &shader_byte_code, &size_shader);
	m_vs = gEngine->createVertexShader(shader_byte_code, size_shader);

	//VertexData
	vertex shape[] =
	{
		//X1 - Y1 - Z1, X2 - Y2 - Z2, R1 - G1 - B1, R2 - G2 - B2   
		{-0.4f, 0.0f, 0.0f, -0.6f, 0.0f, 0.0f,  1, 1, 0,  0, 1, 0}, //Left Point, Yellow - Green
		{-0.1f, 0.1f, 0.0f, -0.1f, 0.1f, 0.0f,  0, 0, 1,  1, 0, 0}, //Upper Left Brace (Unmoving), Blue - Red
		{-0.1f, -0.1f, 0.0f, -0.1f, -0.1f, 0.0f,  0, 0, 1,  1, 0, 0}, //Lower Left Brace (Unmoving), Blue - Red
		{0.0f, 0.5f, 0.0f, 0.0f, 0.7f, 0.0f,  1, 1, 0,  0, 1, 0}, //Upper Point, Yellow - Green
		{0.0f, -0.5f, 0.0f, 0.0f, -0.7f, 0.0f,  1, 1, 0,  0, 1, 0}, //Lower Point, Yellow - Green
		{0.1f, 0.1f, 0.0f, 0.1f, 0.1f, 0.0f,  0, 0, 1,  1, 0, 0}, //Upper Right Brace (Unmoving), Blue - Red
		{0.1f, -0.1f, 0.0f, 0.1f, -0.1f, 0.0f,  0, 0, 1,  1, 0, 0}, //Lower Right Brace (Unmoving), Blue - Red
		{0.4f, 0.0f, 0.0f, 0.6f, 0.0f, 0.0f,  1, 1, 0,  0, 1, 0} //Right Point, Yellow - Green
	};

	//Vertex buffers
	m_vb = gEngine->createVertexBuffer();
	UINT size_list = ARRAYSIZE(shape);
	m_vb->load(shape, sizeof(vertex), size_list, shader_byte_code, size_shader);

	gEngine->releaseCompiledShader();


	gEngine->compilePixelShader(L"PixelShader.hlsl", "psmain", &shader_byte_code, &size_shader);
	m_ps = gEngine->createPixelShader(shader_byte_code, size_shader);
	gEngine->releaseCompiledShader();

	constant cc;
	cc.m_angle = 0;

	m_cb = gEngine->createConstantBuffer();
	m_cb->load(&cc, sizeof(constant));
}
