#include "window.h"
#include "calculator.h"

Window::Window(QWidget *parent) : QMainWindow(parent)
{
    Calculator *calculator = new Calculator;
    setCentralWidget(calculator);

    createAction();
    createMenu();

    setWindowTitle("Calculator");
}

void Window::createAction() {
    quitAction = new QAction(tr("Quit"), this);
    quitAction->setToolTip("Close the program");
    connect(quitAction, SIGNAL(triggered()), this, SLOT(close()));

    aboutQtAction = new QAction(tr("About Qt"), this);
    aboutQtAction->setToolTip("About Qt");
    connect(aboutQtAction, SIGNAL(triggered()), this, SLOT(aboutQtSlot()));

    aboutAction = new QAction(tr("About"), this);
    aboutAction->setToolTip("About this program");
    connect(aboutAction, SIGNAL(triggered()), this, SLOT(aboutSlot()));
}

void Window::createMenu() {
    //fileMenu = new QMenu(tr("File"), this);
    fileMenu = menuBar()->addMenu(tr("File"));
    fileMenu->addAction(quitAction);

    aboutMenu = menuBar()->addMenu(tr("About"));
    aboutMenu->addAction(aboutQtAction);
    aboutMenu->addAction(aboutAction);
}

void Window::aboutQtSlot() {
    //AboutDialog AboutDialog;
    QMessageBox::aboutQt(this, "title");
}

void Window::aboutSlot() {
    about(parent, "About Calculator", "Program version 0.1\n\nMade by Hamza Tamenaoul");
}
