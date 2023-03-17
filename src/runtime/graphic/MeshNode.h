#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <string>
#include <vector>
#include <learnopengl/shader_m.h>
//#include "math/Math.h" //数学头文件引用有问题暂时放弃使用

#define MAX_BONE_INFLUENCE 4

using Vector2=glm::vec2;
using Vector3 = glm::vec3;
using Vector4 = glm::vec4;

struct SEVertex {
	Vector3 Position;
	Vector3 Normal;		//法线
	Vector2 TexCoords;	//纹理坐标
	//glm::vec3 Tangent;//正切线
	//glm::vec3 Bitangent;//副切线

	// tangent
	Vector3 Tangent;
	// bitangent
	Vector3 Bitangent;
	//bone indexes which will influence this vertex
	int m_BoneIDs[MAX_BONE_INFLUENCE];
	//weights from each bone
	float m_Weights[MAX_BONE_INFLUENCE];

	SEVertex() {}
	SEVertex(const Vector3& p, const Vector3& n, const Vector3& t, const Vector2& uv)
		: Position(p), Normal(n), Tangent(t), TexCoords(uv) {}
	SEVertex(float px, float py, float pz,
		float nx, float ny, float nz,
		float tx, float ty, float tz,
		float u, float v)
		: Position(px, py, pz), Normal(nx, ny, nz), Tangent(tx, ty, tz), TexCoords(u, v) {}
};

struct SETexture {
	unsigned int id;
	std::string type;
	std::string path;
};


#include <DirectXMath.h>
#define MAX_BONES 4


glm::mat4 XMMATRIXToGLM(DirectX::XMMATRIX in);
struct SEBoneInfo
{
	DirectX::XMMATRIX boneOffset;
	DirectX::XMMATRIX finalTransformation;

	glm::mat4 boneOffsetGLM;
	glm::mat4 finalTransformationGLM;//找到这个的计算方法
};

struct SEBoneData
{
	uint32_t ids[MAX_BONES];
	float weights[MAX_BONES];
	unsigned char idx;

	SEBoneData() :idx(0), ids{ 0,0,0,0 }, weights{ 0.0f,0.0f,0.0f,0.0f } {};

	void insertData(uint32_t id, float weight)
	{
		//assert(idx < MAX_BONES);
		if (idx >= MAX_BONES) return;
		ids[idx] = id;
		weights[idx] = weight;
		idx++;
	};
};


struct BoneInfo
{
	/*id is index in finalBoneMatrices*/
	int id;

	/*offset matrix transforms vertex from model space to bone space*/
	glm::mat4 offset;

};

class MeshNode
{
public:
	MeshNode() {}
	MeshNode(const std::vector<SEVertex>& vertices, const std::vector<unsigned int>& indices, std::vector<SETexture>& textures);
	~MeshNode();

	bool Init();
public:
	std::vector<SEVertex> vertices;
	std::vector<unsigned int> indices;
	std::vector<SETexture> textures;
	std::vector<SEBoneData> boneData;

	unsigned int VAO, VBO, EBO;     //GL渲染环境
};
