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
    m_statusBar = new QStatusBar(mainWindow);
    mainWindow->setStatusBar(m_statusBar);
    m_statusBar->showMessage("Ready!", 3000);
}

QStatusBar *StatusBarBuilder::getStatusBar() const
{
    return m_statusBar;
}