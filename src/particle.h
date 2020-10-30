#pragma once
#include "Vector3f.h"

class Particle {
public:
	GLuint mTexture;

	Vector3f mPosition;

	float mHalfSize;

	Particle();
	void Draw();
};