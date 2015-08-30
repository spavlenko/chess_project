import QtQuick 2.0
import QtQuick.Controls 1.2
import QtQuick.Layouts 1.1

import Chess 1.0

Item {
    id: root
    property int mode: GameController.INIT

    signal start;
    signal stop;
    signal save;
    signal load;
    signal prev;
    signal next;

    ColumnLayout {
        id: buttons_bar_layout
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.top: parent.top
        anchors.margins: 6
        spacing: 6

        Button {
            id: button_start_stop
            Layout.minimumHeight: 50

            anchors.left: parent.left; anchors.right: parent.right;

            onClicked: {
                root.mode == GameController.GAME ? stop() : start();
            }
           }

        Button {
            id: button_load_save
            Layout.minimumHeight: 50

            anchors.left: parent.left; anchors.right: parent.right;

            onClicked: {
                root.mode == GameController.GAME ? save() : load();
            }
           }


        RowLayout {
            id: prev_next_layout
            anchors.left: parent.left
            anchors.right: parent.right

            Button {
                id: button_prev
                enabled: false
                Layout.minimumWidth: 50

                Layout.minimumHeight: 50
                anchors.left: parent.left
                anchors.right: parent.horizontalCenter

                Text {
                    anchors.centerIn: parent
                    text: "prev"
                }

                onClicked: {
                    prev();
                }
            }

            Button {
                id: button_next
                enabled: false
                Layout.minimumWidth: 50

                Layout.minimumHeight: 50
                anchors.right: parent.right;
                anchors.left: parent.horizontalCenter

                Text {
                    anchors.centerIn: parent
                    text: "next"
                }

                onClicked: {
                    next();
                }
            }

            Connections {
                target: game
                onNextAvailable: {
                   button_next.enabled = available;
                }

                onPrevAvailable: {
                   button_prev.enabled = available;
                }
            }
        }

        states: [
            State {
                when: mode == GameController.INIT

                PropertyChanges{
                    target: button_start_stop
                    text: "Start"
                }

                PropertyChanges{
                    target: button_load_save
                    text: "Load"
                }

                PropertyChanges{
                    target: prev_next_layout
                    visible: false
                }

            },

            State {
                when: mode == GameController.GAME

                PropertyChanges{
                    target: button_start_stop
                    text: "Stop"
                }

                PropertyChanges{
                    target: button_load_save
                    text: "Save"
                }

                PropertyChanges{
                    target: prev_next_layout
                    visible: false
                }
            },

            State {
                when: mode == GameController.PLAYBACK

                PropertyChanges{
                    target: button_start_stop
                    text: "Start"
                }

                PropertyChanges{
                    target: button_load_save
                    text: "Load"
                }

                PropertyChanges{
                    target: prev_next_layout
                    visible: true
                }
            }
        ]
    }
}

