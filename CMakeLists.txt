cmake_minimum_required(VERSION 3.7.0)
project(riks)

add_definitions(-DHYKER_EXPORTS=1)

if (CMAKE_COMPILER_IS_GNUCC OR CMAKE_COMPILER_IS_GNUCXX)
    # Using GCC
    set(CMAKE_SHARED_LINKER_FLAGS "-Wl,--no-undefined")
    set(CMAKE_C_FLAGS   "-Os -s")
    set(CMAKE_CXX_FLAGS "-Os -s -Wall -Wextra")
elseif (CMAKE_CXX_COMPILER_ID MATCHES "Clang")
    # Using Clang
    set(CMAKE_C_FLAGS   "-Os -fembed-bitcode")
    set(CMAKE_CXX_FLAGS "-Os -fembed-bitcode")
elseif (CMAKE_CXX_COMPILER_ID STREQUAL "Intel")
    # Using Intel C++
elseif (CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
    # Using Visual Studio C++
endif ()

set(MACOSX_RPATH OFF)
set(CMAKE_POSITION_INDEPENDENT_CODE ON)
set(CMAKE_BUILD_RPATH "$ORIGIN")
set(CMAKE_CXX_STANDARD 11)

option(BUILD_SHARED_LIBS "Build libraries as shared as opposed to static" ON)

# Conan
include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
conan_basic_setup()

# RIKS++

set(${PROJECT_NAME}_SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/../riks-cpp/src)

set(${PROJECT_NAME}_PUBLIC_SRC
    ${${PROJECT_NAME}_SOURCE_DIR}/hyker/util/base64.cpp
    ${${PROJECT_NAME}_SOURCE_DIR}/hyker/data.cpp
    ${${PROJECT_NAME}_SOURCE_DIR}/hyker/log.cpp

    # RIKS++
    ${${PROJECT_NAME}_SOURCE_DIR}/hyker/rikskit.cpp)

set(${PROJECT_NAME}_PRIVATE_SRC
    ${${PROJECT_NAME}_SOURCE_DIR}/hyker/util/crypto.cpp
    ${${PROJECT_NAME}_SOURCE_DIR}/hyker/util/hex.cpp
    ${${PROJECT_NAME}_SOURCE_DIR}/hyker/util/hmac.cpp
    ${${PROJECT_NAME}_SOURCE_DIR}/hyker/util/http.cpp
    ${${PROJECT_NAME}_SOURCE_DIR}/hyker/util/pbkdf2.cpp
    ${${PROJECT_NAME}_SOURCE_DIR}/hyker/util/random.cpp
    ${${PROJECT_NAME}_SOURCE_DIR}/hyker/util/sha256.cpp
    ${${PROJECT_NAME}_SOURCE_DIR}/hyker/callback.cpp
    ${${PROJECT_NAME}_SOURCE_DIR}/hyker/certificate.cpp
    ${${PROJECT_NAME}_SOURCE_DIR}/hyker/file.cpp
    ${${PROJECT_NAME}_SOURCE_DIR}/hyker/filter.cpp
    ${${PROJECT_NAME}_SOURCE_DIR}/hyker/inbox.cpp
    ${${PROJECT_NAME}_SOURCE_DIR}/hyker/key_pair.cpp
    ${${PROJECT_NAME}_SOURCE_DIR}/hyker/notifier.cpp
    ${${PROJECT_NAME}_SOURCE_DIR}/hyker/ssl_client.cpp
    ${${PROJECT_NAME}_SOURCE_DIR}/hyker/storage.cpp
    ${${PROJECT_NAME}_SOURCE_DIR}/hyker/version.cpp
    ${${PROJECT_NAME}_SOURCE_DIR}/hyker/worker.cpp

    # Outbox++
    ${${PROJECT_NAME}_SOURCE_DIR}/hyker/outbox/api_client.cpp
    ${${PROJECT_NAME}_SOURCE_DIR}/hyker/outbox/io_wrapper.cpp
    ${${PROJECT_NAME}_SOURCE_DIR}/hyker/outbox/messenger.cpp
    ${${PROJECT_NAME}_SOURCE_DIR}/hyker/outbox/transport.cpp
    ${${PROJECT_NAME}_SOURCE_DIR}/hyker/outbox.cpp

    # Cryptobox++
    ${${PROJECT_NAME}_SOURCE_DIR}/hyker/cryptobox/certificate_signing_request.cpp
    ${${PROJECT_NAME}_SOURCE_DIR}/hyker/cryptobox/certificate_validation.cpp
    ${${PROJECT_NAME}_SOURCE_DIR}/hyker/cryptobox/credentials.cpp
    ${${PROJECT_NAME}_SOURCE_DIR}/hyker/cryptobox/public_key_cache.cpp
    ${${PROJECT_NAME}_SOURCE_DIR}/hyker/cryptobox/public_key_lookup.cpp
    ${${PROJECT_NAME}_SOURCE_DIR}/hyker/cryptobox.cpp
    
    # RIKS++
    ${${PROJECT_NAME}_SOURCE_DIR}/hyker/riks/key_sharer.cpp
    ${${PROJECT_NAME}_SOURCE_DIR}/hyker/riks/nonce.cpp
    ${${PROJECT_NAME}_SOURCE_DIR}/hyker/riks/replay_protector.cpp
    ${${PROJECT_NAME}_SOURCE_DIR}/hyker/riks/sym_message.cpp
    ${${PROJECT_NAME}_SOURCE_DIR}/hyker/riks/symkey.cpp
    ${${PROJECT_NAME}_SOURCE_DIR}/hyker/riks/symkey_cache.cpp)

add_executable(${PROJECT_NAME} ../main.cpp)

target_sources(${PROJECT_NAME}
    PUBLIC  ${${PROJECT_NAME}_PUBLIC_SRC}
    PRIVATE ${${PROJECT_NAME}_PRIVATE_SRC})

target_include_directories(${PROJECT_NAME} PRIVATE ${${PROJECT_NAME}_SOURCE_DIR})

# Dependencies

set(THREADS_PREFER_PTHREAD_FLAG ON)
find_package(Threads REQUIRED)
target_link_libraries(${PROJECT_NAME}
    PRIVATE
        ${CONAN_LIBS}
        ${CMAKE_THREAD_LIBS_INIT})
