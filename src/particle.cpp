#include "particle.h"
#include "utils.h"

Particle::Particle()
{
	mLifeTime = -1.0f;
}

// ��������
void Particle::Draw()
{
	// ����Alphaͨ��
	glEnable(GL_BLEND);
	//glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE);
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
// ��ʼ������
void Particle::Init(GLubyte r, GLubyte g, GLubyte b, GLubyte a, float time)
{
	mLivingTime = 0;
	mLifeTime = time;
	mColor[0] = r;
	mColor[1] = g;
	mColor[2] = b;
	mColor[3] = a;
}
// �������ӵ�λ��
void Particle::Update(float deltaTime)
{
	if (mLivingTime > mLifeTime)
		return;
	mLivingTime += deltaTime;
	float maxRadius = 300.0f;
	float rotateSpeed = 120.0f;
	float currentAngle = rotateSpeed * mLivingTime;
	// ���㵱ǰ�İ뾶
	float currentRadius = maxRadius * mLivingTime / mLifeTime;
	// ʹ�û��ȼ���
	mPosition.x = currentRadius * cosf(currentAngle * 3.14 / 180.0f);
	mPosition.y = currentRadius * sinf(currentAngle * 3.14 / 180.0f);
}