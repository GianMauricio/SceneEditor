#include "Pyramid.h"

Pyramid::Pyramid()
{
	type = Type::PYRAMID;
}

Pyramid::~Pyramid()
{
}

void Pyramid::initialize()
{
	//Get instance of engine
	GraphicsEngine* gEngine = GraphicsEngine::getInstance();

	//Establish Pyramid vertices (contains color data)
	vertex vertex_list[] =
	{
		//X - Y - Z
		//APEX
		{Vector3D(0.0f, 1, 0.0f),    Vector3D(1,0,0),  Vector3D(0.2f,0,0) }, //0

		//BASE
		{Vector3D(-0.5f, 0, 0.5f),    Vector3D(0,1,0), Vector3D(0,0.2f,0) }, //1
		{Vector3D(-0.5f, 0, -0.5f),    Vector3D(0,1,1), Vector3D(0,0.2f,0.2f) }, //2
		{Vector3D(0.5f, 0, -0.5f),   Vector3D(0,1,1),  Vector3D(0,0.2f,0.2f) }, //3
		{Vector3D(0.5f, -0, 0.5f),     Vector3D(0,1,0), Vector3D(0,0.2f,0) } //4

	};

	//Load vertex data
	m_vb = GraphicsEngine::getInstance()->createVertexBuffer();
	UINT size_list = ARRAYSIZE(vertex_list);

	//Establish cube indices
	unsigned int index_list[] =
	{
		//FRONT SIDE
		2, 0, 3,

		//LEFT SIDE
		1, 0, 2,

		//BACK SIDE
		4, 0, 1,

		//RIGHT SIDE
		3, 0, 4,

		//BASE1
		1, 2, 3,

		//BASE2
		3, 4, 1
	};

	//Load index data
	m_ib = GraphicsEngine::getInstance()->createIndexBuffer();
	UINT size_index_list = ARRAYSIZE(index_list);

	m_ib->load(index_list, size_index_list);

	//Generate and store render data
	void* shader_byte_code = nullptr;
	size_t size_shader = 0;
	GraphicsEngine::getInstance()->compileVertexShader(L"VertexShader.hlsl", "vsmain", &shader_byte_code, &size_shader);

	m_vs = GraphicsEngine::getInstance()->createVertexShader(shader_byte_code, size_shader);
	m_vb->load(vertex_list, sizeof(vertex), size_list, shader_byte_code, size_shader);

	GraphicsEngine::getInstance()->releaseCompiledShader();

	GraphicsEngine::getInstance()->compilePixelShader(L"PixelShader.hlsl", "psmain", &shader_byte_code, &size_shader);
	m_ps = GraphicsEngine::getInstance()->createPixelShader(shader_byte_code, size_shader);
	GraphicsEngine::getInstance()->releaseCompiledShader();

	//Create constant buffer
	constant cc;
	m_cb = GraphicsEngine::getInstance()->createConstantBuffer();
	m_cb->load(&cc, sizeof(constant));

	//Set own position to world origin to start
	position = Vector3D(0.0f, 0.0f, 0.0f);

	//Set own scale to unit size
	scale = Vector3D(1.0f, 1.0f, 1.0f);
}

void Pyramid::update(float winW, float winH)
{
	//Update time value
	constant cc;
	cc.m_time = EngineTime::getDeltaTime();

	//Calculate new position values
	m_delta_pos += EngineTime::getDeltaTime() / 10.0f;
	if (m_delta_pos > 1.0f)
		m_delta_pos = 0;

	//Create transform matrix
	Matrix4x4 temp;
	m_delta_scale += EngineTime::getDeltaTime() / 0.55f;

	cc.m_world.setScale(scale);

	temp.setIdentity();
	temp.setRotationZ(m_delta_scale);
	cc.m_world *= temp;

	temp.setIdentity();
	temp.setRotationY(m_delta_scale);
	cc.m_world *= temp;

	temp.setIdentity();
	temp.setRotationX(m_delta_scale);
	cc.m_world *= temp;

	temp.setIdentity();
	temp.setTranslation(position);
	cc.m_world *= temp;

	cc.m_view.setIdentity();
	cc.m_proj.setOrthoLH
	(
		winW / 100.0f,
		winH / 100.0f,
		-6.0f,
		10.0f
	);

	m_cb->update(GraphicsEngine::getInstance()->getImmediateDeviceContext(), &cc);
}