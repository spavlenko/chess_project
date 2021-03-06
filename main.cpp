#include <QApplication>
#include <QQmlApplicationEngine>
#include <QQuickView>
#include <QQmlComponent>
#include <QQmlContext>
#include <QWidget>

#include"Figure.h"

#include "BoardController.h"
#include "GameController.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    qmlRegisterType<Figure>("Chess", 1,0, "Figure");

    qmlRegisterType<BoardController>("Chess", 1,0, "GameBoard");
    qmlRegisterType<GameController>("Chess", 1,0, "GameController");

    QQmlApplicationEngine engine;

    QQmlContext* ctx = engine.rootContext();
    auto p_game_controller = new GameController(&engine);
    ctx->setContextProperty("game", p_game_controller);
    engine.load(QUrl(QStringLiteral("qrc:/qml/main.qml")));

    return app.exec();

}
