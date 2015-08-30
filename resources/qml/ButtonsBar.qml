import QtQuick 2.0
import QtQuick.Controls 1.2
import QtQuick.Layouts 1.1

ColumnLayout {
    id: buttons_bar_layout
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

