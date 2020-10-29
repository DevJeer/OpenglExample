#pragma once
#include "ggl.h"

class SkyBox {
	// ����6����պе���Դ
	GLuint mTextures[6];

	// ������ʾ�б�
	GLuint mFastDrawCall;

public:
	void Init(const char *imageDir);

	void DrawCommand();

	void Draw(float x, float y, float z);
};