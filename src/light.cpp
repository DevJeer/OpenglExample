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
	glLightfv(mLightIdentifier, GL_DIFFUSE, specularColor);
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