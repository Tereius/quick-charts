/*
 * This file is part of KQuickCharts
 * SPDX-FileCopyrightText: 2019 Arjen Hiemstra <ahiemstra@heimr.nl>
 *
 * SPDX-License-Identifier: LGPL-2.1-only OR LGPL-3.0-only OR LicenseRef-KDE-Accepted-LGPL
 */

#include "LineChartMaterial.h"

constexpr int MaximumSegmentCount = 400;

LineChartMaterial::LineChartMaterial()
{
    setFlag(QSGMaterial::Blending);
}

LineChartMaterial::~LineChartMaterial()
{
}

QSGMaterialType *LineChartMaterial::type() const
{
    static QSGMaterialType type;
    return &type;
}

QSGMaterialShader *LineChartMaterial::createShader(QSGRendererInterface::RenderMode) const
{
    return new LineChartShader();
}

int LineChartMaterial::compare(const QSGMaterial *other) const
{
    auto material = static_cast<const LineChartMaterial *>(other);

    /* clang-format off */
    if (qFuzzyCompare(material->aspect, aspect)
        && qFuzzyCompare(material->lineWidth, lineWidth)
        && qFuzzyCompare(material->smoothing, smoothing)
        && material->fillColor == fillColor
        && material->lineColor == lineColor
        && material->min == min
        && material->max == max
        && material->values.size() == values.size()
      ) { /* clang-format on */
        return 0;
    }

    return QSGMaterial::compare(other);
}

LineChartShader::LineChartShader()
{
    setShaders(QStringLiteral("linechart.vert"), QStringLiteral("linechart.frag"));
}

LineChartShader::~LineChartShader()
{
}

bool LineChartShader::updateUniformData(QSGMaterialShader::RenderState &state, QSGMaterial *newMaterial, QSGMaterial *oldMaterial)
{
    bool changed = false;
    UniformDataStream uniformData(state);
    auto offset = uniformData.bytes;

    if (state.isMatrixDirty()) {
        uniformData << state.combinedMatrix();
        changed = true;
    } else {
        uniformData.skip<QMatrix4x4>();
    }

    if (state.isOpacityDirty()) {
        uniformData << state.opacity();
        changed = true;
    } else {
        uniformData.skip<float>();
    }

    if (!oldMaterial || newMaterial->compare(oldMaterial) != 0) {
        const auto material = static_cast<LineChartMaterial *>(newMaterial);
        Q_ASSERT(material->values.size() <= MaximumSegmentCount);
        uniformData << material->lineWidth;
        uniformData << material->aspect;
        uniformData << material->smoothing;
        uniformData << QVector4D{material->lineColor.redF(), material->lineColor.greenF(), material->lineColor.blueF(), material->lineColor.alphaF()};
        uniformData << QVector4D{material->fillColor.redF(), material->fillColor.greenF(), material->fillColor.blueF(), material->fillColor.alphaF()};
        uniformData << QVector2D(material->min, material->max);
        for (auto val : material->values) {
          uniformData << QVector4D(val);
        }
        uniformData.skipComponents((MaximumSegmentCount - material->values.size()) * 4);
        uniformData << float(material->values.size());
        changed = true;
    }

    return changed;
}
