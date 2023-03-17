#include "GeometryNode.h"
//#include "MathHelper.h"

void GeometryNode::CreateBox(float width, float height, float depth)
{
	SEVertex v[24];

	float w2 = 0.5f * width;
	float h2 = 0.5f * height;
	float d2 = 0.5f * depth;

	v[0] = SEVertex(-w2, -h2, -d2, 0.0f, 0.0f, -1.0f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f);
	v[1] = SEVertex(-w2, +h2, -d2, 0.0f, 0.0f, -1.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f);
	v[2] = SEVertex(+w2, +h2, -d2, 0.0f, 0.0f, -1.0f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f);
	v[3] = SEVertex(+w2, -h2, -d2, 0.0f, 0.0f, -1.0f, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f);

	v[4] = SEVertex(-w2, -h2, +d2, 0.0f, 0.0f, 1.0f, -1.0f, 0.0f, 0.0f, 1.0f, 1.0f);
	v[5] = SEVertex(+w2, -h2, +d2, 0.0f, 0.0f, 1.0f, -1.0f, 0.0f, 0.0f, 0.0f, 1.0f);
	v[6] = SEVertex(+w2, +h2, +d2, 0.0f, 0.0f, 1.0f, -1.0f, 0.0f, 0.0f, 0.0f, 0.0f);
	v[7] = SEVertex(-w2, +h2, +d2, 0.0f, 0.0f, 1.0f, -1.0f, 0.0f, 0.0f, 1.0f, 0.0f);

	v[8] = SEVertex(-w2, +h2, -d2, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f);
	v[9] = SEVertex(-w2, +h2, +d2, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f);
	v[10] = SEVertex(+w2, +h2, +d2, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f);
	v[11] = SEVertex(+w2, +h2, -d2, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f);

	v[12] = SEVertex(-w2, -h2, -d2, 0.0f, -1.0f, 0.0f, -1.0f, 0.0f, 0.0f, 1.0f, 1.0f);
	v[13] = SEVertex(+w2, -h2, -d2, 0.0f, -1.0f, 0.0f, -1.0f, 0.0f, 0.0f, 0.0f, 1.0f);
	v[14] = SEVertex(+w2, -h2, +d2, 0.0f, -1.0f, 0.0f, -1.0f, 0.0f, 0.0f, 0.0f, 0.0f);
	v[15] = SEVertex(-w2, -h2, +d2, 0.0f, -1.0f, 0.0f, -1.0f, 0.0f, 0.0f, 1.0f, 0.0f);

	v[16] = SEVertex(-w2, -h2, +d2, -1.0f, 0.0f, 0.0f, 0.0f, 0.0f, -1.0f, 0.0f, 1.0f);
	v[17] = SEVertex(-w2, +h2, +d2, -1.0f, 0.0f, 0.0f, 0.0f, 0.0f, -1.0f, 0.0f, 0.0f);
	v[18] = SEVertex(-w2, +h2, -d2, -1.0f, 0.0f, 0.0f, 0.0f, 0.0f, -1.0f, 1.0f, 0.0f);
	v[19] = SEVertex(-w2, -h2, -d2, -1.0f, 0.0f, 0.0f, 0.0f, 0.0f, -1.0f, 1.0f, 1.0f);

	v[20] = SEVertex(+w2, -h2, -d2, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f);
	v[21] = SEVertex(+w2, +h2, -d2, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f);
	v[22] = SEVertex(+w2, +h2, +d2, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 0.0f);
	v[23] = SEVertex(+w2, -h2, +d2, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f);

	mesh.vertices.assign(&v[0], &v[24]);

	UINT i[36];
	i[0] = 0; i[1] = 1; i[2] = 2;
	i[3] = 0; i[4] = 2; i[5] = 3;

	i[6] = 4; i[7] = 5; i[8] = 6;
	i[9] = 4; i[10] = 6; i[11] = 7;

	i[12] = 8; i[13] = 9; i[14] = 10;
	i[15] = 8; i[16] = 10; i[17] = 11;

	i[18] = 12; i[19] = 13; i[20] = 14;
	i[21] = 12; i[22] = 14; i[23] = 15;

	i[24] = 16; i[25] = 17; i[26] = 18;
	i[27] = 16; i[28] = 18; i[29] = 19;

	i[30] = 20; i[31] = 21; i[32] = 22;
	i[33] = 20; i[34] = 22; i[35] = 23;

	mesh.indices.assign(&i[0], &i[36]);

	mesh.Init();
}

