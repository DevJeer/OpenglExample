#pragma once
#include "ggl.h"

// ����ͼƬ����
unsigned char* LoadFileContent(const char* path, int& filesize);

// ����BMP��ʽ���ļ�
unsigned char* DecodeBMP(unsigned char* bmpFileData, int& width, int& height);

// ����2D����
GLuint CreateTexture2D(unsigned char* pixelData, int width, int height, GLenum type);