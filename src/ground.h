#pragma once
#include "ggl.h"

class Ground {
private:
	float mAmbientMaterial[4], mDiffuseMaterial[4], mSpecularMaterial[4];
public:
	void Draw();

	void SetAmbientMaterial(float r, float g, float b, float a);
	void SetDiffuseMaterial(float r, float g, float b, float a);
	void SetSpecularMaterial(float r, float g, float b, float a);
};