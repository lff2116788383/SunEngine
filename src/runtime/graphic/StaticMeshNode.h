#pragma once
#include "entt/entt.hpp"
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include <vector>
#include <string>

#include "MeshNode.h"

glm::mat4 aiToGLMFormat(const aiMatrix4x4& from);
class StaticMeshNode
{
public:
	StaticMeshNode(const char* path, bool gamma = false);
	void Draw();
	~StaticMeshNode();

	void SetShader(const GLchar* vertexPath, const GLchar* fragmentPath);

	std::vector<MeshNode> meshes;
	uint32_t m_numMeshes;

	std::string directory;
	std::vector<SETexture> textures_loaded;
	bool gammaCorrection;

	void loadFile(std::string path);
	void processNode(aiNode* node, const aiScene* scene);
	MeshNode processMesh(aiMesh* mesh, const aiScene* scene);
	std::vector<SETexture> loadMaterialtextures(const aiScene* scene, aiMaterial* mat, aiTextureType type, std::string typeName);

	void ExtractBoneWeightForVertices(std::vector<SEVertex>& vertices, aiMesh* mesh, const aiScene* scene);

	void SetVertexBoneData(SEVertex& vertex, int boneID, float weight);

	void SetVertexBoneDataToDefault(SEVertex& vertex);

	Shader* m_pShader = nullptr;

	operator entt::entity() { return m_pChild; }
	operator entt::entity() const { return m_pChild; }

	const char* m_flie = nullptr;


	std::map<std::string, BoneInfo> m_BoneInfoMap;
	int m_BoneCounter = 0;
	std::vector<glm::mat4> m_FinalBoneMatrices;
	std::vector<glm::mat4> GetFinalBoneMatrices()
	{
		return m_FinalBoneMatrices;
	}
protected:
	entt::entity m_pChild;

	const aiScene* g_pScene;
	Assimp::Importer importer;
	
};

