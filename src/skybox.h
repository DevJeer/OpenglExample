#pragma once
#include "ggl.h"

class SkyBox {
	// 保存6张天空盒的资源
	GLuint mTextures[6];

	// 保存显示列表
	GLuint mFastDrawCall;

public:
	void Init(const char *imageDir);

	void DrawCommand();

	void Draw(float x, float y, float z);
};