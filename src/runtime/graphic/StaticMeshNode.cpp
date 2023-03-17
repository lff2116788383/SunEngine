#include <glad/glad.h>

#include "StaticMeshNode.h"
#include <glm/glm.hpp>
//#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

#include <windows.h>
#include <iostream>

unsigned int GetTextureFromFile(const aiScene* scene, const char* path, const std::string& directory, bool gamma = false);

StaticMeshNode::StaticMeshNode(const char* file, bool gamma) :
	gammaCorrection(gamma), m_flie(file)
{
	loadFile(file);

	m_FinalBoneMatrices.reserve(100);

	for (int i = 0; i < 100; i++)
		m_FinalBoneMatrices.push_back(glm::mat4(1.0f));
}
StaticMeshNode::~StaticMeshNode()
{
}

//加载模型
void StaticMeshNode::loadFile(std::string path) {

	//char workpath[1024] = { 0 };
	//GetModuleFileNameA(NULL, workpath, MAX_PATH);		// 获取到完整路径，如：E:\Tools\qq.exe
	//*strrchr(workpath, '\\') = '\0';					// 截取路径，如：E:\Tools
	//*strrchr(workpath, '\\') = '\0';
	//*strrchr(workpath, '\\') = '\0';
	//char fullPath[1024] = { 0 };
	//sprintf(fullPath, "%s/%s", workpath,file.c_str());
	//std::cout << "work path: " << workpath << " fullPath: " << fullPath << std::endl;

	//std::string path = fullPath;

	//导入成scene对象
	
	g_pScene = importer.ReadFile(path, aiProcess_Triangulate | aiProcess_FlipUVs | aiProcess_CalcTangentSpace);

	//检测是否成功
	if (!g_pScene || g_pScene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !g_pScene->mRootNode) {
		std::cout << "Assimp load failed error info:" << importer.GetErrorString() << std::endl;
		return;
	}

	directory = path.substr(0, path.find_last_of('/'));
	m_numMeshes = g_pScene->mNumMeshes;
	processNode(g_pScene->mRootNode, g_pScene);
}

//处理节点
void StaticMeshNode::processNode(aiNode* node, const aiScene* scene) {
	//处理节点的所有网格信息
	for (int i = 0; i < node->mNumMeshes; ++i) {
		aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];
		meshes.push_back(processMesh(mesh, scene));
	}
	//对所有的子节点做相同处理
	for (int i = 0; i < node->mNumChildren; ++i) {
		processNode(node->mChildren[i], scene);
	}
}

//处理网格
MeshNode StaticMeshNode::processMesh(aiMesh* mesh, const aiScene* scene) {
	std::vector<SEVertex> vertices;
	std::vector<unsigned int> indices;
	std::vector<SETexture> textures;

	for (int i = 0; i < mesh->mNumVertices; ++i) {

		SEVertex vertex;
		SetVertexBoneDataToDefault(vertex);
		//处理顶点，法线和纹理坐标
		glm::vec3 vector;
		vector.x = mesh->mVertices[i].x;
		vector.y = mesh->mVertices[i].y;
		vector.z = mesh->mVertices[i].z;
		vertex.Position = vector;

		vector.x = mesh->mNormals[i].x;
		vector.y = mesh->mNormals[i].y;
		vector.z = mesh->mNormals[i].z;
		vertex.Normal = vector;

		if (mesh->mTextureCoords[0]) {	//看看是否有纹理信息
			glm::vec2 vec;
			vec.x = mesh->mTextureCoords[0][i].x;
			vec.y = mesh->mTextureCoords[0][i].y;
			vertex.TexCoords = vec;
		}
		else
			vertex.TexCoords = glm::vec2(0.0f, 0.0f);

		////切线
		//vector.x = mesh->mTangents[i].x;
		//vector.y = mesh->mTangents[i].y;
		//vector.z = mesh->mTangents[i].z;
		//vertex.Tangent = vector;

		////二重切线
		//vector.x = mesh->mBitangents[i].x;
		//vector.y = mesh->mBitangents[i].y;
		//vector.z = mesh->mBitangents[i].z;
		//vertex.Bitangent = vector;

		vertices.push_back(vertex);
	}

	//处理索引
	for (int i = 0; i < mesh->mNumFaces; ++i) {
		aiFace face = mesh->mFaces[i];
		for (int j = 0; j < face.mNumIndices; ++j)
			indices.push_back(face.mIndices[j]);
	}

	//处理材质
	if (mesh->mMaterialIndex >= 0) {
		aiMaterial* material = scene->mMaterials[mesh->mMaterialIndex];
		std::vector<SETexture> diffuseMaps = loadMaterialtextures(scene,material,
			aiTextureType_DIFFUSE, "texture_diffuse");
		textures.insert(textures.end(), diffuseMaps.begin(), diffuseMaps.end());
		std::vector<SETexture> specularMaps = loadMaterialtextures(scene,material,
			aiTextureType_SPECULAR, "texture_specular");
		textures.insert(textures.end(), specularMaps.begin(), specularMaps.end());
	}

	ExtractBoneWeightForVertices(vertices, mesh, scene);

	return MeshNode(vertices, indices, textures);
}

