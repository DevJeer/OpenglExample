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
	glLightfv(mLightIdentifier, GL_DIFFUSE, specularColor);
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