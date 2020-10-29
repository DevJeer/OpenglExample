#pragma once
#include "Vector3f.h"

class Sprite2D {
public:
	GLuint mTexture;
	Vector3f mVertexes[4];
	void SetImage(const char *imagePath);
	void SetRect(float x, float y, float width, float height);
	void Draw();
};