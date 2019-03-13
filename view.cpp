#include "view.h"

View::View(QMainWindow *mainWindow){
    centralWidget = new QWidget(mainWindow);
    centralWidgetLayout = new QVBoxLayout(centralWidget);

    toolsWidget = new QWidget(centralWidget);
    toolsLayout = new QHBoxLayout(toolsWidget);

    addTaskButton = new QPushButton("Add Task", toolsWidget);
    statusLabel = new QLabel(toolsWidget);
    topWidgetSpacer = new QSpacerItem(150, 20,
                                      QSizePolicy::Expanding,
                                      QSizePolicy::Minimum);
    toolsLayout->addWidget(statusLabel);
    toolsLayout->addItem(topWidgetSpacer);
    toolsLayout->addWidget(addTaskButton);

    toolsWidget->setLayout(toolsLayout);

    tasksScrollArea = new QScrollArea(centralWidget);

    tasksWidget = new QWidget(tasksScrollArea);
    tasksLayout = new QVBoxLayout(tasksWidget);
    tasksSpacer = new QSpacerItem(20, 40,
                                  QSizePolicy::Minimum,
                                  QSizePolicy::Expanding);
    tasksWidget->setLayout(tasksLayout);
    tasksLayout->addItem(tasksSpacer);
    tasksScrollArea->setWidget(tasksWidget);

    centralWidgetLayout->addWidget(toolsWidget);
    centralWidgetLayout->addWidget(tasksScrollArea);
    centralWidget->setLayout(centralWidgetLayout);

    mainWindow->setCentralWidget(centralWidget);
    tasksScrollArea->setWidgetResizable(true);
}
