import QtQuick
import QtQuick.Controls 2.15
// import Utilities 1.0


Rectangle{
    id: mainRectangle
    anchors.fill: parent
    color: utilities.lightBgColor

    Item{
        anchors.centerIn: parent
        width: parent.width * 0.9
        height: parent.height * 0.95


        Column{
            anchors{
                left: parent.left
                top: parent.top
            }
            width: parent.width * 0.5
            height: parent.height
            spacing: 20
            property var displayList: [
                "IP ",
                "current force ",
                "current angle ",
                "target angle ",
                "motor voltage ",
                "motor current ",
                "current mode "
            ]

            Repeater{
                model: parent.displayList
                Text{
                    text: modelData
                    color: "white"
                    font.pixelSize: 16
                    font.family: utilities.defaultFont
                }
            }
        }

        Column{
            anchors{
                right: parent.right
                top: parent.top
            }
            width: parent.width * 0.5
            height: parent.height
            spacing: 20
            property var displayList: [
                ": " + bluetoothSocketManager.ip,
                ": " + bluetoothSocketManager.force.toFixed(3) + " V",
                ": " + bluetoothSocketManager.currentAngle.toFixed(3),
                ": " + bluetoothSocketManager.targetAngle.toFixed(3),
                ": " + bluetoothSocketManager.motorPowerVoltage.toFixed(3) + " V",
                ": " + bluetoothSocketManager.motorPowerCurrent.toFixed(3) + " A",
                ": " + bluetoothSocketManager.currentMode.replace("_MODE", "") + " " + bluetoothSocketManager.currentStatus.replace("MODE_", "")
            ]

            Repeater{
                model: parent.displayList
                Text{
                    text: modelData
                    color: "white"
                    font.pixelSize: 16
                    font.family: utilities.defaultFont
                }
            }
        }

    }


    Rectangle{
        anchors{
            bottom: mainRectangle.bottom
            left: mainRectangle.left
            bottomMargin: 20
            leftMargin: 20
        }
        width: mainRectangle.width * 0.15
        height: mainRectangle.width * 0.1
        radius: height * 0.25
        color: utilities.darkBgColor

        Text{
            anchors.centerIn: parent
            font{
                pixelSize: 15
                family: utilities.defaultFont
            }
            color: "white"
            text: "Debug"
        }

        MouseArea{
            anchors.fill: parent
            onPressed: {
                utilities.currentQmlPage = "qrc:/KneeRehab/ui/qml/HomePage.qml"
            }
        }
    }
}

