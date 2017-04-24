cmake_minimum_required(VERSION 3.7)
project(riks_hello_world_cpp)

set(CMAKE_POSITION_INDEPENDENT_CODE ON)
set(MACOSX_RPATH OFF)

set(CMAKE_INSTALL_RPATH "$ORIGIN")
set(CMAKE_BUILD_WITH_INSTALL_RPATH TRUE)

set(CMAKE_CXX_STANDARD 11)

# Hyker Dependencies

set(HYKER_LIBRARIES ${CMAKE_CURRENT_SOURCE_DIR}/deps)
find_library(RIKS_LIBRARY NAMES riks PATHS ${HYKER_LIBRARIES})

# Riks Hello World!

add_executable(${PROJECT_NAME} "")
target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/deps/include)
target_sources(${PROJECT_NAME} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/main.cpp)
target_link_libraries(${PROJECT_NAME} ${RIKS_LIBRARY} ${CMAKE_DL_LIBS})
