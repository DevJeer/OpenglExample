#include "ground.h"

// 绘制地面
void Ground::Draw()
{
	glEnable(GL_DEPTH_TEST);
	glDisable(GL_TEXTURE_2D);
	glBegin(GL_QUADS);
	// 设置法线
	glNormal3f(0.0f, 1.0f, 0.0f);

	// 绘制地面的算法
	for (int z = 0; z < 40; ++z)
	{
		float zStart = 100.0f - z * 5.0f;
		for (int x = 0; x < 40; ++x)
		{
			float xStart = x * 5.0f - 100.0f;
			if ((z % 2) ^ (x % 2))
			{
				glColor4ub(41, 41, 41, 255);
			}
			else
			{
				glColor4ub(200, 200, 200, 255);
			}
			glVertex3f(xStart, -1.0f, zStart);
			glVertex3f(xStart + 5.0f, -1.0f, zStart);
			glVertex3f(xStart + 5.0f, -1.0f, zStart - 5.0f);
			glVertex3f(xStart, -1.0f, zStart - 5.0f);
		}
	}

	glEnd();
}