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