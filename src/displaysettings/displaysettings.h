/****************************************************************************
**
** Copyright (C) 2016 The Qt Company Ltd.
** Contact: http://www.qt.io/licensing/
**
** This file is part of the Qt Device Utilities module of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:LGPL3$
** Commercial License Usage
** Licensees holding valid commercial Qt licenses may use this file in
** accordance with the commercial license agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and The Qt Company. For licensing terms
** and conditions see http://www.qt.io/terms-conditions. For further
** information use the contact form at http://www.qt.io/contact-us.
**
** GNU Lesser General Public License Usage
** Alternatively, this file may be used under the terms of the GNU Lesser
** General Public License version 3 as published by the Free Software
** Foundation and appearing in the file LICENSE.LGPLv3 included in the
** packaging of this file. Please review the following information to
** ensure the GNU Lesser General Public License version 3 requirements
** will be met: https://www.gnu.org/licenses/lgpl.html.
**
** GNU General Public License Usage
** Alternatively, this file may be used under the terms of the GNU
** General Public License version 2.0 or later as published by the Free
** Software Foundation and appearing in the file LICENSE.GPL included in
** the packaging of this file. Please review the following information to
** ensure the GNU General Public License version 2.0 requirements will be
** met: http://www.gnu.org/licenses/gpl-2.0.html.
**
** $QT_END_LICENSE$
**
****************************************************************************/
#ifndef DISPLAYSETTINGS_H
#define DISPLAYSETTINGS_H

#include <qobject.h>

class DisplaySettingsPrivate;

class Q_DECL_EXPORT DisplaySettings : public QObject
{
    Q_OBJECT

    Q_PROPERTY(int displayBrightness READ displayBrightness WRITE setDisplayBrightness NOTIFY displayBrightnessChanged)
    Q_PROPERTY(int physicalScreenSizeInch READ physicalScreenSizeInch WRITE setPhysicalScreenSizeInch NOTIFY physicalScreenSizeInchChanged)
    Q_PROPERTY(bool physicalScreenSizeOverride READ physicalScreenSizeOverride WRITE setPhysicalScreenSizeOverride NOTIFY physicalScreenSizeOverrideChanged)

public:
    DisplaySettings(QObject *parent = 0);
    ~DisplaySettings();

    int displayBrightness();
    int physicalScreenSizeInch() const;
    bool physicalScreenSizeOverride() const;

public Q_SLOTS:
    bool setDisplayBrightness(int value);
    void setPhysicalScreenSizeInch(int inches);
    void setPhysicalScreenSizeOverride(bool enable);

signals:
    void displayBrightnessChanged(int newValue);
    void physicalScreenSizeInchChanged(int newInches);
    void physicalScreenSizeOverrideChanged(bool newValue);

protected:
    DisplaySettingsPrivate *d_ptr;

    Q_DISABLE_COPY(DisplaySettings)
    Q_DECLARE_PRIVATE(DisplaySettings)
};

#endif // DISPLAYSETTINGS_H
