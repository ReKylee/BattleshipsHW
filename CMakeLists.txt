cmake_minimum_required(VERSION 3.10)
project(BattleshipsHW)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# set(CMAKE_CXX_COMPILER clang++)

add_compile_options(
        -pedantic-errors
        -Wall
)

include(FetchContent)
## --- Fetch FTXUI --------------------------------------------------------------
#
set(FETCHCONTENT_UPDATES_DISCONNECTED ON)
set(FETCHCONTENT_QUIET OFF)

FetchContent_Declare(ftxui
        GIT_REPOSITORY https://github.com/arthursonzogni/ftxui.git
        GIT_TAG v5.0.0
        GIT_PROGRESS TRUE
        GIT_SHALLOW TRUE
        EXCLUDE_FROM_ALL
)
FetchContent_MakeAvailable(ftxui)

# ------------------------------------------------------------------------------
# Define source and include directories
set(SOURCE_DIR "${CMAKE_SOURCE_DIR}/src")
set(INCLUDE_DIR "${CMAKE_SOURCE_DIR}/include")

include_directories(${INCLUDE_DIR})

# Gather all source files
file(GLOB_RECURSE SOURCES "${SOURCE_DIR}/*.cpp")

# Create the executable
add_executable(${PROJECT_NAME} ${SOURCES})

## Link ftxui libraries to the executable
target_link_libraries(${PROJECT_NAME}
        PRIVATE ftxui::component
        PRIVATE ftxui::dom
        PRIVATE ftxui::screen

)
