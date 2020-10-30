#include "particle.h"
#include "utils.h"

Particle::Particle()
{

}

// »æÖÆÁ£×Ó
void Particle::Draw()
{
	glDisable(GL_DEPTH_TEST);
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, mTexture);
	glDisable(GL_LIGHTING);
	glColor4ub(255, 255, 255, 255);
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
}