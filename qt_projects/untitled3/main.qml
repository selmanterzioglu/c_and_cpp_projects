import QtQuick 2.15
import QtQuick.Window 2.15

Image {

    id:root
    Image{
        id: wheel
        Behavior on rotation {
            NumberAnimation{
                duration: 250
            }
        }

    }
}
