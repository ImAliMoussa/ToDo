#include <QInputDialog>
#include <QDebug>
#include "task.h"
#include "taskinputdialog.h"
#include "ui_task.h"

bool Task::statInitFlag = false; //static variables initialized yet?
QPalette Task::redPal;
QPalette Task::yellowPal;
QPalette Task::greenPal;

//static pallete variables initialized before constructor
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

    this->priority = priority;
    this->setWidgetPriorityColors();
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
    bool userDidntPressCancel = false;
    QString input = this->name().remove(0,1);
    int priority = this->priority;
    //input variable initialized to previous input entered
    //weird bug makes name() return a '&' at start of string

    TaskInputDialog::getInfo(&input, &priority, &userDidntPressCancel);

    if (userDidntPressCancel){
        this->setName(input);
        this->priority = priority;
        this->setWidgetPriorityColors();
    }
}

void Task::check(bool checked){
    QFont font(ui->checkBox->font());
    font.setStrikeOut(checked);
    ui->checkBox->setFont(font);
    emit this->statusChanged(this);
}

void Task::setWidgetPriorityColors(){
    switch (this->priority) {
        case 0:
            this->setPalette(Task::greenPal);
            break;
        case 1:
            this->setPalette(Task::yellowPal);
            break;
        case 2:
            this->setPalette(Task::redPal);
            break;
        default:
            qDebug() << "Priority out of range";
            break;
    }
}
