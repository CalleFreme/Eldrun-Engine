# Engine Source Tree

## engine/

Reusable engine code. Purpose:

* contains systems intended to be used by multiple games
* should avoid game-specific content and logic

## engine/core/

Foundational utilities and low-level shared systems.

Typical contents:

* logging
* assertions
* time utilities
* memory helpers
* version information
* common types

This is the layer most other engine modules should depend on. Should be lightweight and stable.

## engine/platform/

Platform-facing runtime code. Isolates OS and window/input concerns from higher-level engine systems.

Typical contents:

* SDL bootstrap
* window creation
* input abstraction
* event pumping
* platform services

## engine/render/

Renderer frontend and rendering systems.

Typical contents:

* camera representation
* render passes/views
* material abstraction
* mesh submission
* render debug utilities
* bgfx integration layer

This folder shoudl represent Eldrun's rendering model, not raw backend code springled through the engine.

## engine/assets/

Asset loading, resource handling, and import/cooking infrastructure.

Typical contents:

* asset handles
* resource cache
* loaders
* import pipeline logic
* metadata definitions

Separates runtime asset use from ad hoc file loading. Supports future hot reload and asset cooking.

## engine/world/

World representation and runtime state containers. Partly ECS-based.

Typical contents:

* scene/world objects
* transforms
* world partition concepts
* streaming boundaries
* serialization boundaries

This folder becomes increasingly important for RPG and large-world development.

The world is currently not represented as a pure ECS, but rather a lightweight custom ECS-ish world model.

## engine/gameplay/

Reusable gameplay-facing framework code.

Ttypical contents:

* application/game hooks
* system integration
* command/event interfaces
* update scheduling helpers

Provides a structured way for game code to plug into the engine.

## engine/tools/