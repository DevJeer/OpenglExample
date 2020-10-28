#include "scene.h"
#include "utils.h"
#include "skybox.h"
#include "model.h"
#include "ground.h"
#include "light.h"

GLuint texture;
SkyBox skybox;
Model model;
Ground ground;
DirectionLight light(GL_LIGHT0);
void Init()
{
	// ���õ�ǰͶӰ�����
	glMatrixMode(GL_PROJECTION);
	gluPerspective(50.0f, 800.0f / 600.0f, 0.1f, 1000.0f);
	// ���õ�ǰģ���ӿھ���
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	// ��ʼ����պ�
	skybox.Init("Res/");
	// ��ʼ��ģ��
	//model.Init("Res/Quad.obj");
	model.Init("Res/Sphere.obj");
	// ����������Դ
	model.mTexture = CreateTexture2DFromBMP("Res/earth.bmp");

	light.SetAmbientColor(0.1f, 0.1f, 0.1f, 1.0f);
	light.SetDiffuseColor(0.8f, 0.8f, 0.8f, 1.0f);
	light.SetSpecularColor(1.0f, 1.0f, 1.0f, 1.0f);
	light.SetPosition(0.0f, 1.0f, 0.0f);
	// ����ģ�͵Ĳ���
	model.SetAmbientMaterial(0.1f, 0.1f, 0.1f, 1.0f);
	model.SetDiffuseMaterial(0.4f, 0.4f, 0.4f, 1.0f);
	model.SetSpecularMaterial(1.0f, 1.0f, 1.0f, 1.0f);

	//int nFileSize = 0;
	//// ����ͼƬ������
	//unsigned char* bmpFileContent = LoadFileContent("Res/test.bmp", nFileSize);
	//int bmpWidth = 0, bmpHeight = 0;
	//// ����BMP
	//unsigned char* pixelData = DecodeBMP(bmpFileContent, bmpWidth, bmpHeight);
	//// �����������
	//texture = CreateTexture2D(pixelData, bmpWidth, bmpHeight, GL_RGB);

	// ���ϴ�������ķ���
	//texture = CreateTexture2DFromBMP("Res/test.bmp");

}

// ��������ƽ��
void DrawModel()
{
	glBegin(GL_QUADS);
	glColor4ub(255, 255, 255, 255);
	glVertex3f(-0.5f, -0.2f, -0.5f);
	glVertex3f(0.5f, -0.2f, -0.5f);
	glVertex3f(0.5f, -0.2f, -1.0f);
	glVertex3f(-0.5f, -0.2f, -1.0f);
	glEnd();
}

void EnableLight()
{
	// ���ù���
	glEnable(GL_LIGHTING);
	// ���ù���0
	glEnable(GL_LIGHT0);
	float lightPos[] = { 0.0f, 1.0f, 0.0f, 0.0f };
	// ����0�Ƿ���⣬��ΪlightPos�������һ��������꣬�������ʵ�ʵ�λ�þ��� x / w  y / w  z/ w
	glLightfv(GL_LIGHT0, GL_POSITION, lightPos);
	// ��ӻ����⣬����ϵ��
	float whiteColor[] = { 1.0f, 1.0f, 1.0f, 1.0f };
	float ambientMat[] = { 0.07f, 0.07f, 0.07f, 1.0f };
	// �������ϵ��
	float diffuseMat[] = { 0.4f, 0.4f, 0.4f, 1.0f };
	// ���淴���ϵ��
	float specularMat[] = { 0.9f, 0.9f, 0.9f, 1.0f };
	glLightfv(GL_LIGHT0, GL_AMBIENT, whiteColor);
	glMaterialfv(GL_LIGHT0, GL_AMBIENT, ambientMat);

	glLightfv(GL_LIGHT0, GL_DIFFUSE, whiteColor);
	glMaterialfv(GL_LIGHT0, GL_DIFFUSE, diffuseMat);

	glLightfv(GL_LIGHT0, GL_SPECULAR, whiteColor);
	glMaterialfv(GL_LIGHT0, GL_SPECULAR, specularMat);
}

void PoloygonTest()
{
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
}

