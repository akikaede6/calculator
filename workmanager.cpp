#include "workmanager.h"
#include "calculate.h"
#include "calculator.h"

#include <QThread>
#include <iostream>

WorkManager *WorkManager::_m = nullptr;

WorkManager::WorkManager(QObject *parent)
    : QObject{parent}
    , m_cal(new Calculate)
    , m_ui(new Calculator)
    , m_thread(new QThread)
{
    connect(m_ui, &Calculator::start, m_cal, &Calculate::parseText);
    std::cout << "start";
    connect(m_cal, &Calculate::finished, m_ui, &Calculator::onCalFinished);
}

WorkManager *WorkManager::Instance(QObject *parent)
{
    if (!_m) {
        _m = new WorkManager(parent);
    }
    return _m;
}

WorkManager::~WorkManager() {}

void WorkManager::destroy()
{
    if (_m) {
        _m->deleteLater();
    }
    _m = nullptr;
}

//void WorkManager::start()
//{
//    m_model->start();
//}

//void WorkManager::clean()
//{
//    m_model->clean();
//}

//UserSettingsModel *PxeManager::model() const
//{
//    return m_model;
//}
