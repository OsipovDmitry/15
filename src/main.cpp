#include <QApplication>

#include "gamewidget.h"
#include "game15.h"

int main(int argc, char **argv) {
    QApplication application(argc, argv);

    game::GameWidget gameWidget;
    gameWidget.show();

    auto pGame15 = game::Game15::createGame15(gameWidget.graphicsController());

    gameWidget.setGame(pGame15);

    return application.exec();
}
