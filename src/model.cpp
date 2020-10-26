#include "model.h"
#include "utils.h"

Model::Model()
{

}

void Model::Init(const char *modelPath)
{
	int nFileSize = 0;
	unsigned char *fileContent = LoadFileContent(modelPath, nFileSize);
	if (fileContent == nullptr)
		return;
	// 将加载的文件放在流中
	std::stringstream ssFileContent((char*)fileContent);
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
				if (szOneLine[1] == 't') {
					printf("texcoord : %s\n", szOneLine);
				}
				else if (szOneLine[1] == 'n') {
					printf("normal : %s\n", szOneLine);
				}
				else {
					printf("position : %s\n", szOneLine);
				}
			}// face
			else if (szOneLine[0] == 'f') {
				printf("draw command : %s\n", szOneLine);
			}
		}
	}
	delete fileContent;
}