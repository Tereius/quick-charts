/*
 * This file is part of KQuickCharts
 * SPDX-FileCopyrightText: 2019 Arjen Hiemstra <ahiemstra@heimr.nl>
 * SPDX-FileCopyrightText: 2022 Łukasz Wojniłowicz <lukasz.wojnilowicz@gmail.com>
 *
 * SPDX-License-Identifier: LGPL-2.1-only OR LGPL-3.0-only OR LicenseRef-KDE-Accepted-LGPL
 */
#version 440
#define MAXIMUM_POINT_COUNT 400

layout(std140, binding = 0) uniform buf {
    highp mat4 matrix;
    lowp float opacity;
    lowp float lineWidth;
    lowp float aspect;
    lowp float smoothing;
    mediump vec4 lineColor;
    mediump vec4 fillColor;
    mediump vec2 bounds;
    lowp vec2 points[MAXIMUM_POINT_COUNT];
    mediump float pointCount;
} ubuf;

layout (location = 0) in highp vec4 in_vertex;
layout (location = 1) in mediump vec2 in_uv; // pass through
layout (location = 0) out mediump vec2 uv;

void main() {
    uv = in_uv;
    uv.y = (1.0 + -1.0 * uv.y) * ubuf.aspect;
    gl_Position = ubuf.matrix * in_vertex;
}
