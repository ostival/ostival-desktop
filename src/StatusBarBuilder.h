/*
================================
All status bar logics goes here
--------------------------------
Coded by:
Team Ostival (hello@ostival.org)
---------------------------------
*/

#ifndef STATUSBARBUILDER_H
#define STATUSBARBUILDER_H

#include <QObject>
#include <QStatusBar>
#include <QMainWindow>

class StatusBarBuilder : public QObject
{
    Q_OBJECT

public:
    explicit StatusBarBuilder(QMainWindow *mainWindow);

    QStatusBar *getStatusBar() const;

private:
    QStatusBar *OstivalStatusBar;
};

#endif