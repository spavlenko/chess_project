import QtQuick 2.0
import "constants.js" as Constants


Item {
    id: root
    height: parent.width
    width: height
    property int cell_size: width/Constants.BOARD_SIZE

    Item {
        id: move
        property int drop_destination: -1
        property int dragging_figure_id: -1
    }

    Grid {
        id: board_grid

        rows: Constants.BOARD_SIZE
        columns: Constants.BOARD_SIZE

        Repeater {
            id: repeater

            model: game.boardController().board;

            BoardCell{
                id: board_cell
                side_length: root.cell_size
                position: index

                onDragEntered: {
                 move.drop_destination = position;
                }

                onDragLeft: {
                 move.drop_destination = -1;
                }
            }
        }

    }

    Grid {
        id: figures_grid
        anchors.fill: parent

        rows: Constants.BOARD_SIZE
        columns: Constants.BOARD_SIZE

        Repeater {
            id: repeater_figures;

            model: game.boardController().board;
            ChessFigure {
               position: index
               size: cell_size
               type: modelData.type;
               side: modelData.side;


               onDragging: {
                   move.dragging_figure_id = position;
                   console.log("Dragging");
               }

               onDropped: {
                   console.log("Move: " + move.dragging_figure_id +
                               " to: " + move.drop_destination);
                   var from = move.dragging_figure_id;
                   var to =  move.drop_destination;

                   move.dragging_figure_id = -1;
                   move.drop_destination = -1;


                   if(from >= 0 && to >= 0 )
                    game.boardController().moveFigure(from, to);

                   //why if i put move.dragging_figure_id = -1; here, I've got  ReferenceError: move is not defined

               }
            }

        }
    }
}
