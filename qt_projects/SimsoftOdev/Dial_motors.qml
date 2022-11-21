import QtQuick 2.9
import QtQuick.Extras 1.4



Item {


CircularGauge {
//    minimumValue: 0
//    maximumValue: 200

    property real minimumValue: 0
    property real maximumValue: 100
    property real labelStepSize: 20

    //value: accelerating ? maximumValue : 0
//    anchors.centerIn: parent

//    property bool accelerating: false

//    Keys.onSpacePressed: accelerating = true
//    Keys.onReleased: {
//        if (event.key === Qt.Key_Space) {
//            accelerating = false;
//            event.accepted = true;
//        }
//    }

//    Behavior on value {
//        NumberAnimation {
//            duration: 1000
//        }
//    }
}
}
