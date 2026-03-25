# Eldrun Rendering Architecture

## Purpose

This document defines the rendering direction for Eldrun during the transition from the current SDL-based bootstrap renderer to a more serious engine-owned rendering layer built on top of **bgfx**.

It exists to answer four practical questions:

1. What is rendered by whom?
2. Where does SDL stop and the renderer begin?
3. What should the rest of the engine depend on?
4. How can Eldrun gain portability and rendering momentum without immediately committing to a raw Vulkan or Direct3D 12 backend?

---

## Current State

At the time of writing, Eldrun uses:

- **SDL3** for application startup, window creation, event polling, and the current renderer bootstrap
- `eldrun::platform::Application` as the runtime shell
- `eldrun::runtime::IAppState` as the game/editor state seam
- `eldrun::render::Renderer` as the current frame clear/present wrapper around `SDL_Renderer`

### Current responsibilities

#### `Application`

Owns:

- SDL initialization and shutdown
- window creation and destruction
- main loop
- event polling
- timing / timestep calculation
- app-state orchestration
- renderer lifecycle orchestration

#### `IAppState`

Owns:

- executable-specific behavior
- per-frame update logic
- per-frame render requests
- startup / shutdown hooks for the active mode or app state

#### `Renderer`

Currently owns:

- SDL renderer creation
- clear color state
- frame begin / end
- presentation

### Current frame flow

```text
main()
  -> Application::run()
      -> initialize()
          -> SDL_Init
          -> SDL_CreateWindow
          -> Renderer::initialize(window)
          -> state->on_enter()
      -> while (running)
          -> process_events()
          -> tick(delta_time)
          -> render_frame()
              -> renderer.begin_frame()
              -> state->render(renderer)
              -> renderer.end_frame()
      -> shutdown()
```

This is a good bootstrap, but it is intentionally temporary.

The current renderer is useful for proving:

- startup path correctness
- runtime ownership structure
- state/render separation
- frame lifecycle boundaries

It is **not** yet the long-term rendering architecture.

---

## Rendering Direction

The long-term design goal is:

- keep **SDL** responsible for platform/runtime concerns
- keep **Eldrun** responsible for renderer architecture and engine-level abstractions
- keep **bgfx** as a backend implementation detail, not the public identity of the engine

That means Eldrun should not become “a bgfx app.”
It should become **an engine with its own renderer API**, where bgfx is the first serious backend.

---

## Why bgfx in Eldrun

For Eldrun, bgfx is valuable because it lets the project move into a more serious rendering phase without forcing the engine to begin with raw backend implementation in Vulkan or Direct3D 12.

The key idea is:

- Eldrun should own the renderer-facing architecture
- bgfx should own the backend-specific graphics API work

This lets Eldrun focus on:

- render passes and views
- frame structure
- scene submission
- resource ownership at the engine level
- debug drawing
- mesh/material/shader abstractions
- editor and game integration

Instead of first spending major effort on:

- Vulkan command submission plumbing
- Direct3D 12 descriptor heap management
- explicit backend synchronization design
- multi-API swapchain/device bring-up
- backend-specific debug and compatibility work

---

## Design Rule

**The rest of the engine should depend on Eldrun render interfaces, not on bgfx directly.**

Good:

```text
Sandbox / Editor / World / Tools
            |
            v
        Eldrun Renderer API
            |
            v
         BgfxRenderer
            |
            v
   D3D12 / Vulkan / Metal / OpenGL
```

Bad:

```text
Sandbox -> bgfx
Editor  -> bgfx
World   -> bgfx
Tools   -> bgfx
```

The first approach preserves engine ownership.
The second leaks backend details everywhere and makes future change harder.

---

## Boundary: Where SDL Stops and bgfx Begins

### SDL should own

- application startup
- window creation
- event polling
- input event collection
- runtime shell plumbing
- access to platform/native window handles

### bgfx should own

- graphics backend initialization
- backend device/context setup
- API-specific rendering work
- presentation backend details
- backend command submission internals

### Eldrun should own

- renderer-facing engine abstractions
- render views / passes
- scene submission structure
- material and shader asset concepts
- render resource handles
- debug drawing interfaces
- renderer statistics surfaced to engine tools

### Handoff flow

```text
main()
  -> Application
      -> SDL_Init
      -> SDL_CreateWindow
      -> extract native window handle
      -> bgfx::setPlatformData(...)
      -> bgfx::init(...)
      -> main loop
          -> SDL events
          -> app state update
          -> renderer submission
          -> bgfx::frame()
```

---

## Recommended Eldrun Renderer Structure

The engine-facing renderer API should stay **small, stable, and engine-owned**.

### Engine-facing interface

