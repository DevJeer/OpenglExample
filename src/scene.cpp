#include "scene.h"
#include "utils.h"
#include "skybox.h"
#include "model.h"
#include "ground.h"
#include "light.h"
#include "camera.h"
#include "sprite.h"
#include "particle.h"

GLuint texture;
SkyBox skybox;
Model model;
Ground ground;
DirectionLight light(GL_LIGHT0);
PointLight light1(GL_LIGHT1), light2(GL_LIGHT2);
SpotLight light3(GL_LIGHT3);
Camera camera;
Sprite2D sprite;
// 粒子
GLuint particleTexture;
Particle particle[1000];

void Init()
{
	glEnable(GL_VERSION);
	GLenum error = glGetError();
	if (error != GL_NO_ERROR)
	{
		printf("error happened : 0x%x\n", error);
	}


	// 打印Opengl的信息
	printf("OpenGL Version : %s\n", glGetString(GL_VERSION));
	printf("Vendor Version : %s\n", glGetString(GL_VENDOR));
	printf("Renderer : %s\n", glGetString(GL_RENDERER));

	// 设置当前投影矩阵的
	glMatrixMode(GL_PROJECTION);
	gluPerspective(50.0f, 800.0f / 600.0f, 0.1f, 1000.0f);
	// 设置当前模型视口矩阵
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	// 初始化天空盒
	skybox.Init("Res/");
	// 初始化模型
	//model.Init("Res/Quad.obj");
	model.Init("Res/Sphere.obj");
	// 加载纹理资源
	model.mTexture = CreateTexture2DFromBMP("Res/earth.bmp");

	light.SetAmbientColor(0.1f, 0.1f, 0.1f, 1.0f);
	light.SetDiffuseColor(0.8f, 0.8f, 0.8f, 1.0f);
	light.SetSpecularColor(1.0f, 1.0f, 1.0f, 1.0f);
	light.SetPosition(0.0f, 1.0f, 0.0f);

	// 设置点光源
	light1.SetAmbientColor(0.1f, 0.1f, 0.1f, 1.0f);
	light1.SetDiffuseColor(0.8f, 0.8f, 0.8f, 1.0f);
	light1.SetSpecularColor(1.0f, 1.0f, 1.0f, 1.0f);
	light1.SetPosition(0.0f, 0.0f, 0.0f);
	light1.SetConstAttenuation(1.0f);
	light1.SetLinearAttenuation(0.2f);

	// 设置第二个点光源
	light2.SetAmbientColor(0.1f, 0.1f, 0.1f, 1.0f);
	light2.SetDiffuseColor(0.1f, 0.4f, 0.6f, 1.0f);
	light2.SetSpecularColor(1.0f, 1.0f, 1.0f, 1.0f);
	light2.SetPosition(0.0f, 0.0f, -10.0f);
	light2.SetConstAttenuation(1.0f);
	light2.SetLinearAttenuation(0.2f);

	// 设置聚光灯
	light3.SetAmbientColor(0.1f, 0.1f, 0.1f, 1.0f);
	light3.SetDiffuseColor(0.0f, 0.8f, 0.0f, 1.0f);
	light3.SetSpecularColor(1.0f, 0.0f, 0.0f, 1.0f);
	light3.SetPosition(5.0f, 30.0f, -10.0f);
	light3.SetDirection(0.0f, -1.0f, 0.0f);
	light3.SetExponent(5.0f);
	light3.SetCutOff(5.0f);

	// 设置模型的材质
	model.SetAmbientMaterial(0.1f, 0.1f, 0.1f, 1.0f);
	model.SetDiffuseMaterial(0.4f, 0.4f, 0.4f, 1.0f);
	model.SetSpecularMaterial(1.0f, 1.0f, 1.0f, 1.0f);

	// 设置地面的材质
	ground.SetAmbientMaterial(0.1f, 0.1f, 0.1f, 1.0f);
	ground.SetDiffuseMaterial(0.4f, 0.4f, 0.4f, 1.0f);
	ground.SetSpecularMaterial(0.0f, 0.0f, 0.0f, 1.0f);

	// 设置camera的宽高
	camera.mViewportWidth = 800.0f;
	camera.mViewportHeight = 600.0f;

	// 给2D精灵赋值
	sprite.SetImage("Res/head.png");
	sprite.SetRect(0.0f, 0.0f, 100.0f, 100.0f);

	// 初始化粒子
	particleTexture = CreateProcedureTexture(128);
	//particle.mHalfSize = 50.0f;
	//particle.mTexture = particleTexture;
	//particle.Init(220, 150, 50, 255, 15.0f);
	//int nFileSize = 0;
	//// 加载图片的内容
	//unsigned char* bmpFileContent = LoadFileContent("Res/test.bmp", nFileSize);
	//int bmpWidth = 0, bmpHeight = 0;
	//// 解码BMP
	//unsigned char* pixelData = DecodeBMP(bmpFileContent, bmpWidth, bmpHeight);
	//// 创建纹理对象
	//texture = CreateTexture2D(pixelData, bmpWidth, bmpHeight, GL_RGB);

	// 整合创建纹理的方法
	//texture = CreateTexture2DFromBMP("Res/test.bmp");

}
// 发射粒子
void EmitParticle(float delta)
{
	static float currentSleepTime = 0.0f;
	static float nextParticleTime = 0.016f;
	static int particleCount = 1;
	if (particleCount == 1000)
		return;
	// 发射粒子
	currentSleepTime += delta;
	if (currentSleepTime >= nextParticleTime)
	{
		// 发射
		currentSleepTime = 0.0f;
	}
	else
		return;
	particle[particleCount - 1].mHalfSize = 50.0f;
	particle[particleCount - 1].mTexture = particleTexture;
	particle[particleCount - 1].Init(220, 150, 50, 255, 10.0f);
	particleCount++;
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

void SkyBoxTest()
{
	// 启用深度测试
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
	// 清除背景颜色
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	// 先绘制3D的场景
	camera.SwitchTo3D();
	// 在绘制每一帧的时候，都先要设置摄像机的位置
	float frameTime = GetFrameTime();
	camera.Update(frameTime);

	//light.Enable();
	// 启用点光源
	light1.Enable();
	light1.Update(camera.mPos.x, camera.mPos.y, camera.mPos.z);
	light2.Enable();
	light2.Update(camera.mPos.x, camera.mPos.y, camera.mPos.z);
	// 启用聚光灯
	light3.Enable();
	light3.Update(camera.mPos.x, camera.mPos.y, camera.mPos.z);
	// 绘制天空盒
	skybox.Draw(camera.mPos.x, camera.mPos.y, camera.mPos.z);
	// 绘制模型
	//model.Draw();
	// 绘制地面
	ground.Draw();


	// 再绘制2D的东西
	camera.SwitchTo2D();
	// 绘制2D纹理
	sprite.Draw();
	// 在绘制粒子之前更新位置
	//particle.Update(frameTime);
	// 绘制粒子
	//particle.Draw();
	EmitParticle(frameTime);
	for (int i = 0; i < 1000; ++i)
	{
		if (particle[i].mLifeTime != -1.0f)
		{
			particle[i].Update(frameTime);
			particle[i].Draw();
		}
		else
			return;
	}

}

// 键盘键按下的事件
void OnKeyDown(char code)
{
	switch (code)
	{
	case 'A':
		camera.mbMoveLeft = true;
		break;
	case 'D':
		camera.mbMoveRight = true;
		break;
	case 'W':
		camera.mbMoveForward = true;
		break;
	case 'S':
		camera.mbMoveBack = true;
		break;
	}
}
// 键盘键抬起的事件
void OnKeyUp(char code)
{
	switch (code)
	{
	case 'A':
		camera.mbMoveLeft = false;
		break;
	case 'D':
		camera.mbMoveRight = false;
		break;
	case 'W':
		camera.mbMoveForward = false;
		break;
	case 'S':
		camera.mbMoveBack = false;
		break;
	}
}
// 鼠标移动时候的事件
void OnMouseMove(float deltaX, float deltaY)
{
	float angleRotatedByUp = deltaX / 1000.0f;
	float angleRotatedByRight = deltaY / 1000.0f;
	camera.Yaw(-angleRotatedByUp);
	camera.Pitch(-angleRotatedByRight);
}