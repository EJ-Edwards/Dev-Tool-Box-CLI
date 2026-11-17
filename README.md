# Dev Tool Box CLI

A command-line toolbox with utilities and games written in C++ and Python.

## Requirements

- Windows
- Visual Studio Build Tools with the C++ workload
- The CMake Tools extension for VS Code
- Python 3 available on `PATH` as `python`

The Python utilities use only the standard library, so no external Python packages need to be installed.

## Configure and build

1. Open the repository folder in VS Code.
2. Use CMake Tools to configure the project and select the Visual Studio C++ kit.
3. Use **CMake: Build** to build all targets.

The executables are created in `build-cmake/bin`:

- `dev_tool_box.exe` — top-level launcher
- `cpp_utilities.exe` — C++ calculator and unit converters
- `cpp_games.exe` — C++ game menu

## Run

Run `build-cmake\bin\dev_tool_box.exe` from the repository root. The launcher starts Python utilities with `python` and starts the C++ utility and game programs from `build-cmake\bin`.

## Project layout

- `main.cpp` — top-level launcher
- `src/utils/python` — Python utilities
- `src/utils/cpp` — C++ calculator and unit converters
- `src/games/cpp` — C++ games and game menu