#include "particle.h"
#include "utils.h"

Particle::Particle()
{

}

// 绘制粒子
void Particle::Draw()
{
	// 开启Alpha通道
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glDisable(GL_DEPTH_TEST);
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, mTexture);
	glDisable(GL_LIGHTING);
	glColor4ubv(mColor);
	glBegin(GL_QUADS);
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(mPosition.x - mHalfSize, mPosition.y - mHalfSize, 0);

	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(mPosition.x + mHalfSize, mPosition.y - mHalfSize, 0);

	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(mPosition.x + mHalfSize, mPosition.y + mHalfSize, 0);

	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(mPosition.x - mHalfSize, mPosition.y + mHalfSize, 0);
	glEnd();
	glDisable(GL_BLEND);
}
// 初始化粒子
void Particle::Init(GLubyte r, GLubyte g, GLubyte b, GLubyte a, float time)
{
	mLivingTime = 0;
	mLifeTime = time;
	mColor[0] = r;
	mColor[1] = g;
	mColor[2] = b;
	mColor[3] = a;
}