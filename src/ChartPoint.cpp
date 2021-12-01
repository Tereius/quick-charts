/*
 * SPDX-FileCopyrightText: 2021 Arjen Hiemstra <ahiemstra@heimr.nl>
 *
 * SPDX-License-Identifier: LGPL-2.1-only OR LGPL-3.0-only OR LicenseRef-KDE-Accepted-LGPL
 */

#include "ChartPoint.h"

ChartPoint::ChartPoint()
{
}

bool ChartPoint::isValid() const
{
    return valueSource != nullptr;
}
