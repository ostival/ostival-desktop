/*
================================
All main window logics goes here
--------------------------------
Coded by:
Team Ostival (hello@ostival.org)
---------------------------------
*/
#include <QWidget>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QPushButton>
#include <QMenuBar>
#include <QMenu>
#include <QAction>
#include <QToolBar>
#include <QDockWidget>
#include <QLabel>
#include <QString>
#include <QMessageBox>
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
    m_rightDockBuilder = new RightDockBuilder(this, this);

    // Status Bar
    m_statusBarBuilder = new StatusBarBuilder(this);
    m_statusBarBuilder->getStatusBar()->showMessage("Ready!", 3000);
}