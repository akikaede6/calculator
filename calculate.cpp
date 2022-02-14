#include "calculate.h"

Calculate::Calculate(QObject *parent)
    : QObject{parent}
{}

bool Calculate::parseText(const QString &text)
{
    QString number;
    for (int i = 0; i < text.size(); i++) {
        if (text.at(text.size() - 1) == "+" || text.at(text.size() - 1) == "-"
            || text.at(text.size() - 1) == "*" || text.at(text.size() - 1) == "/"
            || text.at(text.size() - 1) == "%")
            return false;
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
    return true;
}

auto Calculate::evaluate(QString operate, int a, int b)
{
    if (operate == '+') {
        return a + b;
    } else if (operate == '-') {
        return a - b;
    } else if (operate == '*') {
        return a * b;
    } else if (operate == '/') {
        return a / b;
    } else {
        return a % b;
    }
}

auto Calculate::evaluate(QString operate, double a, double b)
{
    if (operate == '+') {
        return a + b;
    } else if (operate == '-') {
        return a - b;
    } else if (operate == '*') {
        return a * b;
    } else if (operate == '/') {
        return a / b;
    } /*else {
        return false
    }*/
}

bool Calculate::precede(QString input, QString top)
{
    if ((input == "*" || input == "/") && (top == "+" || top == "-"))
        return true;
    return false;
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

QString Calculate::result()
{
    if (isFloat(m_numbers.top()))
        return QString::number(m_numbers.top().toDouble());
    return QString::number(m_numbers.top().toInt());
}

bool Calculate::isFloat(const QString &text)
{
    if (text.contains("."))
        return true;
    return false;
}
