#include "scene.h"
void Init()
{
	// ���õ�ǰͶӰ�����
	glMatrixMode(GL_PROJECTION);
	gluPerspective(50.0f, 800.0f / 600.0f, 0.1f, 1000.0f);
	// ���õ�ǰģ���ӿھ���
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

void Draw()
{
	
}