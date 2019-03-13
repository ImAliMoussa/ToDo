#ifndef TASKINPUTDIALOG_H
#define TASKINPUTDIALOG_H

#include <QDialog>
#include <task.h>

namespace Ui {
class TaskInputDialog;
}

/*
 * Class will have a singleton instance to avoid a new dialog every time.
 */

class TaskInputDialog : public QDialog
{
    Q_OBJECT

public:
    ~TaskInputDialog();

    static void getInfo(QString *taskText,
                        int *priority,
                        bool *userPressedOk);

    // Functions to make class a singleton
    static TaskInputDialog& getInstance(){
        static TaskInputDialog instance;    // Instantiated on first use

        return instance;
    }

    /*
     * Delete copy constructor and assignment operator
     */
    TaskInputDialog(TaskInputDialog const &t) = delete;
    void  operator=(TaskInputDialog const &t) = delete;

private:
    Ui::TaskInputDialog *ui;
    int *priority;
    QString *taskText;
    bool *userPressedOk;

private:
    void taskAccepted();
    void taskRejected();

    /*
     * Constructor made private
     * implemented in cpp file
     */
    explicit TaskInputDialog(QWidget *parent = nullptr);
};

#endif // TASKINPUTDIALOG_H
