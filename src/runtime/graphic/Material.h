#pragma once
/*每个模型都有默认材质 材质都有默认纹理(以白色居多)
材质就是各种贴图和物体对光的交互性质的集合
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
