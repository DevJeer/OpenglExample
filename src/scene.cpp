#include "scene.h"
#include "utils.h"

GLuint texture;
void Init()
{
	// 设置当前投影矩阵的
	glMatrixMode(GL_PROJECTION);
	gluPerspective(50.0f, 800.0f / 600.0f, 0.1f, 1000.0f);
	// 设置当前模型视口矩阵
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	//int nFileSize = 0;
	//// 加载图片的内容
	//unsigned char* bmpFileContent = LoadFileContent("Res/test.bmp", nFileSize);
	//int bmpWidth = 0, bmpHeight = 0;
	//// 解码BMP
	//unsigned char* pixelData = DecodeBMP(bmpFileContent, bmpWidth, bmpHeight);
	//// 创建纹理对象
	//texture = CreateTexture2D(pixelData, bmpWidth, bmpHeight, GL_RGB);

	// 整合创建纹理的方法
	texture = CreateTexture2DFromBMP("Res/test.bmp");

}

// 绘制物体平面
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
	// 启用光照
	glEnable(GL_LIGHTING);
	// 启用光照0
	glEnable(GL_LIGHT0);
	float lightPos[] = { 0.0f, 1.0f, 0.0f, 0.0f };
	// 光照0是方向光，因为lightPos代表的是一个齐次坐标，齐次坐标实际的位置就是 x / w  y / w  z/ w
	glLightfv(GL_LIGHT0, GL_POSITION, lightPos);
	// 添加环境光，反射系数
	float whiteColor[] = { 1.0f, 1.0f, 1.0f, 1.0f };
	float ambientMat[] = { 0.07f, 0.07f, 0.07f, 1.0f };
	// 漫反射的系数
	float diffuseMat[] = { 0.4f, 0.4f, 0.4f, 1.0f };
	// 镜面反射的系数
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
#pragma region 绘制多个图形

	// 在glBegin 和 glEnd之间的顶点会被绘制
	// 每三个点绘制
	// 默认是以逆时针进行绘制的
	/*glBegin(GL_TRIANGLES);
	glColor4ub(255, 255, 255, 255);
	glVertex3f(-0.2f, -0.2f, -1.5f);

	glColor4ub(255, 0, 0, 255);
	glVertex3f(0.2f, -0.2f, -1.5f);

	glColor4ub(0, 255, 0, 255);
	glVertex3f(0.0f, 0.2f, -1.5f);
	glEnd();*/


	// 通过GL_TRIANGLE_STRIP 来绘制三角形
	/*glBegin(GL_TRIANGLE_STRIP);

	glColor4ub(255, 0, 0, 255);  glVertex3f(-0.5f, -0.25f, -2.5f);
	glColor4ub(0, 0, 255, 255);  glVertex3f(0.5f, -0.25f, -2.5f);
	glColor4ub(0, 255, 0, 255);  glVertex3f(-0.5f, 0.25f, -2.5f);
	glColor4ub(0, 255, 0, 255);  glVertex3f(0.5f, 0.25f, -2.5f);
	glColor4ub(255, 0, 0, 255);  glVertex3f(-0.5f, 0.75f, -2.5f);
	glColor4ub(0, 0, 255, 255);  glVertex3f(0.5f, 0.75f, -2.5f);

	glEnd();*/

	// 通过GL_TRIANGLE_FAN 来绘制三角形
	/*glBegin(GL_TRIANGLE_FAN);

	glColor4ub(255, 0, 0, 255);  glVertex3f(0.0f, -0.25f, -2.5f);
	glColor4ub(0, 0, 255, 255);  glVertex3f(0.5f, -0.25f, -2.5f);
	glColor4ub(0, 255, 0, 255);  glVertex3f(0.4f, 0.0f, -2.5f);
	glColor4ub(0, 255, 0, 255);  glVertex3f(0.2f, 0.15f, -2.5f);
	glColor4ub(0, 0, 255, 255);  glVertex3f(0.0f, 0.2f, -2.5f);

	glEnd();*/

	// 绘制点
	/*glPointSize(10.0f);
	glBegin(GL_POINTS);
	glColor4ub(255, 0, 0, 255);  glVertex3f(-0.5f, -0.25f, -2.5f);
	glColor4ub(0, 0, 255, 255);  glVertex3f(0.5f, -0.25f, -2.5f);
	glColor4ub(0, 255, 0, 255);  glVertex3f(0.0f, 0.5f, -2.5f);
	glEnd();*/

	// 绘制线
	/*glLineWidth(10.0f);
	glBegin(GL_LINES);

	glColor4ub(255, 0, 0, 255);  glVertex3f(-0.5f, -0.25f, -2.5f);
	glColor4ub(0, 0, 255, 255);  glVertex3f(0.5f, -0.25f, -2.5f);
	glColor4ub(0, 0, 255, 255);  glVertex3f(0.5f, -0.25f, -2.5f);
	glColor4ub(0, 255, 0, 255);  glVertex3f(1.0f, 0.5f, -2.5f);

	glEnd();*/

	// 绘制线  GL_LINE_LOOP方式
	/*glLineWidth(1.0f);
	glBegin(GL_LINE_LOOP);
	glColor4ub(255, 0, 0, 255);  glVertex3f(-0.5f, -0.25f, -2.5f);
	glColor4ub(0, 0, 255, 255);  glVertex3f(0.5f, -0.25f, -2.5f);
	glColor4ub(0, 255, 0, 255);  glVertex3f(1.0f, 0.5f, -2.5f);
	glColor4ub(255, 0, 0, 255);  glVertex3f(0.5f, 0.5f, -2.5f);
	glColor4ub(255, 0, 0, 255);  glVertex3f(0.0f, 0.25f, -2.5f);
	glEnd();*/

	// 绘制线
	/*glLineWidth(1.0f);
	glBegin(GL_LINE_STRIP);
	glColor4ub(255, 0, 0, 255);  glVertex3f(-0.5f, -0.25f, -2.5f);
	glColor4ub(0, 0, 255, 255);  glVertex3f(0.5f, -0.25f, -2.5f);
	glColor4ub(0, 255, 0, 255);  glVertex3f(1.0f, 0.5f, -2.5f);
	glColor4ub(255, 0, 0, 255);  glVertex3f(0.5f, 0.5f, -2.5f);
	glColor4ub(255, 0, 0, 255);  glVertex3f(0.0f, 0.25f, -2.5f);
	glEnd();*/


	// QUADS （四边形）
	/*glBegin(GL_QUADS);
	glColor4ub(255, 0, 0, 255);  glVertex3f(-0.5f, -0.25f, -2.5f);
	glColor4ub(0, 0, 255, 255);  glVertex3f(0.5f, -0.25f, -2.5f);
	glColor4ub(0, 255, 0, 255);  glVertex3f(1.0f, 0.5f, -2.5f);
	glColor4ub(255, 0, 0, 255);  glVertex3f(0.5f, 0.5f, -2.5f);
	glEnd();*/

	// GL_QUAD_STRIP (绘制四边形)
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

	// GL_POLYGON(绘制多边形)
	/*glBegin(GL_POLYGON);
	glColor4ub(255, 0, 0, 255);  glVertex3f(-0.5f, -0.25f, -2.5f);
	glColor4ub(0, 0, 255, 255);  glVertex3f(0.5f, -0.25f, -2.5f);
	glColor4ub(0, 255, 0, 255);  glVertex3f(1.0f, 0.5f, -2.5f);
	glColor4ub(255, 0, 0, 255);  glVertex3f(0.5f, 0.5f, -2.5f);
	glColor4ub(0, 255, 0, 255);  glVertex3f(0.0f, 0.25f, -2.5f);
	glEnd();*/

