
find_package(Qt6Widgets REQUIRED)
set_package_properties(Qt6Widgets PROPERTIES TYPE REQUIRED PURPOSE "The charts example needs Qt Widgets so the Plasma desktop style works properly.")
find_package(KF6Kirigami2 REQUIRED)
set_package_properties(KF6Kirigami2 PROPERTIES TYPE REQUIRED PURPOSE "The charts example uses Kirigami for its UI.")
find_package(KF6Declarative REQUIRED)
set_package_properties(KF6Declarative PROPERTIES TYPE REQUIRED PURPOSE "The charts example uses items from KF6Declarative for its UI.")

set(quickcharts_example_SRCS
    main.cpp
)

qt_add_resources(quickcharts_example_QRC charts.qrc)

add_executable(kquickcharts_example ${quickcharts_example_SRCS} ${quickcharts_example_QRC})
target_link_libraries(kquickcharts_example Qt6::Quick Qt6::Widgets)

install(TARGETS kquickcharts_example DESTINATION ${KDE_INSTALL_BINDIR})
