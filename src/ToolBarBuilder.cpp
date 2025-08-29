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
    : QObject(parent), OstivalmainWindow(mainWindow)
{
    OstivalguiWindow = qobject_cast<MainGUIWindow *>(mainWindow);

    if (!OstivalguiWindow)
        return;

    QToolBar *toolBar = new QToolBar("Main Toolbar", OstivalmainWindow);
    OstivalmainWindow->addToolBar(Qt::TopToolBarArea, toolBar);

    QAction *addToolAction = new QAction("Action 1", OstivalmainWindow);
    QAction *subtractToolAction = new QAction("Action 2", OstivalmainWindow);
    QAction *multiplyToolAction = new QAction("Action 3", OstivalmainWindow);

}