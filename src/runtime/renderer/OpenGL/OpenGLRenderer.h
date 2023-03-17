#pragma once
#include "singleton/Singleton.h"
class Window;
class MeshNode;
class Shader;
class  OpenGLRenderer
{
	DECL_SINGLETON(OpenGLRenderer)
public:

	bool Init(Window* window);
	void display();

	void InitMesh(MeshNode* mesh);
	void BeginRender();
	void Render(Window* window, MeshNode* mesh =nullptr, Shader* shader = nullptr);
private:
	float testvertex[4][3] = {
{0, 0, 0},
{0.2, 0.2, 0},
{-0.3, 0, 0},
{0, -0.3, 0}
	};
};

