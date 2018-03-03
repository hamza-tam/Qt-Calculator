#include "aboutdialog.h"

AboutDialog::AboutDialog(QWidget *parent) : QMessageBox(parent) {
    setWindowTitle("About Calculator");
    setText("this is some text");
    setModal(true);
    //about(parent, "About Calculator", "Program version 0.1\n\nMade by Hamza Tamenaoul");
    exec();
}
