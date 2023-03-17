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

//#include <windows.h>//��APIENTRY��: ���ض���
////#include <glad/glad.h> //<glad/glad.h>������gl/GL.hͬʱ����
//#include <GLFW/glfw3.h>	//ͷ�ļ���������
////#include <gl/GL.h>	//ϵͳGL


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
class  Window	//GLͷ�ļ��ŵ�Window.cpp �����ظ�����Window.h�����glfw3.h��glad.hǰ��
{
public:
	Window();
	~Window();
public:


	void Release();



	void error_callback(int error, const char* description);

	//�����û�����
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

	//��ȡ���ھ�� ����������Ⱦ��
public:
	GLFWwindow* m_pGLFWWindow = nullptr;
private:
	unsigned int m_uiWindowWidth = 0;
	unsigned int m_uiWindowHeight = 0;
};
/*
������ֻ���𴰿ڵĴ��������ٵȴ���
*/

