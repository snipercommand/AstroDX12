//
// Game.h
//

#pragma once
#include <Common.h>
#include <Rendering/IRenderer.h>
#include <Rendering/IRenderable.h>

class IRenderable;
class Mesh;
namespace AstroTools::Rendering
{
    class ShaderLibrary;
}

// A basic game implementation that creates a D3D12 device and
// provides a game loop.
class Game 
{
public:

    Game() noexcept(false);
    virtual ~Game();

    Game(Game&&) = default;
    Game& operator= (Game&&) = default;

    Game(Game const&) = delete;
    Game& operator= (Game const&) = delete;

    // Initialization and resource management
    void Initialize(HWND window, int width, int height);

    // Basic game loop
    void Tick(float deltaTime);

    // Messages
    void OnActivated();
    void OnDeactivated();
    void OnSuspending();
    void OnResuming();
    void OnWindowMoved();
    void OnWindowSizeChanged(int width, int height);
    void OnMouseDown(WPARAM btnState, int x, int y);
    void OnMouseUp(WPARAM btnState, int x, int y);
    void OnMouseMove(WPARAM mouseBtnState, int x, int y);

    // Properties
    void GetDefaultSize( int& width, int& height ) const noexcept;
    inline float GetAspectRatio() const { return (float)m_screenWidth / (float)m_screenHeight;  }

    void AddRenderable(std::shared_ptr<IRenderable> renderableObj);

    // Scene renderable objects building
    virtual void BuildConstantBuffers() = 0;
    virtual void BuildRootSignature() = 0;
    virtual void BuildShadersAndInputLayout(AstroTools::Rendering::ShaderLibrary& shaderLibrary) = 0;
    virtual void BuildPipelineStateObject() = 0;

protected:
    // Triggered after Initialise, meant for initial state configuration 
    virtual void LoadSceneData() = 0;
    virtual void CreateRenderables() = 0;
    virtual void Update(float deltaTime) = 0;
    virtual void Render(float deltaTime) = 0;

    std::unique_ptr<IRenderer> m_renderer;
    std::vector < std::shared_ptr< IRenderable >> m_sceneRenderables;

private:

    int m_screenWidth;
    int m_screenHeight;

protected:
    POINT m_lastMousePos;
    float m_cameraTheta;
    float m_cameraPhi;
};
