/*
================================
All toolbaar logics goes here
--------------------------------
Coded by:
Team Ostival (hello@ostival.org)
---------------------------------
*/

#ifndef TOOLBARBUILDER_H
#define TOOLBARBUILDER_H

#include <QObject>
#include <QToolBar>

class MainGUIWindow;

class ToolBarBuilder : public QObject
{
    Q_OBJECT

public:
    ToolBarBuilder(QMainWindow *mainWindow, QObject *parent = nullptr);

private:
    QMainWindow *OstivalmainWindow;
    MainGUIWindow *OstivalguiWindow;
};

#endif