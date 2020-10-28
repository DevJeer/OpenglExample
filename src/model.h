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

	float mAmbientMaterial[4], mDiffuseMaterial[4], mSpecularMaterial[4];

public:
	GLuint mTexture;

	Model();
	void Init(const char *modelPath);

	void Draw();

	void SetAmbientMaterial(float r, float g, float b, float a);
	void SetDiffuseMaterial(float r, float g, float b, float a);
	void SetSpecularMaterial(float r, float g, float b, float a);
};