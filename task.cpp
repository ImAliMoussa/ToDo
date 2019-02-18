#include <QInputDialog>
#include <QDebug>
#include "task.h"
#include "ui_task.h"

Task::Task(const QString &name, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Task)
{
    ui->setupUi(this);
    Task::setName(name);


    connect(ui->editButton, &QPushButton::clicked, this, &Task::renameTask);
    connect(ui->removeButton, &QPushButton::clicked, [this]{
        emit this->taskRemoved(this);
    });
}

Task::~Task()
{
    delete ui;
}

void Task::setName(const QString &name){
    this->ui->checkBox->setText(name);
}

QString Task::name() const{
    return ui->checkBox->text();
}

bool Task::isCompleted() const{
    return ui->checkBox->isChecked();
}

void Task::renameTask(){
    bool userDidntPressCancel;
    QString prev = this->name().remove(0,1);
    //weird bug makes name() return a '&' at start of string

    QString input = QInputDialog::getText(this,                     //parent
                                           tr("Edit task"),         //window title
                                           tr("Task:"),             //label
                                           QLineEdit::Normal,
                                           prev,                    //default string
                                           &userDidntPressCancel);

    if (userDidntPressCancel && !input.isEmpty()){
        qDebug() << "Renamed task";
        this->setName(input);
        qDebug() << input;
    }
}
