# SPDX-FileCopyrightText: 2022 Volker Krause <vkrause@kde.org>
# SPDX-License-Identifier: BSD-2-Clause

qt6_add_shaders(QuickCharts "shaders"
    BATCHABLE
    PRECOMPILE
    OPTIMIZED
    PREFIX "/org.kde.quickcharts/"
    GLSL "100es,120"
    FILES
        barchart.vert
        barchart.frag
        linechart.vert
        linechart.frag
        piechart.vert
        piechart.frag
)
