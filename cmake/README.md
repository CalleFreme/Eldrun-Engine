# Build and Configuration with CMake

## cmake/

Support files used by the build system. Purpose:

* keeps the root CMakeLists.txt smaller and cleaner
* centralizes reusable build logic

## cmake/dependencies/

Custom CMake helpers for finding, pinning, or wrapping third-part dependencies.
This folder is useful when a dependency does not slit into the project cleanly
with a single ``add_subdirectory`` or ``find_package`` call.

## cmake/sanitizers/

Reusable CMake snippets for optional sanitizers.
Examples:

* AddressSanitizer
* UndefinedBehaviorSanitizer

This becomes useful when debugging hard-to-find issues.

## cmake/toolschains/

Toolchain definitions for special compilers, platforms, or cross-compiling workflows.

Not every contributor will use this immediately, but it becomes valuable when the project grows beyong one compiler or one platform.

## cmake/warnings/

Compiler warning policy files. Purpose:

* keep warning configuration centralized
* helps enforce a clean codebase without duplication settings in every target.