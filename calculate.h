#ifndef CALCULATE_H
#define CALCULATE_H

#include <QObject>
#include <QStack>

class Calculate : public QObject
{
    Q_OBJECT
public:
    explicit Calculate(QObject *parent = nullptr);

    static auto evaluate(const QString &operate, const int &a, const int &b);
    static auto evaluate(const QString &operate, const double &a, const double &b);
    static bool precede(const QString &input, const QString &top);
    static void calc(QStack<QString> &numbers, QStack<QString> &operators, bool isFloatNumber);
    static bool isFloat(const QString &text);
    void setResult();

public slots:
    void parseText(const QString &text);

signals:
    void finished(bool valid, QString result);

private:
    QStack<QString> m_operators;
    QStack<QString> m_numbers;
    QString m_result;
    bool m_valid;
};

#endif // CALCULATE_H
