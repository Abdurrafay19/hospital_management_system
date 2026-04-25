cmake_minimum_required(VERSION 3.28)
project(MediCore LANGUAGES CXX)

# 1. Organize output files
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

# 2. Fetch SFML 3.1.0 (The working method)
include(FetchContent)
FetchContent_Declare(SFML
    GIT_REPOSITORY https://github.com/SFML/SFML.git
    GIT_TAG 3.1.0
    GIT_SHALLOW ON
    EXCLUDE_FROM_ALL
    SYSTEM)
FetchContent_MakeAvailable(SFML)

# 3. Automatically find all your OOP files (.cpp and .hpp)
# This means you don't have to edit this file every time you add a new class!
file(GLOB_RECURSE SOURCES "src/*.cpp" "src/*.hpp")

# 4. Create the executable using the project name
add_executable(${PROJECT_NAME} ${SOURCES})

# 5. Compiler Settings
target_compile_features(${PROJECT_NAME} PRIVATE cxx_std_17)

# 6. Link SFML components 
# Added Audio and Window explicitly for a more robust OOP project
target_link_libraries(${PROJECT_NAME} PRIVATE 
    SFML::Graphics 
    SFML::Audio 
    SFML::Window 
    SFML::System
)

# 7. IDE convenience (Sets MediCore as the "Play" button target)
set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT ${PROJECT_NAME})