#pragma once
/*ÿ��ģ�Ͷ���Ĭ�ϲ��� ���ʶ���Ĭ������(�԰�ɫ�Ӷ�)
���ʾ��Ǹ�����ͼ������Թ�Ľ������ʵļ���
*/
#include "Texture2D.h"
#include <vector>
class Material
{
public:
	Material();
	~Material();

private:
	std::vector<Texture2D>m_Textures;
};
