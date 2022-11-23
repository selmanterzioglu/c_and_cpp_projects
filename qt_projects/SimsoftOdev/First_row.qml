import QtQuick 2.0

Row {
    spacing: 3

    Display_elements{
        default_text.text: qsTr("HDG")
        display_text.text: qsTr("0")
        value_rect.color: "#2f2f2f"
        display_text.color: "white"
    }
    Display_elements{
        default_text.text: qsTr("COG")
        display_text.text: qsTr("0")
        value_rect.color: "#2f2f2f"
    }
    Display_elements{
        default_text.text: qsTr("MAG")
        display_text.text: qsTr("0")
        value_rect.color: "#2f2f2f"
    }
    Display_elements{
        default_text.text: qsTr("SOG")
        display_text.text: qsTr("0")
        value_rect.color: "#2f2f2f"
    }
    Display_elements{
        default_text.text: qsTr("LOG")
        display_text.text: qsTr("0")
        value_rect.color: "#2f2f2f"
    }
}
