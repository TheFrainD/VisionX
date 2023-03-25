set(VISIONX_EXECUTABLE_NAME VisionX)
file(GLOB_RECURSE VISIONX_SOURCE_FILES *.cpp)

add_executable(${VISIONX_EXECUTABLE_NAME} ${VISIONX_SOURCE_FILES} core/window.cpp)

set_target_properties(
        ${VISIONX_EXECUTABLE_NAME} PROPERTIES

        CXX_EXTENSIONS OFF
        CXX_STANDARD 20
        CXX_STANDARD_REQUIRED ON
)

if (MSVC)
    target_compile_options(${VISIONX_EXECUTABLE_NAME} PRIVATE "/W4")
    target_compile_options(${VISIONX_EXECUTABLE_NAME} PRIVATE "/WX")
    target_compile_options(${VISIONX_EXECUTABLE_NAME} PRIVATE "/wd4100")
else ()
    target_compile_options(${VISIONX_EXECUTABLE_NAME} PRIVATE -Wall -Wextra -Wpedantic -Werror -Wno-unused-parameter -Wno-unused-variable)
endif ()

target_include_directories(
        ${VISIONX_EXECUTABLE_NAME}

        PUBLIC
        ${PROJECT_SOURCE_DIR}/include
        ${CMAKE_CURRENT_BINARY_DIR}/include
)

find_package(OpenGL REQUIRED)

target_compile_definitions(
        ${VISIONX_EXECUTABLE_NAME}

        PUBLIC
        GLFW_INCLUDE_NONE
)

target_link_libraries(
        ${VISIONX_EXECUTABLE_NAME}

        PUBLIC
        ${GLFW_LIB}
        ${GLAD_LIB}
        ${SPDLOG_LIB}
        ${GLM_LIB}
)