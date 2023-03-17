#include "Window.h"
#include <glad/glad.h> //<glad/glad.h>不能与gl/GL.h同时存在
#include <GLFW/glfw3.h>	//头文件问题待解决
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

//处理用户输入
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
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); //加上三角形显示不出来
	//设置OpenGL的版本号，可以不设也别瞎设，设错了图形可能显示不出来
	//glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	//glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);

#ifdef __APPLE__
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

	//其中第一个参数是窗口宽度，第二个参数是窗口高度，第三个参数是窗口标题，第四个参数是显示模式，NULL为窗口化，如果需要显
	//示全屏，则需要指定覆盖的显示器，第五个参数是设置与那个窗口共享资源，默认为NULL，即不共享资源。
	m_pGLFWWindow = glfwCreateWindow(width, height, title.c_str(), NULL, NULL);
	if (!m_pGLFWWindow)
	{
		glfwTerminate();//清除退出
	}

	m_uiWindowHeight = width;
	m_uiWindowHeight = height;

	/////* 设置当前的窗口上下文 *///将创建的窗口作为OpenGL当前的上下文 待定
	glfwMakeContextCurrent(m_pGLFWWindow);//上下文啥意思还不太理解？？

	glfwSetFramebufferSizeCallback(m_pGLFWWindow,framebuffer_size_callback);
	glfwSetCursorPosCallback(m_pGLFWWindow, mouse_callback);
	glfwSetScrollCallback(m_pGLFWWindow, scroll_callback);

	//////交换间隔表示交换缓冲区之前等待的帧数，通常称为vsync。
	//////默认情况下，交换间隔为0，但因为屏幕每秒只更新60-75次，所以大部分的画面不会被显示。
	//////而且，缓冲区有可能在屏幕更新的中间交换，出现屏幕撕裂的情况。
	//////所以，可以将该间隔设为1，即每帧更新一次。它可以设置为更高的值，但这可能导致输入延迟。
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
	glEnable(GL_DEPTH_TEST);	//开启深度测试 否则纹理显示错误

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
	////交换缓冲区。GLFW在默认情况下使用两个缓冲区。每个窗口有两个渲染缓冲区——前缓冲区和后缓冲区。
	////前缓冲区是正在显示的缓冲区，后缓冲区是即将显示的缓冲区。
	glfwSwapBuffers(m_pGLFWWindow);

	////glfw处理事件有2个函数：glfwPollEvents()和glfwWaitEvents(),前者会立即处理已经到位的事件，后者等待。
	////当你制作游戏或是动画时，尽量使用轮询。如果相反，你需要在产生事件后才渲染，可是通过等待
	////来处理事件，即glfwWaitEvent，比如制作编辑器的时候，使用等待可以节省大量硬件资源。
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
