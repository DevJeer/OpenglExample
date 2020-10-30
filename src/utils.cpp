#include "utils.h"
#include "../external/soil.h"
// ����BMP��ʽ���ļ�
unsigned char* DecodeBMP(unsigned char* bmpFileData, int& width, int& height)
{
	// �ж�ͼƬ�Ƿ���λͼ
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

// ����2D����
GLuint CreateTexture2D(unsigned char* pixelData, int width, int height, GLenum type)
{
	GLuint texture;
	// ��gpu������һƬ�ڴ�ռ�
	glGenTextures(1, &texture);
	// ���ó�Ϊ��ǰ���������
	glBindTexture(GL_TEXTURE_2D, texture);
	// �����������/��С�Ĵ���ʽ
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	/*glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);*/
	// ��������uv����ķ�ʽ��ͼƬ����/��С��
	/*glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);*/
	// �����պ�ƴ���кڱߵ����
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	/*glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);*/
	// д��gpu��
	glTexImage2D(GL_TEXTURE_2D, 0, type, width, height, 0, type, GL_UNSIGNED_BYTE, pixelData);
	// ������֮�������󶨵�1��λ��
	glBindTexture(GL_TEXTURE_2D, 0);
	return texture;
}

// ��BMP�ļ��д���2D����
GLuint CreateTexture2DFromBMP(const char *bmpPath)
{
	// ��ȡBMP�ļ�������
	int nFileSize = 0;
	unsigned char *bmpFileContent = LoadFileContent(bmpPath, nFileSize);
	if (bmpFileContent == nullptr)
		return 0;
	// ����bmp����
	int bmpWidth = 0, bmpHeight = 0;
	unsigned char *pixelData = DecodeBMP(bmpFileContent, bmpWidth, bmpHeight);
	if (bmpWidth == 0)
	{
		delete bmpFileContent;
		return 0;
	}
	// �����������
	GLuint texture = CreateTexture2D(pixelData, bmpWidth, bmpHeight, GL_RGB);
	delete bmpFileContent;
	return texture;
}

// ������ʽ�б�
GLuint CreateDisplayList(std::function<void()> foo)
{
	GLuint displayList = glGenLists(1);
	glNewList(displayList, GL_COMPILE);
	foo();
	glEndList();
	return displayList;
}

// ��PNG�м�����Դ
GLuint CreateTexture2DFromPNG(const char *imageFilePath, bool invertY)
{
	int nFileSize = 0;
	unsigned char *filecontent = LoadFileContent(imageFilePath, nFileSize);
	if (filecontent == nullptr)
		return 0;
	// ���������־λ  �������ƶ�ȡͼƬ�ĳ���λ2�Ĵ��ݵ�ͼƬ
	unsigned int flags = SOIL_FLAG_POWER_OF_TWO;
	// �Ƿ�תY�ᣬ������PNG�㷨�й�
	if (invertY)
	{
		flags |= SOIL_FLAG_INVERT_Y;
	}
	// ����PNG��Դ
	GLuint texture = SOIL_load_OGL_texture_from_memory(filecontent, nFileSize, 0, 0, flags);
	return texture;
}
// ������������ �����ɳ����Լ����ɵģ�
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
	// ����2D����Ķ���
	GLuint texture = CreateTexture2D(imageData, size, size, GL_RGBA);
	delete imageData;
	return texture;
}