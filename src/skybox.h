#pragma once
#include "ggl.h"

class SkyBox {
	// ����6����պе���Դ
	GLuint mTextures[6];
public:
	void Init(const char *imageDir);

	void Draw();
};