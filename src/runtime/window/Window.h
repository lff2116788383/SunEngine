#pragma once
//#include "glad/glad.h"
//#include "GLFW/glfw3.h"
////#pragma comment(lib, "opengl32.lib")
////#pragma comment(lib, "glfw3.lib")
//
//#define GLFW_EXPOSE_NATIVE_WIN32
//#define GLFW_EXPOSE_NATIVE_WGL
//#define GLFW_NATIVE_INCLUDE_NONE
//#include <GLFW/glfw3native.h>

//#include <windows.h>//“APIENTRY”: 宏重定义
////#include <glad/glad.h> //<glad/glad.h>不能与gl/GL.h同时存在
//#include <GLFW/glfw3.h>	//头文件问题待解决
////#include <gl/GL.h>	//系统GL


//#ifdef _HAS_STD_BYTE
//#undef _HAS_STD_BYTE
//#endif
//#define _HAS_STD_BYTE 0
//#include <glad/glad.h>
//#include <GLFW/glfw3.h>
//
//#include <glm/glm.hpp>
//#include <glm/gtc/matrix_transform.hpp>
//#include <glm/gtc/type_ptr.hpp>
//
////#include <learnopengl/filesystem.h>
//#include <learnopengl/shader_m.h>
//#include <learnopengl/camera.h>
//#include <learnopengl/model.h>
//
//#include <iostream>

#include <windows.h>
#include <string>
struct GLFWwindow;
typedef void (*GLFWkeyfun)(GLFWwindow*, int, int, int, int);
typedef void (*GLFWmousebuttonfun)(GLFWwindow*, int, int, int);
class  Window	//GL头文件放到Window.cpp 否则重复引用Window.h会出现glfw3.h在glad.h前面
{
public:
	Window();
	~Window();
public:


	void Release();



	void error_callback(int error, const char* description);

	//处理用户输入
	void process_input(GLFWwindow* window);

	void display();

	bool Init(std::string title = "Window", int width = 640, int height = 480);

	/*void SetKeyCallBack(GLFWkeyfun callback);
	void SetMouseButtonCallback(GLFWmousebuttonfun callback);*/
	void Update();


	bool IsClosed();

	void Destroy();

	void SetKeyCallBack(GLFWkeyfun callback);

	void SetMouseButtonCallback(GLFWmousebuttonfun callback);


	unsigned int width()
	{
		return m_uiWindowHeight;
	}

	unsigned int heigth()
	{
		return m_uiWindowHeight;
	}



	GLFWwindow* GetGLFWwindow();

	HWND GetWindowHWND();

	//HWND GetWin32WindowHWND();

	//获取窗口句柄 用于其他渲染器
public:
	GLFWwindow* m_pGLFWWindow = nullptr;
private:
	unsigned int m_uiWindowWidth = 0;
	unsigned int m_uiWindowHeight = 0;
};
/*
窗口类只负责窗口的创建和销毁等处理
*/

