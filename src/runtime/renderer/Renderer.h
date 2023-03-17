#pragma once
#include <entt/entity/registry.hpp>
#include <vector>
enum	//Render API Type
{
	RAT_NULL,
	RAT_OPENGL,
	RAT_DIRECTX9,
	RAT_DIRECTX10,
	RAT_DIRECTX11,
	RAT_DIRECTX12,
	RAT_VUKAN,
	RAT_SOFTWARE,
	RAT_MAX
};
class Window;
class MeshNode;
class Shader;
class  Renderer
{
public:
	Renderer();

	~Renderer();
	bool Init(Window* window);
	bool CreateOpenGL();
	bool CreateDx11();
	bool CreateVukan();
	void DrawFrame();
	void Release();
	void display();
	void Render(Window* window, entt::registry& registry);
	bool InitMesh(MeshNode* mesh);
	void DrawMesh(Window* window, MeshNode* mesh = nullptr, Shader* shader = nullptr);
	void BeginRender();
	unsigned int m_uiRenderAPIType = RAT_OPENGL;
	float vertex[4][3] = {
{0, 0, 0},
{0.2, 0.2, 0},
{-0.3, 0, 0},
{0, -0.3, 0}
	};
};

