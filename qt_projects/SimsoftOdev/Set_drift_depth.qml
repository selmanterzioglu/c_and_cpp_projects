import QtQuick 2.0

Column {
    spacing: 3

    Display_elements{
        default_text.text: qsTr("SET")
        display_text.text: qsTr("0")
        value_rect.color: "#2f2f2f"
        display_text.color: "white"
    }
    Display_elements{
        default_text.text: qsTr("DRIFT")
        display_text.text: qsTr("0")
        value_rect.color: "#2f2f2f"
    }
    Display_elements{
        default_text.text: qsTr("DEPTH")
        display_text.text: qsTr("0")
        value_rect.color: "#2f2f2f"
    }

}
