import QtQuick 2.0
import QtQuick.Controls 2.0


Item{
    width: 1024
    height: 720
    Column {
        id: column
        x: 30
        y: 37
        width: 934
        height: 396
    }

    First_row {
        id: first_row
        x: 46
        y: 67
    }

    Second_row {
        id: second_row
        x: 208
        y: 248
    }

    Row {
        id: row
        x: 52
        y: 136
        width: 630
        height: 179

        Date {
            id: date
        }
    }

    Set_drift_depth {
        id: set_drift_depth
        x: 248
        y: 191
        anchors.topMargin: 0
        anchors.top: row.top
    }

    Slider {
        id: slider
        x: 433
        y: 136
        spacing: 0
        orientation: Qt.Vertical
        stepSize: 10
        to: 50
        from: -54
        anchors.topMargin: 48
        anchors.top: row.top
        value: 0
    }

}



