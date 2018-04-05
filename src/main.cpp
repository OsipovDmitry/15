#include <QApplication>

#include "gamewidget.h"
#include "game15.h"

game::GameWidget *gameWidget;

int main(int argc, char **argv) {
    QApplication application(argc, argv);

	gameWidget = new game::GameWidget;
	gameWidget->show();

	auto pGame15 = game::Game15::createGame15(gameWidget->graphicsController());

	gameWidget->setGame(pGame15);

    return application.exec();
}
