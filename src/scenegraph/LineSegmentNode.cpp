/*
 * This file is part of KQuickCharts
 * SPDX-FileCopyrightText: 2019 Arjen Hiemstra <ahiemstra@heimr.nl>
 *
 * SPDX-License-Identifier: LGPL-2.1-only OR LGPL-3.0-only OR LicenseRef-KDE-Accepted-LGPL
 */

#include "LineSegmentNode.h"

#include <QSGGeometry>

#include "LineChartMaterial.h"


LineSegmentNode::LineSegmentNode()
    : LineSegmentNode(QRectF{})
{
}

LineSegmentNode::LineSegmentNode(const QRectF &rect)
{
    m_geometry = new QSGGeometry{QSGGeometry::defaultAttributes_TexturedPoint2D(), 4};
    QSGGeometry::updateTexturedRectGeometry(m_geometry, rect, QRectF{0, 0, 1, 1});
    setGeometry(m_geometry);

    m_rect = rect;

    m_material = new LineChartMaterial{};
    setMaterial(m_material);

    setFlags(QSGNode::OwnsGeometry | QSGNode::OwnsMaterial);
}

LineSegmentNode::~LineSegmentNode()
{
}

void LineSegmentNode::setRect(const QRectF &rect)
{
    if (rect == m_rect) {
      return;
    }

    m_rect = rect;
    QSGGeometry::updateTexturedRectGeometry(m_geometry, m_rect, QRectF{0, 0, 1, 1});
    markDirty(QSGNode::DirtyGeometry);
}

void LineSegmentNode::setAspect(float xAspect, float yAspect)
{
    if (qFuzzyCompare(xAspect, m_xAspect) && qFuzzyCompare(yAspect, m_yAspect)) {
        return;
    }

    m_yAspect = yAspect;
    m_material->aspect = m_yAspect;
    markDirty(QSGNode::DirtyMaterial);

    m_xAspect = xAspect;
}

void LineSegmentNode::setSmoothing(float smoothing)
{
    if (qFuzzyCompare(smoothing, m_smoothing)) {
        return;
    }

    m_smoothing = smoothing;
    m_material->smoothing = m_smoothing;
    markDirty(QSGNode::DirtyMaterial);
}

void LineSegmentNode::setLineWidth(float width)
{
    if (qFuzzyCompare(width, m_lineWidth)) {
        return;
    }

    m_lineWidth = width;
    m_material->lineWidth = m_lineWidth;
    markDirty(QSGNode::DirtyMaterial);
}

void LineSegmentNode::setLineColor(const QColor &color)
{
    if (color == m_lineColor) {
      return;
    }

    m_lineColor = color;
    m_material->lineColor = m_lineColor;
    markDirty(QSGNode::DirtyMaterial);
}

void LineSegmentNode::setFillColor(const QColor &color)
{
    if (color == m_fillColor) {
      return;
    }

    m_fillColor = color;
    m_material->fillColor = m_fillColor;
    markDirty(QSGNode::DirtyMaterial);
}

void LineSegmentNode::setValues(const QVector<QVector2D> &values)
{
    m_values = values;
}

void LineSegmentNode::setFarLeft(const QVector2D &value)
{
    m_farLeft = value;
}

void LineSegmentNode::setFarRight(const QVector2D &value)
{
    m_farRight = value;
}

void LineSegmentNode::update()
{
    if (m_values.isEmpty() || !m_rect.isValid()) {
        markDirty(QSGNode::DirtyGeometry);
        return;
    }

    QVector<QVector2D> points;
    points.reserve(m_values.size() + 8);

    points << QVector2D{0.0, -0.5};
    points << QVector2D{-0.5, -0.5};

    auto min = std::numeric_limits<float>::max();
    auto max = std::numeric_limits<float>::min();

    if (!m_farLeft.isNull()) {
        points << QVector2D(-0.5, m_farLeft.y() * m_yAspect);
        points << QVector2D(((m_farLeft.x() - m_rect.left()) / m_rect.width()) * m_xAspect, m_farLeft.y() * m_yAspect);
        min = std::min(m_farLeft.y() * m_yAspect, min);
        max = std::max(m_farLeft.y() * m_yAspect, max);
    } else {
        points << QVector2D(-0.5, m_values[0].y() * m_yAspect);
    }

    for (auto value : std::as_const(m_values)) {
        auto x = ((value.x() - m_rect.left()) / m_rect.width()) * m_xAspect;
        points << QVector2D(x, value.y() * m_yAspect);
        min = std::min(value.y() * m_yAspect, min);
        max = std::max(value.y() * m_yAspect, max);
    }

    if (!m_farRight.isNull()) {
        points << QVector2D(((m_farRight.x() - m_rect.left()) / m_rect.width()) * m_xAspect, m_farRight.y() * m_yAspect);
        points << QVector2D(1.5, m_farRight.y() * m_yAspect);
        min = std::min(m_farRight.y() * m_yAspect, min);
        max = std::max(m_farRight.y() * m_yAspect, max);
    } else {
        points << QVector2D(1.5, points.last().y());
    }

    points << QVector2D{1.5, -0.5};
    points << QVector2D{0.0, -0.5};

    m_material->values = points;
    m_material->min = min;
    m_material->max = max;

    markDirty(QSGNode::DirtyMaterial);
}
