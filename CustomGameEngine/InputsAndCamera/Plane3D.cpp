#include "Plane3D.h"

Plane3D::Plane3D()
{
	type = Type::PLANE;
}

Plane3D::~Plane3D()
{
}

void Plane3D::initialize()
{
	//Get instance of engine
	GraphicsEngine* gEngine = GraphicsEngine::getInstance();

	//Establish plane vertices (contains color data)
	vertex vertex_list[] =
	{
		//X - Y - Z
		//FRONT FACE
		{Vector3D(-0.5f,-0.5f,-0.5f),    Vector3D(1, 1, 1),  Vector3D(1, 1, 1)},
		{Vector3D(-0.5f,0.5f,-0.5f),    Vector3D(1, 1, 1), Vector3D(1, 1, 1)},
		{Vector3D(0.5f,0.5f,-0.5f),   Vector3D(1, 1, 1),  Vector3D(1, 1, 1)},
		{Vector3D(0.5f,-0.5f,-0.5f),     Vector3D(1, 1, 1), Vector3D(1, 1, 1)},

		//BACK FACE
		{Vector3D(0.5f,-0.5f,0.5f),    Vector3D(1, 1, 1), Vector3D(1, 1, 1)},
		{Vector3D(0.5f,0.5f,0.5f),    Vector3D(1, 1, 1), Vector3D(1, 1, 1)},
		{Vector3D(-0.5f,0.5f,0.5f),   Vector3D(1, 1, 1),  Vector3D(1, 1, 1)},
		{Vector3D(-0.5f,-0.5f,0.5f),     Vector3D(1, 1, 1), Vector3D(1, 1, 1)}
	};

	//Load vertex data
	m_vb = GraphicsEngine::getInstance()->createVertexBuffer();
	UINT size_list = ARRAYSIZE(vertex_list);

	//Establish plane indices
	unsigned int index_list[] =
	{
		//FRONT SIDE
		0,1,2,  //FIRST TRIANGLE
		2,3,0,  //SECOND TRIANGLE
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

	//Create constant buffer
	constant cc;
	m_cb = GraphicsEngine::getInstance()->createConstantBuffer();
	m_cb->load(&cc, sizeof(constant));

	//Set own position to world origin to start
	position = Vector3D(0.0f, 0.0f, 0.0f);

	//Set own scale to unit size
	//Scale down to make plane
	scale = Vector3D(1.0f, 0.01f, 1.0f);
}

void Plane3D::update(float windowW, float windowH)
{
	//Update time value
	constant cc;

	//Calculate new time values
	m_delta_pos += EngineTime::getDeltaTime() / 10.0f;
	if (m_delta_pos > 10.0f)
		m_delta_pos = 0;
	cc.m_time = m_delta_pos;

	//Set world scale first
	cc.m_world.setIdentity();
	cc.m_world.setScale(scale);

	//Create temp matrix to fulfill backwards multiplication logic
	Matrix4x4 temp;

	/*
	//Account for rotations
	temp.setIdentity();
	temp.setRotationZ(rotation_vals.m_z);
	cc.m_world *= temp;

	temp.setIdentity();
	temp.setRotationY(rotation_vals.m_y);
	cc.m_world *= temp;

	temp.setIdentity();
	temp.setRotationX(rotation_vals.m_x);
	cc.m_world *= temp;
	*/

	//Account for translations
	temp.setIdentity();
	temp.setTranslation(position);
	cc.m_world *= temp;


	//Create transform matrix for worldCamera
	Matrix4x4 world_cam;

	//Set world cam to identity
	world_cam.setIdentity();

	//Reset temp
	temp.setIdentity();

	//Account for camera Y
	temp.setRotationX(m_rot_x);
	world_cam *= temp;

	//Reset Temp
	temp.setIdentity();

	//Account for camera X
	temp.setRotationY(m_rot_y);
	world_cam *= temp;

	//Get the world camera's position
	Vector3D new_pos = m_world_cam.getTranslation() + world_cam.getZDirection() * (m_forward * 0.1f);

	//Account for world cam position
	new_pos = new_pos + world_cam.getXDirection() * (m_rightward * 0.1f);

	//Adjust own position
	world_cam.setTranslation(new_pos);

	//Update world camera position for next frame
	m_world_cam = world_cam;

	//Invert world camera so that the perspective view doesn't break
	world_cam.inverse();

	cc.m_view = world_cam;

	cc.m_proj.setPerspectiveFovLH(1.57f, (windowW / windowH), 0.1f, 100.0f);

	m_cb->update(GraphicsEngine::getInstance()->getImmediateDeviceContext(), &cc);
}
