#pragma once
#include "ggl.h"

class Vector3f {
public:
	float x, y, z;

	Vector3f(float x = 0.0f, float y = 0.0f, float z = 0.0f);
	// 重载向量之间的加法
	Vector3f operator+(Vector3f &r);

	Vector3f operator-(Vector3f &r);

	Vector3f operator*(float scaler);

	float operator*(Vector3f &r);

	void operator=(const Vector3f &r);
	
	void Normalize();

	float Magnitude();
};

Vector3f Cross(Vector3f v1, Vector3f v2);