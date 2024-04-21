cmake_minimum_required(VERSION 3.19.0)

project(myapp)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)

include(FetchContent)

FetchContent_Declare(json URL https://github.com/nlohmann/json/releases/download/v3.11.3/json.tar.xz)
FetchContent_MakeAvailable(json)

find_package(Qt6 COMPONENTS Widgets Core Gui REQUIRED)

add_executable(TextEditor.exe main.cpp MainWindow.cpp)

target_link_libraries(TextEditor PRIVATE Qt6::Widgets Qt6::Core Qt6::Gui nlohmann_json::nlohmann_json)
