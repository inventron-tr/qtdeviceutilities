/****************************************************************************
**
** Copyright (C) 2016 The Qt Company Ltd.
** Contact: https://www.qt.io/licensing/
**
** This file is part of the Device Utilities module of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:GPL$
** Commercial License Usage
** Licensees holding valid commercial Qt licenses may use this file in
** accordance with the commercial license agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and The Qt Company. For licensing terms
** and conditions see https://www.qt.io/terms-conditions. For further
** information use the contact form at https://www.qt.io/contact-us.
**
** GNU General Public License Usage
** Alternatively, this file may be used under the terms of the GNU
** General Public License version 3 or (at your option) any later version
** approved by the KDE Free Qt Foundation. The licenses are as published by
** the Free Software Foundation and appearing in the file LICENSE.GPL3
** included in the packaging of this file. Please review the following
** information to ensure the GNU General Public License requirements will
** be met: https://www.gnu.org/licenses/gpl-3.0.html.
**
** $QT_END_LICENSE$
**
****************************************************************************/
#include "qnetworksettingsinterfacemodel.h"
#include "qnetworksettingsinterface.h"

QT_BEGIN_NAMESPACE

/*!
    \class QNetworkSettingsInterfaceModel
    \inmodule QtDeviceUtilities
    \brief The QNetworkSettingsInterfaceModel class represents a network
    interface model.

    The network interface model contains a list of network interfaces
    attached to the host.
*/

/*!
    \enum QNetworkSettingsInterfaceModel::Roles
    \brief This enum type holds information about a network interface.

    \value  Type
            Network interface \l{QNetworkSettingsType::Types}{type}.
    \value  Status
            Network interface \l{QNetworkSettingsState::States}{state}.
    \value  Name
            Network interface name.
    \value  Powered
            Whether the network interface is powered on or off.
*/

/*!
    Creates a new network interface model with the parent \a parent.
*/
QNetworkSettingsInterfaceModel::QNetworkSettingsInterfaceModel(QObject *parent)
    : QAbstractListModel(parent)
{
    m_roleNames.insert(Qt::UserRole, "modelData");
    m_roleNames.insert(Type, "type");
    m_roleNames.insert(Status, "status");
    m_roleNames.insert(Name, "name");
    m_roleNames.insert(Powered, "powered");
}

/*!
    Returns an array of the names of the roles in the model.
*/
QHash<int, QByteArray> QNetworkSettingsInterfaceModel::roleNames() const
{
    return m_roleNames;
}

/*!
    Returns the number of rows in the model with the parent \a parent.
*/
int QNetworkSettingsInterfaceModel::rowCount(const QModelIndex & parent) const
{
    Q_UNUSED(parent);
    return m_items.count();
}

/*!
    Returns the data at the index \a index in the model for the type of data
    specified by \a role.
*/
QVariant QNetworkSettingsInterfaceModel::data(const QModelIndex & index, int role) const
{
    if (!index.isValid()) return QVariant();

    QNetworkSettingsInterface *item = m_items[index.row()];
    if (role == Qt::UserRole) {
        return QVariant::fromValue(static_cast<QObject*>(item));
    }

    switch (role) {
    case Type:
        return item->type();
        break;
    case Name:
        return item->name();
        break;
    case Status:
        return item->state();
        break;
    case Powered:
        return item->powered();
        break;
    default:
        return QStringLiteral("");
    }

}

/*!
    Appends \a item to the model.
*/
void QNetworkSettingsInterfaceModel::append(QNetworkSettingsInterface* item)
{
    item->setParent(this);
    connectStateChanges(item);

    beginInsertRows(QModelIndex(), rowCount(), rowCount());
    m_items.append(item);
    endInsertRows();
}

/*!
    Inserts \a item into \a row in the model.
*/
void QNetworkSettingsInterfaceModel::insert(int row, QNetworkSettingsInterface* item)
{
    item->setParent(this);
    connectStateChanges(item);

    beginInsertRows(QModelIndex(), row, row);
    m_items.insert(row, item);
    endInsertRows();
}

void QNetworkSettingsInterfaceModel::connectStateChanges(QNetworkSettingsInterface* item)
{
    connect(item, &QNetworkSettingsInterface::stateChanged, this, &QNetworkSettingsInterfaceModel::connectionStatusChanged);
    connect(item, &QNetworkSettingsInterface::poweredChanged, this, &QNetworkSettingsInterfaceModel::poweredChanged);
}

/*!
    Removes the row \a row from the model.
*/
void QNetworkSettingsInterfaceModel::remove(int row)
{
    beginRemoveRows(QModelIndex(), row, row);
    m_items.removeFirst();
    endRemoveRows();
}

bool QNetworkSettingsInterfaceModel::removeInterface(const QString &name)
{
    bool ret = false;
    for (int i=0; i < m_items.count(); i++) {
       if (m_items.at(i)->name() == name) {
           remove(i);
           ret = true;
           break;
       }
    }
    return ret;
}

void QNetworkSettingsInterfaceModel::updated(int row)
{
    dataChanged(createIndex(row, 0), createIndex(row, 0));
}

/*!
    Returns the network interface model.
*/
QList<QNetworkSettingsInterface*> QNetworkSettingsInterfaceModel::getModel()
{
    return m_items;
}

void QNetworkSettingsInterfaceModel::connectionStatusChanged()
{
    QNetworkSettingsInterface *s = qobject_cast<QNetworkSettingsInterface*>(sender());

    int row = 0;
    foreach (QNetworkSettingsInterface* item, m_items) {
        if (item == s) {
            updated(row);
            break;
        }
        row++;
    }

}

void QNetworkSettingsInterfaceModel::poweredChanged()
{
    QNetworkSettingsInterface *s = qobject_cast<QNetworkSettingsInterface*>(sender());
    int row = 0;
    foreach (QNetworkSettingsInterface* item, m_items) {
        if (item == s) {
            updated(row);
            break;
        }
        row++;
    }
}


QT_END_NAMESPACE
