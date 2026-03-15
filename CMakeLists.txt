cmake_minimum_required(VERSION 4.0)
project(pine_engine)

set(CMAKE_CXX_STANDARD 20)

find_package(OpenGL REQUIRED)
find_package(glfw3 CONFIG REQUIRED)
find_package(glad CONFIG REQUIRED)
find_package(glm CONFIG REQUIRED)
find_package(assimp CONFIG REQUIRED)

add_executable(${PROJECT_NAME}
        src/main.cpp
        src/Node.cpp
        src/Scene.cpp
        src/components/MeshComponent.cpp
        src/stb_image.cpp
        src/graphics/AssetManager.cpp
        src/graphics/Shader.cpp
        src/graphics/Shader.h
        src/graphics/Model.cpp
        src/graphics/Model.h
        src/graphics/Mesh.cpp
        src/graphics/Mesh.h
        src/graphics/Camera.cpp
        src/graphics/Camera.h
)

add_custom_command(TARGET pine_engine POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${CMAKE_SOURCE_DIR}/assets
        $<TARGET_FILE_DIR:pine_engine>/assets
)

target_include_directories(${PROJECT_NAME} PRIVATE
        src/
)

target_link_libraries(${PROJECT_NAME} PRIVATE
        OpenGL::GL
        glfw
        glad::glad
        glm::glm
        assimp::assimp
)
