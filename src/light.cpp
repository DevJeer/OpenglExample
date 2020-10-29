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
	/*float pos[] = { x, y, z, 1.0f };
	glLightfv(mLightIdentifier, GL_POSITION, pos);*/
	// �����ӿ�����  ��������Դ֮������λ��
	mPosition[0] = x;
	mPosition[1] = y;
	mPosition[2] = z;
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
// ���¹�Դ��λ��
void PointLight::Update(float x, float y, float z)
{
	// �õ��������ƹ����Ծ���
	float pos[] = { mPosition[0] - x, mPosition[1] - y, mPosition[2] - z, 1.0f };
	glLightfv(mLightIdentifier, GL_POSITION, pos);
}

// ֱ�ӵ��ø���Ĺ��캯��
SpotLight::SpotLight(GLenum light) : PointLight(light)
{

}
// ���þ۹�Ƶĳ���
void SpotLight::SetDirection(float x, float y, float z)
{
	float dir[] = { x, y, z };
	glLightfv(mLightIdentifier, GL_SPOT_DIRECTION, dir);
}
// ���þ۹������һ����Χ���ǲ�˥����
void SpotLight::SetExponent(float v)
{
	glLightf(mLightIdentifier, GL_SPOT_EXPONENT, v);
}
// ���þ۹�Ƶ����䷶Χ
void SpotLight::SetCutOff(float v)
{
	glLightf(mLightIdentifier, GL_SPOT_CUTOFF, v);
}