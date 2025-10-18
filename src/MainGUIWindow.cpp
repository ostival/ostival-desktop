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

    // Left Dock Panel
    OstivalleftDockBuilder = new LeftDockBuilder(this, this);

    // Right Dock Panel
    OstivalrightDockBuilder = new RightDockBuilder(this, this);
    
    // File Menu Bar
    QMenuBar *bar = this->menuBar();
    new FileMenuBuilder(bar, this, OstivalleftDockBuilder, OstivalrightDockBuilder, this);

    // Toolbar
    new ToolBarBuilder(this, this);

    // Central Widget
    CentralWidget *central = new CentralWidget(this);
    setCentralWidget(central);

    // Connect LeftDock signal to CentralWidget slot which will read file and display in qtexteditor
    QObject::connect(OstivalleftDockBuilder, &LeftDockBuilder::fileDoubleClicked,central, &CentralWidget::openFileInEditor);

    // Status Bar
    OstivalstatusBarBuilder = new StatusBarBuilder(this);
    OstivalstatusBarBuilder->getStatusBar()->showMessage("Ready!", 1200);
}