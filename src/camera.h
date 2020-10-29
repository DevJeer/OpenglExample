#pragma once
#include "Vector3f.h"

class Camera {
public:
	Camera();
	Vector3f mPos, mViewCenter, mUp;
	void Update(float deltaTime);
};