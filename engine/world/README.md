# Eldrun World Module

The `engine/world/` module contains Eldrun’s runtime **world representation**.

This is where the engine defines what exists in the game world, how world state is stored, and how runtime objects are identified and organized.

It is one of the most important modules in Eldrun because both of the engine’s target directions depend on it heavily:

- large-world / exploration-heavy RPGs
- simulation-heavy RTS and city-building games

This module is **not** the renderer, **not** the platform layer, and **not** the asset pipeline. It is the part of the engine that answers questions like:

- What is an entity?
- How is world state stored?
- How are transforms, ownership, and lifetime tracked?
- How do we represent objects in a world without tying everything to rendering or UI?
- How can the world scale toward streaming, simulation, save/load, and multiplayer later?

---

## Responsibilities

The world module is responsible for:

- entity identity
- world/scene runtime containers
- transforms and spatial placement
- object lifetime and ownership boundaries
- component-like runtime state storage
- world partitioning or streaming boundaries later
- serialization boundaries for save/load later
- clear separation between simulation state and presentation state

It should provide a stable foundation for higher-level systems without assuming too much about any one game.

---

## What belongs here

Typical things that belong in `engine/world/`:

- `EntityId` or equivalent stable runtime identifiers
- world container types such as `World`
- transform data
- parent/child spatial relationships if used
- component storage or ECS-friendly data structures
- lookup/query support for world objects
- world creation/destruction logic
- world-level serialization boundaries
- world partition / zone / cell structures later

---

## What does **not** belong here

The world module should stay focused.

These usually belong elsewhere:

### Rendering backend details

Do **not** put raw bgfx or backend-specific rendering logic here.

The world may store render-related data such as:

- mesh references
- light data
- camera components

But the actual rendering process belongs in `engine/render/`.

### Platform and input code

Windowing, SDL event handling, and raw input processing belong in `engine/platform/`.

### Asset import/cooking logic

Asset import, conversion, and resource loading infrastructure belong in `engine/assets/`.

### Editor tooling UI

ImGui panels, inspectors, and developer tools belong in `engine/tools/` or the editor project.

### Game-specific behavior

If something exists only for one game prototype, it probably belongs under `games/`, not here.

---

## Design direction

Eldrun is **ECS-friendly**, but not committed to a pure ECS-everywhere architecture.

The intended direction is:

- stable entity IDs
- structured runtime data
- explicit system/update phases
- incremental ECS-style adoption where it clearly helps

That means this module should support:

- clean world state storage
- efficient access patterns where needed
- future simulation scaling
- future networking-friendly state ownership

But it should avoid overengineering too early.

---

## Core principles

### 1. Stable identity

World objects should have identities that do not depend on raw memory addresses.

Why this matters:

- save/load
- future multiplayer
- editor references
- debugging
- runtime lookup

### 2. Structured state

World data should be stored in deliberate structures rather than hidden in deep inheritance trees or scattered ownership chains.

Why this matters:

- maintainability
- performance
- serialization
- simulation clarity

### 3. Simulation first, presentation second

The world module should model authoritative runtime state, not visual polish.

Examples of simulation-oriented state:

- transform
- faction/team
- health
- inventory ownership
- navigation state
- interaction flags

Examples of presentation-oriented state that should stay elsewhere or remain clearly separated:

- screen shake
- temporary VFX handles
- UI animation state
- editor-only display flags

### 4. Explicit boundaries

The world module should make ownership and lifetime easier to understand, not harder.

A contributor should be able to answer:

- when is it created?
- when is it destroyed?
- what other systems are allowed to reference it?

### 5. Gradual scaling

This module should start simple and become more sophisticated as Eldrun’s game needs grow.

The first versions do not need:

- a giant abstract ECS framework
- advanced streaming
- full replication support
- every type of query system

They do need:

- clean foundations
- consistency
- room to grow

---

## Relationship to other modules

### `engine/gameplay/`

`engine/gameplay/` defines how game logic plugs into the engine and how systems update.

A useful mental model is:

- `engine/world/` = what exists
- `engine/gameplay/` = how it changes

### `engine/render/`

The world stores data the renderer may consume, but the renderer should query or read that data through proper boundaries.

Typical flow:

`world state -> render frontend -> renderer backend`

Not:

`world state -> raw backend calls everywhere`

### `engine/assets/`

The world module should refer to assets through handles, IDs, or references rather than owning import logic directly.

### `engine/net/`

Later, networking may depend heavily on the world module for:

- stable IDs
- replication boundaries
- authority rules
- snapshot or delta support

This is one reason the world model should remain disciplined from the beginning.

---

## Early implementation priorities

The first version of this module should focus on a few foundational ideas:

- stable `EntityId`
- a `World` container
- transform representation
- basic creation and destruction of entities
- simple component-like storage
- clear update-safe access patterns
- serialization awareness, even if save/load comes later

Do not try to solve every future world problem in the first iteration.

---

## Example future contents

This folder may eventually contain files or subfolders such as:

```text
engine/world/
├─ README.md
├─ entity_id.h
├─ world.h
├─ world.cpp
├─ transform.h
├─ transform.cpp
├─ components/
├─ queries/
├─ serialization/
└─ partition/
