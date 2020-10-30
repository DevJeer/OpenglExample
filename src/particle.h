#pragma once
#include "Vector3f.h"

class Particle {
public:
	GLuint mTexture;

	Vector3f mPosition;
	// 
	float mHalfSize;
	// ���ӵ��������ڣ�����ʱ��
	float mLifeTime, mLivingTime;

	GLubyte mColor[4];

	Particle();

	void Init(GLubyte r, GLubyte g, GLubyte b, GLubyte a, float life);

	void Draw();

	
};