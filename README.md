# Eldrun Engine

Eldrun is a C++ game engine project focused on **3D-first development**, with **2D support planned later**, aimed at games such as:

- open-world or zone-based RPGs
- RTS and city-building games
- future multiplayer-capable simulation-heavy games

The current phase of the project is **engine bootstrap**: repository structure, CMake, SDL-based application startup, and the first runnable sandbox/editor executables.

---

## Current Status

Eldrun currently has:

- a structured repository layout
- CMake-based build configuration
- shared CMake presets
- vendored SDL3 integration
- a minimal `core` module
- a minimal `platform` module
- a runnable **sandbox** executable
- a runnable **editor** executable

At this stage, Eldrun is proving its foundations:

- build system
- runtime startup
- window creation
- application loop
- development workflow

Rendering, asset loading, gameplay systems, and tooling will be added incrementally.

---

## Goals

Eldrun is being built to support:

- **C++** as the implementation language
- **3D-first engine development**
- **later 2D support**
- **world-driven RPGs**
- **RTS / city-builder simulation**
- **clean engine/game separation**
- **future editor and multiplayer support**
- **good developer experience across environments**

Eldrun is **not** intended to be a universal engine for every possible genre, yet.

---

## Repository Structure

```text
Eldrun-Engine/
├─ CMakeLists.txt
├─ CMakePresets.json
├─ README.md
├─ LICENSE
├─ .gitignore
├─ .editorconfig
├─ docs/
├─ cmake/
├─ external/
│  └─ SDL/
├─ engine/
│  ├─ core/
│  ├─ platform/
│  ├─ render/
│  ├─ runtime/
│  ├─ assets/
│  ├─ world/
│  ├─ gameplay/
│  ├─ tools/
│  └─ net/
├─ editor/
│  └─ eldrun_editor/
├─ games/
│  └─ sandbox/
├─ tests/
├─ samples/
└─ assets/
```

### Key directories

#### `engine/`

Reusable engine code.

Examples:

- core utilities
- platform/bootstrap code
- rendering systems
- world/simulation systems
- future networking support

#### `games/`

Game projects built on top of Eldrun.

Right now this includes:

- `sandbox/` — the first runtime testbed for the engine

#### `editor/`

The future editor application.

Right now this contains:

- `eldrun_editor/` — an early executable shell running on the same platform layer as the sandbox

#### `external/`

Vendored third-party dependencies.

Right now:

- `SDL/` — vendored SDL3 source

#### `docs/`

Architecture, bootstrap, and design documentation.

#### `cmake/`

CMake helper modules and project-specific build logic.

---

## Requirements

### Minimum tools

To build Eldrun, you should have:

- **Git**
- **CMake**
- a **C++20-capable compiler**
- the appropriate development environment for your platform

### Recommended on Windows

- **Visual Studio 2022** with the C++ workload installed
- **CMake**
- **Git**
- optionally **VS Code** with:
  - CMake Tools
  - C/C++ extension

---

## Dependency Setup

Eldrun currently uses a **vendored SDL3** setup.

That means SDL3 is expected to exist inside:

```text
external/SDL
```

### Initialize or update submodules

If you are cloning the repository fresh, run:

```bash
git submodule update --init --recursive
```

If SDL has not been added yet in your local clone, make sure the `external/SDL` submodule is present before configuring the project.

### Important current build assumptions

For now, Eldrun uses:

- `ELDRUN_USE_SYSTEM_SDL=OFF`
- `ELDRUN_ENABLE_INSTALL=OFF`

This is intentional for the current bootstrap phase:

- SDL3 is vendored as a subproject
- install/export packaging is deferred until dependency strategy is more mature

---

## Build Presets

Eldrun uses `CMakePresets.json` as the shared build entry point.

This keeps setup consistent across:

- Visual Studio
- VS Code
- command-line CMake
- Ninja-based workflows
- future CI

### Current presets

Typical presets include:

- `windows-vs2022-debug`
- `windows-vs2022-release`
- `windows-ninja-debug`
- `windows-ninja-release`
- `linux-ninja-debug`
- `linux-ninja-release`

---

## Building Eldrun

### Windows with Visual Studio generator

From the repository root:

```bash
cmake --preset windows-vs2022-debug
cmake --build --preset windows-vs2022-debug
```

This configures and builds the project using the Visual Studio 2022 generator.

#### Build a specific target

To build only the sandbox:

```bash
cmake --build --preset windows-vs2022-debug --target eldrun_sandbox --config Debug
```

To build only the editor:

```bash
cmake --build --preset windows-vs2022-debug --target eldrun_editor --config Debug
```

### Windows with Ninja

For VS Code or command-line workflows, Ninja is often the smoother choice:

```bash
cmake --preset windows-ninja-debug
cmake --build --preset windows-ninja-debug
```

#### Why use Ninja in VS Code?

The Ninja workflow is often simpler for:

- IntelliSense integration
- compile command generation
- build output layout
- command-line iteration

