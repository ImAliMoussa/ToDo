#ifndef TASKINPUTDIALOG_H
#define TASKINPUTDIALOG_H

#include <QDialog>
#include <task.h>

namespace Ui {
class TaskInputDialog;
}

class TaskInputDialog : public QDialog
{
    Q_OBJECT

public:
    explicit TaskInputDialog(QWidget *parent = nullptr);
    ~TaskInputDialog();

    static void getInfo(QString *taskText,
                        int *priority,
                        QFont *font,
                        bool *userPressedOk);
private:
    Ui::TaskInputDialog *ui;
    int *priority;
    QFont *font;
    QString *taskText;
    bool *userPressedOk;

private:
    void taskAccepted();
    void taskRejected();
};

#endif // TASKINPUTDIALOG_H
