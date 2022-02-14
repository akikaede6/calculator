#ifndef CALCULATOR_H
#define CALCULATOR_H

#include <QWidget>

class QPushButton;
class QLineEdit;
class Calculator : public QWidget
{
    Q_OBJECT
public:
    explicit Calculator(QWidget *parent = nullptr);

    void initUI();
    void initConnection() const;
    auto generateButton(const QString &text) const;

public slots:
    void onDigitClicked();
    void onCalculatorClicked();
    void onEqClicked();
    void onClearClicked();

private:
    enum { buttonNumber = 10 };
    enum ROW { ROW_ZERO, ROW_ONE, ROW_TWO, ROW_THREE, ROW_FOUR, ROW_FIVE };
    enum COL { COL_ZERO, COL_ONE, COL_TWO, COL_THREE, COL_FOUR, COL_FIVE };
    const int width = 300;
    const int height = 400;
    QLineEdit *m_input;
    std::array<QPushButton *, buttonNumber> m_digitButton;
    QPushButton *m_eq;
    QPushButton *m_clear;
};

#endif // CALCULATOR_H
