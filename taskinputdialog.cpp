#include "taskinputdialog.h"
#include "ui_taskinputdialog.h"

TaskInputDialog::TaskInputDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::TaskInputDialog)
{
    ui->setupUi(this);
    setWindowTitle("New Task");

    ui->priorityComboBox->addItem("Low");
    ui->priorityComboBox->addItem("Medium");
    ui->priorityComboBox->addItem("High");

    connect(ui->okCancelBox, &QDialogButtonBox::accepted,
            this, &TaskInputDialog::taskAccepted);
    connect(ui->okCancelBox, &QDialogButtonBox::rejected,
            this, &TaskInputDialog::taskRejected);
}

TaskInputDialog::~TaskInputDialog()
{
    delete ui;
}

void TaskInputDialog::getInfo(QString *taskText,
                              int *priority,
                              QFont *font,
                              bool *userPressedOk)
{
    TaskInputDialog inputDialog;
    inputDialog.taskText = taskText;
    inputDialog.font = font;
    inputDialog.priority = priority;
    inputDialog.userPressedOk = userPressedOk;
    inputDialog.exec();
}

void TaskInputDialog::taskAccepted()
{
    *userPressedOk = true;
    *taskText = ui->taskLineEdit->text();
    *priority = ui->priorityComboBox->currentIndex();
    *font = ui->fontComboBox->currentFont();
}

void TaskInputDialog::taskRejected()
{
    *userPressedOk = false;
}

















