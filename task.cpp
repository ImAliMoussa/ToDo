#include <QInputDialog>
#include <QDebug>
#include "task.h"
#include "ui_task.h"

bool Task::statInitFlag = false;
QPalette Task::redPal;
QPalette Task::yellowPal;
QPalette Task::greenPal;

void Task::staticInit(){
    Task::redPal = QPalette();
    Task::yellowPal = QPalette();
    Task::greenPal = QPalette();

    Task::greenPal.setColor(QPalette::Foreground, Qt::green);
    Task::greenPal.setColor(QPalette::ButtonText, Qt::green);

    Task::redPal.setColor(QPalette::Foreground, Qt::red);
    Task::redPal.setColor(QPalette::ButtonText, Qt::red);

    Task::yellowPal.setColor(QPalette::Foreground, Qt::yellow);
    Task::yellowPal.setColor(QPalette::ButtonText, Qt::yellow);

    Task::statInitFlag = true;
}

Task::Task(const QString &name, int priority, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Task){
    if (statInitFlag == false){
        staticInit();
    }

    ui->setupUi(this);
    Task::setName(name);

    connect(ui->editButton, &QPushButton::clicked, this, &Task::renameTask);
    connect(ui->removeButton, &QPushButton::clicked, [this]{
        emit this->taskRemoved(this);
    });
    connect(ui->checkBox, &QCheckBox::toggled, this, &Task::check);
    switch (priority) {
        case 1:
            this->setPalette(Task::greenPal);
            break;
        case 2:
            this->setPalette(Task::yellowPal);
            break;
        case 3:
            this->setPalette(Task::redPal);
            break;
    }
    this->setAutoFillBackground(true);
}

Task::~Task(){
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

void Task::check(bool checked){
    QFont font(ui->checkBox->font());
    font.setStrikeOut(checked);
    ui->checkBox->setFont(font);
    emit this->statusChanged(this);
}
