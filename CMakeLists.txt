cmake_minimum_required(VERSION 3.7)
project(riks_hello_world_cpp)

set(CMAKE_POSITION_INDEPENDENT_CODE ON)
set(MACOSX_RPATH OFF)

set(CMAKE_INSTALL_RPATH "$ORIGIN")
set(CMAKE_BUILD_WITH_INSTALL_RPATH TRUE)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${CMAKE_CURRENT_SOURCE_DIR}/cmake/modules)
set(CMAKE_CXX_STANDARD 11)


# Riks Hello World!

# do we need this ????????????/
#include_directories(${CMAKE_SOURCE_DIR}/deps/include)

set(SOURCE_FILES ${PROJECT_SOURCE_DIR}/main.cpp)

include_directories(${PROJECT_SOURCE_DIR}/deps/include)
link_directories(deps)
add_executable(riks_hello_world_cpp ${SOURCE_FILES})
target_include_directories(riks_hello_world_cpp PUBLIC ${PROJECT_SOURCE_DIR}deps/include)
target_link_libraries(riks_hello_world_cpp riks cryptobox toolbox outbox )#crypto ssl cryptopp)


# RIKS
#link_directories(deps)
#link_directories(build)
#target_include_directoriees
#target_link_libraries(${PROJECT_NAME} cryptobox)
#target_link_libraries(${PROJECT_NAME} toolbox)
#target_link_libraries(${PROJECT_NAME} outbox)


#openssl
#target_link_libraries(${PROJECT_NAME} crypto)
#target_link_libraries(${PROJECT_NAME} ssl)

#crypto++
#target_link_libraries(${PROJECT_NAME} cryptopp)



# Boost.Serialization Boost.ASIO
#target_link_libraries(${PROJECT_NAME} boost_serialization)
#target_link_libraries(${PROJECT_NAME} boost_system)
