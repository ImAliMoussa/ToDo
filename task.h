#ifndef TASK_H
#define TASK_H

#include <QWidget>
#include <QString>


namespace Ui {
class Task;
}

class Task : public QWidget
{
    Q_OBJECT

public:
    explicit Task(const QString& name, int priority, QWidget *parent = nullptr);
    ~Task();

    void setName(const QString &name);
    QString name() const;
    bool isCompleted() const;

signals:
    void taskRemoved(Task *task);
    void statusChanged(Task *task);

public slots:
    void renameTask();

private slots:
    void check(bool checked);

public:
    static bool statInitFlag;
    static QPalette redPal;
    static QPalette yellowPal;
    static QPalette greenPal;
    static void staticInit();

private:
    Ui::Task *ui;
    int priority;
    void setWidgetPriorityColors();
};

#endif // TASK_H
