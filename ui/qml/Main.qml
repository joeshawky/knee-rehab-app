import QtQuick
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.3

Window {
    id: _root

    width: 550
    height: 881

    visible: true
    title: qsTr("Knee Rehab")



    Loader {
        id: mainLoader
        anchors.fill: parent
        source: utilities.currentQmlPage
    }



}
