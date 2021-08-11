#include "Shape.h"

Shape::Shape()
{
}

Shape::~Shape()
{
}

void Shape::draw()
{
	//std::cout << "drawing" << std::endl;
	//Draw the triangles by indice
	GraphicsEngine::getInstance()->getImmediateDeviceContext()->setConstantBuffer(m_vs, m_cb);
	GraphicsEngine::getInstance()->getImmediateDeviceContext()->setConstantBuffer(m_ps, m_cb);

	//Set shaders
	GraphicsEngine::getInstance()->getImmediateDeviceContext()->setVertexShader(m_vs);
	GraphicsEngine::getInstance()->getImmediateDeviceContext()->setPixelShader(m_ps);

	//Set vertices
	GraphicsEngine::getInstance()->getImmediateDeviceContext()->setVertexBuffer(m_vb);
	//Set indices
	GraphicsEngine::getInstance()->getImmediateDeviceContext()->setIndexBuffer(m_ib);

	//Draw
	GraphicsEngine::getInstance()->getImmediateDeviceContext()->drawIndexedTriangleList(m_ib->getSizeIndexList(), 0, 0);
}

void Shape::update(float windowW, float windowH)
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
	
	//Account for translations
	temp.setIdentity();
	temp.setTranslation(position);
	cc.m_world *= temp;

	cc.m_view = CameraList::getInstance()->getCurrentCamera();

	cc.m_proj = CameraList::getInstance()->getProjectionMatrix();

	m_cb->update(GraphicsEngine::getInstance()->getImmediateDeviceContext(), &cc);
}

void Shape::destroy()
{
	//Release buffers
	m_vb->release();
	m_vs->release();
	m_ps->release();
	m_ib->release();
	m_cb->release();
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

void Shape::setPosition(Vector3D newPos)
{
	position = newPos;
}

void Shape::setScale(Vector3D newScale)
{
	scale = newScale;
}

bool Shape::getViewPers()
{
	return viewPers;
}

void Shape::setViewPers(bool newView)
{
	viewPers = newView;
}
