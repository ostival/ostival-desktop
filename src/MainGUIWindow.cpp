/*
================================
All main window logics goes here
--------------------------------
Coded by:
Team Ostival (hello@ostival.org)
---------------------------------
*/

#include "MainGUIWindow.h"
#include "FileMenuBuilder.h"
#include "ToolBarBuilder.h"
#include "LeftDockBuilder.h"
#include "RightDockBuilder.h"
#include "CentralWidget.h"
#include "StatusBarBuilder.h"

MainGUIWindow::MainGUIWindow(QWidget *parent)
    : QMainWindow(parent)
{
    // File Menu Bar
    QMenuBar *bar = this->menuBar();
    new FileMenuBuilder(bar, this, this);

    // Toolbar
    new ToolBarBuilder(this, this);

    // Central Widget
    CentralWidget *central = new CentralWidget(this);
    setCentralWidget(central);

    // Left Dock Panel
    new LeftDockBuilder(this, this);

    // Right Dock Panel
    OstivalrightDockBuilder = new RightDockBuilder(this, this);

    // Status Bar
    OstivalstatusBarBuilder = new StatusBarBuilder(this);
    OstivalstatusBarBuilder->getStatusBar()->showMessage("Ready!", 1200);
}