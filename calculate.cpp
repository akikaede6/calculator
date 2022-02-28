#include "calculate.h"

#include <iostream>

Calculate::Calculate(QObject *parent)
    : QObject{parent}
    , m_valid{false}
{}

void Calculate::parseText(const QString &text)
{
    QString number;
    for (int i = 0; i < text.size(); i++) {
        if (text.at(text.size() - 1) == "+" || text.at(text.size() - 1) == "-"
            || text.at(text.size() - 1) == "*" || text.at(text.size() - 1) == "/"
            || text.at(text.size() - 1) == "%") {
            m_valid = false;
            return;
        }
        m_valid = true;
        if (text.at(i).isNumber() || text.at(i) == ".") {
            number.append(text.at(i));
            if (i == text.size() - 1) {
                m_numbers.push(number);
                number.clear();
            }
        } else {
            if (m_operators.empty() || precede(text.at(i), m_operators.top())) {
                m_operators.push(text.at(i));
                m_numbers.push(number);
                number.clear();
            } else {
                calc(m_numbers, m_operators, isFloat(text));
            }
        }
    }
    while (!m_operators.empty()) {
        calc(m_numbers, m_operators, isFloat(text));
    }
    setResult();
    std::cout << m_numbers.top().toStdString();
}

void Calculate::setResult()
{
    if (isFloat(m_numbers.top()))
        m_result = QString::number(m_numbers.top().toDouble());
    else
        m_result = QString::number(m_numbers.top().toInt());
    emit finished(m_valid, m_result);
}

auto Calculate::evaluate(const QString &operate, const int &a, const int &b)
{
    if (operate == '+')
        return a + b;
    if (operate == '-')
        return a - b;
    if (operate == '*')
        return a * b;
    if (operate == '/')
        return a / b;
    return a % b;
}

auto Calculate::evaluate(const QString &operate, const double &a, const double &b)
{
    if (operate == '+')
        return a + b;
    if (operate == '-')
        return a - b;
    if (operate == '*')
        return a * b;
    if (operate == '/')
        return a / b;
}

bool Calculate::precede(const QString &input, const QString &top)
{
    return (input == "*" || input == "/") && (top == "+" || top == "-");
}

void Calculate::calc(QStack<QString> &numbers, QStack<QString> &operators, bool isFloatNumber)
{
    if (!isFloatNumber) {
        int a = numbers.top().toInt();
        numbers.pop();
        int b = numbers.top().toInt();
        numbers.pop();
        numbers.push(QString::number(evaluate(operators.top(), a, b)));
        operators.pop();
    } else {
        double a = numbers.top().toDouble();
        numbers.pop();
        double b = numbers.top().toDouble();
        numbers.pop();
        numbers.push(QString::number(evaluate(operators.top(), a, b)));
        operators.pop();
    }
}

bool Calculate::isFloat(const QString &text)
{
    return text.contains(".");
}
