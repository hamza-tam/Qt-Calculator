#include "calculator.h"

Calculator::Calculator(QWidget *parent) : QWidget(parent) {
    // Initilizing program variables
    inDisplay = 0;
    waitingOperand = true;
    factor = 0;
    sum = 0;
    pendingAdditionOperation.clear();
    pendingMultiplicationOperation.clear();

    // Creating the display
    display = new QLineEdit(QString::number(inDisplay));
    display->setReadOnly(true);
    display->setAlignment(Qt::AlignRight);
    display->setMaxLength(15);

    // Setting the display font
    QFont font = display->font();
    font.setPointSize(font.pointSize() + 8);
    display->setFont(font);

    // creating digit buttons buttons
    for (int i = 0; i < numberDigitButtons; i++) {
        digitButtons[i] = createButton(QString::number(i), SLOT(digitClicked()));
    }

    // Creating the buttons
    pointButton = createButton(tr("."), SLOT(pointClicked()));
    divideButton = createButton(tr("/"), SLOT(multiplyClicked()));
    multiplyButton = createButton(tr("x"), SLOT(multiplyClicked()));
    sumButton = createButton(tr("+"), SLOT(sumClicked()));
    subButton = createButton(tr("-"), SLOT(sumClicked()));
    backButton = createButton(tr("Backspace"), SLOT(backClicked()));
    clearButton = createButton(tr("Clear"), SLOT(clearClicked()));
    equalButton = createButton(tr("="), SLOT(equalClicked()));
    clearAllButton = createButton(tr("C"), SLOT(clearAllClicked()));

    // Setting the layout
    QGridLayout *mainLayout = new QGridLayout;
    mainLayout->setSizeConstraint(QLayout::SetFixedSize);

    mainLayout->addWidget(display, 0 , 0, 1, 6);

    int row, col;
    for (int i = 0; i < numberDigitButtons; i++) {
        if (i == 0) { col = 0; row = 5; }
        else {
            col = (i + 2) % 3;
            row = (3 - ( (i + 2) / 3 ) ) + 2;
        }
        mainLayout->addWidget(digitButtons[i], row, col);
    }

    mainLayout->addWidget(pointButton, 5, 1);
    mainLayout->addWidget(backButton, 1, 0, 1, 2);
    mainLayout->addWidget(clearButton, 1, 2);
    mainLayout->addWidget(clearAllButton, 1, 3);
    mainLayout->addWidget(divideButton, 2, 3);
    mainLayout->addWidget(multiplyButton, 3, 3);
    mainLayout->addWidget(subButton, 4, 3);
    mainLayout->addWidget(sumButton, 5, 3);
    mainLayout->addWidget(equalButton, 5, 2);

    // Setting window last parameters
    setLayout(mainLayout);

    setWindowTitle(tr("Calculator"));


}

Button* Calculator::createButton(const QString &text, const char *slot) {
    Button *button = new Button(text);
    connect(button, SIGNAL(clicked()), this, slot);

    return button;
}

void Calculator::digitClicked() {
    Button *clickedButton = qobject_cast<Button *>(sender());
    int digitSelected = clickedButton->text().toInt();

    if (display->text() == "0" && digitSelected == 0.0) {
        return;
    }

    if (waitingOperand) {
        display->clear();
        waitingOperand = false;
    }

    display->setText(display->text() + QString::number(digitSelected));
}

void Calculator::multiplyClicked() {
    Button *buttonClicked = qobject_cast<Button *>(sender());
    QString operation = buttonClicked->text();
    double operand = display->text().toDouble();

    // Calculating any pending multiplicative operation
    if (!pendingMultiplicationOperation.isEmpty()) {
        calculate(operand, pendingMultiplicationOperation);

        display->setText(QString::number(factor));
        pendingAdditionOperation.clear();
    } else {
        factor = operand;
    }

    // Adding operation to the cue
    pendingMultiplicationOperation = operation;
    waitingOperand = true;
}

void Calculator::sumClicked() {
    Button *buttonClicked = qobject_cast<Button *>(sender());
    QString operation = buttonClicked->text();
    operand = display->text().toDouble();

    // Calculating any pending multiplicative operation
    if (!pendingMultiplicationOperation.isEmpty()) {
        calculate(operand, pendingMultiplicationOperation);

        display->setText(QString::number(factor));
        operand = factor;
        factor = 0;
        pendingMultiplicationOperation.clear();
    }

    // Calculating any pending additive operation
    if (!pendingAdditionOperation.isEmpty()) {
        calculate(operand, pendingAdditionOperation);

        display->setText(QString::number(sum));
    } else {
        sum = operand;
    }

    // Adding the current selected operation to the cue
    pendingAdditionOperation = operation;
    waitingOperand = true;
}

void Calculator::equalClicked() {
    double operand = display->text().toDouble();

    // Calculating any pending multilicative operation
    if (!pendingMultiplicationOperation.isEmpty()) {
        calculate(operand, pendingMultiplicationOperation);

        display->setText(QString::number(factor));
        operand = factor;
        factor = 0;
        pendingAdditionOperation.clear();
    }

    // Calculating any pending additive operation
    if (!pendingAdditionOperation.isEmpty()) {
        calculate(operand, pendingAdditionOperation);
        pendingAdditionOperation.clear();
    } else {
        sum = operand;
    }

    // Displaying and resetting
    display->setText(QString::number(sum));
    sum = 0;
    factor = 0;
    pendingAdditionOperation.clear();
    pendingAdditionOperation.clear();
    waitingOperand = true;
}

void Calculator::pointClicked() {
    if (waitingOperand)
        display->setText("0");
    if (!display->text().contains("."))
        display->setText(display->text() + tr("."));
}

void Calculator::backClicked() {
    if (waitingOperand) return;

    QString text = display->text();
    text.chop(1);

    if (text.isEmpty()) {
        text = "0";
        waitingOperand = true;
    }

    display->setText(text);
}

void Calculator::clearClicked() {
    if (waitingOperand) return;

    display->setText("0");
    waitingOperand = true;
}

void Calculator::clearAllClicked() {
    display->setText("0");
    sum = 0;
    factor = 0;
    pendingAdditionOperation.clear();
    pendingMultiplicationOperation.clear();
    waitingOperand = true;
}

bool Calculator::calculate(double operand, const QString &operation) {
    if (operation == tr("+")) sum += operand;
    if (operation == tr("x")) factor *= operand;
    if (operation == tr("-")) sum -= operand;
    if (operation == tr("/")) factor /= operand;

    return true;
}
