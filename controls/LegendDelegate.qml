import QtQuick 2.9
import QtQuick.Layouts 1.2
import QtQuick.Controls 2.2

import org.kde.quickcharts 1.0 as Charts
import org.kde.quickcharts.controls 1.0

RowLayout {
    id: delegate

    Layout.fillHeight: false
    Layout.preferredWidth: 0

    property string name
    property color color
    property string value
    property color valueColor: name.color

    property real colorWidth: Theme.smallSpacing
    property real valueWidth: -1

    property bool colorVisible: true
    property bool valueVisible: true

    property alias font: name.font

    property Component indicator: null

    property real layoutWidth: -1

    spacing: Theme.smallSpacing

    opacity: parent.height >= y + height // This will hide the item if it is out of bounds

    Loader {
        Layout.preferredHeight: name.contentHeight
        Layout.preferredWidth: delegate.colorWidth

        visible: delegate.colorVisible

        property color delegateColor: delegate.color

        sourceComponent: delegate.indicator != null ? delegate.indicator : defaultIndicator

    }

    Label {
        id: name

        Layout.fillWidth: true
        Layout.fillHeight: true

        text: delegate.name
        visible: {
            if (delegate.layoutWidth < 0) {
                return true;
            }

            return delegate.layoutWidth - delegate.colorWidth - delegate.spacing * 2 >= contentWidth
        }
        verticalAlignment: Qt.AlignVCenter
    }

    Label {
        id: value

        Layout.fillHeight: true
        Layout.preferredWidth: delegate.valueWidth

        text: delegate.value;
        font: name.font
        color: delegate.valueColor
        verticalAlignment: Qt.AlignVCenter
        horizontalAlignment: Qt.AlignRight

        visible: {
            if (!delegate.valueVisible) {
                return false;
            }

            if (delegate.layoutWidth < 0) {
                return true;
            }

            return delegate.layoutWidth - delegate.colorWidth - delegate.spacing * 4 - name.contentWidth >= delegate.valueWidth
        }
    }

    Component { id: defaultIndicator; Rectangle { color: delegateColor } }
}
