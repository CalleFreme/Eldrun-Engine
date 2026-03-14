# External dependencies

## external/

Pinned third-party source dependencies. Purpose:

* makes dependency ownership explicit
* support reproducible onboarding
* makes it obvious which external project Eldrun depends on

Recommended contents:

* SDL3
* bgfx
* bx
* bimg
* Dear ImGui

Important rule: Do not casually modify code under external/ unless maintaining a deliberate fork.

## external/SDL/

SDL3 source or submodule. Used for:

* window creation
* input
* platform-facing application behavior

## external/bgfx/

bgfx source or submodule. Used for:

* renderer abstraction layer
* rendering backend integration

## external/bx/ and external/bimg/

Companion libraries used by bgfx. bgfx depends on them as part of its ecosystem.

## external/imgui/

Dear ImGui source or submodule. Used for:

* developer tools
* debug overlays
* temporary editor-like UI