// Copyright (C) 2019 The Qt Company Ltd.
// SPDX-License-Identifier: LicenseRef-Qt-Commercial OR GPL-3.0-only
#include "qnetworksettingsforeign.h"

/*!
    \qmlmodule QtDeviceUtilities.NetworkSettings
    \ingroup qtdevice-utilities-qml-modules
    \ingroup qmlmodules
    \title Qt Network Settings QML Types

    \brief Provides singleton QML types for controlling network settings.

    Qt Network Settings QML module provides singleton QML types for controlling
    network settings in an embedded device.

    To import and use the module's QML types, use the following statement:

    \badcode
    import QtDeviceUtilities.NetworkSettings
    \endcode

    \l{Qt Device Utilities WiFi Tutorial} demonstrates how you can use
    \l{QtDeviceUtilities.NetworkSettings}{NetworkSettings} for connecting to WiFi.

    \note Some functions may not be available on all of the platforms.

    \section1 QML Types
*/

/*!
    \qmltype NetworkSettingsManager
    \inqmlmodule QtDeviceUtilities.NetworkSettings
    \brief A singleton QML type for managing network settings.

    There is no need to create an instance of this object. To use it,
    simply import the \c {QtDeviceUtilities.NetworkSettings} module.

    \l{Qt Device Utilities WiFi Tutorial} demonstrates how you can use
    \l{NetworkSettingsManager} for connecting to WiFi.
*/

/*!
    \qmlproperty model NetworkSettingsManager::services
    \readonly

    Holds the service model. A delegate in a view that uses
    the \e services model can access the NetworkService
    item with the \e entry role.

    The services list in the model can be controlled with the
    \c type property, and NetworkService items can be retrieved
    with the \c {itemFromRow(int index)} method. For example, to
    select the first available wired network service:

    \code
    property var service: null
    ...
    NetworkSettingsManager.services.type = NetworkSettingsType.Wired;
    service = NetworkSettingsManager.services.itemFromRow(0);
    \endcode

    Available service types:

    \value NetworkSettingsType.Wired     Wired network
    \value NetworkSettingsType.Wifi      Wifi network
    \value NetworkSettingsType.Bluetooth Bluetooth network
    \value NetworkSettingsType.Unknown   Unknown network type

    \sa NetworkService
*/

/*!
    \qmlproperty model NetworkSettingsManager::interfaces
    \readonly

    Holds the interface model. A delegate in a view that uses
    the \e interfaces model can access the NetworkInterface
    item with the \e entry role.

    \sa NetworkInterface
*/

/*!
    \qmlmethod NetworkService NetworkSettingsManager::service(string name, int type)

    Returns the service with name \a name and type \a type.

    \sa services
*/

/*!
    \qmlmethod NetworkInterface NetworkSettingsManager::interface(int type, int instance)

    Returns the interface with type \a type and order number of \a instance

    \sa NetworkInterface
*/

/*!
    \qmlmethod NetworkSettingsManager::userAgent.setPassphrase(string passphrase)

    Sets the \a passphrase for connecting to a Wifi network.

    This method needs to be called in response to receiving a showUserCredentialsInput() signal.

    \sa userAgent.showUserCredentialsInput()
*/

/*!
    \qmlsignal NetworkSettingsManager::userAgent.showUserCredentialsInput()

    This signal is emitted when user credentials are required for connecting to a Wifi network.

    \sa userAgent.setPassphrase()
*/

/*!
    \qmlmethod NetworkSettingsManager::userAgent.cancelInput()

    Cancels the user credentials input request.
*/

/*!
    \qmlsignal NetworkSettingsManager::userAgent.error()

    This signal is emitted when the connection failed due to invalid user credentials.
*/
