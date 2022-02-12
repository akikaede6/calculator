#include "calculator.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Calculator calcutor;
    calcutor.show();
    return a.exec();
}
