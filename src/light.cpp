#include "light.h"

Light::Light()
{

}
// 设置环境光
void Light::SetAmbientColor(float r, float g, float b, float a)
{
	float ambientColor[] = { r, g, b, a };
	glLightfv(mLightIdentifier, GL_AMBIENT, ambientColor);
}
// 设置漫反射
void Light::SetDiffuseColor(float r, float g, float b, float a)
{
	float diffuseColor[] = { r, g, b, a };
	glLightfv(mLightIdentifier, GL_DIFFUSE, diffuseColor);
}
// 设置镜面高光
void Light::SetSpecularColor(float r, float g, float b, float a)
{
	float specularColor[] = { r, g, b, a };
	glLightfv(mLightIdentifier, GL_SPECULAR, specularColor);
}
// 开启灯光
void Light::Enable()
{
	// 开启光照
	glEnable(GL_LIGHTING);
	// 开启指定的一盏灯
	glEnable(mLightIdentifier);
}


DirectionLight::DirectionLight(GLenum light)
{
	mLightIdentifier = light;
}
// 设置直射光的位置
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
// 设置常数衰减系数
void PointLight::SetConstAttenuation(float v)
{
	glLightf(mLightIdentifier, GL_CONSTANT_ATTENUATION, v);
}
// 设置线性衰减系数
void PointLight::SetLinearAttenuation(float v)
{
	glLightf(mLightIdentifier, GL_LINEAR_ATTENUATION, v);
}
// 设置平方项衰减系数
void PointLight::SetQuadricAttenuation(float v)
{
	glLightf(mLightIdentifier, GL_QUADRATIC_ATTENUATION, v);
}