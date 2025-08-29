/*
================================
All left dock logics goes here
--------------------------------
Coded by:
Team Ostival (hello@ostival.org)
---------------------------------
*/

#ifndef LEFTDOCKBUILDER_H
#define LEFTDOCKBUILDER_H

#include <QObject>
#include <QDockWidget>

class QMainWindow;

class LeftDockBuilder : public QObject
{
    Q_OBJECT

public:
    explicit LeftDockBuilder(QMainWindow *mainWindow, QObject *parent = nullptr);

private:
    QMainWindow *OstivalmainWindow;
    QDockWidget *OstivalleftDock;
};

#endif