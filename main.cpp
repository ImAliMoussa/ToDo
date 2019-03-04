#include "mainwindow.h"
#include <view.h>
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow *w = new MainWindow();
    View *view = new View(w);
    w->setView(view);
    w->setUpSlots();
    w->show();

    return a.exec();
}
