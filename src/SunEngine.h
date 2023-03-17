#pragma once
#include "singleton/Singleton.h"

#include "window/Window.h"
#include "renderer/Renderer.h"
class SunEngine
{
	DECL_SINGLETON(SunEngine)	//����ʵ���಻��Ҫ���캯��
public:
	~SunEngine();
	bool Init();
	void Update();
	void Run();
	void Release();

	void display();
	void RendererTest();
public:
	Window* m_pMainWindow = nullptr;
	Renderer* m_pRenderer = nullptr;
	entt::registry registry;
private:
	bool m_bIsRunning = false;

	float vertex[4][3] = {
	{0, 0, 0},
	{0.2, 0.2, 0},
	{-0.3, 0, 0},
	{0, -0.3, 0}
	};

	
};