```cpp
// eldrun/render/renderer.hpp
namespace eldrun
{
    struct RendererConfig
    {
        uint32_t width = 1280;
        uint32_t height = 720;
        bool vsync = true;
        bool debug = true;
    };

    struct FrameContext
    {
        float deltaTime = 0.0f;
        uint64_t frameIndex = 0;
    };

    class IRenderer
    {
    public:
        virtual ~IRenderer() = default;

        virtual bool initialize(void* nativeWindowHandle,
                                void* nativeDisplayHandle,
                                const RendererConfig& config) = 0;
        virtual void shutdown() = 0;

        virtual void resize(uint32_t width, uint32_t height) = 0;

        virtual void beginFrame(const FrameContext& frame) = 0;
        virtual void endFrame() = 0;

        virtual void beginWorldView() = 0;
        virtual void endWorldView() = 0;

        virtual void clear(float r, float g, float b, float a) = 0;

        virtual void drawDebugGrid() = 0;
        virtual void drawDebugLine(/*...*/) = 0;
        virtual void drawMesh(/* mesh, material, transform */) = 0;

        virtual void drawUi() = 0;

        virtual const char* backendName() const = 0;
    };
}
```

### Intent of this interface

This interface is deliberately:

- **not Vulkan-shaped**
- **not Direct3D 12-shaped**
- **not bgfx-shaped**
- **not SDL-shaped**

It is meant to be **Eldrun-shaped**.

That preserves control over the architecture while still allowing a bgfx implementation underneath.

---

## bgfx-backed implementation

Then Eldrun provides a concrete backend implementation.

```cpp
// eldrun/render/backends/bgfx_renderer.hpp
namespace eldrun
{
    class BgfxRenderer final : public IRenderer
    {
    public:
        bool initialize(void* nativeWindowHandle,
                        void* nativeDisplayHandle,
                        const RendererConfig& config) override;
        void shutdown() override;

        void resize(uint32_t width, uint32_t height) override;

        void beginFrame(const FrameContext& frame) override;
        void endFrame() override;

        void beginWorldView() override;
        void endWorldView() override;

        void clear(float r, float g, float b, float a) override;

        void drawDebugGrid() override;
        void drawDebugLine(/*...*/) override;
        void drawMesh(/*...*/) override;

        void drawUi() override;

        const char* backendName() const override;

    private:
        RendererConfig m_config{};
        uint32_t m_width = 0;
        uint32_t m_height = 0;
        bool m_initialized = false;
    };
}
```

This class is the place where bgfx types and calls are allowed to exist freely.

That should **not** be true of the rest of the engine.

---

## Application Layer Recommendation

`Application` should remain generic and lifecycle-focused.

```cpp
class Application
{
public:
    bool initialize();
    void run();
    void shutdown();

private:
    void processEvents();
    void tick(float dt);

private:
    std::unique_ptr<IAppState> m_appState;
    std::unique_ptr<IRenderer> m_renderer;
    SDL_Window* m_window = nullptr;
    bool m_running = false;
};
```

### `Application` responsibilities

- initialize SDL
- create the window
- acquire native platform handles from SDL
- construct the concrete renderer implementation
- initialize the renderer
- own the main loop
- route resize events
- call app-state update and render hooks

The application layer should **coordinate** rendering, not become the renderer.

---

## App State Boundary Recommendation

`IAppState` should remain the behavior seam between executable-specific logic and the shared engine runtime shell.

```cpp
class IAppState
{
public:
    virtual ~IAppState() = default;

    virtual void onEnter() = 0;
    virtual void onExit() = 0;

    virtual void update(float dt) = 0;
    virtual void render(IRenderer& renderer) = 0;

    virtual void onResize(uint32_t width, uint32_t height) = 0;
};
```

This makes it easy to support:

- `SandboxAppState`
- future `EditorAppState`
- future mode/state transitions inside one runtime shell

The app state decides **what should be drawn**.
The renderer decides **how it is drawn**.

---

## Proposed `engine/render/` Structure

```text
engine/render/
├─ renderer.hpp                 // IRenderer
├─ renderer_config.hpp
├─ render_types.hpp             // handles, ids, enums
├─ render_stats.hpp
├─ backends/
│  └─ bgfx_renderer.hpp/.cpp
├─ scene/
│  ├─ camera.hpp
│  ├─ render_scene.hpp
│  ├─ visible_set.hpp
│  └─ debug_draw.hpp
├─ resources/
│  ├─ mesh.hpp
│  ├─ texture.hpp
│  ├─ shader.hpp
│  ├─ material.hpp
│  └─ gpu_buffer.hpp
└─ passes/
   ├─ world_pass.hpp
   ├─ debug_pass.hpp
   └─ ui_pass.hpp
```

### Intent of this structure

- `renderer.hpp` defines the engine-owned boundary
- `backends/` contains implementation details
- `scene/` holds render-side scene organization
- `resources/` defines render resource concepts
- `passes/` defines frame structure and rendering phases

This keeps bgfx from becoming the architecture.
It remains only one backend inside the architecture.

---

## Concrete Integration Flow

```text
Executable (sandbox/editor)
    |
    v
Application
    |- initializes SDL
    |- creates SDL window
    |- gets native window handle
    |- creates BgfxRenderer as IRenderer
    |- owns IAppState
    |
    v
BgfxRenderer::initialize(...)
    |- bgfx::setPlatformData(...)
    |- bgfx::init(...)
    |- configure resolution / vsync / debug
    |- set default views
    |
    v
Main loop
    |- SDL_PollEvent(...)
    |- handle quit / resize / input
    |- appState.update(dt)
    |- renderer.beginFrame(...)
    |- appState.render(renderer)
    |- renderer.endFrame()
    |
    v
BgfxRenderer::endFrame()
    |- bgfx::frame()
```

