#pragma once
#include "ggl.h"

class Light {
protected:
	// ʹ��opengl�е���һյ��
	GLenum mLightIdentifier;
	Light();

public:
	// ���û�����
	void SetAmbientColor(float r, float g, float b, float a);
	// ����������
	void SetDiffuseColor(float r, float g, float b, float a);
	// ���þ��淴��
	void SetSpecularColor(float r, float g, float b, float a);
	// �����ƹ�
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