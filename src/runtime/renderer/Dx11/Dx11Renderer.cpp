#include "Dx11Renderer.h"
#include "window/Window.h"
bool Dx11Renderer::InitDevice(Window* window)
{
    HRESULT hr = S_OK;

    //列出所有考虑的FeatureLevel：
    D3D_FEATURE_LEVEL featureLevels[] =
    {
        D3D_FEATURE_LEVEL_11_0,
        D3D_FEATURE_LEVEL_10_1,
        D3D_FEATURE_LEVEL_10_0,
    };

    //列出所有考虑的驱动类型（越靠前越优先考虑）
    D3D_DRIVER_TYPE driverTypes[] =
    {
        D3D_DRIVER_TYPE_HARDWARE,
        D3D_DRIVER_TYPE_WARP,
        D3D_DRIVER_TYPE_REFERENCE,
    };

    //创建SwapChain的描述结构体
    DXGI_SWAP_CHAIN_DESC swapchainDescription;
    ZeroMemory(&swapchainDescription, sizeof(swapchainDescription));
    swapchainDescription.BufferCount = 1;
    swapchainDescription.BufferDesc.Width = window->width();
    swapchainDescription.BufferDesc.Height = window->heigth();
    swapchainDescription.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
    swapchainDescription.BufferDesc.RefreshRate.Numerator = 60;
    swapchainDescription.BufferDesc.RefreshRate.Denominator = 1;
    swapchainDescription.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
    swapchainDescription.OutputWindow = window->GetWindowHWND();
    swapchainDescription.SampleDesc.Count = 1;
    swapchainDescription.SampleDesc.Quality = 0;
    swapchainDescription.Windowed = TRUE;

    D3D_DRIVER_TYPE         outDriverType;	//最终决定的DriverType
    D3D_FEATURE_LEVEL       outFeatureLevel;//最终决定的FeatureLevel
    //按照驱动类型依次尝试创建Device和SwapChain
    for (UINT driverTypeIndex = 0; driverTypeIndex < ARRAYSIZE(driverTypes); driverTypeIndex++)
    {
        outDriverType = driverTypes[driverTypeIndex];
        hr = D3D11CreateDeviceAndSwapChain(NULL, outDriverType, NULL, 0, featureLevels, ARRAYSIZE(featureLevels),
            D3D11_SDK_VERSION, &swapchainDescription, &g_pSwapChain, &g_pd3dDevice, &outFeatureLevel, &g_pImmediateContext);
        if (SUCCEEDED(hr))
            break;
    }
    if (FAILED(hr))
        return false;

    //从SwapChain那里得到BackBuffer
    ID3D11Texture2D* pBackBuffer = NULL;
    hr = g_pSwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (LPVOID*)&pBackBuffer);
    if (FAILED(hr))
        return false;

    //创建一个 render target view
    hr = g_pd3dDevice->CreateRenderTargetView(pBackBuffer, NULL, &g_pRenderTargetView);
    pBackBuffer->Release();
    if (FAILED(hr))
        return false;

    //输出合并阶段（Output-Merger Stage）设置RenderTarget
    g_pImmediateContext->OMSetRenderTargets(1, &g_pRenderTargetView, NULL);

  
	return true;
}

void Dx11Renderer::CleanDevice()
{
    ReleaseCOM(g_pd3dDevice);
    ReleaseCOM(g_pImmediateContext);
    ReleaseCOM(g_pSwapChain);
    ReleaseCOM(g_pRenderTargetView);
}

bool Dx11Renderer::Init(Window* window)
{
    return InitDevice(window);
}

void Dx11Renderer::Render()
{
    // 清理 back buffer 
    float ClearColor[4] = { 0.0f, 0.0f, 0.75f, 1.0f };
    g_pImmediateContext->ClearRenderTargetView(g_pRenderTargetView, ClearColor);

    // Present the information rendered to the back buffer to the front buffer (the screen)
    g_pSwapChain->Present(0, 0);
}

void Dx11Renderer::Release()
{
    CleanDevice();
}
