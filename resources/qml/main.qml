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

        ColumnLayout {
            id: buttons_bar_layout
            anchors.top: row_layout.top
            anchors.left: board.right;
            anchors.right: row_layout.right;
            anchors.bottom: row_layout.bottom;
            anchors.margins: 6
            spacing: 6

            Button {
                id: button_load
                Layout.minimumWidth: 50
                Layout.preferredWidth: 100
                Layout.minimumHeight: 50

                anchors.left: parent.left; anchors.right: parent.right;
                Text {
                    anchors.centerIn: parent
                    text: "Load game"
                }

                onClicked: {
                    game.load();
                }
               }

            Button {
                id: button_save
                Layout.minimumWidth: 40
                Layout.preferredWidth: 47

                Layout.minimumHeight: 50

                anchors.left: parent.left; anchors.right: parent.right;
                Text {
                    anchors.centerIn: parent
                    text: "Save game"
                }

                onClicked: {
                    game.save();
                }
            }

            RowLayout {
                id: prev_next_layout
                anchors.top: button_save.bottom
                anchors.left: parent.left
                anchors.right: parent.right

                Button {
                    id: button_prev
                    Layout.minimumWidth: 50

                    Layout.minimumHeight: 50
                    anchors.left: parent.left
                    anchors.right: parent.horizontalCenter

                    Text {
                        anchors.centerIn: parent
                        text: "<<"
                    }

                    onClicked: {
                        if(!game.prevTransition())
                          console.log("Unable to perform prev");
                    }
                }

                Button {
                    id: button_next
                    Layout.minimumWidth: 50

                    Layout.minimumHeight: 50
                    anchors.right: parent.right;
                    anchors.left: parent.horizontalCenter

                    Text {
                        anchors.centerIn: parent
                        text: ">>"
                    }

                    onClicked: {
                        if(!game.nextTransition())
                          console.log("Unable to perform next");
                    }
                }

            }

        }


    }


}
