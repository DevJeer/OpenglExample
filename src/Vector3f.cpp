#include "Vector3f.h"

Vector3f::Vector3f(float x, float y, float z)
{
	this->x = x;
	this->y = y;
	this->z = z;
}

// 向量之间的加法
Vector3f Vector3f::operator+(Vector3f &r)
{
	return Vector3f(x + r.x, y + r.y, z + r.z);
}

// 向量之间的减法
Vector3f Vector3f::operator-(Vector3f &r)
{
	return Vector3f(x - r.x, y - r.y, z - r.z);
}

// 向量 *  数
Vector3f Vector3f::operator*(float scaler)
{
	return Vector3f(x * scaler, y * scaler, z * scaler);
}

// 向量 * 向量
float Vector3f::operator*(Vector3f &r)
{
	return x * r.x + y * r.y + z * r.z;
}

// 向量赋值
void Vector3f::operator=(const Vector3f &r)
{
	x = r.x;
	y = r.y;
	z = r.z;
}

// 归一化
void Vector3f::Normalize()
{
	float len = Magnitude();
	x /= len;
	y /= len;
	z /= len;
}

// 向量的长度
float Vector3f::Magnitude()
{
	return sqrtf(x * x + y * y + z * z);
}

// 叉乘
Vector3f Cross(Vector3f v1, Vector3f v2)
{
	return Vector3f(v1.y * v2.z - v1.z * v2.y,
					v1.z * v2.x - v1.x * v2.z,
					v1.x * v2.y - v1.y * v2.x);
}