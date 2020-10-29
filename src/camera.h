#pragma once
#include "Vector3f.h"

class Camera {
public:
	Camera();
	// 定义四个标志位， 表明摄像机朝哪个方向移动
	bool mbMoveLeft, mbMoveRight, mbMoveForward, mbMoveBack;

	Vector3f mPos, mViewCenter, mUp;

	void Update(float deltaTime);

	void Pitch(float angle);

	void Yaw(float angle);
};