#ifndef CALCULATOR_H
#define CALCULATOR_H

#include <QWidget>

enum {buttonNumber = 10};

class QPushButton;
class QLineEdit;
class Calculator : public QWidget
{
    Q_OBJECT
public:
    explicit Calculator(QWidget *parent = nullptr);

    void initUI();
    void initConnection() const;
    QPushButton *generateButton(QString text);

public slots:
    void onDigitClicked();
    void onCalculatorClicked();
    void onEqClicked();
    void onClearClicked();
    void onSignClicked();

private:
    QLineEdit *m_input;

    QPushButton *m_digitButton[buttonNumber];

    QPushButton *m_eq;
    QPushButton *m_clear;
};

#endif // CALCULATOR_H
