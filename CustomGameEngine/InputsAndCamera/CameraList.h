#pragma once
#include "Camera.h"
class CameraList
{
public:
	static CameraList* getInstance();
	static void initialize(float newWinW, float newWinH);
	static void destroy();

	void update();

	Camera* getCamera();
	Matrix4x4 getCurrentCamera();
	Matrix4x4 getProjectionMatrix();

private:
	CameraList();
	~CameraList();
	CameraList(CameraList const&) {};
	CameraList& operator = (CameraList const&) {};
	static CameraList* sharedInstance;

	Camera* currentCamera;
};

