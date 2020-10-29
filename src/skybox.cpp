#include "skybox.h"
#include "utils.h"

// imageDirΪ��պ����ڵ�·��
void SkyBox::Init(const char *imageDir)
{
	char temp[256];
	memset(temp, 0, 256);
	strcpy(temp, imageDir);
	strcat(temp, "front.bmp");
	// ����������Դ�����Ҵ����������
	mTextures[0] = CreateTexture2DFromBMP(temp);

	// back
	memset(temp, 0, 256);
	strcpy(temp, imageDir);
	strcat(temp, "back.bmp");
	// ����������Դ
	mTextures[1] = CreateTexture2DFromBMP(temp);

	// left
	memset(temp, 0, 256);
	strcpy(temp, imageDir);
	strcat(temp, "left.bmp");
	mTextures[2] = CreateTexture2DFromBMP(temp);

	// right
	memset(temp, 0, 256);
	strcpy(temp, imageDir);
	strcat(temp, "right.bmp");
	mTextures[3] = CreateTexture2DFromBMP(temp);

	// top
	memset(temp, 0, 256);
	strcpy(temp, imageDir);
	strcat(temp, "top.bmp");
	mTextures[4] = CreateTexture2DFromBMP(temp);

	// bottom
	memset(temp, 0, 256);
	strcpy(temp, imageDir);
	strcat(temp, "bottom.bmp");
	mTextures[5] = CreateTexture2DFromBMP(temp);

	mFastDrawCall = CreateDisplayList([this]() -> void {
		DrawCommand();
	});
}

// ������պ�
void SkyBox::DrawCommand()
{
	// �ر���Ȳ��ԣ���opengl��Ϊ��պ�������Զ�ĵط�
	glDisable(GL_DEPTH_TEST);
	// ����պв��ܵƹ��Ӱ��
	glDisable(GL_LIGHTING);

	glEnable(GL_TEXTURE_2D);
	// front
	glBindTexture(GL_TEXTURE_2D, mTextures[0]);
	glBegin(GL_QUADS);
	glColor4ub(255, 255, 255, 255);
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(-0.5f, -0.5f, -0.5f);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(0.5f, -0.5f, -0.5f);
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(0.5f, 0.5f, -0.5f);
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(-0.5f, 0.5f, -0.5f);
	glEnd();

	// back
	glBindTexture(GL_TEXTURE_2D, mTextures[1]);
	glBegin(GL_QUADS);
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(0.5f, -0.5f, 0.5f);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(-0.5f, -0.5f, 0.5f);
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(-0.5f, 0.5f, 0.5f);
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(0.5f, 0.5f, 0.5f);
	glEnd();

	// left
	glBindTexture(GL_TEXTURE_2D, mTextures[2]);
	glBegin(GL_QUADS);
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(-0.5f, -0.5f, 0.5f);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(-0.5f, -0.5f, -0.5f);
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(-0.5f, 0.5f, -0.5f);
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(-0.5f, 0.5f, 0.5f);
	glEnd();

	// right
	glBindTexture(GL_TEXTURE_2D, mTextures[3]);
	glBegin(GL_QUADS);
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(0.5f, -0.5f, -0.5f);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(0.5f, -0.5f, 0.5f);
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(0.5f, 0.5f, 0.5f);
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(0.5f, 0.5f, -0.5f);
	glEnd();

	// top
	glBindTexture(GL_TEXTURE_2D, mTextures[4]);
	glBegin(GL_QUADS);
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(-0.5f, 0.5f, -0.5f);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(0.5f, 0.5f, -0.5f);
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(0.5f, 0.5f, 0.5f);
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(-0.5f, 0.5f, 0.5f);
	glEnd();

	// bottom
	glBindTexture(GL_TEXTURE_2D, mTextures[5]);
	glBegin(GL_QUADS);
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(-0.5f, -0.5f, 0.5f);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(0.5f, -0.5f, 0.5f);
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(0.5f, -0.5f, -0.5f);
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(-0.5f, -0.5f, -0.5f);
	glEnd();
}

void SkyBox::Draw(float x, float y, float z)
{
	glPushMatrix();
	glTranslatef(x, y, z);
	glCallList(mFastDrawCall);
	glPopMatrix();
}