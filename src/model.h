#pragma once
#include "ggl.h"

// Opengl中模型顶点的数据结构
struct VertexData {
	float position[3];
	float normal[3];
	float texcoord[2];
};

class Model {
private:
	// 模型的顶点数据
	VertexData *mVertexes;
	// 模型绘制的索引
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