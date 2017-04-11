cmake_minimum_required(VERSION 3.7)
project(riks_hello_world_cpp)

set(CMAKE_INSTALL_RPATH "$ORIGIN")
set(CMAKE_BUILD_WITH_INSTALL_RPATH TRUE)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${CMAKE_CURRENT_SOURCE_DIR}/cmake/modules)
set(CMAKE_CXX_STANDARD 11)

# Riks Hello World!

set(SOURCE_FILES main.cpp)
link_directories(.)
include_directories(${CMAKE_SOURCE_DIR}/deps/include)
add_executable(riks_hello_world_cpp ${SOURCE_FILES})

# RIKS
target_link_libraries(${PROJECT_NAME} riks)
target_link_libraries(${PROJECT_NAME} cryptobox)
target_link_libraries(${PROJECT_NAME} toolbox)
target_link_libraries(${PROJECT_NAME} outbox)


#openssl
target_link_libraries(${PROJECT_NAME} crypto)
target_link_libraries(${PROJECT_NAME} ssl)



# Boost.Serialization Boost.ASIO
target_link_libraries(${PROJECT_NAME} boost_serialization)
target_link_libraries(${PROJECT_NAME} boost_system)
#find_package(Boost 1.58.0 COMPONENTS serialization system REQUIRED)
#if (Boost_FOUND)
#    include_directories(${Boost_INCLUDE_DIRS})
#    target_link_libraries(${PROJECT_NAME} ${Boost_LIBRARIES})
#endif ()

# Crypto++

find_package(Crypto++)
if (CRYPTO++_FOUND)
    include_directories(${CRYPTO++_INCLUDE_DIR})
    target_link_libraries(${PROJECT_NAME} ${CRYPTO++_LIBRARIES})
endif ()
