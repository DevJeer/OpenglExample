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
	// �����������Ľṹ��
	struct VertexDefine {
		int posIndex;
		int texcoordIndex;
		int normalIndex;
	};

	int nFileSize = 0;
	unsigned char *fileContent = LoadFileContent(modelPath, nFileSize);
	if (fileContent == nullptr)
		return;
	// ����λ�� �������� ����
	std::vector<FloatData> positions, texcoords, normals;
	// �����������Ҫ����Ϣ
	std::vector<VertexDefine> vertexes;
	std::vector<int> indexes;

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
				// ����һ��������
				std::stringstream ssOneLine(szOneLine);
				ssOneLine >> temp;
				std::string vertexStr;
				// ��ȡÿ�е�����  �����������Σ�ÿ�ж�����������
				for (int i = 0; i < 3; i++)
				{
					// ���ݸ�ʽ�� 1/1/1 2/2/2 3/3/3
					ssOneLine >> vertexStr;
					size_t pos = vertexStr.find_first_of('/');
					std::string posIndexStr = vertexStr.substr(0, pos);
					// ��ȡ�����������Ϣ
					size_t pos2 = vertexStr.find_first_of('/', pos + 1);
					std::string texcoordIndexStr = vertexStr.substr(pos + 1, pos2 - 1 - pos);
					// ��ȡ���ߵ���Ϣ
					std::string normalIndexStr = vertexStr.substr(pos2 + 1, vertexStr.length() - 1 - pos2);
					// ת��Ϊint����
					VertexDefine vd;
					vd.posIndex = atoi(posIndexStr.c_str());
					vd.texcoordIndex = atoi(texcoordIndexStr.c_str());
					vd.normalIndex = atoi(normalIndexStr.c_str());


					int nCurrentVertexIndex = -1;
					int nCurrentVertexCount = (int)vertexes.size();
					// �����Ƿ����ظ��ĵ�
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
					// ����ͬ�Ļ�������������
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
	delete fileContent;
}