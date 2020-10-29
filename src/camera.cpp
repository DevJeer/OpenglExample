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
// 沿自身x轴旋转
void Camera::Pitch(float angle)
{
	Vector3f viewDirection = mViewCenter - mPos;
	viewDirection.Normalize();
	Vector3f rightDirection = Cross(viewDirection, mUp);
	rightDirection.Normalize();

	RotateView(angle, rightDirection.x, rightDirection.y, rightDirection.z);
}
// 绕世界坐标系的y轴旋转
void Camera::Yaw(float angle)
{
	RotateView(angle, mUp.x, mUp.y, mUp.z);
}

// 绕任意轴旋转的方法
void Camera::RotateView(float angle, float x, float y, float z)
{
	Vector3f viewDirection = mViewCenter - mPos;
	Vector3f newDirection(0.0f, 0.0f, 0.0f);
	float C = cosf(angle);
	float S = sinf(angle);
	Vector3f tempX(C + x * x * (1 - C),
		x * y * (1 - C) - z * S,
		x * z * (1 - C) + y * S);
	newDirection.x = tempX * viewDirection;
	Vector3f tempY(x * y * (1 - C) + z * S,
		C + y * y * (1 - C),
		y * z * (1 - C) - x * S);
	newDirection.y = tempY * viewDirection;
	Vector3f tempZ(x * z * (1 - C) - y * S,
		y * z * (1 - C) + x * S,
		C + z * z * (1 - C));
	newDirection.z = tempZ * viewDirection;
	mViewCenter = mPos + newDirection;
}