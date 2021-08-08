#include "Shape.h"

Shape::Shape()
{
}

Shape::~Shape()
{
}

void Shape::draw()
{
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

void Shape::update(float windowW, float windowH) {

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

void Shape::setWorldCam(Matrix4x4 newWorldCam)
{
	m_world_cam = newWorldCam;
}
