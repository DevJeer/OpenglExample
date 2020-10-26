#include "model.h"
#include "utils.h"

Model::Model()
{

}

void Model::Init(const char *modelPath)
{
	// ���屣�涥�����ݵĽṹ��
	struct FloatData {
		float v[3];
	};

	int nFileSize = 0;
	unsigned char *fileContent = LoadFileContent(modelPath, nFileSize);
	if (fileContent == nullptr)
		return;
	// ����λ�� �������� ����
	std::vector<FloatData> positions, texcoords, normals;

	// �����ص��ļ���������
	std::stringstream ssFileContent((char*)fileContent);
	std::string temp;
	char szOneLine[256];
	while (!ssFileContent.eof())
	{
		memset(szOneLine, 0, 256);
		ssFileContent.getline(szOneLine, 256);
		// ����ȡ�����ַ������� > 0�ż���
		if (strlen(szOneLine) > 0)
		{
			// ���ض�����Ϣ	v
			// ��������		vt
			// ��������		vn	
			if (szOneLine[0] == 'v') {
				// ����һ��������
				std::stringstream ssOneLine(szOneLine);
				if (szOneLine[1] == 't') {
					ssOneLine >> temp;
					// ��ȡ�����������Ϣ
					FloatData floatData;
					ssOneLine >> floatData.v[0];
					ssOneLine >> floatData.v[1];
					texcoords.push_back(floatData);
					printf("texcoord : %f, %f\n", floatData.v[0], floatData.v[1]);
				}
				else if (szOneLine[1] == 'n') {
					ssOneLine >> temp;
					// ��ȡ���ߵ���Ϣ
					FloatData floatData;
					ssOneLine >> floatData.v[0];
					ssOneLine >> floatData.v[1];
					ssOneLine >> floatData.v[2];
					printf("normal : %f, %f, %f\n", floatData.v[0], floatData.v[1], floatData.v[2]);
				}
				else {
					ssOneLine >> temp;
					// ��ȡλ����Ϣ
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