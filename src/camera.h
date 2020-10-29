#pragma once
#include "Vector3f.h"

class Camera {
public:
	Camera();
	// �����ĸ���־λ�� ������������ĸ������ƶ�
	bool mbMoveLeft, mbMoveRight, mbMoveForward, mbMoveBack;

	Vector3f mPos, mViewCenter, mUp;

	void Update(float deltaTime);

	void Pitch(float angle);

	void Yaw(float angle);
};