Visual Studio users may still prefer the Visual Studio preset.

---

## Running Eldrun

### Sandbox

After a successful build with the Visual Studio preset, the sandbox executable is typically located under a path similar to:

```text
out/build/windows-vs2022-debug/games/sandbox/Debug/eldrun_sandbox.exe
```

Run it from PowerShell:

```powershell
.\out\build\windows-vs2022-debug\games\sandbox\Debug\eldrun_sandbox.exe
```

### Editor

The editor executable is typically located under a path similar to:

```text
out/build/windows-vs2022-debug/editor/eldrun_editor/Debug/eldrun_editor.exe
```

Run it from PowerShell:

```powershell
.\out\build\windows-vs2022-debug\editor\eldrun_editor\Debug\eldrun_editor.exe
```

---

## SDL Runtime DLL on Windows

Eldrun currently builds against **shared SDL3** on Windows.

That means the SDL runtime DLL must be available next to the executable at runtime.

This is currently handled by a post-build copy step in the executable targets so that `SDL3.dll` is copied to the correct output directory automatically.

If an executable launches but immediately appears to do nothing, check whether `SDL3.dll` is present next to the executable.

---

## Development Workflow

A good first local workflow is:

1. clone the repository
2. initialize submodules
3. configure with a preset
4. build the sandbox
5. run the sandbox
6. verify a window opens and the app exits cleanly

### Example

```bash
git submodule update --init --recursive
cmake --preset windows-vs2022-debug
cmake --build --preset windows-vs2022-debug --target eldrun_sandbox --config Debug
```

Then run:

```powershell
.\out\build\windows-vs2022-debug\games\sandbox\Debug\eldrun_sandbox.exe
```

---

## Important Files

### `CMakeLists.txt`

Root CMake entry point.

Purpose:

- defines the project
- configures global build options
- adds major subdirectories and targets
- acts as the build-system source of truth

This is the main file that makes Eldrun buildable in Visual Studio, Ninja, and other CMake-capable environments.

### `CMakePresets.json`

Shared CMake configure/build presets.

Purpose:

- gives consistent named build configurations
- makes Visual Studio and command-line setup simpler
- reduces onboarding friction

### `.editorconfig`

Shared editing and formatting conventions.

Purpose:

- keeps whitespace, line endings, indentation, and related formatting rules consistent across editors
- helps keep contributions cleaner across Visual Studio, VS Code, and other environments

### `.gitignore`

Tells Git which generated or machine-specific files should not be committed.

Examples:

- build folders
- IDE-local state
- generated caches
- runtime artifacts

---

## Current Architecture Direction

Eldrun currently separates responsibilities like this:

- **SDL3** handles platform concerns such as windowing, input, and application bootstrap
- **engine/core** contains foundational engine utilities
- **engine/platform** contains the application/runtime entry path
- **games/sandbox** is the first engine-hosted executable
- **editor/eldrun_editor** is a second executable built on the same engine foundation

This is intentional: the goal is to keep engine systems modular and reusable, while allowing games and tools to grow on top of them.

---

## What Comes Next

The next major milestones are:

- current state: shared runtime shell + renderer bootstrap
- next state: bgfx backend transition + first 3D scene
- start building toward a true gameplay prototype

---

## Contributing to the Codebase

When contributing, try to follow these rules:

- keep engine code reusable
- keep game-specific code inside `games/`
- avoid leaking third-party APIs everywhere
- prefer target-based CMake changes over global flag hacks
- keep the repository buildable from presets
- update docs when architecture or workflow changes

---

## Naming and Style Conventions

### Header extensions

Eldrun uses:

- `.hpp` for C++ headers
- `.cpp` for C++ source files

This keeps project-owned C++ code visually distinct and avoids ambiguity with C-style headers.

### Include style

Prefer includes like:

```cpp
#include "eldrun/core/log.hpp"
#include "eldrun/platform/application.hpp"
```

rather than short ambiguous include names.

This makes ownership clearer and scales better as the project grows.

---

## Troubleshooting

### Configure succeeds, but IntelliSense cannot find headers

If the build succeeds but the editor shows include errors, the problem is often editor configuration rather than CMake itself.

For VS Code:

- make sure CMake Tools is using the correct preset
- prefer the Ninja preset for day-to-day VS Code work
- reconfigure after changing CMake files

### Built executable does not appear to run

Check:

- whether the correct executable path is being used
- whether `SDL3.dll` is present next to the executable
- whether the correct build configuration (`Debug`) was built

### Visual Studio preset vs Ninja preset

Both are supported, but:

- Visual Studio presets are natural for Visual Studio
- Ninja presets are often smoother in VS Code

---

## License

See `LICENSE` for the current project license.

---

## Project State Summary

Eldrun is early, and currently, it now has:

- a strong repository layout
- a working CMake setup
- a working dependency integration path
- a working runtime bootstrap
- runnable executables
- a clear architectural direction

That makes this the right time to continue building outward into rendering, world systems, and actual game prototyping.
