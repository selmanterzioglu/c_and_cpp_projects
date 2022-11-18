import QtQuick 2.9
import QtQuick.Window 2.2

Window {
       
    visible: true
        
    title: qsTr("Hello World")

    width: 640
    height: 480
    
    Dial {
        id: dial
        anchors.centerIn: parent
        //value: slider.x * 100 / (container.width - 32)
        value: 0
    }




}