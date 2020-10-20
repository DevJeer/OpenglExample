#pragma once
#include "ggl.h"

// 加载图片内容
unsigned char* LoadFileContent(const char* path, int& filesize);

// 解码BMP格式的文件
unsigned char* DecodeBMP(unsigned char* bmpFileData, int& width, int& height);

// 创建2D纹理
GLuint CreateTexture2D(unsigned char* pixelData, int width, int height, GLenum type);