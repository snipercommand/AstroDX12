//
// Game.cpp
//

#include "Game.h"
#include "Rendering/RendererDX12.h"
#include "winnt.h"
#include "Maths/MathUtils.h"

extern void ExitGame() noexcept;

using namespace DirectX;

using Microsoft::WRL::ComPtr;

Game::Game() noexcept(false)
{
    //m_deviceResources = std::make_unique<DX::DeviceResources>();
    //m_deviceResources->RegisterDeviceNotify(this);
    m_renderer = std::make_unique<RendererDX12>();
}

Game::~Game()
{
    m_renderer->Shutdown();
    m_renderer.reset();
    //if (m_deviceResources)
    //{
    //    m_deviceResources->WaitForGpu();
    //}
}

// Initialize the Direct3D resources required to run.
void Game::Initialize(HWND window, int width, int height)
{
    OnWindowSizeChanged(width, height);
    m_renderer->Init( window, width, height);

    LoadSceneData();

    BuildConstantBuffers();
    BuildRootSignature();
    BuildShadersAndInputLayout();
    BuildPipelineStateObject();

    m_renderer->FinaliseInit();

    CreateRenderables();

    //m_deviceResources->SetWindow(window, width, height);

    // TODO: Change the timer settings if you want something other than the default variable timestep mode.
    // e.g. for 60 FPS fixed timestep update logic, call:
    /*
    m_timer.SetFixedTimeStep(true);
    m_timer.SetTargetElapsedSeconds(1.0 / 60);
    */

}

#pragma region Frame Update
// Executes the basic game loop.
void Game::Tick(float deltaTime)
{
    Update(deltaTime);
    Render(deltaTime);
}

// Updates the world.
void Game::Update(float deltaTime)
{
}
#pragma endregion

#pragma region Frame Render
// Draws the scene.
void Game::Render(float deltaTime)
{
}
#pragma endregion

#pragma region Message Handlers
// Message handlers
void Game::OnActivated()
{
    // TODO: Game is becoming active window.
}

void Game::OnDeactivated()
{
    // TODO: Game is becoming background window.
}

void Game::OnSuspending()
{
    // TODO: Game is being power-suspended (or minimized).
}

void Game::OnResuming()
{
    // TODO: Game is being power-resumed (or returning from minimize).
}

void Game::OnWindowMoved()
{
    //auto r = m_deviceResources->GetOutputSize();
    //m_deviceResources->WindowSizeChanged(r.right, r.bottom);
}

void Game::OnWindowSizeChanged(int width, int height)
{
    m_screenWidth = width;
    m_screenHeight = height;

    //if (!m_deviceResources->WindowSizeChanged(width, height))
    //    return;

    //CreateWindowSizeDependentResources();

    // TODO: Game window is being resized.
}

// Properties
void Game::GetDefaultSize(int& width, int& height) const noexcept
{
    // TODO: Change to desired default window size (note minimum size is 320x200).
    width = 2048;
    height = 1080;
}
void Game::AddRenderable(std::shared_ptr<IRenderable> renderableObj)
{
    m_sceneRenderables.emplace_back(renderableObj);
}

#pragma endregion
