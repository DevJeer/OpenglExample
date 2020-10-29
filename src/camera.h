#pragma once
#include "Vector3f.h"

class Camera {
public:
	Camera();
	// �����ĸ���־λ�� ������������ĸ������ƶ�
	bool mbMoveLeft, mbMoveRight, mbMoveForward, mbMoveBack;

	Vector3f mPos, mViewCenter, mUp;

	int mViewportWidth, mViewportHeight;

	void Update(float deltaTime);

	void Pitch(float angle);

	void Yaw(float angle);

	void RotateView(float angle, float x, float y, float z);

	void SwitchTo3D();

	void SwitchTo2D();
};