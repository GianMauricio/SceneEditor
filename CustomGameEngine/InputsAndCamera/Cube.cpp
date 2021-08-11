#include "Cube.h"

Cube::Cube()
{
	type = Type::CUBE;
}

Cube::~Cube()
{
}

void Cube::initialize()
{
	//Get instance of engine
	GraphicsEngine* gEngine = GraphicsEngine::getInstance();

	//Establish Cube vertices (contains color data)
	vertex vertex_list[] =
	{
		//X - Y - Z
		//FRONT FACE
		{Vector3D(-0.5f,-0.5f,-0.5f),    Vector3D(1,0,0),  Vector3D(0.2f,0,0) },
		{Vector3D(-0.5f,0.5f,-0.5f),    Vector3D(1,1,0), Vector3D(0.2f,0.2f,0) },
		{Vector3D(0.5f,0.5f,-0.5f),   Vector3D(1,1,0),  Vector3D(0.2f,0.2f,0) },
		{Vector3D(0.5f,-0.5f,-0.5f),     Vector3D(1,0,0), Vector3D(0.2f,0,0) },

		//BACK FACE
		{Vector3D(0.5f,-0.5f,0.5f),    Vector3D(0,1,0), Vector3D(0,0.2f,0) },
		{Vector3D(0.5f,0.5f,0.5f),    Vector3D(0,1,1), Vector3D(0,0.2f,0.2f) },
		{Vector3D(-0.5f,0.5f,0.5f),   Vector3D(0,1,1),  Vector3D(0,0.2f,0.2f) },
		{Vector3D(-0.5f,-0.5f,0.5f),     Vector3D(0,1,0), Vector3D(0,0.2f,0) }

	};

	//Load vertex data
	m_vb = GraphicsEngine::getInstance()->createVertexBuffer();
	UINT size_list = ARRAYSIZE(vertex_list);

	//Establish cube indices
	unsigned int index_list[] =
	{
		//FRONT SIDE
		0,1,2,  
		2,3,0,

		//BACK SIDE
		4,5,6,
		6,7,4,

		//TOP SIDE
		1,6,5,
		5,2,1,

		//BOTTOM SIDE
		7,0,3,
		3,4,7,

		//RIGHT SIDE
		3,2,5,
		5,4,3,

		//LEFT SIDE
		7,6,1,
		1,0,7
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

	//Set own position to world origin to start
	position = Vector3D(0.0f, 0.0f, 0.0f);

	//Set own scale to unit size
	scale = Vector3D(1.0f, 1.0f, 1.0f);

	//Set own rotations to 0 across all axes
	rotation_vals = Vector3D(0.0f, 0.0f, 0.0f);

	//Create constant buffer
	constant cc;
	m_cb = GraphicsEngine::getInstance()->createConstantBuffer();
	m_cb->load(&cc, sizeof(constant));
}
