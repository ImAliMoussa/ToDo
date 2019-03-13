#include <QDebug>
#include "taskinputdialog.h"
#include "ui_taskinputdialog.h"

TaskInputDialog::TaskInputDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::TaskInputDialog){
    qDebug() << "Instance of input dialog created";

    ui->setupUi(this);
    setWindowTitle("New Task");

    ui->priorityComboBox->addItem("Low");
    ui->priorityComboBox->addItem("Medium");
    ui->priorityComboBox->addItem("High");

    //call ::taskAccepted if "Ok"     button is pressed
    //call ::taskRejected if "Cancel" button is pressed
    connect(ui->okCancelBox, &QDialogButtonBox::accepted,
            this, &TaskInputDialog::taskAccepted);
    connect(ui->okCancelBox, &QDialogButtonBox::rejected,
            this, &TaskInputDialog::taskRejected);
}

TaskInputDialog::~TaskInputDialog(){
    delete ui;
}

/*
 * getInfo is passed three arguments, all three are pointers
 * getInfo stores the three pointers and will not manipulate contents of memory
 * pointed to by them. Contents of memory locations pointed to by pointers will
 * be manipulated in ::taskAccepted and ::taskRejected
 *
 * Input dialog is executed at end of the ::getInfo
 *
 * Now one of two functions will be executed: 1) ::taskAccepted (user pressed Ok)
 *                                            2) ::taskRejected (pressed cancel)
*/

void TaskInputDialog::getInfo(QString *taskText,
                              int *priority,
                              bool *userPressedOk)
{
    TaskInputDialog& inputDialog = TaskInputDialog::getInstance();

    inputDialog.taskText = taskText;
    inputDialog.priority = priority;
    inputDialog.userPressedOk = userPressedOk;
    inputDialog.ui->taskLineEdit->setFocus();

    if (taskText->isEmpty()){
        inputDialog.ui->taskLineEdit->setText("Untitled Task");
    } else {
        inputDialog.ui->taskLineEdit->setText(*taskText);
    }

    if (*priority != -1){
        inputDialog.ui->priorityComboBox->setCurrentIndex(*priority);
    } else {
        inputDialog.ui->priorityComboBox->setCurrentIndex(0);
    }

    inputDialog.exec();
}

void TaskInputDialog::taskAccepted(){
    *userPressedOk = true;
    *taskText = ui->taskLineEdit->text();
    *priority = ui->priorityComboBox->currentIndex();
}

void TaskInputDialog::taskRejected(){
    *userPressedOk = false;
}
