from conans import ConanFile, CMake

class VisionXConan(ConanFile):
    settings = (
        "os",
        "compiler",
        "build_type",
        "arch"
    )

    requires = (
        "glm/0.9.9.8",
    )

    options = {
        "build_tests": [True, False],
    }

    default_options = {
        "build_tests": False,
    }

    generators = "cmake"

    def configure(self):
        if self.settings.os == "Linux" and self.settings.compiler.libcxx == "libstdc++":
            raise Exception("Inexor is not compatible with libstdc++. "
                            "Please change the 'compiler.libcxx'-setting "
                            "(e.g. to libstdc++11).")

    def requirements(self):
        if self.options.build_tests:
            self.requires("gtest/1.12.1")

    def build(self):
        cmake = CMake(self)
        cmake.configure()
        cmake.build()
