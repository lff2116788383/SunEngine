//#define NOMINMAX //预处理器加上NOMINMAX

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "SunEngine.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>



#include "ecs/Components/Transform.h"
#include "graphic/GeometryNode.h"
#include "graphic/StaticMeshNode.h"
#include "graphic/SkeletonMeshNode.h"
#include <iostream>
#include <stb_image.h>

Transform* tr;
float speed = 0.1f;

struct Position {
	float x;
	float y;
};

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	if (action != GLFW_PRESS)
		return;
	std::cout << "key pressed: " << key << std::endl;
	switch (key)//监听键盘按下操作
	{
	case GLFW_KEY_ESCAPE:
		glfwSetWindowShouldClose(window, GL_TRUE);
		break;
	case GLFW_KEY_W:
		tr->Translate(0.0 ,1.0 * speed, 0.0);
		break;
	case GLFW_KEY_A:
		tr->Translate(-1.0* speed, 0.0, 0.0);
		break;
	case GLFW_KEY_S:
		tr->Translate(0.0, -1.0 * speed, 0.0);
		break;
	case GLFW_KEY_D:
		tr->Translate(1.0 * speed, 0.0, 0.0);
		break;
	default:
		break;
	}
}
void mouse_button_callback(GLFWwindow* window, int button, int action, int mods)
{
	if (action == GLFW_PRESS) switch (button)
	{
	case GLFW_MOUSE_BUTTON_LEFT:
		std::cout << "Mosue left button clicked!" << std::endl;
		break;
	case GLFW_MOUSE_BUTTON_MIDDLE:
		std::cout << "Mosue middle button clicked!" << std::endl;
		break;
	case GLFW_MOUSE_BUTTON_RIGHT:
		std::cout << "Mosue right button clicked!" << std::endl;
		tr->Scale(0.5f, 0.5f, 0.5f);
		break;
	default:
		return;
	}
	return;
}


int main()
{
	std::cout << "SunEngine Start" << std::endl;
	if (!SunEngine::GetInstance()->Init())
	{
		std::cout << "SunEngine  Init Failed!" << std::endl;
		return -1;
	}

	////call_back 回调 输入监听函数
	SunEngine::GetInstance()->m_pMainWindow->SetKeyCallBack(key_callback);
	////glfwSetFramebufferSizeCallback(RPGEngine3D::GetInstance()->GetWindow()->GetGLFWwindow(), framebuffer_size_callback);
	SunEngine::GetInstance()->m_pMainWindow->SetMouseButtonCallback(mouse_button_callback);

	const auto entity = SunEngine::GetInstance()->registry.create();

	SunEngine::GetInstance()->registry.emplace<Position>(entity, 1.f,  1.f);

	/*几何体绘制测试*/
	//SunEngine::GetInstance()->registry.emplace<GeometryNode>(entity);
	//auto& geometryNode = SunEngine::GetInstance()->registry.get<GeometryNode>(entity);
	//geometryNode.CreateTriangle();
	//geometryNode.SetShader("D:/UserProfiles/LewisLiu/Desktop/SunEngine/shader/3.3.shader.vs"
	//	, "D:/UserProfiles/LewisLiu/Desktop/SunEngine/shader/3.3.shader.fs");


	/*加载静态网格体*/
	/*SunEngine::GetInstance()->registry.emplace<StaticMeshNode>(entity, "D:/UserProfiles/LewisLiu/Desktop/SunEngine/resources/objects/backpack/backpack.obj");
	auto& staticMeshNode = SunEngine::GetInstance()->registry.get<StaticMeshNode>(entity);
	staticMeshNode.SetShader("D:/UserProfiles/LewisLiu/Desktop/SunEngine/shader/shader.vs"
		, "D:/UserProfiles/LewisLiu/Desktop/SunEngine/shader/shader.fs");*/

	/*骨骼动画测试 默认播放第一个动画 未完成 原因最终骨骼矩阵计算错误*/
	SunEngine::GetInstance()->registry.emplace<SkeletonMeshNode>(entity, "D:/UserProfiles/LewisLiu/Desktop/SunEngine/resources/objects/vampire/dancing_vampire.dae");
	auto& skeletonMeshNode = SunEngine::GetInstance()->registry.get<SkeletonMeshNode>(entity);
	skeletonMeshNode.SetShader("D:/UserProfiles/LewisLiu/Desktop/SunEngine/shader/anim_model.vs"
		, "D:/UserProfiles/LewisLiu/Desktop/SunEngine/shader/anim_model.fs");

	SunEngine::GetInstance()->registry.emplace<Transform>(entity);

	tr = &SunEngine::GetInstance()->registry.get<Transform>(entity);


	SunEngine::GetInstance()->Run();
	SunEngine::GetInstance()->Release();

	return 0;
}






