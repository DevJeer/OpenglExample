#include "ground.h"

// ���Ƶ���
void Ground::Draw()
{
	glEnable(GL_LIGHTING);
	// ���ò���
	glMaterialfv(GL_FRONT, GL_AMBIENT, mAmbientMaterial);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, mDiffuseMaterial);
	glMaterialfv(GL_FRONT, GL_SPECULAR, mSpecularMaterial);
	// ��Ϊ������û�в��ʵģ����������ڸ�����Ӧ�ù��յ�ʱ��Ҫ������ɫ׷��
	glEnable(GL_COLOR_MATERIAL);

	glEnable(GL_DEPTH_TEST);
	glDisable(GL_TEXTURE_2D);
	glBegin(GL_QUADS);
	// ���÷���
	glNormal3f(0.0f, 1.0f, 0.0f);

	// ���Ƶ�����㷨
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

void Ground::SetAmbientMaterial(float r, float g, float b, float a)
{
	mAmbientMaterial[0] = r;
	mAmbientMaterial[1] = g;
	mAmbientMaterial[2] = b;
	mAmbientMaterial[3] = a;
}

void Ground::SetDiffuseMaterial(float r, float g, float b, float a)
{
	mDiffuseMaterial[0] = r;
	mDiffuseMaterial[1] = g;
	mDiffuseMaterial[2] = b;
	mDiffuseMaterial[3] = a;
}

void Ground::SetSpecularMaterial(float r, float g, float b, float a)
{
	mSpecularMaterial[0] = r;
	mSpecularMaterial[1] = g;
	mSpecularMaterial[2] = b;
	mSpecularMaterial[3] = a;
}