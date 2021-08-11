#pragma once
#include "InputListener.h"
#include "InputSystem.h"
#include "Matrix4x4.h"
#include "EngineTime.h"
#include <string>
class Camera : public InputListener
{
public:
	Camera(float newWinW, float newWinH);
	~Camera();

	//Internal functions
	void update(float deltaTime);
	Matrix4x4 getViewmatrix();
	Matrix4x4 getProjMatrix();

	//Set functions
	void setWindowDimensions(float newWinW, float newWinH);

	//Input listener override
	void onKeyDown(int key) override;
	void onKeyUp(int key) override;

	void onMouseMove(const Point& mouse_pos) override;

	void onLeftMouseDown(const Point& mouse_pos) override;
	void onLeftMouseUp(const Point& mouse_pos) override;

	void onRightMouseDown(const Point& mouse_pos) override;
	void onRightMouseUp(const Point& mouse_pos) override;

private:
	Matrix4x4 viewMatrix;
	Matrix4x4 projMatrix;

	//Window values
	float winW, winH;

	//Camera values
	float m_rot_x = 0.0f;
	float m_rot_y = 0.0f;

	bool zoomIn = false;
	bool zoomOut = false;

	float m_scale_cube = 1;
	float m_forward = 0.0f;
	float m_rightward = 0.0f;

	float zoom_value = 100.0f;

	//Fucking preserve this shit for the love of god, if this thing dies we all die with it
	bool viewPers = true;
	Matrix4x4 m_world_cam;
};

