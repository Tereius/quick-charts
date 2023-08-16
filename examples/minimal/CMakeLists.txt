
qt_add_executable(MinimalExample main.cpp)

qt_add_resources(MinimalExample Gui FILES main.qml)

target_link_libraries(MinimalExample
											PRIVATE Qt6::Widgets
											PRIVATE Qt6::Core
											PRIVATE Qt6::Quick
											PRIVATE Qt6::Qml
											PRIVATE Qt6::Quick
											PRIVATE QuickCharts
											PRIVATE QuickChartsControls
											)
