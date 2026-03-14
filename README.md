# Eldrun-Engine

## Getting Started

First, make sure you have [CMake](https://cmake.org/) installed.

The following commands will build Eldrun on Windows:

```bash
cmake --preset windows-vs2022-debug
cmake --build --preset windows-vs2022-debug
```

## Important files

### CmakeLists.txt

Root CMake entry point. Purpose:

* defines the project
* configures global build options
* adds major subdirectories and targets
* acts as the build-system source of truth

This is the main file that makes Eldrun buildable in Visual Studio, Ninja, and other CMake-capable environments.

### CMakePresets.json

Shared CMake configure/build presets. Purpose:

* gives consistens named build configurations
* makes Visual Studio and command-line setup simpler
* reduces onboarding friction

Typical contents:

* windows-vs2022-debug
* windows-vs2022-release
* windows-ninja-debug
* windows-ninja-release
* linux-ninja-debug
* linux-ninja-release

ELDRUN_USE_SYSTEM_SDL=OFF for now, since we have a vendored SDL3.
ELDRUN_ENABLE_INSTALL=OFF for now, since we have a vendored SDL3.

### editorconfig.json

Shared editing and formatting conventions. Purpose:

* makes the editor's formatting consistent
* makes the editor's syntax highlighting consistent
* keeps whitespace, line endings, indentation, and related text-formatting rules consistent across editors.

