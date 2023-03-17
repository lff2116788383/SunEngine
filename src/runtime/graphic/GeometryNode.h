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
	// ϸ������
	void Subdivide(MeshNode& meshData);
	// ����һ������
	void CreateBox(float width, float height, float depth);
	// ����һ����
	void CreateGrid(float width, float depth, UINT m, UINT n, MeshNode& meshData);

	/*�����ݲ���ʹ��*/
	// ����һ��Բ��
	static void CreateCylinder(float bottomRadius, float topRadius, float height, UINT sliceCount, UINT stackCount, MeshNode& meshData);
	// Բ��TopԲ��
	static void BuildCylinderTopCap(float bottomRadius, float topRadius, float height, UINT sliceCount, UINT stackCount, MeshNode& meshData);
	// Բ��BottomԲ��
	static void BuildCylinderBottomCap(float bottomRadius, float topRadius, float height, UINT sliceCount, UINT stackCount, MeshNode& meshData);
	// ��������
	static void CreateSphere(float radius, UINT sliceCount, UINT stackCount, MeshNode& meshData);
	// ʹ�ô����ǵķ�ʽ��������
	static void CreateGeosphere(float radius, UINT numSubdivisions, MeshNode& meshData);
	

	void SetShader(const GLchar* vertexPath, const GLchar* fragmentPath);
	MeshNode mesh;
	Shader* m_pShader = nullptr;
};

