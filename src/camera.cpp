#include "camera.h"

Camera::Camera() :
	mPos(0.0f, 0.0f, 0.0f),
	mViewCenter(0.0f, 0.0f, -1.0f),
	mUp(0.0f, 1.0f, 0.0f) {

}

void Camera::Update(float deltaTime)
{
	float moveSpeed = 10.0f;
#pragma region x y z坐标的实现方式

	/*if (mbMoveLeft)
	{
		float delta = deltaTime * moveSpeed;
		mPos.x = mPos.x - delta;
		mViewCenter.x = mViewCenter.x - delta;
	}
	if (mbMoveRight)
	{
		float delta = deltaTime * moveSpeed;
		mPos.x = mPos.x + delta;
		mViewCenter.x = mViewCenter.x + delta;
	}
	if (mbMoveForward)
	{
		float delta = -deltaTime * moveSpeed;
		mPos.z = mPos.z + delta;
		mViewCenter.z = mViewCenter.z + delta;
	}
	if (mbMoveBack)
	{
		float delta = -deltaTime * moveSpeed;
		mPos.z = mPos.z - delta;
		mViewCenter.z = mViewCenter.z - delta;
	}*/
#pragma endregion

	// 使用向量的方式实现
	// 计算朝向前方的向量
	Vector3f forwardDirection = mViewCenter - mPos;
	forwardDirection.Normalize();
	// 计算朝右的向量
	Vector3f rightDirection = Cross(forwardDirection, mUp);
	rightDirection.Normalize();
	if (mbMoveLeft)
	{
		Vector3f delta = rightDirection * deltaTime * moveSpeed;
		mPos = mPos - delta;
		mViewCenter = mViewCenter - delta;
	}
	if (mbMoveRight)
	{
		Vector3f delta = rightDirection * deltaTime * moveSpeed;
		mPos = mPos + delta;
		mViewCenter = mViewCenter + delta;
	}
	if (mbMoveForward)
	{
		Vector3f delta = forwardDirection * deltaTime * moveSpeed;
		mPos = mPos + delta;
		mViewCenter = mViewCenter + delta;
	}
	if (mbMoveBack)
	{
		Vector3f delta = forwardDirection * deltaTime * moveSpeed;
		mPos = mPos - delta;
		mViewCenter = mViewCenter - delta;
	}

	glLoadIdentity();
	gluLookAt(mPos.x, mPos.y, mPos.z,
		mViewCenter.x, mViewCenter.y, mViewCenter.z,
		mUp.x, mUp.y, mUp.z);
}