void GeometryNode::CreateGrid(float width, float depth, UINT m, UINT n, MeshNode& meshData) 
{
	UINT vertexCount = m * n;	// 顶点数量
	UINT faceCount = (m - 1)*(n - 1) * 2;	// 三角数量

	float halfWidth = 0.5f*width;
	float halfDepth = 0.5f*depth;

	// 计算一格的宽高
	float dx = width / (n - 1);
	float dz = depth / (m - 1);

	float du = 1.0f / (n - 1);
	float dv = 1.0f / (m - 1);

	// 创建顶点
	meshData.vertices.resize(vertexCount);
	for (UINT i = 0; i < m; ++i)
	{
		float z = halfDepth - i * dz;
		for (UINT j = 0; j < n; ++j)
		{
			float x = -halfWidth + j * dx;
			meshData.vertices[i * n + j].Position = Vector3(x, 0.0f, z);	// 顶点的位置
			meshData.vertices[i * n + j].Normal = Vector3(0.0f, 1.0f, 0.0f);
			meshData.vertices[i * n + j].Tangent = Vector3(1.0f, 0.0f, 0.0f);

			// 当前点与00点的xy距离
			meshData.vertices[i*n + j].TexCoords.x = j * du;
			meshData.vertices[i*n + j].TexCoords.y = i * dv;
		}
	}

	// 创建索引
	meshData.indices.resize(faceCount * 3);
	UINT k = 0;
	for (UINT i = 0; i < m - 1; ++i)
	{
		for (UINT j = 0; j < n - 1; ++j) 
		{
			// 一个Quad
			meshData.indices[k] = i * n + j;
			meshData.indices[k + 1] = i * n + j + 1;
			meshData.indices[k + 2] = (i + 1) * n + j;

			meshData.indices[k + 3] = (i + 1) * n + j;
			meshData.indices[k + 4] = i * n + j + 1;
			meshData.indices[k + 5] = (i + 1) * n + j + 1;

			k += 6;
		}
	}
	mesh.Init();
}

void GeometryNode::CreateCylinder(float bottomRadius, float topRadius, float height, UINT sliceCount, UINT stackCount, MeshNode& meshData)
{
	meshData.vertices.clear();
	meshData.indices.clear();

	// 圆柱壁的部分是由多个环组成（环是首尾相连的成圆形的线），两个环组成一个stack，组成stack的方片称为slice
	float stackHeight = height / stackCount;	// 一个stack的高度
	float radiusStep = (topRadius - bottomRadius) / stackCount;	// stack的上下半径差

	UINT ringCount = stackCount + 1;	// 环的数量

	// 计算所有的顶点
	//for (UINT i = 0; i < ringCount; i++)
	//{
	//	float y = -0.5f * height + i * stackHeight;	// 环的高度
	//	float r = bottomRadius + i * radiusStep;	// 环的半径

	//	float dTheta = 2.0f * XM_PI / sliceCount;	// 一个slice的角度（整环为2pi）
	//	for (UINT j = 0; j <= sliceCount; j++)
	//	{
	//		SEVertex vertex;

	//		float c = cosf(j*dTheta);
	//		float s = sinf(j*dTheta);
	//		vertex.Position = Vector3(r*c, y, r*s);	// 根据角度计算x和z坐标

	//		vertex.TexCoords.x = (float)j / sliceCount;	// 纹理坐标
	//		vertex.TexCoords.y = 1.0f - (float)i / stackCount;

	//		vertex.Tangent = Vector3(-s, 0.0f, c);
	//		float dr = bottomRadius - topRadius;
	//		Vector3 bitangent(dr*c, -height, dr*s);

	//		// 根据切线和副切线计算法线
	//		XMVECTOR T = XMLoadFloat3(&vertex.Tangent);
	//		XMVECTOR B = XMLoadFloat3(&bitangent);
	//		XMVECTOR N = XMVector3Normalize(XMVector3Cross(T, B));

	//		XMStoreFloat3(&vertex.Normal, N);
	//		meshData.vertices.push_back(vertex);
	//	}
	//}

	//// 添加索引信息
	//UINT ringSEVertexCount = sliceCount + 1;
	//for (UINT i = 0; i < stackCount; i++)
	//{
	//	for (UINT j = 0; j < sliceCount; j++)
	//	{
	//		meshData.indices.push_back(i*ringSEVertexCount + j);
	//		meshData.indices.push_back((i+1)*ringSEVertexCount + j);
	//		meshData.indices.push_back((i+1)*ringSEVertexCount + j+1);

	//		meshData.indices.push_back(i*ringSEVertexCount + j);
	//		meshData.indices.push_back((i+1)*ringSEVertexCount + j+1);
	//		meshData.indices.push_back(i*ringSEVertexCount + j+1);
	//	}
	//}

	//BuildCylinderTopCap(bottomRadius, topRadius, height, sliceCount, stackCount, meshData);
	//BuildCylinderBottomCap(bottomRadius, topRadius, height, sliceCount, stackCount, meshData);
}

