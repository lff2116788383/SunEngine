#pragma once
/*骨架网格体除了静态网格体的顶点和纹理数据还包括骨骼数据用来播放动画*/
#include "StaticMeshNode.h"

//static constexpr uint32_t MAX_BONES = 4;

DirectX::XMMATRIX aiToXMMATRIX(aiMatrix4x4 in);

class SkeletonMeshNode:public StaticMeshNode
{
public:
	SkeletonMeshNode(const char* path, bool gamma = false);
	~SkeletonMeshNode();

	void LoadBoneData();		//预加载骨骼信息
private:
	std::unordered_map<std::string, uint32_t> m_boneMap;
	std::vector<SEBoneInfo> m_boneInfo;
	uint32_t m_numBones = 0;

public:
	void UpdateAnimation(float time, uint32_t animIdx);/*更新动画以后就得到了所有骨骼的最终矩阵*/
	void UpdateNodeHierarchy(float time, const aiScene* pScene , const aiNode* pNode, const aiAnimation* pAnimation, const DirectX::XMMATRIX& parentTansformMatrix);

	void UpdateNodeHierarchy(float time, const aiScene* pScene, const aiNode* pNode, const aiAnimation* pAnimation, glm::mat4 parentTansformMatrix);

	
};

