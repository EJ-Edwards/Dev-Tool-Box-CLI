cmake_minimum_required(VERSION 3.20)

project(DevToolBoxCLI LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin")
foreach(configuration Debug Release RelWithDebInfo MinSizeRel)
    string(TOUPPER "${configuration}" configuration_upper)
    set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_${configuration_upper}
        "${CMAKE_BINARY_DIR}/bin")
endforeach()

add_executable(cpp_utilities
    src/utils/cpp/utilsmain.cpp
    src/utils/cpp/calculator.cpp
    src/utils/cpp/unit_converter.cpp
)

add_executable(cpp_games
    src/games/cpp/game_main.cpp
    src/games/cpp/maingame.cpp
    src/games/cpp/blackjack.cpp
    src/games/cpp/rock_paper_scissors.cpp
    src/games/cpp/snake.cpp
)

add_executable(dev_tool_box main.cpp)
add_dependencies(dev_tool_box cpp_utilities cpp_games)

set_property(TARGET dev_tool_box PROPERTY
    VS_DEBUGGER_WORKING_DIRECTORY "${CMAKE_SOURCE_DIR}")