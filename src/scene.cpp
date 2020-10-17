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
	// ���������ɫ
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);

#pragma region ���ƶ��ͼ��

	// ��glBegin �� glEnd֮��Ķ���ᱻ����
	// ÿ���������
	// Ĭ��������ʱ����л��Ƶ�
	/*glBegin(GL_TRIANGLES);
	glColor4ub(255, 255, 255, 255);
	glVertex3f(-0.2f, -0.2f, -1.5f);

	glColor4ub(255, 0, 0, 255);
	glVertex3f(0.2f, -0.2f, -1.5f);

	glColor4ub(0, 255, 0, 255);
	glVertex3f(0.0f, 0.2f, -1.5f);
	glEnd();*/


	// ͨ��GL_TRIANGLE_STRIP ������������
	/*glBegin(GL_TRIANGLE_STRIP);

	glColor4ub(255, 0, 0, 255);  glVertex3f(-0.5f, -0.25f, -2.5f);
	glColor4ub(0, 0, 255, 255);  glVertex3f(0.5f, -0.25f, -2.5f);
	glColor4ub(0, 255, 0, 255);  glVertex3f(-0.5f, 0.25f, -2.5f);
	glColor4ub(0, 255, 0, 255);  glVertex3f(0.5f, 0.25f, -2.5f);
	glColor4ub(255, 0, 0, 255);  glVertex3f(-0.5f, 0.75f, -2.5f);
	glColor4ub(0, 0, 255, 255);  glVertex3f(0.5f, 0.75f, -2.5f);

	glEnd();*/

	// ͨ��GL_TRIANGLE_FAN ������������
	/*glBegin(GL_TRIANGLE_FAN);

	glColor4ub(255, 0, 0, 255);  glVertex3f(0.0f, -0.25f, -2.5f);
	glColor4ub(0, 0, 255, 255);  glVertex3f(0.5f, -0.25f, -2.5f);
	glColor4ub(0, 255, 0, 255);  glVertex3f(0.4f, 0.0f, -2.5f);
	glColor4ub(0, 255, 0, 255);  glVertex3f(0.2f, 0.15f, -2.5f);
	glColor4ub(0, 0, 255, 255);  glVertex3f(0.0f, 0.2f, -2.5f);

	glEnd();*/

	// ���Ƶ�
	/*glPointSize(10.0f);
	glBegin(GL_POINTS);
	glColor4ub(255, 0, 0, 255);  glVertex3f(-0.5f, -0.25f, -2.5f);
	glColor4ub(0, 0, 255, 255);  glVertex3f(0.5f, -0.25f, -2.5f);
	glColor4ub(0, 255, 0, 255);  glVertex3f(0.0f, 0.5f, -2.5f);
	glEnd();*/

	// ������
	/*glLineWidth(10.0f);
	glBegin(GL_LINES);

	glColor4ub(255, 0, 0, 255);  glVertex3f(-0.5f, -0.25f, -2.5f);
	glColor4ub(0, 0, 255, 255);  glVertex3f(0.5f, -0.25f, -2.5f);
	glColor4ub(0, 0, 255, 255);  glVertex3f(0.5f, -0.25f, -2.5f);
	glColor4ub(0, 255, 0, 255);  glVertex3f(1.0f, 0.5f, -2.5f);

	glEnd();*/

	// ������  GL_LINE_LOOP��ʽ
	/*glLineWidth(1.0f);
	glBegin(GL_LINE_LOOP);
	glColor4ub(255, 0, 0, 255);  glVertex3f(-0.5f, -0.25f, -2.5f);
	glColor4ub(0, 0, 255, 255);  glVertex3f(0.5f, -0.25f, -2.5f);
	glColor4ub(0, 255, 0, 255);  glVertex3f(1.0f, 0.5f, -2.5f);
	glColor4ub(255, 0, 0, 255);  glVertex3f(0.5f, 0.5f, -2.5f);
	glColor4ub(255, 0, 0, 255);  glVertex3f(0.0f, 0.25f, -2.5f);
	glEnd();*/

	// ������
	/*glLineWidth(1.0f);
	glBegin(GL_LINE_STRIP);
	glColor4ub(255, 0, 0, 255);  glVertex3f(-0.5f, -0.25f, -2.5f);
	glColor4ub(0, 0, 255, 255);  glVertex3f(0.5f, -0.25f, -2.5f);
	glColor4ub(0, 255, 0, 255);  glVertex3f(1.0f, 0.5f, -2.5f);
	glColor4ub(255, 0, 0, 255);  glVertex3f(0.5f, 0.5f, -2.5f);
	glColor4ub(255, 0, 0, 255);  glVertex3f(0.0f, 0.25f, -2.5f);
	glEnd();*/


	// QUADS ���ı��Σ�
	/*glBegin(GL_QUADS);
	glColor4ub(255, 0, 0, 255);  glVertex3f(-0.5f, -0.25f, -2.5f);
	glColor4ub(0, 0, 255, 255);  glVertex3f(0.5f, -0.25f, -2.5f);
	glColor4ub(0, 255, 0, 255);  glVertex3f(1.0f, 0.5f, -2.5f);
	glColor4ub(255, 0, 0, 255);  glVertex3f(0.5f, 0.5f, -2.5f);
	glEnd();*/

	// GL_QUAD_STRIP (�����ı���)
	/*glBegin(GL_QUAD_STRIP);
	glColor4ub(255, 0, 0, 255);  glVertex3f(-0.25f, -0.25f, -2.5f);
	glColor4ub(0, 0, 255, 255);  glVertex3f(0.25f, -0.25f, -2.5f);
	glColor4ub(255, 0, 0, 255);  glVertex3f(-0.25f, 0.25f, -2.5f);
	glColor4ub(0, 255, 0, 255);  glVertex3f(0.25f, 0.25f, -2.5f);
	glColor4ub(0, 255, 0, 255);  glVertex3f(-0.25f, 0.5f, -2.5f);
	glColor4ub(255, 0, 0, 255);  glVertex3f(0.25f, 0.5f, -2.5f);
	glColor4ub(0, 255, 0, 255);  glVertex3f(-0.25f, 0.75f, -2.5f);
	glColor4ub(255, 0, 0, 255);  glVertex3f(0.25f, 0.75f, -2.5f);
	glEnd();*/

	// GL_POLYGON(���ƶ����)
	/*glBegin(GL_POLYGON);
	glColor4ub(255, 0, 0, 255);  glVertex3f(-0.5f, -0.25f, -2.5f);
	glColor4ub(0, 0, 255, 255);  glVertex3f(0.5f, -0.25f, -2.5f);
	glColor4ub(0, 255, 0, 255);  glVertex3f(1.0f, 0.5f, -2.5f);
	glColor4ub(255, 0, 0, 255);  glVertex3f(0.5f, 0.5f, -2.5f);
	glColor4ub(0, 255, 0, 255);  glVertex3f(0.0f, 0.25f, -2.5f);
	glEnd();*/

#pragma endregion
	// �ƶ�����
	// ����ǰ�ľ��������һ����λ����
	/*glLoadIdentity();
	glTranslatef(0.0f, 0.0f, -2.5f);
	glBegin(GL_TRIANGLES);
	glColor4ub(255, 0, 0, 255);  glVertex3f(-0.5f, -0.25f, 0.0f);
	glColor4ub(0, 0, 255, 255);  glVertex3f(0.5f, -0.25f, 0.0f);
	glColor4ub(0, 255, 0, 255);  glVertex3f(0.0f, 0.5f, 0.0f);
	glEnd();*/

	//��ת����
	glLoadIdentity();
	// ��z�������ת
	glRotatef(30.0f, 0.0f, 0.0f, 1.0f);
	glBegin(GL_TRIANGLES);
	glColor4ub(255, 0, 0, 255);  glVertex3f(-0.5f, -0.25f, -2.5f);
	glColor4ub(0, 0, 255, 255);  glVertex3f(0.5f, -0.25f, -2.5f);
	glColor4ub(0, 255, 0, 255);  glVertex3f(0.0f, 0.5f, -2.5f);
	glEnd();
}