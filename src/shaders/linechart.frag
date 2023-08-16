/*
 * This file is part of KQuickCharts
 * SPDX-FileCopyrightText: 2019 Arjen Hiemstra <ahiemstra@heimr.nl>
 * SPDX-FileCopyrightText: 2022 Łukasz Wojniłowicz <lukasz.wojnilowicz@gmail.com>
 *
 * SPDX-License-Identifier: LGPL-2.1-only OR LGPL-3.0-only OR LicenseRef-KDE-Accepted-LGPL
 */
#version 440
#extension GL_GOOGLE_include_directive: enable
#include "sdf.glsl"
#define MAXIMUM_POINT_COUNT 400

layout(std140, binding = 0) uniform buf {
    highp mat4 matrix;
    lowp float opacity; // inherited opacity of this item - offset 64
    lowp float lineWidth; // offset 68
    lowp float aspect; // offset 72
    lowp float smoothing; // offset 76
    mediump vec4 lineColor; // 80
    mediump vec4 fillColor; // 96
    mediump vec2 bounds; // x: min - y: max 112
    lowp vec2 points[MAXIMUM_POINT_COUNT]; // 120
    mediump float pointCount; // 6528
} ubuf; // size 6532

layout (location = 0) in mediump vec2 uv;
layout (location = 0) out lowp vec4 out_color;

void main()
{

    lowp vec2 point = uv;

    lowp vec4 color = vec4(0.0, 0.0, 0.0, 0.0);

    lowp float bounds_range = max(0.01, ubuf.lineWidth);

    // bounds.y contains the line segment's maximum value. If we are a bit above
    // that, we will never render anything, so just discard the pixel.
    if (point.y > ubuf.bounds.y + bounds_range) {
        out_color = vec4(0.0);
        return;
    }

    // bounds.x contains the line segment's minimum value. If we are a bit below
    // that, we know we will always be inside the polygon described by points.
    // So just return a pixel with fillColor.
    if (point.y < ubuf.bounds.x - bounds_range) {
        out_color = ubuf.fillColor * ubuf.opacity;
        return;
    }

    lowp float polygon = sdf_polygon(point, ubuf.points, int(ubuf.pointCount));

    color = sdf_render(polygon, color, ubuf.fillColor);

    if (ubuf.lineWidth > 0.0) {
        color = mix(color, ubuf.lineColor, 1.0 - smoothstep(-ubuf.smoothing, ubuf.smoothing, sdf_annular(polygon, ubuf.lineWidth)));
    }

    out_color = color * ubuf.opacity;
}
