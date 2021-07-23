#include "Shape.h"



Shape::Shape()
{
}

Shape::~Shape()
{
}

void Shape::initialize(vec3 position, vec3 scale, vec3 color)
{
	//Get instance of engine
	GraphicsEngine* gEngine = GraphicsEngine::getInstance();

	//Is there a way to change this?
	//VertexData
	vertex shape[] =
	{
		//X1 - Y1 - Z1, X2 - Y2 - Z2, R1 - G1 - B1, R2 - G2 - B2   
		{-1.0f * scale.x + position.x, 1.0f * scale.y + position.y, 1.0f * scale.z + position.z,
		 -1.0f * scale.x + position.x, 1.0f * scale.y + position.y, 1.0f * scale.z + position.z,
		  color.x, color.y, color.z, color.x, color.y, color.z}, //Upper Left Corner
		{ 1.0f * scale.x + position.x, 1.0f * scale.y + position.y, 1.0f * scale.z + position.z,
		  1.0f * scale.x + position.x, 1.0f * scale.y + position.y, 1.0f * scale.z + position.z,
		  color.x, color.y, color.z, color.x, color.y, color.z}, //Upper Right Corner
		{-1.0f * scale.x + position.x, -1.0f * scale.y + position.y, 1.0f * scale.z + position.z,
		 -1.0f * scale.x + position.x, -1.0f * scale.y + position.y, 1.0f * scale.z + position.z,
		  color.x, color.y, color.z, color.x, color.y, color.z}, //Lower Left Corner
		{ 1.0f * scale.x + position.x, -1.0f * scale.y + position.y, 1.0f * scale.z + position.z,
		  1.0f * scale.x + position.x, -1.0f * scale.y + position.y, 1.0f * scale.z + position.z,
		  color.x, color.y, color.z, color.x, color.y, color.z}, //Lower Right Corner
	};

	//Generate shape data
	void* shader_byte_code = nullptr;
	size_t size_shader = 0;

	gEngine->compileVertexShader(L"VertexShader.hlsl", "vsmain", &shader_byte_code, &size_shader);
	this->m_vs = gEngine->createVertexShader(shader_byte_code, size_shader);

	//Vertex buffers
	UINT size_list = ARRAYSIZE(shape);

	this->m_vb = gEngine->createVertexBuffer();
	this->m_vb->load(shape, sizeof(vertex), size_list, shader_byte_code, size_shader);

	gEngine->releaseCompiledShader();
	gEngine->compilePixelShader(L"PixelShader.hlsl", "psmain", &shader_byte_code, &size_shader);
	this->m_ps = gEngine->createPixelShader(shader_byte_code, size_shader);
	gEngine->releaseCompiledShader();

	constant cc;
	cc.m_angle = 0;

	this->m_cb = gEngine->createConstantBuffer();
	this->m_cb->load(&cc, sizeof(constant));
}

void Shape::initialize(vec3 position1, vec3 position2, vec3 scale1, vec3 scale2, vec3 color1, vec3 color2)
{
	//Get instance of engine
	GraphicsEngine* gEngine = GraphicsEngine::getInstance();

	//Is there a way to change this?
	//VertexData
	vertex shape[] =
	{
		//X1 - Y1 - Z1, X2 - Y2 - Z2, R1 - G1 - B1, R2 - G2 - B2   
		{-1.0f * scale.x + position.x, 1.0f * scale.y + position.y, 1.0f * scale.z + position.z,
		 -1.0f * scale.x + position.x, 1.0f * scale.y + position.y, 1.0f * scale.z + position.z,
		  color.x, color.y, color.z, color.x, color.y, color.z}, //Upper Left Corner
		{ 1.0f * scale.x + position.x, 1.0f * scale.y + position.y, 1.0f * scale.z + position.z,
		  1.0f * scale.x + position.x, 1.0f * scale.y + position.y, 1.0f * scale.z + position.z,
		  color.x, color.y, color.z, color.x, color.y, color.z}, //Upper Right Corner
		{-1.0f * scale.x + position.x, -1.0f * scale.y + position.y, 1.0f * scale.z + position.z,
		 -1.0f * scale.x + position.x, -1.0f * scale.y + position.y, 1.0f * scale.z + position.z,
		  color.x, color.y, color.z, color.x, color.y, color.z}, //Lower Left Corner
		{ 1.0f * scale.x + position.x, -1.0f * scale.y + position.y, 1.0f * scale.z + position.z,
		  1.0f * scale.x + position.x, -1.0f * scale.y + position.y, 1.0f * scale.z + position.z,
		  color.x, color.y, color.z, color.x, color.y, color.z}, //Lower Right Corner
	};

	//Generate shape data
	void* shader_byte_code = nullptr;
	size_t size_shader = 0;

	gEngine->compileVertexShader(L"VertexShader.hlsl", "vsmain", &shader_byte_code, &size_shader);
	this->m_vs = gEngine->createVertexShader(shader_byte_code, size_shader);

	//Vertex buffers
	UINT size_list = ARRAYSIZE(shape);

	this->m_vb = gEngine->createVertexBuffer();
	this->m_vb->load(shape, sizeof(vertex), size_list, shader_byte_code, size_shader);

	gEngine->releaseCompiledShader();
	gEngine->compilePixelShader(L"PixelShader.hlsl", "psmain", &shader_byte_code, &size_shader);
	this->m_ps = gEngine->createPixelShader(shader_byte_code, size_shader);
	gEngine->releaseCompiledShader();

	constant cc;
	cc.m_angle = 0;

	this->m_cb = gEngine->createConstantBuffer();
	this->m_cb->load(&cc, sizeof(constant));
}

void Shape::draw()
{
	GraphicsEngine::getInstance()->getImmediateDeviceContext()->setConstantBuffer(m_vs, m_cb);
	GraphicsEngine::getInstance()->getImmediateDeviceContext()->setConstantBuffer(m_ps, m_cb);
	GraphicsEngine::getInstance()->getImmediateDeviceContext()->setVertexShader(m_vs);
	GraphicsEngine::getInstance()->getImmediateDeviceContext()->setPixelShader(m_ps);
	GraphicsEngine::getInstance()->getImmediateDeviceContext()->setVertexBuffer(m_vb);
	GraphicsEngine::getInstance()->getImmediateDeviceContext()->drawTriangleStrip(m_vb->getSizeVertexList(), 0);
}

void Shape::destroy()
{
	m_vb->release();
	m_vs->release();
	m_ps->release();
}

VertexBuffer* Shape::getVB()
{
	return this->m_vb;
}

ConstantBuffer* Shape::getCB()
{
	return this->m_cb;
}

VertexShader* Shape::getVS()
{
	return this->m_vs;
}

PixelShader* Shape::getPS()
{
	return this->m_ps;
}
