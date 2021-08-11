#include "Camera.h"

Camera::Camera(float newWinW, float newWinH)
{
	//Make view matrix not null
	InputSystem::getInstance()->addListener(this);
	winH = newWinH;
	winW = newWinW;
}

Camera::~Camera()
{
}

void Camera::update(float deltaTime)
{
	//Create transform matrices for worldCamera calculations
	Matrix4x4 temp;

	//Set viewmatrix to identity
	viewMatrix.setIdentity();

	if (zoomIn) {
		m_scale_cube += 0.5f * deltaTime;
		zoom_value += 20.0f * deltaTime;
	}

	if (zoomOut) {
		m_scale_cube -= 0.5f * deltaTime;
		zoom_value -= 20.0f * deltaTime;
	}

	//Account for world scaling
	/*
	temp.setIdentity();
	temp.setScale(Vector3D(m_scale_cube, m_scale_cube, m_scale_cube));
	viewMatrix *= temp;
	*/

	//Account for rotation
	temp.setIdentity();
	temp.setRotationX(m_rot_x);
	viewMatrix *= temp;

	temp.setIdentity();
	temp.setRotationY(m_rot_y);
	viewMatrix *= temp;

	Vector3D new_pos = m_world_cam.getTranslation();
	Vector3D orthoPos = Vector3D(new_pos.m_x, new_pos.m_y, -10);

	if (viewPers) {
		new_pos = m_world_cam.getTranslation() + viewMatrix.getZDirection() * (m_forward * deltaTime * 10);

		//Account for displacement Horizontal
		new_pos = new_pos + viewMatrix.getXDirection() * (m_rightward * deltaTime * 10);

		//Adjust own position
		viewMatrix.setTranslation(new_pos);
	}

	else {
		orthoPos = orthoPos + m_world_cam.getYDirection() * (m_forward * deltaTime * 10);

		//Account for displacement Horizontal
		orthoPos = orthoPos + m_world_cam.getXDirection() * (m_rightward * deltaTime * 10);

		//Adjust own position
		viewMatrix.setTranslation(orthoPos);
	}

	//Invert world camera so that the perspective view doesn't break
	m_world_cam = viewMatrix;

	viewMatrix.inverse();

	//Generate new projection matrix
	if (viewPers) {
		projMatrix.setPerspectiveFovLH(1.57f, (winW / winH), 0.1f, 100.0f);
	}

	else {
		projMatrix.setOrthoLH
		(
			winW / zoom_value,
			winH / zoom_value,
			0.1f,
			100.0f
		);
	}
}

Matrix4x4 Camera::getViewmatrix()
{
	return viewMatrix;
}

Matrix4x4 Camera::getProjMatrix()
{
	return projMatrix;
}

void Camera::setWindowDimensions(float newWinW, float newWinH)
{
	winW = newWinW;
	winH = newWinH;
}

void Camera::onKeyDown(int key)
{
	//This works because chars have an implicit integer value attached to them
	switch (key)
	{
	case 'W':
		m_forward = 1.0f;
		break;

	case 'S':
		m_forward = -1.0f;
		break;

	case 'A':
		m_rightward = -1.0f;
		break;

	case 'D':
		m_rightward = 1.0f;
		break;

	case 'P':
		viewPers = true;
		break;

	case 'O':
		viewPers = false;
		break;

	default:
		//std::cout << "Key not implemented; key code is: " << key << std::endl;
		break;
	}
}

void Camera::onKeyUp(int key)
{
	m_forward = 0.0f;
	m_rightward = 0.0f;
}

void Camera::onMouseMove(const Point& mouse_pos)
{
	//std::cout << "mouse moved" << std::endl;
	m_rot_y += (mouse_pos.m_x - (winW / 2.0f)) * EngineTime::getDeltaTime() * 0.1f;
	m_rot_x += (mouse_pos.m_y - (winH / 2.0f)) * EngineTime::getDeltaTime() * 0.1f;
	
	InputSystem::getInstance()->setCursorPosition(Point((int)(winW / 2.0f), (int)(winH / 2.0f)));
}

void Camera::onLeftMouseDown(const Point& mouse_pos)
{
	//std::cout << "mouse 1 down" << std::endl;
	//m_scale_cube += 0.1f;
	zoomIn = true;
}

void Camera::onLeftMouseUp(const Point& mouse_pos)
{
	//std::cout << "mouse 1 up" << std::endl;
	//m_scale_cube = 1.0f;
	zoomIn = false;
}

void Camera::onRightMouseDown(const Point& mouse_pos)
{
	//std::cout << "mouse 2 down" << std::endl;
	//m_scale_cube -= 0.5f;
	zoomOut = true;
}

void Camera::onRightMouseUp(const Point& mouse_pos)
{
	//std::cout << "mouse 2 up" << std::endl;
	//m_scale_cube = 1.0f;
	zoomOut = false;
}
