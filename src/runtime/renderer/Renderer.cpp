#include "Renderer.h"
#include "window/Window.h"
//#include "World/GameWorld.h"
#include "OpenGL/OpenGLRenderer.h"
#include "Dx11/Dx11Renderer.h"
#include "Vukan/VukanRenderer.h"

#include <glad/glad.h> //<glad/glad.h>不能与gl/GL.h同时存在
#include <GLFW/glfw3.h>	//头文件问题待解决

//#include "graphic/MeshNode.h"
#include "graphic/GeometryNode.h"
#include "graphic/StaticMeshNode.h"
#include "graphic/SkeletonMeshNode.h"
#include "ecs/Components/Transform.h"

#include <learnopengl/camera.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <iostream>

extern Camera camera;
extern float deltaTime;
Renderer::Renderer()
{
}

Renderer::~Renderer()
{
}
bool Renderer::Init(Window* window)
{
	/*	Dx11Renderer::DestroyGetInstance();
		VukanRender::DestroyGetInstance();*/


	switch (m_uiRenderAPIType)
	{
	case RAT_OPENGL:
		if (!CreateOpenGL())
		{
			return false;
		}
		std::cout << "Renderer API: " << typeid(OpenGLRenderer).name() << std::endl;
		return OpenGLRenderer::GetInstance()->Init(window);
	case RAT_DIRECTX11:
		if (!CreateDx11())
		{
			return false;
		}
		std::cout << "Renderer API: " << typeid(Dx11Renderer).name() << std::endl;
		return Dx11Renderer::GetInstance()->Init(window);
		break;
	case RAT_VUKAN:
		if (!CreateVukan())
		{
			return false;
		}
		std::cout << "Renderer API: " << typeid(VukanRenderer).name() << std::endl;
		//return VuKanRenderer::GetInstance()->Init(window);
		break;
	default:
		break;
	}
	return true;
}
bool Renderer::CreateOpenGL()
{
	if (OpenGLRenderer::GetInstance())
	{
		if (m_uiRenderAPIType == RAT_OPENGL)
		{
			return true;
		}
		else
		{
			//Dx11Renderer::DestroyGetInstance();
			return false;
		}
	}
	else
	{
		if (m_uiRenderAPIType == RAT_OPENGL)
		{
			OpenGLRenderer::GetInstance();
			return true;
		}
		else
		{
			return false;
		}
	}
	return true;
}
bool Renderer::CreateDx11()
{
	if (Dx11Renderer::GetInstance())
	{
		if (m_uiRenderAPIType == RAT_DIRECTX11)
		{
			return true;
		}
		else
		{
			//Dx11Renderer::DestroyGetInstance();
			return false;
		}
	}
	else
	{
		if (m_uiRenderAPIType == RAT_DIRECTX11)
		{
			Dx11Renderer::GetInstance();
			return true;
		}
		else
		{
			return false;
		}
	}
	return true;
}
bool Renderer::CreateVukan()
{
	VukanRenderer::GetInstance();
	return true;
}
void Renderer::DrawFrame()
{
	/*switch (m_uiRenderAPIType)
	{
	case RAT_DIRECTX11:
		Dx11Renderer::GetInstance()->DrawFrame();
		break;
	case RAT_VUKAN:
		VukanRenderer::GetInstance()->DrawFrame();
		break;
	default:
		break;
	}*/
}
void Renderer::Release() 
{
	switch (m_uiRenderAPIType)
	{

	case RAT_DIRECTX11:
		Dx11Renderer::GetInstance()->Release();
		break;

	default:
		break;
	}
}
void Renderer::display()
{
	glClear(GL_COLOR_BUFFER_BIT);

	// 绘制顶点连线
	glColor3f(1, 1, 0);//曲线颜色
	glBegin(GL_LINES);
	for (int i = 0; i < 3; i++)
	{
		for (int j = i + 1; j < 4; j++) {
			glVertex3fv(vertex[i]);
			glVertex3fv(vertex[j]);
		}
	}
	glEnd();

	glFlush();
}
void Renderer::Render(Window* window, entt::registry& registry)
{

	//auto view = registry.view<StaticMesh>();

	//// use a callback
	//view.each([](const auto& mesh) { /* ... */ });

	//// use an extended callback
	//view.each([](const auto entity, const auto& mesh) { /* ... */ });

	//// use a range-for
	//for (auto [entity, mesh] : view.each()) {
	//	// ...
	//}

	// use forward iterators and get only the components of interest
	//for (auto entity : view) {
	//	auto& staticMesh = view.get<StaticMesh>(entity);
	//	// ...

	//		// opengl render 
	//	// ------
	//	glClearColor(0.05f, 0.05f, 0.05f, 1.0f);
	//	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	//	// don't forget to enable shader before setting uniforms
	//	staticMesh.m_pShader->use();

	//	// view/projection transformations
	//	glm::mat4 projection = glm::perspective(glm::radians(camera.Zoom), float(window->width()/window->heigth()), 0.1f, 100.0f);
	//	glm::mat4 view = camera.GetViewMatrix();
	//	staticMesh.m_pShader->setMat4("projection", glm::value_ptr(projection));
	//	staticMesh.m_pShader->setMat4("view", glm::value_ptr(view));

	//	// render the loaded model
	//	//glm::mat4 model = glm::mat4(1.0f);
	//	model = glm::translate(model, glm::vec3(0.0f, 0.0f, 0.0f)); // translate it down so it's at the center of the scene
	//	model = glm::scale(model, glm::vec3(1.0f, 1.0f, 1.0f));	// it's a bit too big for our scene, so scale it down
	//	staticMesh.m_pShader->setMat4("model", glm::value_ptr(model));
	//	staticMesh.Draw(*staticMesh.m_pShader);
	//}

	
	//取出所有网格放进渲染器绘制		所有绘制的网格体都放在一个循环里渲染 待整理
	auto view = registry.view<StaticMeshNode>();
	for (auto entity : view) {
		auto& staticMeshNode = view.get<StaticMeshNode>(entity);

		auto& transform=registry.get<Transform>(entity);
		BeginRender();

		// don't forget to enable shader before setting uniforms
		staticMeshNode.m_pShader->use();

		// view/projection transformations
		glm::mat4 projection = glm::perspective(glm::radians(camera.Zoom), float(window->width()/window->heigth()), 0.1f, 100.0f);
		glm::mat4 view = camera.GetViewMatrix();
		staticMeshNode.m_pShader->setMat4("projection", projection);
		staticMeshNode.m_pShader->setMat4("view", view);

		// render the loaded model
		//glm::mat4 model = glm::mat4(1.0f);
		//model = glm::translate(model, glm::vec3(0.0f, 0.0f, 0.0f)); // translate it down so it's at the center of the scene
		//model = glm::scale(model, glm::vec3(1.0f, 1.0f, 1.0f));	// it's a bit too big for our scene, so scale it down
		//staticMeshNode.m_pShader->setMat4("model", glm::value_ptr(model));
		staticMeshNode.m_pShader->setMat4("model", transform.model);
		//staticMeshNode.Draw(*staticMeshNode.m_pShader);

		//绘制网格
		for (int i = 0; i < staticMeshNode.meshes.size(); ++i)
		{
			DrawMesh(window, &staticMeshNode.meshes[i], staticMeshNode.m_pShader);
		}
	}

	auto view1 = registry.view<SkeletonMeshNode>();
	for (auto entity : view1) {
		auto& skeletonMeshNode = view1.get<SkeletonMeshNode>(entity);

		auto& transform = registry.get<Transform>(entity);

		//更新动画数据
		skeletonMeshNode.UpdateAnimation(deltaTime,0);

		BeginRender();

		// don't forget to enable shader before setting uniforms
		skeletonMeshNode.m_pShader->use();

		// view/projection transformations
		glm::mat4 projection = glm::perspective(glm::radians(camera.Zoom), float(window->width() / window->heigth()), 0.1f, 100.0f);
		glm::mat4 view = camera.GetViewMatrix();
		skeletonMeshNode.m_pShader->setMat4("projection", projection);
		skeletonMeshNode.m_pShader->setMat4("view", view);

	/*	auto boneTransforms = skeletonMeshNode.m_boneInfo;
		for (int i = 0; i < boneTransforms.size(); ++i)
			skeletonMeshNode.m_pShader->setMat4("finalBonesMatrices[" + std::to_string(i) + "]", boneTransforms[i].finalTransformationGLM);*/

		auto transforms = skeletonMeshNode.GetFinalBoneMatrices();
		for (int i = 0; i < transforms.size(); ++i)
		{
			//std::cout << "skeletonMeshNode the" << i  << "th bone Mat[0][0]" << transforms[i][0][0] << std::endl;
			skeletonMeshNode.m_pShader->setMat4("finalBonesMatrices[" + std::to_string(i) + "]", transforms[i]);//名字跟vs文件要一致
		}
		

		// render the loaded model
		//glm::mat4 model = glm::mat4(1.0f);
		//model = glm::translate(model, glm::vec3(0.0f, 0.0f, 0.0f)); // translate it down so it's at the center of the scene
		//model = glm::scale(model, glm::vec3(1.0f, 1.0f, 1.0f));	// it's a bit too big for our scene, so scale it down
		//staticMeshNode.m_pShader->setMat4("model", glm::value_ptr(model));
		skeletonMeshNode.m_pShader->setMat4("model", transform.model);
		//staticMeshNode.Draw(*staticMeshNode.m_pShader);

		//绘制网格
		for (int i = 0; i < skeletonMeshNode.meshes.size(); ++i)
		{
			DrawMesh(window, &skeletonMeshNode.meshes[i], skeletonMeshNode.m_pShader);
		}
	}


	auto view2 = registry.view<GeometryNode>();
	for (auto entity : view2) {
		auto& geometryNode = view2.get<GeometryNode>(entity);

		auto& transform = registry.get<Transform>(entity);
		BeginRender();

		geometryNode.m_pShader->use();

		glm::mat4 projection = glm::perspective(glm::radians(camera.Zoom), float(window->width() / window->heigth()), 0.1f, 100.0f);
		glm::mat4 view = camera.GetViewMatrix();
		geometryNode.m_pShader->setMat4("projection", projection);
		geometryNode.m_pShader->setMat4("view", view);

		geometryNode.m_pShader->setMat4("model", transform.model);

		glBindVertexArray(geometryNode.mesh.VAO);
		glDrawArrays(GL_TRIANGLES, 0, 3);
		glBindVertexArray(0);


		//绘制网格
		//DrawMesh(window, &geometryNode.mesh, geometryNode.m_pShader);
	}
}

bool Renderer::InitMesh(MeshNode* mesh)
{
	switch (m_uiRenderAPIType)
	{
	case RAT_OPENGL:
		OpenGLRenderer::GetInstance()->InitMesh(mesh);
		break;
	//case RAT_DIRECTX11:
	//	Dx11Renderer::GetInstance()->InitMesh();
	//	break;
		/*case RAT_VUKAN:
			VukanRenderer::GetInstance()->InitMesh();
			break;*/
	default:
		break;
	}
	return true;;
}

void Renderer::DrawMesh(Window* window, MeshNode* mesh, Shader* shader)
{
	switch (m_uiRenderAPIType)
	{
	case RAT_OPENGL:
		OpenGLRenderer::GetInstance()->Render(window,mesh,shader);
		break;
	case RAT_DIRECTX11:
		Dx11Renderer::GetInstance()->Render();
		break;
		/*case RAT_VUKAN:
			VukanRenderer::GetInstance()->Renderer();
			break;*/
	default:
		break;
	}
}

void Renderer::BeginRender()
{
	switch (m_uiRenderAPIType)
	{
	case RAT_OPENGL:
		OpenGLRenderer::GetInstance()->BeginRender();
		break;
	default:
		break;
	}
}
