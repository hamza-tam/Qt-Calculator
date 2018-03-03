#ifndef ABOUTDIALOG_H
#define ABOUTDIALOG_H

#include <QObject>
#include <QWidget>
#include <QDialog>
#include <QMessageBox>

class AboutDialog : public QMessageBox
{   
    Q_OBJECT

public:
    AboutDialog(QWidget *parent = 0);

private:
};

#endif // ABOUTDIALOG_H
