#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QVector>
#include <task.h>
#include <view.h>


namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void updateStatus();
    void setView(View *view);
    void setUpSlots();

public slots:
    void addTask();
    void removeTask(Task *task);
    void taskStatusChanged(Task *task); //task completion status

private:
    Ui::MainWindow *ui;
    QVector<Task*> mTasks;
    int completedCount;
    View *view;
};

#endif // MAINWINDOW_H
