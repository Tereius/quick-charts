
qt_add_qml_module(QuickChartsControls
									URI "org.kde.quickcharts.controls"
									VERSION "1.0"
									OUTPUT_DIRECTORY "org/kde/quickcharts/controls"
									#NO_PLUGIN_OPTIONAL
									#NO_GENERATE_PLUGIN_SOURCE
									#CLASS_NAME ChartsControlsPlugin

									#SOURCES
									#ChartsControlsPlugin.h
									#ChartsControlsPlugin.cpp

									QML_FILES
									Legend.qml
									LegendDelegate.qml
									LineChartControl.qml
									PieChartControl.qml
									Theme.qml
									Logging.qml
									styles/org.kde.desktop/Theme.qml
									)

#target_sources(QuickChartsControlsplugin PRIVATE ChartsControlsPlugin.h ChartsControlsPlugin.cpp)


target_link_libraries(QuickChartsControls
											PUBLIC Qt6::Core
											PUBLIC Qt6::Quick
											PUBLIC Qt6::Qml
											PUBLIC Qt6::Gui
											PUBLIC Qt6::QuickControls2
)

install_qml_module(QuickChartsControls)
