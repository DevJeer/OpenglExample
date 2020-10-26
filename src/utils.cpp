#include "utils.h"

// 解码BMP格式的文件
unsigned char* DecodeBMP(unsigned char* bmpFileData, int& width, int& height)
{
	// 判断图片是否是位图
	if (0x4D42 == *((unsigned short*)bmpFileData))
	{
		int pixelDataOffset = *((int*)(bmpFileData + 10));
		width = *((int*)(bmpFileData + 18));
		height = *((int*)(bmpFileData + 22));
		unsigned char* pixelData = bmpFileData + pixelDataOffset;
		for (int i = 0; i < width * height * 3; i += 3)
		{
			// BGR ---> RGB
			unsigned char temp = pixelData[i];
			pixelData[i] = pixelData[i + 2];
			pixelData[i + 2] = temp;
		}
		return pixelData;
	}
	return nullptr;
}

// 创建2D纹理
GLuint CreateTexture2D(unsigned char* pixelData, int width, int height, GLenum type)
{
	GLuint texture;
	// 在gpu中申请一片内存空间
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);
	// 设置纹理过大/过小的处理方式
	/*glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);*/
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	// 设置uv坐标的方式（图片过大/过小）
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
	/*glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);*/
	// 写到gpu中
	glTexImage2D(GL_TEXTURE_2D, 0, type, width, height, 0, type, GL_UNSIGNED_BYTE, pixelData);
	glBindTexture(GL_TEXTURE_2D, 0);
	return texture;
}

// 从BMP文件中创建2D纹理
GLuint CreateTexture2DFromBMP(const char *bmpPath)
{
	// 读取BMP文件的内容
	int nFileSize = 0;
	unsigned char *bmpFileContent = LoadFileContent(bmpPath, nFileSize);
	if (bmpFileContent == nullptr)
		return 0;
	// 解码bmp内容
	int bmpWidth = 0, bmpHeight = 0;
	unsigned char *pixelData = DecodeBMP(bmpFileContent, bmpWidth, bmpHeight);
	if (bmpWidth == 0)
	{
		delete bmpFileContent;
		return 0;
	}
	GLuint texture = CreateTexture2D(pixelData, bmpWidth, bmpHeight, GL_RGB);
	delete bmpFileContent;
	return texture;
}

// 创建显式列表
GLuint CreateDisplayList(std::function<void()> foo)
{
	GLuint displayList = glGenLists(1);
	glNewList(displayList, GL_COMPILE);
	foo();
	glEndList();
	return displayList;
}