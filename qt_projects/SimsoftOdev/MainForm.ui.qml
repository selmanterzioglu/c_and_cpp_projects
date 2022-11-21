import QtQuick 2.7

Rectangle {
    property alias mouseArea: mouseArea

    width: 360
    height: 360

    MouseArea {
        id: mouseArea
        anchors.rightMargin: 57
        anchors.bottomMargin: 55
        anchors.leftMargin: -57
        anchors.topMargin: -55
        anchors.fill: parent

        Dial_motors {
            id: dial_motors
            x: 145
            y: 148
        }
    }
}
