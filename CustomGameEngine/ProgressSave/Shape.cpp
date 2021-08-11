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

void Shape::setRotX(float newRot)
{
	m_rot_x = newRot;
}

void Shape::setRotY(float newRot)
{
	m_rot_y = newRot;
}

void Shape::setZoomFactor(float newZoom)
{
	m_scale_cube = newZoom;
}

void Shape::setPerspective(float newForward, float newRightward)
{
	m_forward = newForward;
	m_rightward = newRightward;
}
