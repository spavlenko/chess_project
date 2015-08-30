import QtQuick 2.0
import "."

Item {
    id: root
    property int side_length: -1
    property int position: -1
    property bool drop_allowed: false
    property int board_size: -1
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
            color: (Math.floor(root.position / board_size)
                    + (root.position % board_size)) % 2
                    ? Style.color_cell_white : Style.color_cell_black
        }

        states:[
            State {
               when: drop_area.dragging
               PropertyChanges {
                   target: cell
                   border.width: 2
                   color: Style.color_cell_to_drop
                   border.color: root.drop_allowed ? Style.color_cell_drop_allowed : Style.color_cell_drop_forbidden

               }
            }
        ]
    }
}