std::vector<SETexture> StaticMeshNode::loadMaterialtextures(const aiScene* scene,aiMaterial* mat, aiTextureType type, std::string typeName) {
	std::vector<SETexture> textures;
	for (int i = 0; i < mat->GetTextureCount(type); ++i) {
		aiString str;
		mat->GetTexture(type, i, &str);

		bool skip = false;
		for (int j = 0; j < textures_loaded.size(); ++j) {
			if (std::strcmp(textures_loaded[j].path.c_str(), str.C_Str()) == 0) {
				textures.push_back(textures_loaded[j]);
				skip = true;
				break;
			}
		}

		if (!skip) {
			SETexture texture;
			texture.id = GetTextureFromFile(scene,str.C_Str(), directory);
			texture.type = typeName;
			texture.path = str.C_Str();
			textures.push_back(texture);
			textures_loaded.push_back(texture);
		}
	}

	return textures;
}

unsigned int GetTextureFromFile(const aiScene* scene,const char* path, const std::string& directory, bool gamma) {
	std::string filename = path;
	filename = directory + '/' + filename;
	std::cout << "texture path: " << path << " texture filename: " << filename << std::endl;
	unsigned int textureID;
	glGenTextures(1, &textureID);

	int width, height, nrComponents;
	unsigned char* data;

	if (path[0] == '*')
	{
		int textureIdx = atoi(&path[1]);
		data = static_cast<unsigned char*>(
			stbi_load_from_memory((stbi_uc*)(scene->mTextures[textureIdx]->pcData),
				scene->mTextures[textureIdx]->mWidth,
				&width,
				&height,
				&nrComponents,
				0));
	}
	else
	{


		data = stbi_load(filename.c_str(), &width, &height, &nrComponents, 0);

	}
	if (data) {

		//初始化纹理
		GLenum format;
		if (nrComponents == 1)
			format = GL_RED;
		else if (nrComponents == 3)
			format = GL_RGB;
		else if (nrComponents == 4)
			format = GL_RGBA;

		glBindTexture(GL_TEXTURE_2D, textureID);
		glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		stbi_image_free(data);
	}
	else {
		std::cout << "load texture failed path:" << path << std::endl;
		stbi_image_free(data);
	}

	return textureID;

}


void StaticMeshNode::SetShader(const GLchar* vertexPath, const GLchar* fragmentPath)
{
	m_pShader = new Shader(vertexPath, fragmentPath);
}

void StaticMeshNode::Draw()
{

}


void StaticMeshNode::ExtractBoneWeightForVertices(std::vector<SEVertex>& vertices, aiMesh* mesh, const aiScene* scene)
{
	auto& boneInfoMap = m_BoneInfoMap;
	int& boneCount = m_BoneCounter;

	for (int boneIndex = 0; boneIndex < mesh->mNumBones; ++boneIndex)
	{
		int boneID = -1;
		std::string boneName = mesh->mBones[boneIndex]->mName.C_Str();
		if (boneInfoMap.find(boneName) == boneInfoMap.end())
		{
			BoneInfo newBoneInfo;
			newBoneInfo.id = boneCount;
			newBoneInfo.offset = aiToGLMFormat(mesh->mBones[boneIndex]->mOffsetMatrix);
			boneInfoMap[boneName] = newBoneInfo;
			boneID = boneCount;
			boneCount++;
		}
		else
		{
			boneID = boneInfoMap[boneName].id;
		}
		assert(boneID != -1);
		auto weights = mesh->mBones[boneIndex]->mWeights;
		int numWeights = mesh->mBones[boneIndex]->mNumWeights;

		for (int weightIndex = 0; weightIndex < numWeights; ++weightIndex)
		{
			int vertexId = weights[weightIndex].mVertexId;
			float weight = weights[weightIndex].mWeight;
			assert(vertexId <= vertices.size());
			SetVertexBoneData(vertices[vertexId], boneID, weight);
		}
	}
}

void StaticMeshNode::SetVertexBoneData(SEVertex& vertex, int boneID, float weight)
{
	for (int i = 0; i < MAX_BONE_INFLUENCE; ++i)
	{
		if (vertex.m_BoneIDs[i] < 0)
		{
			vertex.m_Weights[i] = weight;
			vertex.m_BoneIDs[i] = boneID;
			break;
		}
	}
}


void StaticMeshNode::SetVertexBoneDataToDefault(SEVertex& vertex)
{
	for (int i = 0; i < MAX_BONE_INFLUENCE; i++)
	{
		vertex.m_BoneIDs[i] = -1;
		vertex.m_Weights[i] = 0.0f;
	}
}

glm::mat4 aiToGLMFormat(const aiMatrix4x4& from)
{
	glm::mat4 to;
	//the a,b,c,d in assimp is the row ; the 1,2,3,4 is the column
	to[0][0] = from.a1; to[1][0] = from.a2; to[2][0] = from.a3; to[3][0] = from.a4;
	to[0][1] = from.b1; to[1][1] = from.b2; to[2][1] = from.b3; to[3][1] = from.b4;
	to[0][2] = from.c1; to[1][2] = from.c2; to[2][2] = from.c3; to[3][2] = from.c4;
	to[0][3] = from.d1; to[1][3] = from.d2; to[2][3] = from.d3; to[3][3] = from.d4;
	return to;
}