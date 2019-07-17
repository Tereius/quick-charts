#include "PieChartMaterial.h"

PieChartMaterial::PieChartMaterial()
{
    setFlag(QSGMaterial::Blending);
}

PieChartMaterial::~PieChartMaterial()
{
}

QSGMaterialType *PieChartMaterial::type() const
{
    static QSGMaterialType type;
    return &type;
}

QSGMaterialShader *PieChartMaterial::createShader() const
{
    return new PieChartShader();
}

QVector2D PieChartMaterial::aspectRatio() const
{
    return m_aspectRatio;
}

float PieChartMaterial::innerRadius() const
{
    return m_innerRadius;
}

float PieChartMaterial::outerRadius() const
{
    return m_outerRadius;
}

QColor PieChartMaterial::backgroundColor() const
{
    return m_backgroundColor;
}

QVector<QVector2D> PieChartMaterial::triangles() const
{
    return m_triangles;
}

QVector<QVector4D> PieChartMaterial::colors() const
{
    return m_colors;
}

QVector<int> PieChartMaterial::segments() const
{
    return m_segments;
}

bool PieChartMaterial::smoothEnds() const
{
    return m_smoothEnds;
}

void PieChartMaterial::setAspectRatio(const QVector2D &aspect)
{
    m_aspectRatio = aspect;
}

void PieChartMaterial::setInnerRadius(float radius)
{
    m_innerRadius = radius;
}

void PieChartMaterial::setOuterRadius(float radius)
{
    m_outerRadius = radius;
}

void PieChartMaterial::setBackgroundColor(const QColor& color)
{
    m_backgroundColor = color;
}

void PieChartMaterial::setTriangles(const QVector<QVector2D> &triangles)
{
    m_triangles = triangles;
}

void PieChartMaterial::setColors(const QVector<QVector4D> &colors)
{
    m_colors = colors;
}

void PieChartMaterial::setSegments(const QVector<int>& segments)
{
    m_segments = segments;
}

void PieChartMaterial::setSmoothEnds(bool smooth)
{
    m_smoothEnds = smooth;
}

PieChartShader::PieChartShader()
{
    setShaders(QStringLiteral("piechart.vert"), QStringLiteral("piechart.frag"));
}

PieChartShader::~PieChartShader()
{
}

const char *const *PieChartShader::attributeNames() const
{
    static char const *const names[] = { "in_vertex", "in_uv", nullptr };
    return names;
}

void PieChartShader::initialize()
{
    QSGMaterialShader::initialize();
    m_matrixLocation = program()->uniformLocation("matrix");
    m_opacityLocation = program()->uniformLocation("opacity");
    m_innerRadiusLocation = program()->uniformLocation("innerRadius");
    m_outerRadiusLocation = program()->uniformLocation("outerRadius");
    m_aspectLocation = program()->uniformLocation("aspect");
    m_backgroundColorLocation = program()->uniformLocation("backgroundColor");
    m_trianglesLocation = program()->uniformLocation("triangles");
    m_colorsLocation = program()->uniformLocation("colors");
    m_segmentsLocation = program()->uniformLocation("segments");
    m_segmentCountLocation = program()->uniformLocation("segmentCount");
    m_smoothEndsLocation = program()->uniformLocation("smoothEnds");
}

void PieChartShader::updateState(const QSGMaterialShader::RenderState &state, QSGMaterial *newMaterial, QSGMaterial *oldMaterial)
{
    if (state.isMatrixDirty())
        program()->setUniformValue(m_matrixLocation, state.combinedMatrix());
    if (state.isOpacityDirty())
        program()->setUniformValue(m_opacityLocation, state.opacity());

    if (!oldMaterial || newMaterial->compare(oldMaterial) != 0) {
        PieChartMaterial *material = static_cast<PieChartMaterial *>(newMaterial);
        program()->setUniformValue(m_innerRadiusLocation, material->innerRadius());
        program()->setUniformValue(m_outerRadiusLocation, material->outerRadius());
        program()->setUniformValue(m_aspectLocation, material->aspectRatio());
        program()->setUniformValue(m_backgroundColorLocation, material->backgroundColor());
        program()->setUniformValueArray(m_trianglesLocation, material->triangles().constData(), material->triangles().size());
        program()->setUniformValueArray(m_colorsLocation, material->colors().constData(), material->colors().size());
        program()->setUniformValueArray(m_segmentsLocation, material->segments().constData(), material->segments().size());
        program()->setUniformValue(m_segmentCountLocation, material->segments().size());
        program()->setUniformValue(m_smoothEndsLocation, material->smoothEnds());
    }
}
