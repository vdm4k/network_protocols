cmake_minimum_required(VERSION 3.3.2)
project(protocols_test VERSION 1.0.0 DESCRIPTION "protocols library tests" LANGUAGES CXX)

include("${PROJECT_SOURCE_DIR}/third_party/gtest.cmake")

file(GLOB_RECURSE CPP_FILES ${${PROJECT_NAME}_SOURCE_DIR}/*.cpp)
file(GLOB_RECURSE H_FILES   ${${PROJECT_NAME}_SOURCE_DIR}/*.h)

add_executable(${PROJECT_NAME} ${CPP_FILES} ${H_FILES})

target_compile_features(${PROJECT_NAME} PUBLIC cxx_std_17)
target_compile_options(${PROJECT_NAME} PUBLIC "-Wall;-Wextra"
    PRIVATE "$<$<CONFIG:DEBUG>:${DEBUG_OPTIONS}>"
    PRIVATE "$<$<CONFIG:RELEASE>:${RELEASE_OPTIONS}>")

enable_testing()

if(NOT DEFINED WITH_SANITIZER)
    option(WITH_SANITIZER "Sanitizer" OFF)
endif()

if(WITH_SANITIZER)
    target_compile_options(${PROJECT_NAME} PRIVATE $<$<CONFIG:Debug>:-fsanitize=address>)
    target_link_libraries(${PROJECT_NAME} PRIVATE $<$<CONFIG:Debug>:-fsanitize=address>
        network_protocols::network_protocols GTest::gtest GTest::gtest_main ${CMAKE_THREAD_LIBS_INIT})
else()
    target_link_libraries(${PROJECT_NAME}
        PUBLIC
        network_protocols::network_protocols GTest::gtest GTest::gtest_main ${CMAKE_THREAD_LIBS_INIT})
endif()

include(GoogleTest)
gtest_discover_tests(${PROJECT_NAME})