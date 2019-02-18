#include <QDebug>
#include <QInputDialog>
#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    mTasks()
{
    ui->setupUi(this);
    connect(ui->addTaskButton, &QPushButton::clicked, this, &MainWindow::addTask);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::addTask(){
    bool userDidntPressCancel;
    QString input = QInputDialog::getText(this,                     //parent
                                           tr("New Task"),          //window title
                                           tr("Task:"),             //label
                                           QLineEdit::Normal,
                                           tr("Untitled Task"),     //default string
                                           &userDidntPressCancel);

    if (userDidntPressCancel && !input.isEmpty()){
        qDebug() << "Adding a new task!";

        Task *newTask = new Task(input);
        this->mTasks.append(newTask);
        this->ui->tasksLayout->addWidget(newTask);
        connect(newTask, &Task::taskRemoved, this, &MainWindow::removeTask);
    }
}

void MainWindow::removeTask(Task *task){
    this->mTasks.removeOne(task);
    ui->tasksLayout->removeWidget(task);
    task->setParent(nullptr);
    delete task;
}
