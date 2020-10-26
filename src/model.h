#pragma once
#include "ggl.h"

// Opengl��ģ�Ͷ�������ݽṹ
struct VertexData {
	float position[3];
	float normal[3];
	float texcoord[2];
};

class Model {
private:
	// ģ�͵Ķ�������
	VertexData *mVertexes;
	// ģ�ͻ��Ƶ�����
	unsigned short *mIndexes;
	int mIndexCount;

public:
	GLuint mTexture;

	Model();
	void Init(const char *modelPath);

	void Draw();
};