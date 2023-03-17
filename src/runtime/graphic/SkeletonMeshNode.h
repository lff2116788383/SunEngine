#pragma once
/*�Ǽ���������˾�̬������Ķ�����������ݻ��������������������Ŷ���*/
#include "StaticMeshNode.h"

//static constexpr uint32_t MAX_BONES = 4;

DirectX::XMMATRIX aiToXMMATRIX(aiMatrix4x4 in);

class SkeletonMeshNode:public StaticMeshNode
{
public:
	SkeletonMeshNode(const char* path, bool gamma = false);
	~SkeletonMeshNode();

	void LoadBoneData();		//Ԥ���ع�����Ϣ
private:
	std::unordered_map<std::string, uint32_t> m_boneMap;
	std::vector<SEBoneInfo> m_boneInfo;
	uint32_t m_numBones = 0;

public:
	void UpdateAnimation(float time, uint32_t animIdx);/*���¶����Ժ�͵õ������й��������վ���*/
	void UpdateNodeHierarchy(float time, const aiScene* pScene , const aiNode* pNode, const aiAnimation* pAnimation, const DirectX::XMMATRIX& parentTansformMatrix);

	void UpdateNodeHierarchy(float time, const aiScene* pScene, const aiNode* pNode, const aiAnimation* pAnimation, glm::mat4 parentTansformMatrix);

	
};

