#pragma once
#include <vector>
#include <wrl/client.h>
//#include <assert.h>
//#include "dxerr.h"
//#include <string>
//#include <sstream>
//#include <fstream>
//#include <filesystem>
//#include <d3dcompiler.h>
//#include <d3d11_1.h>
#include "MeshNode.h"

//#include <DirectXMath.h>
//using namespace DirectX;

class GeometryNode
{
public:
	GeometryNode();
	~GeometryNode();

	void CreateTriangle();
	// 细分三角
	void Subdivide(MeshNode& meshData);
	// 创建一个方块
	void CreateBox(float width, float height, float depth);
	// 创建一个面
	void CreateGrid(float width, float depth, UINT m, UINT n, MeshNode& meshData);

	/*以下暂不能使用*/
	// 创建一个圆柱
	static void CreateCylinder(float bottomRadius, float topRadius, float height, UINT sliceCount, UINT stackCount, MeshNode& meshData);
	// 圆柱Top圆形
	static void BuildCylinderTopCap(float bottomRadius, float topRadius, float height, UINT sliceCount, UINT stackCount, MeshNode& meshData);
	// 圆柱Bottom圆形
	static void BuildCylinderBottomCap(float bottomRadius, float topRadius, float height, UINT sliceCount, UINT stackCount, MeshNode& meshData);
	// 创建球体
	static void CreateSphere(float radius, UINT sliceCount, UINT stackCount, MeshNode& meshData);
	// 使用纯三角的方式创建球体
	static void CreateGeosphere(float radius, UINT numSubdivisions, MeshNode& meshData);
	

	void SetShader(const GLchar* vertexPath, const GLchar* fragmentPath);
	MeshNode mesh;
	Shader* m_pShader = nullptr;
};