void GeometryNode::BuildCylinderTopCap(float bottomRadius, float topRadius, float height, UINT sliceCount, UINT stackCount, MeshNode& meshData)
{
	// 起始index
	//UINT baseIndex = (UINT)meshData.vertices.size();
	//
	//float y = 0.5f*height;
	//float dTheta = 2.0f*XM_PI / sliceCount;

	//// 添加圆的周边点
	//for (UINT i = 0; i <= sliceCount; i++)
	//{
	//	float x = topRadius * cosf(i*dTheta);
	//	float z = topRadius * sinf(i*dTheta);

	//	float u = x / height + 0.5f;
	//	float v = z / height + 0.5f;

	//	meshData.vertices.push_back(SEVertex(x, y, z, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f, 0.0f, u, v));
	//}

	//// 添加圆的中点
	//meshData.vertices.push_back(SEVertex(0.0f, y, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.5f, 0.5f));

	//UINT centerIndex = (UINT)meshData.vertices.size() - 1;
	//for (UINT i = 0; i < sliceCount; ++i)
	//{
	//	meshData.indices.push_back(centerIndex);
	//	meshData.indices.push_back(baseIndex + i + 1);
	//	meshData.indices.push_back(baseIndex + i);
	//}
}

void GeometryNode::BuildCylinderBottomCap(float bottomRadius, float topRadius, float height, UINT sliceCount, UINT stackCount, MeshNode& meshData)
{
	// 原理和top相同
	UINT baseIndex = (UINT)meshData.vertices.size();
	float y = -0.5f*height;

	float dTheta = 2.0f*glm::pi<float>() / sliceCount;
	for (UINT i = 0; i <= sliceCount; i++)
	{
		float x = bottomRadius * cosf(i*dTheta);
		float z = bottomRadius * sinf(i*dTheta);

		float u = x / height + 0.5f;
		float v = z / height + 0.5f;

		meshData.vertices.push_back(SEVertex(x, y, z, 0.0f, -1.0f, 0.0f, 1.0f, 0.0f, 0.0f, u, v));
	}

	meshData.vertices.push_back(SEVertex(0.0f, y, 0.0f, 0.0f, -1.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.5f, 0.5f));

	UINT centerIndex = (UINT)meshData.vertices.size() - 1;

	for (UINT i = 0; i < sliceCount; i++)
	{
		meshData.indices.push_back(centerIndex);
		meshData.indices.push_back(baseIndex + i);
		meshData.indices.push_back(baseIndex + i + 1);
	}
}

