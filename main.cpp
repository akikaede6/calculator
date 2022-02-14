#include "calculator.h"

#include <QApplication>

auto main(int argc, char *argv[]) -> int
{
    QApplication a(argc, argv);
    Calculator calcutor;
    calcutor.show();
    return a.exec();
}
