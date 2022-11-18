import QtQuick 2.9

Item {
    id: root
    property real value : 0

    width: 400; height: 400

    Image { source: "./assets/dial/background.png" }

//! [needle_shadow]

/*!
    Image {
        x: 96
        y: 35
        source: "./assets/dial/needle_shadow.png"
        transform: Rotation {
            origin.x: 9; origin.y: 67
            angle: needleRotation.angle
        }
    }
*/


//! [needle_shadow]
//! [needle]
    Image {
        id: needle
        x: 238; y: 90
        antialiasing: true
        source: "./assets/dial/needle.png"
        transform: Rotation {
            id: needleRotation
            origin.x: 5; origin.y: 65
            //! [needle angle]
            angle: Math.min(Math.max(-130, root.value*2.6 - 130), 133)
            Behavior on angle {
                SpringAnimation {
                    spring: 1.4
                    damping: .15
                }
            }
            //! [needle angle]
        }
    }
//! [needle]
//! [overlay]
    //Image { x: 21; y: 18; source: "./assets/dial/overlay.png" }
//! [overlay]
}
