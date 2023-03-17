#include "MeshNode.h"
#include "SunEngine.h"

MeshNode::MeshNode(const std::vector<SEVertex>& vertices, const std::vector<unsigned int>& indices, std::vector<SETexture>& textures) {
	(this->vertices).insert((this->vertices).end(), vertices.begin(), vertices.end());
	(this->indices).insert((this->indices).end(), indices.begin(), indices.end());
	(this->textures).insert((this->textures).end(), textures.begin(), textures.end());

	Init();
}

MeshNode::~MeshNode()
{
}

bool MeshNode::Init()
{
	//使用渲染API初始化顶点索引等数据
	SunEngine::GetInstance()->m_pRenderer->InitMesh(this);
	return false;
}

glm::mat4 XMMATRIXToGLM(DirectX::XMMATRIX in)
{
	/*return  glm::mat4(
		in.r[1].m128_f32[1], in.r[1].m128_f32[2], in.r[1].m128_f32[3], in.r[1].m128_f32[4],
		in.r[2].m128_f32[1], in.r[2].m128_f32[2], in.r[2].m128_f32[3], in.r[2].m128_f32[4],
		in.r[3].m128_f32[1], in.r[3].m128_f32[2], in.r[3].m128_f32[3], in.r[3].m128_f32[4],
		in.r[4].m128_f32[1], in.r[4].m128_f32[2], in.r[4].m128_f32[3], in.r[4].m128_f32[4]);*/

	return  glm::mat4(
		in.r[1].m128_f32[1], in.r[2].m128_f32[1], in.r[3].m128_f32[1], in.r[4].m128_f32[1],
		in.r[1].m128_f32[2], in.r[2].m128_f32[2], in.r[3].m128_f32[2], in.r[4].m128_f32[2],
		in.r[1].m128_f32[3], in.r[2].m128_f32[3], in.r[3].m128_f32[3], in.r[4].m128_f32[3],
		in.r[1].m128_f32[4], in.r[2].m128_f32[4], in.r[3].m128_f32[4], in.r[4].m128_f32[4]);
}