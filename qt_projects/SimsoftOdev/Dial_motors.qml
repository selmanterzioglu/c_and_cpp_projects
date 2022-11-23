import QtQuick 2.5
import QtQuick.Extras 1.4
import QtQuick.Controls.Styles 1.4
import QtQuick.Controls 1.4


Rectangle{
    color: "#000000"

    CircularGauge {
        id: circular
        property real minimumValue: -1000
        property real maximumValue: 1000

        property real minimumValueAngle: -145
        property real maximumValueAngle: 145
        x: 0
        y: 0
        value: 1
        visible: true
        scale: 1

        style: CircularGaugeStyle{

            foreground: Item {
                Rectangle {
                    width: outerRadius * 0.2
                    height: width
                    radius: width / 2
                    color: "#e5e5e5"
                    anchors.centerIn: parent
                }
            }

            needle: Rectangle {
                y: outerRadius * 0.15
                implicitWidth: outerRadius * 0.03
                implicitHeight: outerRadius * 0.9
                antialiasing: true
                color: "white"
            }
            labelStepSize :200
            tickmarkStepSize: 200

            property real minimumValueAngle: circular.minimumValueAngle
            property real maximumValueAngle: circular.maximumValueAngle

            tickmarkLabel:  Text {
                id: tickmark_id
                color: get_color(tickmark_id);
                text:styleData.value
                antialiasing: true
            }
            function get_color(tickmark_id)
            {
                var handColor = tickmark_id.text

                if(handColor > 0)
                    return "green"

                else if (handColor < 0)
                    return "red"

                return  "white";
            }

        }
    }
}
