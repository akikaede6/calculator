#include "mainwindow.h"
#include "calculator.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    setFixedSize(300, 400);
    Calculator *calcutor = new Calculator(this);
    setCentralWidget(calcutor);
}

MainWindow::~MainWindow()
{
}


