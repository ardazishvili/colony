cmake_minimum_required(VERSION 3.10)
set (CMAKE_CXX_STANDARD 20)
set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g")
project(Colony)

find_package(spdlog CONFIG REQUIRED)

link_directories(fig/cbuild)

file(GLOB_RECURSE SOURCE_FILES figImpl/*.cpp helpers/*.cpp logic/*.cpp view/*.cpp main.cp main.cpp)
file(GLOB_RECURSE HEADER_FILES figImpl/*.h helpers/*.h logic/*.h view/*.h)
add_executable(colony ${SOURCE_FILES} ${HEADER_FILES})
target_include_directories(colony PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})
target_include_directories(colony PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/fig)

target_link_libraries(colony fig glfw dl GL GLEW assimp pthread spdlog::spdlog)
file(COPY assets DESTINATION ${CMAKE_BINARY_DIR})
file(COPY shaders DESTINATION ${CMAKE_BINARY_DIR})
file(COPY config.json DESTINATION ${CMAKE_BINARY_DIR})
