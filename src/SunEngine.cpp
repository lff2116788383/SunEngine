#include "SunEngine.h"
#include <glad/glad.h> //<glad/glad.h>������gl/GL.hͬʱ����
#include <GLFW/glfw3.h>	//ͷ�ļ���������
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

	//��Ⱦ����Entt ECSϵͳ
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

	// ���ƶ�������
	glColor3f(1, 1, 0);//������ɫ
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
	// ����ģ��
	display();//�Զ�����ƺ���

	//������������GLFW��Ĭ�������ʹ��������������ÿ��������������Ⱦ����������ǰ�������ͺ󻺳�����
	//ǰ��������������ʾ�Ļ��������󻺳����Ǽ�����ʾ�Ļ�������
	glfwSwapBuffers(m_pMainWindow->GetGLFWwindow());

	//glfw�����¼���2��������glfwPollEvents()��glfwWaitEvents(),ǰ�߻����������Ѿ���λ���¼������ߵȴ���
	//����������Ϸ���Ƕ���ʱ������ʹ����ѯ������෴������Ҫ�ڲ����¼������Ⱦ������ͨ���ȴ�
	//�������¼�����glfwWaitEvent�����������༭����ʱ��ʹ�õȴ����Խ�ʡ����Ӳ����Դ��
	glfwPollEvents();
}

