#include "sprite.h"
#include "utils.h"
// 创建纹理
void Sprite2D::SetImage(const char *imagePath)
{
	//mTexture = CreateTexture2DFromBMP(imagePath);
	// 加载PNG格式的图片
	mTexture = CreateTexture2DFromPNG(imagePath);
}
// 设置纹理的大小
void Sprite2D::SetRect(float x, float y, float width, float height)
{
	// 第一个点
	mVertexes[0].x = x;
	mVertexes[0].y = y;
	// 第二个点
	mVertexes[1].x = x + width;
	mVertexes[1].y = y;
	// 第三个点
	mVertexes[2].x = x + width;
	mVertexes[2].y = y + height;
	// 第四个点
	mVertexes[3].x = x;
	mVertexes[3].y = y + height;
}

void Sprite2D::Draw()
{
	// PNG有Alpha通道的图片无法正常显示， 需要开启Alpha测试
	glEnable(GL_ALPHA_TEST);
	glAlphaFunc(GL_GREATER, 0.0f); // 使用它会有锯齿状的边框

	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, mTexture);
	glDisable(GL_LIGHTING);
	glColor4ub(255, 255, 255, 255);
	glBegin(GL_QUADS);
	// 第一个点
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(mVertexes[0].x, mVertexes[0].y, mVertexes[0].z);
	// 第二个点
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(mVertexes[1].x, mVertexes[1].y, mVertexes[1].z);
	// 第三个点
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(mVertexes[2].x, mVertexes[2].y, mVertexes[2].z);
	// 第四个点
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(mVertexes[3].x, mVertexes[3].y, mVertexes[3].z);
	glEnd();
}