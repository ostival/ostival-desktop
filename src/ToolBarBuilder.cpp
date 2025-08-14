/*
================================
All toolbaar logics goes here
--------------------------------
Coded by:
Team Ostival (hello@ostival.org)
---------------------------------
*/
#include <QAction>
#include "ToolBarBuilder.h"
#include "MainGUIWindow.h"

ToolBarBuilder::ToolBarBuilder(QMainWindow *mainWindow, QObject *parent)
    : QObject(parent), m_mainWindow(mainWindow)
{
    m_guiWindow = qobject_cast<MainGUIWindow *>(mainWindow);

    if (!m_guiWindow)
        return;

    QToolBar *toolBar = new QToolBar("Main Toolbar", m_mainWindow);
    m_mainWindow->addToolBar(Qt::TopToolBarArea, toolBar);

    QAction *addToolAction = new QAction("Action 1", m_mainWindow);
    QAction *subtractToolAction = new QAction("Action 2", m_mainWindow);
    QAction *multiplyToolAction = new QAction("Action 3", m_mainWindow);

}