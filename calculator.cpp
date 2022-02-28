#include "calculator.h"
#include "calculate.h"

#include <QGridLayout>
#include <QLineEdit>
#include <QPushButton>
#include <QRegExpValidator>
#include <QScriptEngine>
#include <QThread>

Calculator::Calculator(QWidget *parent)
    : QWidget{parent}
    , m_input{new QLineEdit}
    , m_digitButton{nullptr}
    , m_eq{new QPushButton("=")}
    , m_clear{new QPushButton("C")}
{
    setFixedSize(width, height);
    initUI();
    initConnection();
}

auto Calculator::generateButton(const QString &text) const
{
    auto *button = new QPushButton(text);
    connect(button, &QPushButton::clicked, this, &Calculator::onCalculatorClicked);
    return button;
}

void Calculator::initUI()
{
    auto *mainlayout = new QGridLayout(this);

    QRegExp regx("[1-9][0-9]+$");
    m_input->setValidator(new QRegExpValidator(regx, this));
    m_input->setAlignment(Qt::AlignRight);

    for (int i = 0; i < buttonNumber; i++)
        m_digitButton[i] = new QPushButton(QString::number(i));

    mainlayout->addWidget(m_input, ROW_ZERO, COL_ZERO, 1, 4);

    mainlayout->addWidget(m_clear, ROW_ONE, COL_ZERO);
    mainlayout->addWidget(generateButton("+/-"), ROW_ONE, COL_ONE);
    mainlayout->addWidget(generateButton("%"), ROW_ONE, COL_TWO);
    mainlayout->addWidget(generateButton("/"), ROW_ONE, COL_THREE);

    mainlayout->addWidget(generateButton("*"), ROW_TWO, COL_THREE);
    mainlayout->addWidget(generateButton("-"), ROW_THREE, COL_THREE);
    mainlayout->addWidget(generateButton("+"), ROW_FOUR, COL_THREE);

    mainlayout->addWidget(m_digitButton[0], ROW_FIVE, COL_ZERO, 1, 2);
    mainlayout->addWidget(generateButton("."), ROW_FIVE, COL_TWO);
    mainlayout->addWidget(m_eq, ROW_FIVE, COL_THREE);

    for (int i = 1; i < buttonNumber; i++) {
        int row = (buttonNumber - 1 - i) / 3 + 2;
        int col = (i + 2) % 3;
        mainlayout->addWidget(m_digitButton[i], row, col);
    }

    setLayout(mainlayout);
}

void Calculator::initConnection() const
{
    for (const auto &button : m_digitButton)
        connect(button, &QPushButton::clicked, this, &Calculator::onDigitClicked);
    connect(m_eq, &QPushButton::clicked, this, &Calculator::onEqClicked);
    connect(m_clear, &QPushButton::clicked, this, &Calculator::onClearClicked);
}

void Calculator::onDigitClicked()
{
    auto *digitBtn = qobject_cast<QPushButton *>(sender());
    if (m_input->text() == "0")
        m_input->setText(digitBtn->text());
    m_input->setText(m_input->text() + digitBtn->text());
}

void Calculator::onCalculatorClicked()
{
    auto *operateBtn = qobject_cast<QPushButton *>(sender());
    if (operateBtn->text() == "+/-") {
        if (m_input->text().front() == "-")
            m_input->setText(m_input->text().remove(0, 1));
        else
            m_input->setText(m_input->text().prepend("-"));
    } else if (!m_input->text().isEmpty()
               && (m_input->text().back() == "+" || m_input->text().back() == "-"
                   || m_input->text().back() == "*" || m_input->text().back() == "/"
                   || m_input->text().back() == "%"))
        m_input->setText(m_input->text().replace(m_input->text().back(), operateBtn->text()));
    else
        m_input->setText(m_input->text() + operateBtn->text());
}

void Calculator::onEqClicked()
{
    //    m_input->setText(QScriptEngine().evaluate(m_input->text()).toString());
    emit start(m_input->text());
}

void Calculator::onClearClicked()
{
    m_input->clear();
}

void Calculator::onCalFinished(bool valid, const QString &result)
{
    if (!valid)
        m_input->setText("error");
    else
        m_input->setText(result);
}
