/*
================================
All status bar logics goes here
--------------------------------
Coded by:
Team Ostival (hello@ostival.org)
---------------------------------
*/

#include "StatusBarBuilder.h"

StatusBarBuilder::StatusBarBuilder(QMainWindow *mainWindow)
{
    OstivalStatusBar = new QStatusBar(mainWindow);
    mainWindow->setStatusBar(OstivalStatusBar);
    OstivalStatusBar->showMessage("Ready!", 3000);
}

QStatusBar *StatusBarBuilder::getStatusBar() const
{
    return OstivalStatusBar;
}