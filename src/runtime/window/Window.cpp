#include "Window.h"
#include <glad/glad.h> //<glad/glad.h>������gl/GL.hͬʱ����
#include <GLFW/glfw3.h>	//ͷ�ļ���������
#include <assert.h>
#include <iostream>
#include <stb_image.h>
#include <learnopengl/camera.h>

#define GLFW_EXPOSE_NATIVE_WIN32
#define GLFW_EXPOSE_NATIVE_WGL
#define GLFW_NATIVE_INCLUDE_NONE
#include <GLFW/glfw3native.h>
// camera
Camera camera(glm::vec3(0.0f, 0.0f, 3.0f));
float lastX = 640 / 2.0f;
float lastY = 480 / 2.0f;
bool firstMouse = true;

// timing
extern float deltaTime;
extern float lastFrame;

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void mouse_callback(GLFWwindow* window, double xpos, double ypos);
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
void processInput(GLFWwindow* window);

Window::Window()
{
}
Window::~Window()
{
}
void Window::Release()
{
	Destroy();
}
void Window::error_callback(int error, const char* description) {
	std::cout << "Error:" << error + description << std::endl;
}

//�����û�����
void Window::process_input(GLFWwindow* window) {
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
		glfwSetWindowShouldClose(window, GL_TRUE);
	}
}

void Window::display()
{
}

// process all input: query GLFW whether relevant keys are pressed/released this frame and react accordingly
// ---------------------------------------------------------------------------------------------------------
void processInput(GLFWwindow* window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);

	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
		camera.ProcessKeyboard(FORWARD, deltaTime);
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
		camera.ProcessKeyboard(BACKWARD, deltaTime);
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
		camera.ProcessKeyboard(LEFT, deltaTime);
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
		camera.ProcessKeyboard(RIGHT, deltaTime);
}

// glfw: whenever the window size changed (by OS or user resize) this callback function executes
// ---------------------------------------------------------------------------------------------
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	// make sure the viewport matches the new window dimensions; note that width and 
	// height will be significantly larger than specified on retina displays.
	glViewport(0, 0, width, height);
}

// glfw: whenever the mouse moves, this callback is called
// -------------------------------------------------------
void mouse_callback(GLFWwindow* window, double xposIn, double yposIn)
{
	float xpos = static_cast<float>(xposIn);
	float ypos = static_cast<float>(yposIn);

	if (firstMouse)
	{
		lastX = xpos;
		lastY = ypos;
		firstMouse = false;
	}

	float xoffset = xpos - lastX;
	float yoffset = lastY - ypos; // reversed since y-coordinates go from bottom to top

	lastX = xpos;
	lastY = ypos;

	camera.ProcessMouseMovement(xoffset, yoffset);
}

// glfw: whenever the mouse scroll wheel scrolls, this callback is called
// ----------------------------------------------------------------------
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
	camera.ProcessMouseScroll(static_cast<float>(yoffset));
}

bool Window::Init(std::string title, int width, int height)
{
	if (!glfwInit())
		return false;
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); //������������ʾ������
	//����OpenGL�İ汾�ţ����Բ���Ҳ��Ϲ�裬�����ͼ�ο�����ʾ������
	//glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	//glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);

#ifdef __APPLE__
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

	//���е�һ�������Ǵ��ڿ�ȣ��ڶ��������Ǵ��ڸ߶ȣ������������Ǵ��ڱ��⣬���ĸ���������ʾģʽ��NULLΪ���ڻ��������Ҫ��
	//ʾȫ��������Ҫָ�����ǵ���ʾ����������������������Ǹ����ڹ�����Դ��Ĭ��ΪNULL������������Դ��
	m_pGLFWWindow = glfwCreateWindow(width, height, title.c_str(), NULL, NULL);
	if (!m_pGLFWWindow)
	{
		glfwTerminate();//����˳�
	}

	m_uiWindowHeight = width;
	m_uiWindowHeight = height;

	/////* ���õ�ǰ�Ĵ��������� *///�������Ĵ�����ΪOpenGL��ǰ�������� ����
	glfwMakeContextCurrent(m_pGLFWWindow);//������ɶ��˼����̫��⣿��

	glfwSetFramebufferSizeCallback(m_pGLFWWindow,framebuffer_size_callback);
	glfwSetCursorPosCallback(m_pGLFWWindow, mouse_callback);
	glfwSetScrollCallback(m_pGLFWWindow, scroll_callback);

	//////���������ʾ����������֮ǰ�ȴ���֡����ͨ����Ϊvsync��
	//////Ĭ������£��������Ϊ0������Ϊ��Ļÿ��ֻ����60-75�Σ����Դ󲿷ֵĻ��治�ᱻ��ʾ��
	//////���ң��������п�������Ļ���µ��м佻����������Ļ˺�ѵ������
	//////���ԣ����Խ��ü����Ϊ1����ÿ֡����һ�Ρ�����������Ϊ���ߵ�ֵ��������ܵ��������ӳ١�
	//glfwSwapInterval(1);

	// glad: load all OpenGL function pointers
	// ---------------------------------------
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		return false;
	}

	// tell stb_image.h to flip loaded texture's on the y-axis (before loading model).
	stbi_set_flip_vertically_on_load(true);

	// configure global opengl state
	// -----------------------------
	glEnable(GL_DEPTH_TEST);	//������Ȳ��� ����������ʾ����

	return true;
}

void Window::SetKeyCallBack(GLFWkeyfun callback)
{
	glfwSetKeyCallback(m_pGLFWWindow, callback);

}
void Window::SetMouseButtonCallback(GLFWmousebuttonfun callback)
{
	glfwSetMouseButtonCallback(m_pGLFWWindow, callback);
}
void Window::Update()
{
	////������������GLFW��Ĭ�������ʹ��������������ÿ��������������Ⱦ����������ǰ�������ͺ󻺳�����
	////ǰ��������������ʾ�Ļ��������󻺳����Ǽ�����ʾ�Ļ�������
	glfwSwapBuffers(m_pGLFWWindow);

	////glfw�����¼���2��������glfwPollEvents()��glfwWaitEvents(),ǰ�߻����������Ѿ���λ���¼������ߵȴ���
	////����������Ϸ���Ƕ���ʱ������ʹ����ѯ������෴������Ҫ�ڲ����¼������Ⱦ������ͨ���ȴ�
	////�������¼�����glfwWaitEvent�����������༭����ʱ��ʹ�õȴ����Խ�ʡ����Ӳ����Դ��
	glfwPollEvents();

}


bool Window::IsClosed()
{
	return glfwWindowShouldClose(m_pGLFWWindow);
}

void Window::Destroy()
{
	glfwDestroyWindow(m_pGLFWWindow);
	glfwTerminate();
}

GLFWwindow* Window::GetGLFWwindow()
{
	assert(m_pGLFWWindow != nullptr);
	return m_pGLFWWindow;
}

HWND Window::GetWindowHWND()
{
	return glfwGetWin32Window(m_pGLFWWindow);
}

//HWND Window::GetWindowHWND()
//{
//	return GetActiveWindow();
//}
//
//HWND Window::GetWin32WindowHWND()
//{
//	return glfwGetWin32Window(m_pGLFWWindow);
//}
