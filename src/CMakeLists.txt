
qt_add_qml_module(QuickCharts
									URI "org.kde.quickcharts"
                                    VERSION "1.0"
									OUTPUT_DIRECTORY "org/kde/quickcharts"
									NO_PLUGIN_OPTIONAL
									NO_GENERATE_PLUGIN_SOURCE
									CLASS_NAME QuickChartsPlugin

									SOURCES
									BarChart.cpp
									BarChart.h
									Chart.cpp
									Chart.h
									datasource/ArraySource.cpp
									datasource/ArraySource.h
									datasource/ChartAxisSource.cpp
									datasource/ChartAxisSource.h
									datasource/ChartDataSource.cpp
									datasource/ChartDataSource.h
									datasource/ColorGradientSource.cpp
									datasource/ColorGradientSource.h
									datasource/HistoryProxySource.cpp
									datasource/HistoryProxySource.h
									datasource/MapProxySource.cpp
									datasource/MapProxySource.h
									datasource/ModelSource.cpp
									datasource/ModelSource.h
									datasource/SingleValueSource.cpp
									datasource/SingleValueSource.h
									decorations/AxisLabels.cpp
									decorations/AxisLabels.h
									decorations/GridLines.cpp
									decorations/GridLines.h
									decorations/LegendLayout.cpp
									decorations/LegendLayout.h
									decorations/LegendModel.cpp
									decorations/LegendModel.h
									ItemBuilder.cpp
									ItemBuilder.h
									LineChart.cpp
									LineChart.h
									PieChart.cpp
									PieChart.h
									RangeGroup.cpp
									RangeGroup.h
									scenegraph/BarChartMaterial.cpp
									scenegraph/BarChartMaterial.h
									scenegraph/BarChartNode.cpp
									scenegraph/BarChartNode.h
									scenegraph/LineChartMaterial.cpp
									scenegraph/LineChartMaterial.h
									scenegraph/LineChartNode.cpp
									scenegraph/LineChartNode.h
									scenegraph/LineGridNode.cpp
									scenegraph/LineGridNode.h
									scenegraph/LineSegmentNode.cpp
									scenegraph/LineSegmentNode.h
									scenegraph/PieChartMaterial.cpp
									scenegraph/PieChartMaterial.h
									scenegraph/PieChartNode.cpp
									scenegraph/PieChartNode.h
									scenegraph/SDFShader.cpp
									scenegraph/SDFShader.h
									XYChart.cpp
									XYChart.h


									)


ecm_qt_declare_logging_category(QuickCharts
																HEADER charts_general_logging.h
																IDENTIFIER GENERAL
																CATEGORY_NAME kf.quickcharts.general
																DEFAULT_SEVERITY Warning
																DESCRIPTION "KQuickCharts Library - General"
																EXPORT KQuickCharts
																)

ecm_qt_declare_logging_category(QuickCharts
																HEADER charts_datasource_logging.h
																IDENTIFIER DATASOURCE
																CATEGORY_NAME kf.quickcharts.datasource
																DEFAULT_SEVERITY Warning
																DESCRIPTION "KQuickCharts Library - Data Sources"
																EXPORT KQuickCharts
																)

ecm_qt_declare_logging_category(QuickCharts
																HEADER charts_deprecated_logging.h
																IDENTIFIER DEPRECATED
																CATEGORY_NAME kf.quickcharts.deprecated
																DEFAULT_SEVERITY Warning
																DESCRIPTION "KQuickCharts Library - Deprecated API"
																EXPORT KQuickCharts
																)

#target_link_libraries(QuickCharts PRIVATE QuickChartsStatic)

target_sources(QuickChartsplugin PRIVATE ChartsPlugin.h ChartsPlugin.cpp)

#target_link_libraries(QuickChartsplugin PRIVATE QuickChartsStatic)

target_link_libraries(QuickCharts
											PUBLIC Qt6::Core
											PUBLIC Qt6::Quick
											PUBLIC Qt6::Qml
											PUBLIC Qt6::Quick
											)

add_subdirectory(shaders)

ecm_generate_export_header(QuickCharts
    BASE_NAME QuickCharts
    GROUP_BASE_NAME KF
    VERSION ${KF_VERSION}
    DEPRECATED_BASE_VERSION 0
    DEPRECATION_VERSIONS
    EXCLUDE_DEPRECATED_BEFORE_AND_AT ${EXCLUDE_DEPRECATED_BEFORE_AND_AT}
)

install_qml_module(QuickCharts)

#ecm_finalize_qml_module(QuickCharts DESTINATION ${KDE_INSTALL_QMLDIR})

#ecm_qt_install_logging_categories(EXPORT KQuickCharts DESTINATION ${KDE_INSTALL_LOGGINGCATEGORIESDIR})
