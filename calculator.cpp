#include "calculator.h"

#include <QGridLayout>
#include <QDebug>
#include <QScriptEngine>
#include <QPushButton>
#include <QLineEdit>
#include <iostream>

Calculator::Calculator(QWidget *parent)
    : QWidget{parent}
{
    initUI();
    initConnection();
}

void Calculator::initUI()
{
    QGridLayout *mainlayout = new QGridLayout(this);
    m_input = new QLineEdit;

    m_eq = new QPushButton("=");
    m_clear = new QPushButton("C");

    for (int i = 0; i < buttonNumber; i++)
        m_digitButton[i] = new QPushButton(QString::number(i));

    mainlayout->addWidget(m_input, 0, 0, 1, 4);

    mainlayout->addWidget(m_clear, 1, 0);
    mainlayout->addWidget(generateButton("+/-"), 1, 1);
    mainlayout->addWidget(generateButton("%"), 1, 2);
    mainlayout->addWidget(generateButton("/"), 1, 3);

    mainlayout->addWidget(generateButton("*"), 2, 3);
    mainlayout->addWidget(generateButton("-"), 3, 3);
    mainlayout->addWidget(generateButton("+"), 4, 3);

    mainlayout->addWidget(m_digitButton[0], 5, 0, 1, 2);
    mainlayout->addWidget(generateButton("."), 5, 2);
    mainlayout->addWidget(m_eq, 5, 3);

    for (int i = 1; i < buttonNumber; i++)
    {
        int row = (buttonNumber - 1 - i) / 3 + 2;
        int col = (i + 2) % 3;
        mainlayout->addWidget(m_digitButton[i], row, col);
    }

    setLayout(mainlayout);
}

void Calculator::initConnection() const
{
    for (int i = 0; i < buttonNumber; i++)
        connect(m_digitButton[i], &QPushButton::clicked, this, &Calculator::onDigitClicked);
    connect(m_eq, &QPushButton::clicked, this, &Calculator::onEqClicked);
    connect(m_clear, &QPushButton::clicked, this, &Calculator::onClearClicked);
}

QPushButton *Calculator::generateButton(QString text)
{
    QPushButton *button = new QPushButton(text);
    connect(button, &QPushButton::clicked, this, &Calculator::onCalculatorClicked);
    return button;
}

void Calculator::onDigitClicked()
{
    QPushButton *digitBtn = qobject_cast<QPushButton *>(sender());
    if (m_input->text() == "0")
        m_input->setText(digitBtn->text());
    m_input->setText(m_input->text() + digitBtn->text());
}

void Calculator::onCalculatorClicked()
{
    QPushButton *operateBtn = qobject_cast<QPushButton *>(sender());
    if (operateBtn->text() == "+/-")
    {
        if (m_input->text().front() == "-")
            m_input->setText(m_input->text().remove(0, 1));
        else
            m_input->setText(m_input->text().prepend("-"));
    }
    else if (m_input->text().back() == "+" ||
             m_input->text().back() == "-" ||
             m_input->text().back() == "*" ||
             m_input->text().back() == "/" ||
             m_input->text().back() == "%")
        m_input->setText(m_input->text().replace(m_input->text().back(), operateBtn->text()));
    else
        m_input->setText(m_input->text() + operateBtn->text());
}

void Calculator::onEqClicked()
{
    m_input->setText(QScriptEngine().evaluate(m_input->text()).toString());
}

void Calculator::onClearClicked()
{
    m_input->clear();
}

void Calculator::onSignClicked()
{

}
