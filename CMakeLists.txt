cmake_minimum_required(VERSION 3.21.1)

set(KF_VERSION "5.240.0") # handled by release scripts
set(KF_DEP_VERSION "5.240.0") # handled by release scripts
set(CMAKE_INCLUDE_CURRENT_DIR ON)

project(KQuickCharts VERSION ${KF_VERSION})

include(ECMGenerateExportHeader)
include(ECMQtDeclareLoggingCategory)
include(QtAppBase)

set(REQUIRED_QT_VERSION 6.4.0)
find_package(Qt6 ${REQUIRED_QT_VERSION} CONFIG REQUIRED Widgets Qml Quick QuickControls2 ShaderTools)

qt_policy(
        SET QTP0001 NEW
)

qt_standard_project_setup()

add_subdirectory(controls)
add_subdirectory(src)
add_subdirectory(examples)
