/*
================================
All right dock logics goes here
--------------------------------
Coded by:
Team Ostival (hello@ostival.org)
---------------------------------
*/

#include <QLabel>
#include <QMainWindow>
#include "RightDockBuilder.h"

RightDockBuilder::RightDockBuilder(QMainWindow *mainWindow, QObject *parent)
    : QObject(parent), OstivalmainWindow(mainWindow)
{
    OstivalrightDock = new QDockWidget("Right Panel", OstivalmainWindow);
    OstivalmainWindow->addDockWidget(Qt::RightDockWidgetArea, OstivalrightDock);

    QLabel *rightContent = new QLabel("<h3>Info</h3><p>Info will display here.</p>", OstivalrightDock);
    rightContent->setAlignment(Qt::AlignTop | Qt::AlignHCenter);
    rightContent->setWordWrap(true);

    OstivalrightDock->setWidget(rightContent);
    OstivalrightDock->setFeatures(QDockWidget::DockWidgetClosable | QDockWidget::DockWidgetMovable);
}

void RightDockBuilder::hideDock()
{
    if (OstivalrightDock)
        OstivalrightDock->hide();
}

void RightDockBuilder::showDock()
{
    if (OstivalrightDock)
        OstivalrightDock->show();
}