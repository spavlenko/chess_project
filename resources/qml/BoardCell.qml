import QtQuick 2.0
import "."
import "constants.js" as Constants

Item {
    id: root
    property int side_length: -1
    property int position: -1

    width: side_length
    height: side_length

    signal dragEntered
    signal dragLeft


    DropArea {
        id: drop_area
        property bool dragging: false
        width: root.side_length
        height: root.side_length

        onEntered: {
            dragging = true;
            dragEntered();
        }

        onExited: {
            dragging = false;
            dragLeft();
        }

        Rectangle {
            id: cell
            width: parent.width;
            height: parent.height
            border.width: 1
            border.color: Style.color_border
            color: (Math.floor(root.position / Constants.BOARD_SIZE)
                    + (root.position % Constants.BOARD_SIZE)) % 2
                    ? Style.color_cell_white : Style.color_cell_black
        }

        states:
            State {
            when: drop_area.dragging
            PropertyChanges {
                target: cell
                color: Style.color_cell_to_drop

            }
        }

    }
}
