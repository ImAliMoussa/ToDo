#include <QDebug>
#include <QInputDialog>
#include <QDesktopWidget>
#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    mTasks(),
    completedCount(0)
{
    //ui->setupUi(this);

    this->setWindowTitle("ToDo");
    this->setGeometry(
            QStyle::alignedRect(
                Qt::LeftToRight,
                Qt::AlignCenter,
                this->size(),
                qApp->desktop()->availableGeometry()
            )
        );
}

void MainWindow::setUpSlots() {
    connect(view->addTaskButton, &QPushButton::clicked,
            this, &MainWindow::addTask);
    updateStatus();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::updateStatus(){
    int toDoCount = this->mTasks.size() - this->completedCount;

    QString newStatus = QString("Status : %1 todo / %2 completed")
            .arg(toDoCount)
            .arg(completedCount);

    view->statusLabel->setText(newStatus);
}

void MainWindow::setView(View *view){
    this->view = view;
}

/*
 *  MAINWINDOW SLOTS:
 *
*/

//void MainWindow::addTask(){
//    bool userDidntPressCancel;
//    QString input = QInputDialog::getText(this,                     //parent
//                                           tr("New Task"),          //window title
//                                           tr("Task:"),             //label
//                                           QLineEdit::Normal,
//                                           tr("Untitled Task"),     //default string
//                                           &userDidntPressCancel);

//    if (userDidntPressCancel && !input.isEmpty()){
//        qDebug() << "Adding a new task!";

//        Task *newTask = new Task(input);
//        this->mTasks.append(newTask);
//        this->view->tasksLayout->insertWidget(0,newTask);

//        connect(newTask, &Task::taskRemoved, this, &MainWindow::removeTask);
//        connect(newTask, &Task::statusChanged,
//                this, &MainWindow::taskStatusChanged);

//        updateStatus();
//    }
//}

void MainWindow::addTask(){
    bool userDidntPressCancel = false;
    int priority = -1;
    QString input;
    TaskInputDialog::getInfo(&input, &priority, &userDidntPressCancel);

    if (userDidntPressCancel && !input.isEmpty()){
        qDebug() << "Adding a new task!";

        Task *newTask = new Task(input, priority + 1);
        this->mTasks.append(newTask);
        this->view->tasksLayout->insertWidget(0,newTask);

        connect(newTask, &Task::taskRemoved, this, &MainWindow::removeTask);
        connect(newTask, &Task::statusChanged,
                this, &MainWindow::taskStatusChanged);

        updateStatus();
    }
}


void MainWindow::removeTask(Task *task){
    this->mTasks.removeOne(task);
    view->tasksLayout->removeWidget(task);
    task->setParent(nullptr);
    delete task;
    updateStatus();
}

void MainWindow::taskStatusChanged(Task *task){
    if (task->isCompleted()) {
        ++this->completedCount;
    } else {
        --this->completedCount;
    }
    this->updateStatus();
}