void GeometryNode::CreateSphere(float radius, UINT sliceCount, UINT stackCount, MeshNode& meshData)
{
	//meshData.vertices.clear();
	//meshData.indices.clear();

	//// 球最高点顶点坐标
	//SEVertex topSEVertex(0.0f, +radius, 0.0f, 0.0f, +1.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f);
	//SEVertex bottomSEVertex(0.0f, -radius, 0.0f, 0.0f, -1.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f);

	//meshData.vertices.push_back(topSEVertex);
	//float phiStep = glm::pi<float>() / stackCount;	// 每圈stack所占的角度
	//float thetaStep = 2.0f* glm::pi<float>() / sliceCount;	// 每个slice占在一圈stack中所占的角度

	//// 计算stack，最顶点的除外
	//for (UINT i = 1; i <= stackCount - 1; i++)
	//{
	//	float phi = i * phiStep;
	//	
	//	for (UINT j = 0; j <= sliceCount; j++)
	//	{
	//		float theta = j * thetaStep;
	//		SEVertex v;

	//		v.Position.x = radius * sinf(phi) * cosf(theta);
	//		v.Position.y = radius * cosf(phi);
	//		v.Position.z = radius * sinf(phi) * sinf(theta);

	//		// 切线保证与原点到Position的矢量垂直，即dot(Position, Tangent)=0
	//		v.Tangent.x = -radius * sinf(phi) * sinf(theta);
	//		v.Tangent.y = 0.0f;
	//		v.Tangent.z = +radius * sinf(phi) * cosf(theta);

	//		XMVECTOR T = XMLoadFloat3(&v.Tangent);
	//		XMStoreFloat3(&v.Tangent, XMVector3Normalize(T));

	//		XMVECTOR p = XMLoadFloat3(&v.Position);
	//		XMStoreFloat3(&v.Normal, XMVector3Normalize(p));

	//		v.TexCoords.x = theta / XM_2PI;
	//		v.TexCoords.y = phi / XM_PI;

	//		meshData.vertices.push_back(v);
	//	}
	//}
	//meshData.vertices.push_back(bottomSEVertex);

	//// 添加顶层的stack的索引
	//for (UINT i = 1; i <= sliceCount; i++)
	//{
	//	meshData.indices.push_back(0);
	//	meshData.indices.push_back(i + 1);
	//	meshData.indices.push_back(i);
	//}
	//
	//// 添加中间的stack索引
	//UINT baseIndex = 1;
	//UINT ringSEVertexCount = sliceCount + 1;
	//for (UINT i = 0; i < stackCount - 2; i++)
	//{
	//	for (UINT j = 0; j < sliceCount; ++j)
	//	{
	//		meshData.indices.push_back(baseIndex + i * ringSEVertexCount + j);
	//		meshData.indices.push_back(baseIndex + i * ringSEVertexCount + j+1);
	//		meshData.indices.push_back(baseIndex + (i+1) * ringSEVertexCount + j);
	//	
	//		meshData.indices.push_back(baseIndex + (i + 1) * ringSEVertexCount + j);
	//		meshData.indices.push_back(baseIndex + i * ringSEVertexCount + j+1);
	//		meshData.indices.push_back(baseIndex + (i + 1) * ringSEVertexCount + j+1);
	//	}
	//}

	//UINT southPoleIndex = (UINT)meshData.vertices.size() - 1;

	//// 添加底层的索引
	//baseIndex = southPoleIndex - ringSEVertexCount;
	//for (UINT i = 0; i < sliceCount; i++)
	//{
	//	meshData.indices.push_back(southPoleIndex);
	//	meshData.indices.push_back(baseIndex + i);
	//	meshData.indices.push_back(baseIndex + i + 1);
	//}

}

void GeometryNode::CreateGeosphere(float radius, UINT numSubdivisions, MeshNode& meshData)
{
	// 限制细分的次数
	//numSubdivisions = MathHelper::Min(numSubdivisions, 5u);

	//// 使用一个20面体来近似这个球
	//const float X = 0.525731f;
	//const float Z = 0.850651f;

	//Vector3 pos[12] =
	//{
	//	Vector3(-X, 0.0f, Z),  Vector3(X, 0.0f, Z),
	//	Vector3(-X, 0.0f, -Z), Vector3(X, 0.0f, -Z),
	//	Vector3(0.0f, Z, X),   Vector3(0.0f, Z, -X),
	//	Vector3(0.0f, -Z, X),  Vector3(0.0f, -Z, -X),
	//	Vector3(Z, X, 0.0f),   Vector3(-Z, X, 0.0f),
	//	Vector3(Z, -X, 0.0f),  Vector3(-Z, -X, 0.0f)
	//};

	//DWORD k[60] =
	//{
	//	1,4,0,  4,9,0,  4,5,9,  8,5,4,  1,8,4,
	//	1,10,8, 10,3,8, 8,3,5,  3,2,5,  3,7,2,
	//	3,10,7, 10,6,7, 6,11,7, 6,0,11, 6,1,0,
	//	10,1,6, 11,0,9, 2,11,9, 5,2,9,  11,2,7
	//};

	//meshData.vertices.resize(12);
	//meshData.indices.resize(60);

	//for (UINT i = 0; i < 12; i++)
	//	meshData.vertices[i].Position = pos[i];
	//for (UINT i = 0; i < 60; i++)
	//	meshData.indices[i] = k[i];
	//for (UINT i = 0; i < numSubdivisions; i++)
	//	Subdivide(meshData);


	//for (UINT i = 0; i < meshData.vertices.size(); i++)
	//{
	//	XMVECTOR n = XMVector3Normalize(XMLoadFloat3(&meshData.vertices[i].Position));
	//	XMVECTOR p = radius * n;

	//	XMStoreFloat3(&meshData.vertices[i].Position, p);
	//	XMStoreFloat3(&meshData.vertices[i].Normal, n);

	//	// 计算角度
	//	float theta = MathHelper::AngleFromXY(meshData.vertices[i].Position.x, meshData.vertices[i].Position.z);
	//	float phi = acosf(meshData.vertices[i].Position.y / radius);

	//	meshData.vertices[i].TexCoords.x = theta / XM_2PI;
	//	meshData.vertices[i].TexCoords.y = phi / XM_PI;

	//	meshData.vertices[i].Tangent.x = -radius * sinf(phi) * sinf(theta);
	//	meshData.vertices[i].Tangent.y = 0.0f;
	//	meshData.vertices[i].Tangent.z = +radius * sinf(phi) * cosf(theta);

	//	XMVECTOR T = XMLoadFloat3(&meshData.vertices[i].Tangent);
	//	XMStoreFloat3(&meshData.vertices[i].Tangent, XMVector3Normalize(T));
	//}
}



