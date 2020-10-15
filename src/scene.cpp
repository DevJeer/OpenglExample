#include "scene.h"
void Init()
{
	// 设置当前投影矩阵的
	glMatrixMode(GL_PROJECTION);
	gluPerspective(50.0f, 800.0f / 600.0f, 0.1f, 1000.0f);
	// 设置当前模型视口矩阵
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

void Draw()
{
	
}