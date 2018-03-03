#ifndef WINDOW_H
#define WINDOW_H

#include <QWidget>
#include <QMainWindow>

#include <QAction>
#include <QMenu>
#include <QMenuBar>


class Window : public QMainWindow
{
    Q_OBJECT

public:
    Window(QWidget *parent = 0);

private:
    // Window menus
    QMenu *fileMenu;
    QMenu *aboutMenu;

    // Window actions
    QAction *quitAction;
    QAction *aboutQtAction;
    QAction *aboutAction;

    // Methods
    void createMenu();
    void createAction();

private slots:
    void aboutQtSlot();
    void aboutSlot();

};

#endif // WINDOW_H
