import QtQuick 2.3
import QtQuick.Controls 1.2

import "constants.js" as Constants

ApplicationWindow {
    visible: true
    width: Constants.WND_MINIMUM_WIDTH
    height: Constants.WND_MINIMUM_HEIGHT

    title: qsTr("Chess")

    menuBar: MenuBar {
        Menu {
            title: qsTr("File")
            MenuItem {
                text: qsTr("&Open")
                onTriggered: console.log("Open action triggered");
            }
            MenuItem {
                text: qsTr("Exit")
                onTriggered: Qt.quit();
            }
        }
    }
    Board {

        anchors.centerIn: parent
    }

}