GeometryNode::GeometryNode()
{
}

GeometryNode::~GeometryNode()
{
}

void GeometryNode::CreateTriangle()
{
	float vertices[] = {
		// positions         // colors
		 0.5f, -0.5f, 0.0f,  1.0f, 0.0f, 0.0f,  // bottom right
		-0.5f, -0.5f, 0.0f,  0.0f, 1.0f, 0.0f,  // bottom left
		 0.0f,  0.5f, 0.0f,  0.0f, 0.0f, 1.0f   // top 
	};



	glGenVertexArrays(1, &mesh.VAO);
	glGenBuffers(1, &mesh.VBO);
	// bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
	glBindVertexArray(mesh.VAO);

	glBindBuffer(GL_ARRAY_BUFFER, mesh.VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	// position attribute
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	// color attribute
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);
}

void GeometryNode::Subdivide(MeshNode& meshData)
{
	// 保存一份拷贝
	MeshNode inputCopy = meshData;

	meshData.vertices.resize(0);
	meshData.indices.resize(0);

	UINT numTris = inputCopy.indices.size() / 3;	// 三角型的数量
	for (UINT i = 0; i < numTris; i++)
	{
		SEVertex v0 = inputCopy.vertices[inputCopy.indices[i * 3 + 0]];
		SEVertex v1 = inputCopy.vertices[inputCopy.indices[i * 3 + 1]];
		SEVertex v2 = inputCopy.vertices[inputCopy.indices[i * 3 + 2]];

		// 生成中点的三个点
		SEVertex m0, m1, m2;
		m0.Position = Vector3(
			0.5f*(v0.Position.x + v1.Position.x),
			0.5f*(v0.Position.y + v1.Position.y),
			0.5f*(v0.Position.z + v1.Position.z));
		m1.Position = Vector3(
			0.5f*(v1.Position.x + v2.Position.x),
			0.5f*(v1.Position.y + v2.Position.y),
			0.5f*(v1.Position.z + v2.Position.z));
		m2.Position = Vector3(
			0.5f*(v0.Position.x + v2.Position.x),
			0.5f*(v0.Position.y + v2.Position.y),
			0.5f*(v0.Position.z + v2.Position.z));

		// 添加新的顶点索引信息
		meshData.vertices.push_back(v0);
		meshData.vertices.push_back(v1);
		meshData.vertices.push_back(v2);
		meshData.vertices.push_back(m0);
		meshData.vertices.push_back(m1);
		meshData.vertices.push_back(m2);

		meshData.indices.push_back(i * 6 + 0);
		meshData.indices.push_back(i * 6 + 3);
		meshData.indices.push_back(i * 6 + 5);

		meshData.indices.push_back(i * 6 + 3);
		meshData.indices.push_back(i * 6 + 4);
		meshData.indices.push_back(i * 6 + 5);

		meshData.indices.push_back(i * 6 + 5);
		meshData.indices.push_back(i * 6 + 4);
		meshData.indices.push_back(i * 6 + 2);

		meshData.indices.push_back(i * 6 + 3);
		meshData.indices.push_back(i * 6 + 1);
		meshData.indices.push_back(i * 6 + 4);
	}
	mesh.Init();
}

void GeometryNode::SetShader(const GLchar* vertexPath, const GLchar* fragmentPath)
{
	m_pShader = new Shader(vertexPath, fragmentPath);
}