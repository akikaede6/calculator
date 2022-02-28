#ifndef WORKMANAGER_H
#define WORKMANAGER_H

#include <QObject>

class Calculator;
class Calculate;
class WorkManager : public QObject
{
    Q_OBJECT
public:
    explicit WorkManager(QObject *parent = nullptr);
    static WorkManager *Instance(QObject *parent = nullptr);
    ~WorkManager();
    void destroy();

private:
    Calculate *m_cal;
    Calculator *m_ui;
    QThread *m_thread;

private:
    static WorkManager *_m;
};

#endif // WORKMANAGER_H
