import QtQuick 2.0

Row {
    spacing: 3
    id:item

    property alias display_text: text_id
    property alias default_text: d_text
    property alias default_rect: d_rect
    property alias value_rect: v_rect
    property alias image: image

    Rectangle{
        id: d_rect
        Image {
            id: image
            width: 50; height: 50
        }
        Text {
            anchors.horizontalCenter: default_rect.horizontalCenter
            anchors.verticalCenter: default_rect.verticalCenter
            id: d_text
        }
        width: 50; height: 50
    }
    Rectangle{
        id: v_rect
        Text{
            anchors.horizontalCenter: v_rect.horizontalCenter
            anchors.verticalCenter: v_rect.verticalCenter
            id: text_id
            color:"white"
        }
        width: 100; height: 50
    }
}
