import QtQuick 2.15

Item {
    id:root
    property real value  : 0
    width: 210; height: 210
    Image{source: "background.png"}
    Image{
        x: 95; y:35
        source: "needl_shadow.png"
        transform: Rotation{
            origin.x: 9; origin.y:67
            angle: needleRotation.angle
        }
    }
    Image {
        x:98; y:33
        antialiasing: true
        source: "needle.png"
        transform:Rotation{
            id: needleRotation
            origin.x: 5; origin.y: 65
            // needle angle

            angle: Math.min(Math.max(-130, root.value*2.6 - 130), 133)
            Behavior on angle{
                SpringAnimation{
                    spring: 1.4
                    damping .15
                }
                }
                }

                }



                }
