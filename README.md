# Eldrun-Engine

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

### editorconfig.json

Shared editing and formatting conventions. Purpose:

* makes the editor's formatting consistent
* makes the editor's syntax highlighting consistent
* keeps whitespace, line endings, indentation, and related text-formatting rules consistent across editors.

