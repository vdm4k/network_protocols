cmake_minimum_required(VERSION 3.1.0)
project(network_protocols VERSION 0.0.2 DESCRIPTION "network protocols" LANGUAGES CXX)

# cpp files
set(H_FILES
    include/protocols/ip/address.h
    include/protocols/ip/full_address.h
    include/protocols/ip/v4.h
    include/protocols/ip/v6.h
)

# cpp files
set(CPP_FILES
    source/protocols/ip/address.cpp
    source/protocols/ip/full_address.cpp
    source/protocols/ip/v4.cpp
    source/protocols/ip/v6.cpp
)

add_library(${PROJECT_NAME} STATIC ${CPP_FILES} ${H_FILES})
add_library(bro::${PROJECT_NAME} ALIAS ${PROJECT_NAME})
add_library(network_protocols::${PROJECT_NAME} ALIAS ${PROJECT_NAME})

target_compile_features(${PROJECT_NAME} PUBLIC cxx_std_17)
if(MSVC)
    target_compile_options(${PROJECT_NAME} PRIVATE /W4 /WX)
else()
    target_compile_options(${PROJECT_NAME} PRIVATE "-Wall;-Wextra"
        PUBLIC "$<$<CONFIG:DEBUG>:${DEBUG_OPTIONS}>"
        PUBLIC "$<$<CONFIG:RELEASE>:${RELEASE_OPTIONS}>")
endif()

set(CMAKE_POSITION_INDEPENDENT_CODE ON)
target_include_directories(${PROJECT_NAME} PUBLIC
    $<BUILD_INTERFACE:${${PROJECT_NAME}_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:include/${PROJECT_NAME}>)

#sanitizer
if(NOT DEFINED WITH_SANITIZER)
    option(WITH_SANITIZER "Enable address sanitizer" OFF)
endif()

if(WITH_SANITIZER)
    target_compile_options(${PROJECT_NAME} INTERFACE -fsanitize=address -fPIC)
    target_link_options(${PROJECT_NAME} INTERFACE -fsanitize=address)
endif()

option(WITH_TESTS "Build tests" OFF)
if(WITH_TESTS)
    add_subdirectory(test)
endif(WITH_TESTS)
