#!/usr/bin/env python
# -*- coding: utf-8 -*-

from conan import ConanFile
from conan.tools.cmake import CMake, CMakeToolchain
from conan.tools.env import VirtualBuildEnv
from conan.tools.files import patch, copy, replace_in_file, get
from conan.tools.scm import Git
import json, os

required_conan_version = ">=2.0"

class QuickChartsConan(ConanFile):

    jsonInfo = json.load(open("info.json", 'r'))
    # Package reference
    name = jsonInfo["projectName"]
    version = "%u.%u.%u" % (jsonInfo["version"]["major"], jsonInfo["version"]["minor"], jsonInfo["version"]["patch"])
    user = jsonInfo["domain"]
    channel = "%s" % ("snapshot" if jsonInfo["version"]["snapshot"] else "stable")
    # Metadata
    description = jsonInfo["projectDescription"]
    license = jsonInfo["license"]
    author = jsonInfo["vendor"]
    url = jsonInfo["repository"]
    homepage = "https://api.kde.org/ecm/"
    topics = ("Qt", "QtQuick", "Qml", "Charts")
    exports = ["info.json", "LICENSES/*"]
    exports_sources = ["controls/*", "src/*", "examples/*", "autotests/*", "CMakeLists.txt"]
    settings = "os", "arch", "compiler", "build_type"
    options = {}
    default_options = {"qt/*:GUI": True,
                       "qt/*:opengl": "desktop",
                       "qt/*:qtbase": True,
                       "qt/*:widgets": True,
                       "qt/*:qtdeclarative": True,
                       "qt/*:qtcharts": True,
                       "qt/*:qtpositioning": True,
                       "qt/*:qtlocation": True,
                       "qt/*:qtsvg": True,
                       "qt/*:qttools": True,
                       "qt/*:qttranslations": True,
                       "qt/*:qt5compat": True,
                       "qt/*:qtvirtualkeyboard": True}
    requires = ("qt/[~6.5]@%s/stable" % user, "qt_app_base/[~1]@%s/snapshot" % user)

    def build_requirements(self):
        self.tool_requires("extra-cmake-modules/%s@%s/stable" % (self.version, self.user), visible=True)

    def generate(self):
        tc = CMakeToolchain(self, generator="Ninja")
        tc.generate()
        ms = VirtualBuildEnv(self)
        ms.generate()

    def build(self):
        cmake = CMake(self)
        cmake.configure()
        cmake.build()

    def package(self):
        cmake = CMake(self)
        cmake.install()
        #replace_in_file(self, "%s/lib/cmake/KF6QuickCharts/KF6QuickChartsConfig.cmake" % self.package_folder, "ecm_find_qmlmodule(org.kde.quickcharts 1.0)", "set(KDE_INSTALL_FULL_QMLDIR \"${CMAKE_CURRENT_LIST_DIR}/../../qml\")\necm_find_qmlmodule(org.kde.quickcharts 1.0)")

    def package_info(self):
        self.cpp_info.builddirs = ["lib/cmake"]
        self.runenv_info.prepend_path("QML_IMPORT_PATH", os.path.join(self.package_folder, "qml"))
