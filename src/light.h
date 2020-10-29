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

class DirectionLight : public Light {
public:
	DirectionLight(GLenum light);

	void SetPosition(float x, float y, float z);
};

class PointLight : public Light {
	float mPosition[3];
public:
	PointLight(GLenum light);
	void SetPosition(float x, float y, float z);
	void SetConstAttenuation(float v);
	void SetLinearAttenuation(float v);
	void SetQuadricAttenuation(float v);

	void Update(float x, float y, float z);
};

class SpotLight : public PointLight {
public:
	SpotLight(GLenum light);
	void SetDirection(float x, float y, float z);
	void SetExponent(float v);
	void SetCutOff(float v);
};