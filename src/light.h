#pragma once
#include "ggl.h"

class Light {
protected:
	// 使用opengl中的哪一盏灯
	GLenum mLightIdentifier;
	Light();

public:
	// 设置环境光
	void SetAmbientColor(float r, float g, float b, float a);
	// 设置漫反射
	void SetDiffuseColor(float r, float g, float b, float a);
	// 设置镜面反射
	void SetSpecularColor(float r, float g, float b, float a);
	// 开启灯光
	void Enable();
};