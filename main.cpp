#include "calculator.h"
#include "workmanager.h"

#include <QApplication>

auto main(int argc, char *argv[]) -> int
{
    QApplication a(argc, argv);
    Calculator calcutor;
    WorkManager *manager = new WorkManager;
    calcutor.show();
    return a.exec();
}
