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

	int nFileSize = 0;
	unsigned char *fileContent = LoadFileContent(modelPath, nFileSize);
	if (fileContent == nullptr)
		return;
	// 保存位置 纹理坐标 法线
	std::vector<FloatData> positions, texcoords, normals;

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
					printf("normal : %f, %f, %f\n", floatData.v[0], floatData.v[1], floatData.v[2]);
				}
				else {
					ssOneLine >> temp;
					// 读取位置信息
					FloatData floatData;
					ssOneLine >> floatData.v[0];
					ssOneLine >> floatData.v[1];
					ssOneLine >> floatData.v[2];
					printf("position : %f, %f, %f\n", floatData.v[0], floatData.v[1], floatData.v[2]);
				}
			}// face
			else if (szOneLine[0] == 'f') {
				printf("draw command : %s\n", szOneLine);
			}
		}
	}
	delete fileContent;
}