---

## What Should Not Leak Out of `BgfxRenderer`

Try hard to keep these out of general engine code:

- `bgfx::VertexLayout`
- `bgfx::ProgramHandle`
- `bgfx::TextureHandle`
- `bgfx::setState`
- `bgfx::submit`
- backend-specific capability checks everywhere
- raw bgfx view IDs scattered through gameplay or tool code

Instead, prefer Eldrun-owned concepts such as:

- `MeshHandle`
- `TextureHandle`
- `MaterialHandle`
- `RenderViewId`
- `RenderStats`
- `RendererCapabilities`

This is the difference between:

- **using bgfx as an implementation detail**, and
- **letting bgfx define the whole renderer vocabulary**

The first is the intended design.

---

## A Good First Practical bgfx Milestone

The first serious renderer milestone should be small and disciplined.

### `Application` owns

- SDL init/shutdown
- window
- main loop
- event polling
- resize handling
- renderer and app-state orchestration

### `BgfxRenderer` owns

- bgfx init/shutdown
- view setup
- clear color
- frame begin/end
- one world view
- one debug pass
- basic stats readback

### `SandboxAppState` owns

- camera parameters
- sandbox update logic
- asking the renderer to draw a grid / axes / test primitive or mesh

That is enough for:

- a clear background
- a camera
- a debug grid
- a first 3D scene foothold
- on-screen stats or debug information

It is also enough to demonstrate the new renderer boundary clearly.

---

## Example Application Initialization Sketch

```cpp
bool Application::initialize()
{
    // 1. SDL init
    // 2. create window
    // 3. query native handle(s) from SDL
    // 4. create renderer = std::make_unique<BgfxRenderer>()
    // 5. renderer->initialize(nativeWindow, nativeDisplay, config)
    // 6. appState->onEnter()
    return true;
}
```

## Example Main Loop Sketch

```cpp
while (m_running)
{
    processEvents();

    const float dt = /* timestep */;
    m_appState->update(dt);

    FrameContext frame{};
    frame.deltaTime = dt;
    frame.frameIndex = m_frameIndex++;

    m_renderer->beginFrame(frame);
    m_appState->render(*m_renderer);
    m_renderer->endFrame();
}
```

## Example Sandbox Render Sketch

```cpp
void SandboxAppState::render(IRenderer& renderer)
{
    renderer.beginWorldView();
    renderer.clear(0.08f, 0.09f, 0.12f, 1.0f);
    renderer.drawDebugGrid();
    // later: renderer.drawMesh(...)
    renderer.endWorldView();
}
```

This creates a clean responsibility split:

- the app state decides **what to render**
- the renderer decides **how to render it**
- bgfx decides **which backend actually executes it**

---

## Current vs Target Design

### Current

- `Renderer` wraps `SDL_Renderer`
- `Application` owns the concrete renderer directly
- `IAppState::render()` receives the current renderer type
- rendering is still bootstrap-oriented

### Target

- Eldrun introduces an engine-owned `IRenderer`
- `Application` owns a renderer through that interface
- `BgfxRenderer` becomes the first serious implementation
- SDL remains responsible for window/runtime duties
- app states render through Eldrun abstractions rather than through SDL or bgfx directly

This means the migration path is evolutionary, not destructive.

Eldrun does **not** need to throw away the current bootstrap.
It needs to replace the current renderer seam with a stronger one.

---

## Migration Recommendation

A practical migration path would look like this:

1. keep the current SDL bootstrap working
2. introduce an `IRenderer` interface
3. adapt `Application` to own a renderer behind that interface
4. adapt `IAppState::render()` to use the interface
5. preserve the current SDL renderer behind a temporary implementation if helpful
6. add `BgfxRenderer` as the next backend
7. move sandbox rendering toward world-view and debug-draw calls
8. start introducing camera, mesh, material, and simple pass concepts

This reduces risk while keeping progress visible.

---

## What This Design Optimizes For

This rendering direction is meant to optimize for:

- strong engine-owned boundaries
- a clean separation of platform and renderer responsibilities
- practical portability
- momentum toward a visible 3D rendering milestone
- learning value at the renderer architecture level
- freedom to grow into more advanced rendering systems later

It intentionally does **not** optimize for:

- immediate raw Vulkan or Direct3D 12 exposure everywhere
- backend-specific maximization before the engine architecture is stable
- letting third-party API vocabulary spread through the codebase

---

## Summary

The rendering direction for Eldrun should be:

- **SDL for platform and runtime shell**
- **Eldrun-owned interfaces for renderer architecture**
- **bgfx as a backend implementation detail**
- **app states expressing render intent through engine abstractions**

In short:

> Eldrun should not be “a bgfx project.”
> It should be an engine with its own renderer boundary, where bgfx is the first serious backend.

That gives the project a good balance of:

- portability
- momentum
- architectural ownership
- learning value
- future flexibility

