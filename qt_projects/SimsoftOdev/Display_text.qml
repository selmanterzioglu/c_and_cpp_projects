import QtQuick 2.0

Row {
    spacing: 3

    Text {
        text: qsTr("HDG VALUE")
    }
    Rectangle{
        Text {
            id: hdg_text
            text: qsTr("0")
            color:"white"
        }
        width: 100; height: 50
        color:"#2f2f2f"
    }

    Text {
        text: qsTr("COG VALUE")
    }
    Rectangle{
        Text {
            id: cog_text
            text: qsTr("0")
            color:"white"
        }
        width: 100; height: 50
        color:"#2f2f2f"
    }
    Text {
        text: qsTr("MAG VALUE")
    }
    Rectangle{
        Text {
            id: mag_text
            text: qsTr("0")
            color:"white"
        }
        width: 100; height: 50
        color:"#2f2f2f"
    }
    Text {
        text: qsTr("SOG VALUE")
    }
    Rectangle{
        Text {
            id: sog_text
            text: qsTr("0")
            color:"white"
        }
        width: 100; height: 50
        color:"#2f2f2f"
    }
    Text {
        text: qsTr("LOG VALUE")
    }
    Rectangle{
        Text {
            id: log_text
            text: qsTr("0")
            color:"white"
        }
        width: 100; height: 50
        color:"#2f2f2f"
    }
}
