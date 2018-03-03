#include <QApplication>

#include "window.h"
#include "calculator.h"

int main (int argc, char** argv) {

    QApplication app(argc, argv);

    Window window;
    window.show();

    /*
    Calculator calc;
    calc.show();
    */
    return app.exec();
}

