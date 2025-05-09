import QtQuick
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.3


Rectangle{
    id: mainRectangle
    anchors.fill: parent
    color: utilities.darkBgColor

    property string mode: bluetoothSocketManager.currentMode
    property bool mode_active: bluetoothSocketManager.currentStatus === "MODE_START" ? true : false

    property bool exercise_mode: mode === "EXERCISE_MODE"
    property bool training_mode: mode === "TRAINING_MODE"
    property bool free_mode: mode === "IMPEDANCE_MODE"


    Row{
        id: modesTitle
        anchors{
            horizontalCenter: mainRectangle.horizontalCenter
            top: mainRectangle.top
            topMargin: mainRectangle.height * 0.025
        }
        width: _root.width * 0.85
        spacing: 10
        Text{
            anchors{
                verticalCenter: modesTitle.verticalCenter
            }
            text: "Modes"
            color: "white"
            font.pixelSize: 32
            font.family: utilities.defaultFont
        }
        Image{
            anchors{
                verticalCenter: modesTitle.verticalCenter
                verticalCenterOffset: 3
            }

            source: "qrc:/images/purple-arrow.svg"
        }
    }

    Column{
        spacing: 15
        anchors{
            horizontalCenter: mainRectangle.horizontalCenter
            top: modesTitle.bottom
            topMargin: 15
        }

        Rectangle{
            id: trainingModeRectangle
            width: _root.width * 0.85
            height: mainRectangle.height * 0.075
            radius: height * 0.25
            color: utilities.lightBgColor

            RowLayout{
                id: trainingModeRow
                width: trainingModeRectangle.width
                height: trainingModeRectangle.height
                spacing: 0

                Image{
                    source: "qrc:/images/training-mode-icon.svg"
                    Layout.alignment: Qt.AlignVCenter
                    Layout.leftMargin: 15
                }

                Text{
                    font{
                        pixelSize: 20
                        family: utilities.defaultFont
                    }
                    Layout.alignment: Qt.AlignVCenter
                    Layout.fillWidth: true
                    Layout.leftMargin: 20
                    text: "Training Mode"
                    color: utilities.modeTextColor
                }

                Image{
                    source: mainRectangle.training_mode && mainRectangle.mode_active ? "qrc:/images/stop-icon.svg" : "qrc:/images/play-icon.svg"
                    Layout.alignment: Qt.AlignRight
                    Layout.rightMargin: 15
                    MouseArea{
                        anchors.fill: parent
                        onClicked: {
                            bluetoothSocketManager.setMode("TRAINING_MODE")
                        }
                    }
                }
            }
        }

        Rectangle{
            id: exerciseModeRectangle
            width: _root.width * 0.85
            height: mainRectangle.height * 0.075
            radius: height * 0.25
            color: utilities.lightBgColor

            RowLayout{
                id: exerciseModeRow
                width: exerciseModeRectangle.width
                height: exerciseModeRectangle.height
                spacing: 0

                Image{
                    source: "qrc:/images/exercise-mode-icon.svg"
                    Layout.alignment: Qt.AlignVCenter
                    Layout.leftMargin: 15
                }

                Text{
                    font{
                        pixelSize: 20
                        family: utilities.defaultFont
                    }
                    Layout.alignment: Qt.AlignVCenter
                    Layout.fillWidth: true
                    Layout.leftMargin: 20
                    text: "Exercise Mode"
                    color: utilities.modeTextColor

                }

                Image{
                    source: mainRectangle.exercise_mode && mainRectangle.mode_active ? "qrc:/images/stop-icon.svg" : "qrc:/images/play-icon.svg"
                    Layout.alignment: Qt.AlignRight
                    Layout.rightMargin: 15
                    MouseArea{
                        anchors.fill: parent
                        onClicked: {
                            bluetoothSocketManager.setMode("EXERCISE_MODE")
                        }
                    }
                }
            }
        }

        Rectangle{
            id: impedanceModeRectangle
            width: _root.width * 0.85
            height: mainRectangle.height * 0.075
            radius: height * 0.25
            color: utilities.lightBgColor

            RowLayout{
                id: freegModeRow
                width: impedanceModeRectangle.width
                height: impedanceModeRectangle.height
                spacing: 0

                Image{
                    source: "qrc:/images/free-mode-icon.svg"
                    Layout.alignment: Qt.AlignVCenter
                    Layout.leftMargin: 15
                }

                Text{
                    font{
                        pixelSize: 20
                        family: utilities.defaultFont
                    }
                    Layout.alignment: Qt.AlignVCenter
                    Layout.fillWidth: true
                    Layout.leftMargin: 20
                    text: "Impedance Control"
                    color: utilities.modeTextColor

                }

                Image{
                    // source: "qrc:/images/play-icon.svg"
                    source: mainRectangle.free_mode && mainRectangle.mode_active ? "qrc:/images/stop-icon.svg" : "qrc:/images/play-icon.svg"
                    Layout.alignment: Qt.AlignRight
                    Layout.rightMargin: 15
                    MouseArea{
                        anchors.fill: parent
                        onClicked: {
                            bluetoothSocketManager.setMode("IMPEDANCE_MODE")
                        }
                    }
                }
            }
        }

        //spacer
        Item{
            width: _root.width * 0.85
            height: mainRectangle.height * 0.015
        }

        RowLayout{
            id: angleRowLayout
            width: _root.width * 0.85
            height: _root.height * 0.2

            Rectangle{
                id: currentAngleRectangle
                Layout.alignment: Qt.AlignLeft
                Layout.fillWidth: true
                height: angleRowLayout.height
                radius: height * 0.1
                color: utilities.lightBgColor

                Text{
                    anchors{
                        horizontalCenter: parent.horizontalCenter
                        top: parent.top
                        topMargin: 15
                    }
                    font{
                        family: utilities.defaultFont
                        pixelSize: 18
                    }
                    text: "Current Angle"
                    color: "white"
                }

                Image{
                    id: currentAngleImage
                    anchors{
                        centerIn: currentAngleRectangle
                        verticalCenterOffset: 10
                        horizontalCenterOffset: -45
                    }
                    source: "qrc:/images/angle-icon.svg"
                }

                Text{
                    id: currentAngleText
                    property double counter: 0.0
                    property bool counterIncrease: true
                    anchors{
                        verticalCenter: currentAngleImage.verticalCenter
                        left: currentAngleImage.right
                        leftMargin: 5
                    }
                    font{
                        family: utilities.defaultFont
                        pixelSize: 20
                    }
                    // text: "90.0°"
                    text: bluetoothSocketManager.rpConnected ? bluetoothSocketManager.currentAngle.toFixed(2) + "°" : "xxx"

                    Timer{
                        interval: 100
                        running: false
                        repeat: false
                        onTriggered: {
                            console.log(`rpConnected: ${bluetoothSocketManager.rpConnected}`);
                        }
                    }

                    color: "white"

                    Timer{
                        interval: 20
                        running: false
                        repeat: false
                        onTriggered: {
                            if (currentAngleText.counter === 0.0)
                                currentAngleText.counterIncrease = true;
                            else if (currentAngleText.counter === 180.0)
                                currentAngleText.counterIncrease = false;


                            if (currentAngleText.counterIncrease)
                                currentAngleText.counter += 0.1;
                            else
                                currentAngleText.counter -= 0.1;


                            let displayCounter = currentAngleText.counter.toFixed(1);
                            currentAngleText.counter = currentAngleText.counter.toFixed(1)

                            currentAngleText.text = `${displayCounter}°`
                        }
                    }
                }
            }

            Item{
                height: angleRowLayout.height
                Layout.preferredWidth: angleRowLayout.width * 0.0
            }

            Rectangle{
                id: targetAngleRectangle
                Layout.alignment: Qt.AlignRight
                Layout.fillWidth: true
                height: angleRowLayout.height
                radius: height * 0.1
                color: utilities.lightBgColor

                Text{
                    anchors{
                        horizontalCenter: parent.horizontalCenter
                        top: parent.top
                        topMargin: 15
                    }
                    font{
                        family: utilities.defaultFont
                        pixelSize: 18
                    }
                    text: "Target Angle"
                    color: "white"
                }

                Image{
                    id: targetAngleImage
                    anchors{
                        centerIn: targetAngleRectangle
                        verticalCenterOffset: 10
                        horizontalCenterOffset: -45
                    }
                    source: "qrc:/images/angle-icon.svg"
                }

                Text{
                    id: targetAngleText


                    anchors{
                        verticalCenter: targetAngleImage.verticalCenter
                        left: targetAngleImage.right
                    }
                    font{
                        family: utilities.defaultFont
                        pixelSize: 20
                    }
                    text: !bluetoothSocketManager.rpConnected || bluetoothSocketManager.targetAngleSeconds === -1 ? "xxx" : bluetoothSocketManager.targetAngle.toFixed(2) + "°"
                    color: "white"
                }
            }
        }
    }

    Text{
        anchors{
            bottom: mainRectangle.bottom
            right: mainRectangle.right
            bottomMargin: 20
            rightMargin: 20
        }
        font{
            pixelSize: 15
            family: utilities.defaultFont
        }

        color: "#9277DE"
        text: bluetoothSocketManager.rpConnected ?  "ip: " + bluetoothSocketManager.ip : "ip: "
    }

    Rectangle{
        id: debugRectangle
        anchors{
            bottom: mainRectangle.bottom
            left: mainRectangle.left
            bottomMargin: 20
            leftMargin: 20
        }
        width: mainRectangle.width * 0.15
        height: mainRectangle.width * 0.1
        radius: height * 0.25
        color: utilities.lightBgColor

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
                utilities.currentQmlPage = "qrc:/KneeRehab/ui/qml/DebugPage.qml"
            }
        }
    }

    Rectangle{
        anchors{
            bottom: mainRectangle.bottom
            left: debugRectangle.right
            bottomMargin: 20
            leftMargin: 25
        }
        width: mainRectangle.width * 0.25
        height: mainRectangle.width * 0.1
        radius: height * 0.25
        color: utilities.lightBgColor

        Text{
            anchors.centerIn: parent
            font{
                pixelSize: 15
                family: utilities.defaultFont
            }
            color: "white"
            text: bluetoothSocketManager.rpConnected ? "Disconnect" : "Connect"
        }

        MouseArea{
            anchors.fill: parent
            onPressed: {
                bluetoothSocketManager.toggleConnection();
                // utilities.currentQmlPage = "qrc:/KneeRehab/ui/qml/DebugPage.qml"
            }
        }
    }
}

