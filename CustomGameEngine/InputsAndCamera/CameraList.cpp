#include "CameraList.h"

CameraList* CameraList::sharedInstance = NULL;

CameraList* CameraList::getInstance()
{
	return sharedInstance;
}

void CameraList::initialize(float newWinW, float newWinH)
{
	sharedInstance = new CameraList();
	sharedInstance->currentCamera = new Camera(newWinW, newWinH);
}

void CameraList::destroy()
{
}

void CameraList::update()
{
	currentCamera->update(EngineTime::getDeltaTime());
}

Camera* CameraList::getCamera()
{
	return currentCamera;
}

Matrix4x4 CameraList::getCurrentCamera()
{
	return currentCamera->getViewmatrix();
}

Matrix4x4 CameraList::getProjectionMatrix()
{
	return currentCamera->getProjMatrix();
}

CameraList::CameraList()
{
}

CameraList::~CameraList()
{
}
