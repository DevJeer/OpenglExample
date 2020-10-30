#include "utils.h"
#include "../external/soil.h"
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
	// 设置成为当前处理的纹理
	glBindTexture(GL_TEXTURE_2D, texture);
	// 设置纹理过大/过小的处理方式
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	/*glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);*/
	// 设置纹理uv坐标的方式（图片过大/过小）
	/*glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);*/
	// 解决天空盒拼接有黑边的情况
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	/*glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);*/
	// 写到gpu中
	glTexImage2D(GL_TEXTURE_2D, 0, type, width, height, 0, type, GL_UNSIGNED_BYTE, pixelData);
	// 将加载之后的纹理绑定到1号位置
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
	// 创建纹理对象
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

// 从PNG中加载资源
GLuint CreateTexture2DFromPNG(const char *imageFilePath, bool invertY)
{
	int nFileSize = 0;
	unsigned char *filecontent = LoadFileContent(imageFilePath, nFileSize);
	if (filecontent == nullptr)
		return 0;
	// 设置这个标志位  可以限制读取图片的长宽位2的次幂的图片
	unsigned int flags = SOIL_FLAG_POWER_OF_TWO;
	// 是否反转Y轴，与具体的PNG算法有关
	if (invertY)
	{
		flags |= SOIL_FLAG_INVERT_Y;
	}
	// 加载PNG资源
	GLuint texture = SOIL_load_OGL_texture_from_memory(filecontent, nFileSize, 0, 0, flags);
	return texture;
}
// 创建程序纹理 （是由程序自己生成的）
GLuint CreateProcedureTexture(int size)
{
	unsigned char *imageData = new unsigned char[size * size * 4];
	for (int y = 0; y < size; ++y)
	{
		for (int x = 0; x < size; ++x)
		{
			int currentPixelOffset = (x + y * size) * 4;
			imageData[currentPixelOffset] = 255;
			imageData[currentPixelOffset + 1] = 255;
			imageData[currentPixelOffset + 2] = 255;
			imageData[currentPixelOffset + 3] = 255;
		}
	}
	// 创建2D纹理的对象
	GLuint texture = CreateTexture2D(imageData, size, size, GL_RGBA);
	delete imageData;
	return texture;
}