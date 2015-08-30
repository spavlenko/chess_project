import QtQuick 2.3
import QtQuick.Controls 1.2
import QtQuick.Layouts 1.1


ApplicationWindow {
    visible: true
    width: 640
    height: 480

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

            mode: game.mode

            onStart: game.start();
            onStop: game.stop();
            onSave: game.save();
            onLoad: game.load();
            onPrev: game.prevTransition();
            onNext: game.nextTransition();
        }

    }


}
