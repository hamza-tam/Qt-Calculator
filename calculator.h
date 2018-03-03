#ifndef CALCULATOR_H
#define CALCULATOR_H

#include <QWidget>
#include <QLineEdit>
#include <QGridLayout>

#include "button.h"


class Calculator : public QWidget
{
    Q_OBJECT

public:
    Calculator(QWidget *parent = 0);

private:
    Button* createButton(const QString &text, const char *slot);
    bool calculate(double operand, const QString &operation);

private:
    // Calculator variables
    double total;
    double inDisplay;
    bool waitingOperand;
    double sum;
    double factor;
    double operand;
    QString pendingMultiplicationOperation;
    QString pendingAdditionOperation;

    // Layout components
    QLineEdit *display;
    enum { numberDigitButtons = 10 };
    Button *digitButtons[numberDigitButtons];
    Button *pointButton;
    Button *divideButton;
    Button *multiplyButton;
    Button *sumButton;
    Button *subButton;
    Button *backButton;
    Button *clearButton;
    Button *equalButton;
    Button *clearAllButton;

private slots:
    void digitClicked();
    void pointClicked();
    void sumClicked();
    void multiplyClicked();
    void equalClicked();
    void backClicked();
    void clearClicked();
    void clearAllClicked();

};

#endif // CALCULATOR_H
