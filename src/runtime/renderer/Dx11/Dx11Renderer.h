#pragma once


#include <d3d11_1.h>
#include <d3dcompiler.h>
//#include "GameTimer.h"

// ��̬���ӿ�
#pragma comment(lib, "d3d11.lib")
#pragma comment(lib, "dxgi.lib")
#pragma comment(lib, "dxguid.lib")
#pragma comment(lib, "D3DCompiler.lib")
#pragma comment(lib, "winmm.lib")

#include <d3d11.h>
#include <tchar.h>
#include <assert.h>


#include "singleton/Singleton.h"


#define ReleaseCOM(x) { if(x){ x->Release(); x=0; } }

#define Log(x){ std::wostringstream outs; outs << x << L"\n"; OutputDebugString(outs.str().c_str()); }
class Window;
class Dx11Renderer 
{
	DECL_SINGLETON(Dx11Renderer)
public:
	

	//��ʼ��D3D�������Ǹ��������õĴ��ھ��
	bool InitDevice(Window* window);

	void CleanDevice();

	bool Init(Window* window);
	void Render();
	void Release();
private:
	//DX11�Ķ���
	ID3D11Device* g_pd3dDevice = NULL;
	ID3D11DeviceContext* g_pImmediateContext = NULL;
	IDXGISwapChain* g_pSwapChain = NULL;
	ID3D11RenderTargetView* g_pRenderTargetView = NULL;
};