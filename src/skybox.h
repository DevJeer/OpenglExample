#pragma once
#include "ggl.h"

class SkyBox {
	// 保存6张天空盒的资源
	GLuint mTextures[6];
public:
	void Init(const char *imageDir);

	void Draw();
};