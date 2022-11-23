import QtQuick 2.0

Row {
    spacing: 3
    id:item

    property alias display_text: text_id
    property alias default_text: d_text
    property alias default_rect: d_rect

    Rectangle{
        id: d_rect
        Text {
            anchors.horizontalCenter: default_rect.horizontalCenter
            anchors.verticalCenter: default_rect.verticalCenter
            id: d_text
            text: qsTr("DEFAULT VALUE")
        }
        width: 50; height: 50
    }
    Rectangle{
        id: value_rect
        Text{
            anchors.horizontalCenter: value_rect.horizontalCenter
            anchors.verticalCenter: value_rect.verticalCenter
            id: text_id
            color:"white"
        }
        width: 100; height: 50
    }
}
