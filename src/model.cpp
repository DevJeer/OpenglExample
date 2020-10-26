#include "model.h"
#include "utils.h"

Model::Model()
{

}

void Model::Init(const char *modelPath)
{
	// 定义保存顶点数据的结构体
	struct FloatData {
		float v[3];
	};
	// 定义绘制所需的结构体
	struct VertexDefine {
		int posIndex;
		int texcoordIndex;
		int normalIndex;
	};

	int nFileSize = 0;
	unsigned char *fileContent = LoadFileContent(modelPath, nFileSize);
	if (fileContent == nullptr)
		return;
	// 保存位置 纹理坐标 法线
	std::vector<FloatData> positions, texcoords, normals;
	// 保存绘制所需要的信息
	std::vector<VertexDefine> vertexes;
	std::vector<int> indexes;

	// 将加载的文件放在流中
	std::stringstream ssFileContent((char*)fileContent);
	std::string temp;
	char szOneLine[256];
	while (!ssFileContent.eof())
	{
		memset(szOneLine, 0, 256);
		ssFileContent.getline(szOneLine, 256);
		// 当读取到的字符串长度 > 0才继续
		if (strlen(szOneLine) > 0)
		{
			// 加载顶点信息	v
			// 纹理坐标		vt
			// 法线坐标		vn	
			if (szOneLine[0] == 'v') {
				// 定义一个流对象
				std::stringstream ssOneLine(szOneLine);
				if (szOneLine[1] == 't') {
					ssOneLine >> temp;
					// 读取纹理坐标的信息
					FloatData floatData;
					ssOneLine >> floatData.v[0];
					ssOneLine >> floatData.v[1];
					texcoords.push_back(floatData);
					printf("texcoord : %f, %f\n", floatData.v[0], floatData.v[1]);
				}
				else if (szOneLine[1] == 'n') {
					ssOneLine >> temp;
					// 读取法线的信息
					FloatData floatData;
					ssOneLine >> floatData.v[0];
					ssOneLine >> floatData.v[1];
					ssOneLine >> floatData.v[2];
					normals.push_back(floatData);
					printf("normal : %f, %f, %f\n", floatData.v[0], floatData.v[1], floatData.v[2]);
				}
				else {
					ssOneLine >> temp;
					// 读取位置信息
					FloatData floatData;
					ssOneLine >> floatData.v[0];
					ssOneLine >> floatData.v[1];
					ssOneLine >> floatData.v[2];
					positions.push_back(floatData);
					printf("position : %f, %f, %f\n", floatData.v[0], floatData.v[1], floatData.v[2]);
				}
			}// face
			else if (szOneLine[0] == 'f') {
				// 定义一个流对象
				std::stringstream ssOneLine(szOneLine);
				ssOneLine >> temp;
				std::string vertexStr;
				// 读取每行的数据  假设是三角形，每行都有三个顶点
				for (int i = 0; i < 3; i++)
				{
					// 数据格式是 1/1/1 2/2/2 3/3/3
					ssOneLine >> vertexStr;
					size_t pos = vertexStr.find_first_of('/');
					std::string posIndexStr = vertexStr.substr(0, pos);
					// 读取纹理坐标的信息
					size_t pos2 = vertexStr.find_first_of('/', pos + 1);
					std::string texcoordIndexStr = vertexStr.substr(pos + 1, pos2 - 1 - pos);
					// 读取法线的信息
					std::string normalIndexStr = vertexStr.substr(pos2 + 1, vertexStr.length() - 1 - pos2);
					// 转换为int类型
					VertexDefine vd;
					vd.posIndex = atoi(posIndexStr.c_str());
					vd.texcoordIndex = atoi(texcoordIndexStr.c_str());
					vd.normalIndex = atoi(normalIndexStr.c_str());


					int nCurrentVertexIndex = -1;
					int nCurrentVertexCount = (int)vertexes.size();
					// 查找是否有重复的点
					for (int j = 0; j < nCurrentVertexCount; j++)
					{
						if (vertexes[j].posIndex == vd.posIndex &&
							vertexes[j].texcoordIndex == vd.texcoordIndex &&
							vertexes[j].normalIndex == vd.normalIndex)
						{
							nCurrentVertexIndex = j;
							break;
						}
					}
					// 不相同的话，就添加这个点
					if (nCurrentVertexIndex == -1)
					{
						nCurrentVertexIndex = (int)vertexes.size();
						vertexes.push_back(vd);
					}
					indexes.push_back(nCurrentVertexIndex);
				}
			}
		}
	}

	mIndexCount = (int)indexes.size();
	// 填充索引
	mIndexes = new unsigned short[mIndexCount];
	for (int i = 0; i < mIndexCount; i++)
	{
		mIndexes[i] = indexes[i];
	}
	int vertexCount = (int)vertexes.size();
	mVertexes = new VertexData[vertexCount];
	for (int i = 0; i < vertexCount; ++i)
	{
		// 根据索引来找到顶点 / 纹理 / 法线
		memcpy(mVertexes[i].position, positions[vertexes[i].posIndex - 1].v, sizeof(float) * 3);
		memcpy(mVertexes[i].texcoord, texcoords[vertexes[i].texcoordIndex - 1].v, sizeof(float) * 2);
		memcpy(mVertexes[i].normal, normals[vertexes[i].normalIndex - 1].v, sizeof(float) * 3);
	}

	delete fileContent;
}

// 绘制模型
void Model::Draw()
{
	glPushMatrix();
	glTranslatef(0.0f, 0.0f, -2.0f);
	glBegin(GL_TRIANGLES);
	for (int i = 0; i < mIndexCount; ++i)
	{
		glTexCoord2fv(mVertexes[mIndexes[i]].texcoord);
		glNormal3fv(mVertexes[mIndexes[i]].normal);
		glVertex3fv(mVertexes[mIndexes[i]].position);
	}
	glEnd();
	glPopMatrix();
}