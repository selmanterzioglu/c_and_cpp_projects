import QtQuick 2.0

Column {
    spacing: 3

    //date
    Display_elements{
        display_text.color: "black"
        default_text.text: qsTr("SHIP")
        display_text.text: qsTr("24 Sep 2021")
    }
    //clock info
    Display_elements{
        display_text.color: "black"
        image.source: "./assets/clock.png"
        display_text.text: qsTr("09:42:11")
    }
    // sim info
    Display_elements{
        display_text.color: "black"
        default_text.text: qsTr("SIM")
        display_text.text: qsTr("00:00:00")
    }
}
