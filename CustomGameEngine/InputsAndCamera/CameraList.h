#pragma once
#include "Camera.h"
class CameraList
{
public:
	static CameraList* getInstance();
	static void initialize(float newWinW, float newWinH);
	static void destroy();

	void update();

	Matrix4x4 getCurrentCamera();

private:
	CameraList();
	~CameraList();
	CameraList(CameraList const&) {};
	CameraList& operator = (CameraList const&) {};
	static CameraList* sharedInstance;

	Camera* currentCamera;
};

