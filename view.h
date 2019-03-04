#ifndef VIEW_H
#define VIEW_H

#include <QWidget>
#include <QLabel>
#include <QPushButton>
#include <QSpacerItem>
#include <QScrollArea>
#include <QMainWindow>
#include <QHBoxLayout>
#include <QVBoxLayout>

class View
{
public:
    // Widget Containing all
    QWidget *centralWidget;
    QVBoxLayout *centralWidgetLayout;

    // TOP WIDGET
    QWidget *toolsWidget;
    QHBoxLayout *toolsLayout;
    QPushButton *addTaskButton;
    QSpacerItem *topWidgetSpacer;
    QLabel *statusLabel;

    //CENTER WIDGET CONTAINING TASKS
    QScrollArea *tasksScrollArea;
    QWidget *tasksWidget;
    QVBoxLayout *tasksLayout;
    QSpacerItem *tasksSpacer;

public:
    View(QMainWindow *mainWindow);
};

#endif // VIEW_H
