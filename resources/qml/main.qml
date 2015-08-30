import QtQuick 2.3
import QtQuick.Controls 1.2
import QtQuick.Layouts 1.1

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

    RowLayout {
        id: row_layout
        anchors.fill: parent
        spacing: 6

        Board {
            id: board
            anchors.left: row_layout.left;
            anchors.top: row_layout.top;
            anchors.bottom: parent.bottom;

            anchors.margins: 6

        }

        ButtonsBar {
            id: game_controls_bar
            anchors.top: row_layout.top
            anchors.left: board.right;
            anchors.right: row_layout.right;
            anchors.bottom: row_layout.bottom;
        }

    }


}
