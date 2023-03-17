#include "SunEngine.h"
#include <glad/glad.h> //<glad/glad.h>不能与gl/GL.h同时存在
#include <GLFW/glfw3.h>	//头文件问题待解决
#include <iostream>
// timing
float deltaTime = 0.0f;
float lastFrame = 0.0f;

SunEngine::~SunEngine()
{
}

bool SunEngine::Init()
{
	m_pMainWindow = new Window();
	m_pRenderer = new Renderer();
	if (!m_pMainWindow->Init())
	{
		std::cout << "Window Init Failed!" << std::endl;
		return false;
	}

	if (!m_pRenderer->Init(m_pMainWindow))
	{
		std::cout << "Window Init Failed!" << std::endl;
		return false;
	}

	m_bIsRunning = true;
	return true;
}

void SunEngine::Update()
{
	float currentFrame = static_cast<float>(glfwGetTime());
	deltaTime = currentFrame - lastFrame;
	lastFrame = currentFrame;

	//渲染整个Entt ECS系统
	m_pRenderer->Render(m_pMainWindow, registry);



	m_pMainWindow->Update();


}

void SunEngine::Run()
{
	while (!m_pMainWindow->IsClosed())
	{
		Update();
	}
	Release();
}

void SunEngine::Release()
{
	m_pRenderer->Release();
	m_pMainWindow->Release();
}


void SunEngine::display()
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
void SunEngine::RendererTest()
{
	std::cout << "RendererTest..." << std::endl;
	// 绘制模型
	display();//自定义绘制函数

	//交换缓冲区。GLFW在默认情况下使用两个缓冲区。每个窗口有两个渲染缓冲区——前缓冲区和后缓冲区。
	//前缓冲区是正在显示的缓冲区，后缓冲区是即将显示的缓冲区。
	glfwSwapBuffers(m_pMainWindow->GetGLFWwindow());

	//glfw处理事件有2个函数：glfwPollEvents()和glfwWaitEvents(),前者会立即处理已经到位的事件，后者等待。
	//当你制作游戏或是动画时，尽量使用轮询。如果相反，你需要在产生事件后才渲染，可是通过等待
	//来处理事件，即glfwWaitEvent，比如制作编辑器的时候，使用等待可以节省大量硬件资源。
	glfwPollEvents();
}

