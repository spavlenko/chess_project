import QtQuick 2.3
import QtQuick.Controls 1.2
import QtQuick.Dialogs 1.2
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
            onSave: save_game_dialog.open();
            onLoad: load_game_dialog.open();
            onPrev: game.prevTransition();
            onNext: game.nextTransition();
        }

        FileDialog {
            id: save_game_dialog
            title: "Save Game"
            selectExisting: false
            nameFilters: [ "Chess save files (*.csf)"]
            onAccepted: {
                game.save(save_game_dialog.fileUrl);
            }
        }

        FileDialog {
            id: load_game_dialog
            title: "Open Game"
            nameFilters: [ "Chess save files (*.csf)" ]
            onAccepted: {
                game.load(load_game_dialog.fileUrl);
            }
        }

    }


}
