#include "mainwindow.h"
#include "view.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    MainWindow *window = new MainWindow();
    View *view = new View(window);
    window->setView(view);
    window->setUpSlots();
    window->show();

    return app.exec();
}
