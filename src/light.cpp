#include "light.h"

Light::Light()
{

}
// ���û�����
void Light::SetAmbientColor(float r, float g, float b, float a)
{
	float ambientColor[] = { r, g, b, a };
	glLightfv(mLightIdentifier, GL_AMBIENT, ambientColor);
}
// ����������
void Light::SetDiffuseColor(float r, float g, float b, float a)
{
	float diffuseColor[] = { r, g, b, a };
	glLightfv(mLightIdentifier, GL_DIFFUSE, diffuseColor);
}
// ���þ���߹�
void Light::SetSpecularColor(float r, float g, float b, float a)
{
	float specularColor[] = { r, g, b, a };
	glLightfv(mLightIdentifier, GL_SPECULAR, specularColor);
}
// �����ƹ�
void Light::Enable()
{
	// ��������
	glEnable(GL_LIGHTING);
	// ����ָ����һյ��
	glEnable(mLightIdentifier);
}


DirectionLight::DirectionLight(GLenum light)
{
	mLightIdentifier = light;
}
// ����ֱ����λ��
void DirectionLight::SetPosition(float x, float y, float z)
{
	float position[] = { x, y, z, 0.0f };
	glLightfv(mLightIdentifier, GL_POSITION, position);
}

PointLight::PointLight(GLenum light)
{
	mLightIdentifier = light;
}

void PointLight::SetPosition(float x, float y, float z)
{
	float pos[] = { x, y, z, 1.0f };
	glLightfv(mLightIdentifier, GL_POSITION, pos);
}
// ���ó���˥��ϵ��
void PointLight::SetConstAttenuation(float v)
{
	glLightf(mLightIdentifier, GL_CONSTANT_ATTENUATION, v);
}
// ��������˥��ϵ��
void PointLight::SetLinearAttenuation(float v)
{
	glLightf(mLightIdentifier, GL_LINEAR_ATTENUATION, v);
}
// ����ƽ����˥��ϵ��
void PointLight::SetQuadricAttenuation(float v)
{
	glLightf(mLightIdentifier, GL_QUADRATIC_ATTENUATION, v);
}