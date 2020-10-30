#pragma once
#include "ggl.h"

// 加载图片内容
unsigned char* LoadFileContent(const char* path, int& filesize);

// 解码BMP格式的文件
unsigned char* DecodeBMP(unsigned char* bmpFileData, int& width, int& height);

// 创建2D纹理
GLuint CreateTexture2D(unsigned char* pixelData, int width, int height, GLenum type);

// 从BMP文件中创建2D纹理
GLuint CreateTexture2DFromBMP(const char *bmpPath);

// 创建显式列表
GLuint CreateDisplayList(std::function<void()> foo);

float GetFrameTime();
// 根据PNG图片创建纹理对象
GLuint CreateTexture2DFromPNG(const char *imageFilePath, bool invertY = true);

GLuint CreateProcedureTexture(int size);