import QtQuick 2.0
import Chess 1.0
import "."


Item {
    id: root
    height: parent.width
    width: height
    property int board_size: 8
    property int cell_size: width/board_size
    property int side: game.activeSide;
    Item {
        id: move
        property int drop_destination: -1
        property int dragging_figure_id: -1
    }

    Grid {
        id: board_grid
        rows: board_size
        columns: board_size

        Repeater {
            id: repeater

            model: game.boardController().board;

            BoardCell{
                id: board_cell
                side_length: root.cell_size
                position: index
                board_size: root.board_size
                onDragEntered: {
                    move.drop_destination = position;
                    board_cell.drop_allowed =
                            game.boardController().isMoveAllowed(move.dragging_figure_id, position);

                }

                onDragLeft: {
                    board_cell.drop_allowed = false;
                    move.drop_destination = -1;
                }
            }
        }
    }

    Grid {
        id: figures_grid
        anchors.fill: parent

        rows: board_size
        columns: board_size

        Repeater {
            id: repeater_figures;

            model: game.boardController().board;
            ChessFigure {
               id: figure
               position: index
               size: cell_size
               type: modelData.type;
               side: modelData.side;


               onDragging: {
                   move.dragging_figure_id = position;
               }

               onDropped: {
                   var from = move.dragging_figure_id;
                   var to =  move.drop_destination;

                   move.dragging_figure_id = -1;
                   move.drop_destination = -1;

                   if(from >= 0 && to >= 0 )
                    game.boardController().moveFigure(from, to);

               }

               states:
                   State{
                   when: root.side
                   PropertyChanges {
                       target: figure
                       dragable: figure.side == root.side && game.mode != GameController.PLAYBACK

                   }
               }
            }
        }
    }
}
