//row.qml


import QtQuick 2.3


BrightSquare{
	id: root
	width: 400; height: 120

	Row{
		id: row
		anchors.centerIn:parent
		spacing: 20

		Rectangle {color: "red"
			width: 300 
			height: 300
		}
		
		Rectangle {color: "blue"
			width: 300 
			height: 300
		}
		
		Rectangle {color: "green"
			width: 300 
			height: 300
		}
	}
}