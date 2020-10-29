#include "camera.h"

Camera::Camera() :
	mPos(0.0f, 0.0f, 0.0f),
	mViewCenter(0.0f, 0.0f, -1.0f),
	mUp(0.0f, 1.0f, 0.0f) {

}

void Camera::Update(float deltaTime)
{
	glLoadIdentity();
	gluLookAt(mPos.x, mPos.y, mPos.z,
		mViewCenter.x, mViewCenter.y, mViewCenter.z,
		mUp.x, mUp.y, mUp.z);
}