void MoveTest()
{
	//��ת����
	//glLoadIdentity();
	//// ��z�������ת
	//glRotatef(30.0f, 0.0f, 0.0f, 1.0f);
	//glBegin(GL_TRIANGLES);
	//glColor4ub(255, 0, 0, 255);  glVertex3f(-0.5f, -0.25f, -2.5f);
	//glColor4ub(0, 0, 255, 255);  glVertex3f(0.5f, -0.25f, -2.5f);
	//glColor4ub(0, 255, 0, 255);  glVertex3f(0.0f, 0.5f, -2.5f);
	//glEnd();

	// ��������
	//glLoadIdentity();
	//// ��z�������ת
	//glScalef(0.2f, 0.2f, 0.2f);
	//glBegin(GL_TRIANGLES);
	//glColor4ub(255, 0, 0, 255);  glVertex3f(-0.5f, -0.25f, -5.0f);
	//glColor4ub(0, 0, 255, 255);  glVertex3f(0.5f, -0.25f, -5.0f);
	//glColor4ub(0, 255, 0, 255);  glVertex3f(0.0f, 0.5f, -5.0f);
	//glEnd();

	// �����ѹջ�ͳ�ջ
	/*glLoadIdentity();
	glPushMatrix();
		glTranslatef(-1.0f, 0.0f, 0.0f);
		glBegin(GL_TRIANGLES);
		glColor4ub(255, 0, 0, 255);  glVertex3f(-0.5f, -0.25f, -5.0f);
		glColor4ub(0, 0, 255, 255);  glVertex3f(0.5f, -0.25f, -5.0f);
		glColor4ub(0, 255, 0, 255);  glVertex3f(0.0f, 0.5f, -5.0f);
		glEnd();
	glPopMatrix();
	glPushMatrix();
		glTranslatef(1.0f, 0.0f, 0.0f);
		glBegin(GL_TRIANGLES);
		glColor4ub(255, 0, 0, 255);  glVertex3f(-0.5f, -0.25f, -5.0f);
		glColor4ub(0, 0, 255, 255);  glVertex3f(0.5f, -0.25f, -5.0f);
		glColor4ub(0, 255, 0, 255);  glVertex3f(0.0f, 0.5f, -5.0f);
		glEnd();
	glPopMatrix();*/

	// �����˶�
	/*glLoadIdentity();
	glPushMatrix();
	glTranslatef(0.0f, 0.0f, -5.0f);
		glPushMatrix();
		glRotatef(30.0f, 0.0f, 1.0f, 0.0f);
		glBegin(GL_TRIANGLES);
		glColor4ub(255, 0, 0, 255);  glVertex3f(-0.5f, -0.25f, 0.0f);
		glColor4ub(0, 0, 255, 255);  glVertex3f(0.5f, -0.25f, 0.0f);
		glColor4ub(0, 255, 0, 255);  glVertex3f(0.0f, 0.5f, 0.0f);
		glEnd();
		glPopMatrix();
	glPopMatrix();
	glPushMatrix();
	glRotatef(30.0f, 0.0f, 1.0f, 0.0f);
		glPushMatrix();
		glTranslatef(0.0f, 0.0f, -5.0f);
		glBegin(GL_TRIANGLES);
		glColor4ub(255, 0, 0, 255);  glVertex3f(-0.5f, -0.25f, 0.0f);
		glColor4ub(0, 0, 255, 255);  glVertex3f(0.5f, -0.25f, 0.0f);
		glColor4ub(0, 255, 0, 255);  glVertex3f(0.0f, 0.5f, 0.0f);
		glEnd();
		glPopMatrix();
	glPopMatrix();*/

	// �����������λ��  ��δ�������ڻ�����������֮ǰ
	//         �������λ��   �۾������ӵ㣨��һ���㣩 ��ͷ������ȥ�ķ�������
	//gluLookAt(0.0f, 0.0f, 0.0f, 0.0f, 0.0f, -1.0f, 0.0f, 1.0f, 0.0f);

	//DrawModel();
}

// ������������ķ���
void glClampTestCode(float sliceNum)
{
	glBegin(GL_QUADS);
	glColor4ub(255, 255, 255, 255);
	// ��������1  ��ʱ��
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(-0.1f, -0.1f, -0.4f);

	glTexCoord2f(sliceNum, 0.0f);
	glVertex3f(0.1f, -0.1f, -0.4f);

	glTexCoord2f(sliceNum, sliceNum);
	glVertex3f(0.1f, 0.1f, -0.4f);

	glTexCoord2f(0.0f, sliceNum);
	glVertex3f(-0.1f, 0.1f, -0.4f);
	glEnd();
}

void TextureTest()
{
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, texture);
	//glBegin(GL_QUADS);
	//glColor4ub(255, 255, 255, 255);
	//// ��������1  ��ʱ��
	//glTexCoord2f(0.0f, 0.0f);
	//glVertex3f(-0.1f, -0.1f, -0.4f);

	//glTexCoord2f(1.0f, 0.0f);
	//glVertex3f(0.1f, -0.1f, -0.4f);

	//glTexCoord2f(1.0f, 1.0f);
	//glVertex3f(0.1f, 0.1f, -0.4f);

	//glTexCoord2f(0.0f, 1.0f);
	//glVertex3f(-0.1f, 0.1f, -0.4f);
	//glEnd();

	glClampTestCode(1.0f);
}

void SkyBoxTest()
{
	// ������Ȳ���
	glEnable(GL_DEPTH_TEST);

	glBegin(GL_QUADS);
	/*glColor4ub(200, 50, 0, 255);
	glVertex3f(-0.1f, -0.1f, -0.4f);
	glVertex3f(0.1f, -0.1f, -0.4f);
	glVertex3f(0.1f, 0.1f, -0.4f);
	glVertex3f(-0.1f, 0.1f, -0.4f);*/

	glColor4ub(0, 50, 200, 255);
	glVertex3f(-0.1f, -0.1f, -0.6f);
	glVertex3f(0.1f, -0.1f, -0.6f);
	glVertex3f(0.1f, 0.1f, -0.6f);
	glVertex3f(-0.1f, 0.1f, -0.6f);
	glEnd();
}

void Draw()
{
	// ���������ɫ
	glClearColor(0.1f, 0.4f, 0.6f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	light.Enable();
	// ������պ�
	skybox.Draw();
	// ����ģ��
	model.Draw();
	// ���Ƶ���
	ground.Draw();

}