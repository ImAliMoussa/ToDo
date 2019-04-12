#include "mainwindow.h"
#include "view.h"
#include <QApplication>
#include <QFile>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    MainWindow *window = new MainWindow();
    View *view = new View(window);
    QFile file(":/Stylesheets/styelsheet.qss");
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
       return 1;

    QString StyleSheet = QLatin1String(file.readAll());

    //qApp->setStyleSheet(StyleSheet);
    window->setView(view);
    window->setUpSlots();
    window->show();

    return app.exec();
}
