import QtQuick 2.0

Item {
    id:item
    Text {
        text: qsTr("HDG VALUE")
    }
    Rectangle{
        Text {
            id: id
            text: qsTr("0")
            color:"white"
        }
        width: 100; height: 50
        color:"#2f2f2f"
    }
}
