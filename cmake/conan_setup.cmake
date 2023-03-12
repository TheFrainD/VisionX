if(VISIONX_BUILD_TESTS)
    set(tests_option True)
else()
    set(tests_option False)
endif()

if(UNIX)
    set(compiler_libcxx SETTINGS compiler.libcxx=libstdc++11)
endif()

list(APPEND CMAKE_MODULE_PATH ${CMAKE_BINARY_DIR})
list(APPEND CMAKE_PREFIX_PATH ${CMAKE_BINARY_DIR})

if(NOT EXISTS "${CMAKE_BINARY_DIR}/conan.cmake")
    message(STATUS "Downloading conan.cmake from https://github.com/conan-io/cmake-conan")
    file(DOWNLOAD "https://raw.githubusercontent.com/conan-io/cmake-conan/4b01ffd8c058f5784ebf39b9bebab3961be52888/conan.cmake"
        "${CMAKE_BINARY_DIR}/conan.cmake"
        EXPECTED_HASH SHA256=B48262E9B603378E16E1056E786BF389EB7F2FE2267DACBB41C5A9E33A07E0F1
        TLS_VERIFY ON)
endif()

set(CONAN_SYSTEM_INCLUDES ON)

include(conan)

conan_check(VERSION 1.59.0 REQUIRED)

# We could set this variable globally but it goes against current conventions where the CXX standard is set per target.
get_property(is_multi_config GLOBAL PROPERTY GENERATOR_IS_MULTI_CONFIG)

# if a specific build type is set ignore the multi config generator
if(${is_multi_config} AND NOT DEFINED CMAKE_BUILD_TYPE)
    foreach(TYPE ${CMAKE_CONFIGURATION_TYPES})
        conan_cmake_autodetect(conan_settings BUILD_TYPE ${TYPE})
        conan_cmake_install(
            PATH_OR_REFERENCE ${PROJECT_SOURCE_DIR}
            BUILD outdated
            REMOTE conancenter
            PROFILE ${VISIONX_CONAN_PROFILE}
            GENERATOR cmake_multi
            OPTIONS build_tests=${tests_option}
            SETTINGS ${conan_settings}
            ${compiler_libcxx}
        )
    endforeach()

    include(conanbuildinfo_multi)
else()
    conan_cmake_autodetect(conan_settings)
    conan_cmake_install(
        PATH_OR_REFERENCE ${PROJECT_SOURCE_DIR}
        BUILD outdated
        REMOTE conancenter
        PROFILE ${VISIONX_CONAN_PROFILE}
        OPTIONS build_tests=${tests_option}
        SETTINGS ${conan_settings}
        ${compiler_libcxx}
    )
    include(conanbuildinfo)
endif()

conan_basic_setup()