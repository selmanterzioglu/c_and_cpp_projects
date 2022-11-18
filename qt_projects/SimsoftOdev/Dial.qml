import QtQuick 2.9
Item {
    id: root
    property real value : 0

    width: 210; height: 210

    Image { source: "./assets/dial/background.png" }

    Image {
        id: needle
        x: 98; y: 33
        antialiasing: true
        source: "./assets/dial/needle.png"
        transform: Rotation {
            id: needleRotation
            origin.x: 5; origin.y: 65
            angle: Math.min(Math.max(-130, (value+50)*2.6 - 130), 133)
            Behavior on angle {
                SpringAnimation {
                    spring: 1.4
                    damping: .15
                }
            }
        }
    }
}
