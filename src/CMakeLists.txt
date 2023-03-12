set(VISIONX_EXECUTABLE_NAME VisionX)
set(VISIONX_SOURCE_FILES main.cpp)

add_executable(${VISIONX_EXECUTABLE_NAME} ${VISIONX_SOURCE_FILES})

set_target_properties(
    ${VISIONX_EXECUTABLE_NAME} PROPERTIES

    CXX_EXTENSIONS OFF
    CXX_STANDARD 20
    CXX_STANDARD_REQUIRED ON
)

if(MSVC)
    target_compile_options(${VISIONX_EXECUTABLE_NAME} PRIVATE "/W4")
    target_compile_options(${VISIONX_EXECUTABLE_NAME} PRIVATE "/WX")
    target_compile_options(${VISIONX_EXECUTABLE_NAME} PRIVATE "/wd4100")
else()
    target_compile_options(${VISIONX_EXECUTABLE_NAME} PRIVATE -Wall -Wextra -Wpedantic -Werror -Wno-unused-parameter -Wno-unused-variable)
endif()

target_include_directories(
    ${VISIONX_EXECUTABLE_NAME}

    PUBLIC
    ${PROJECT_SOURCE_DIR}/include
)

target_link_libraries(
    ${VISIONX_EXECUTABLE_NAME}

    PUBLIC
    ${CONAN_LIBS}
)