#ifndef CALCULATE_H
#define CALCULATE_H

#include <QObject>
#include <QStack>

class Calculate : public QObject
{
public:
    explicit Calculate(QObject *parent = nullptr);
    bool parseText(const QString &text);
    auto evaluate(QString operate, int a, int b);
    auto evaluate(QString operate, double a, double b);
    bool precede(QString input, QString top);
    void calc(QStack<QString> &numbers, QStack<QString> &operators, bool isFloatNumber);
    QString result();
    bool isFloat(const QString &text);

private:
    QStack<QString> m_operators;
    QStack<QString> m_numbers;
};

#endif // CALCULATE_H
