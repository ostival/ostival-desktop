/*
================================
All right dock logics goes here
--------------------------------
Coded by:
Team Ostival (hello@ostival.org)
---------------------------------
*/

#ifndef RIGHTDOCKBUILDER_H
#define RIGHTDOCKBUILDER_H

#include <QObject>
#include <QDockWidget>

class QMainWindow;

class RightDockBuilder : public QObject
{
    Q_OBJECT

public:
    explicit RightDockBuilder(QMainWindow *mainWindow, QObject *parent = nullptr);
    QDockWidget* getRightDockWidget() const;

private:
    QMainWindow *OstivalmainWindow;
    QDockWidget *OstivalrightDock;
};

#endif