import QtQuick 2.0
import Chess 1.0
import "."

Item {
    id: root

    property int position: -1
    property int size:  -1

    property int  type: Figure.NONE
    property int  side: Figure.WHITE
    property bool dragable: false

    signal dragging
    signal dropped

    width: size
    height: size

    MouseArea {
           id: mouse

           anchors.fill: parent
           drag.target: represetntation
           enabled: dragable

           onPressed: root.dragging();
           onReleased: root.dropped();
    }

    Rectangle {
        id: represetntation
        anchors.verticalCenter: parent.verticalCenter
        anchors.horizontalCenter: parent.horizontalCenter

        width: parent.size
        height: parent.size

        Drag.active: mouse.drag.active
        Drag.hotSpot.x: size/2
        Drag.hotSpot.y: size/2
        color: "transparent"
        border.width: 0

        Image  {
          id: image
          source: getImagePath(type, side)
          fillMode: Image.PreserveAspectFit
          anchors.fill: parent
          anchors.margins: 2
        }

        states: [
            State {
               when: mouse.drag.active
               ParentChange {
                   target: represetntation;
                   parent: root
               }

               AnchorChanges {
                   target: represetntation;
                   anchors.verticalCenter: undefined;
                   anchors.horizontalCenter: undefined
               }
             },

            State {
                when:root.dragable

                PropertyChanges {
                    target: represetntation
                    border.color: Style.color_border_active_side
                    border.width: 2
                }
            }

            ]
    }



    function getImagePath(type, side) {

        if(type === Figure.NONE)
            return "";

        var figure_color = side === Figure.BLACK ? "black" : "white";
        var figure_type = "";

        switch(type) {
            case Figure.KING:
                figure_type = "king";
                break;
            case Figure.QUEEN:
                figure_type = "queen";
                break;
            case Figure.KNIGHT:
                figure_type = "knight";
                break;
            case Figure.BISHOP:
                figure_type = "bishop";
                break;
            case Figure.ROOK:
                figure_type = "rook";
                break;
            case Figure.PAWN:
                figure_type = "pawn";
                break;

            default:
                return "";
        }

        return "qrc:/images/" + figure_color + "/" + figure_type ;
    }


}