#pragma endregion
	// 移动物体
	// 给当前的矩阵里加载一个单位矩阵
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
	//旋转物体
	//glLoadIdentity();
	//// 绕z轴进行旋转
	//glRotatef(30.0f, 0.0f, 0.0f, 1.0f);
	//glBegin(GL_TRIANGLES);
	//glColor4ub(255, 0, 0, 255);  glVertex3f(-0.5f, -0.25f, -2.5f);
	//glColor4ub(0, 0, 255, 255);  glVertex3f(0.5f, -0.25f, -2.5f);
	//glColor4ub(0, 255, 0, 255);  glVertex3f(0.0f, 0.5f, -2.5f);
	//glEnd();

	// 缩放物体
	//glLoadIdentity();
	//// 绕z轴进行旋转
	//glScalef(0.2f, 0.2f, 0.2f);
	//glBegin(GL_TRIANGLES);
	//glColor4ub(255, 0, 0, 255);  glVertex3f(-0.5f, -0.25f, -5.0f);
	//glColor4ub(0, 0, 255, 255);  glVertex3f(0.5f, -0.25f, -5.0f);
	//glColor4ub(0, 255, 0, 255);  glVertex3f(0.0f, 0.5f, -5.0f);
	//glEnd();

	// 矩阵的压栈和出栈
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

	// 复合运动
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

	// 放置摄像机的位置  这段代码必须在绘制其他物体之前
	//         摄像机的位置   眼睛看的视点（是一个点） 从头顶发出去的方向向量
	//gluLookAt(0.0f, 0.0f, 0.0f, 0.0f, 0.0f, -1.0f, 0.0f, 1.0f, 0.0f);

	//DrawModel();
}

// 测试纹理采样的方法
void glClampTestCode(float sliceNum)
{
	glBegin(GL_QUADS);
	glColor4ub(255, 255, 255, 255);
	// 纹理坐标1  逆时针
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
	//// 纹理坐标1  逆时针
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

void Draw()
{
	// 清除背景颜色
	glClearColor(0.1f, 0.4f, 0.6f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);
	

	
}