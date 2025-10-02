/*
================================
All left dock logics goes here
--------------------------------
Coded by:
Team Ostival (hello@ostival.org)
---------------------------------
*/

#include <QLabel>
#include <QMainWindow>
#include "LeftDockBuilder.h"

LeftDockBuilder::LeftDockBuilder(QMainWindow *mainWindow, QObject *parent)
    : QObject(parent), OstivalmainWindow(mainWindow)
{
    OstivalleftDock = new QDockWidget("Left Panel", OstivalmainWindow);
    OstivalmainWindow->addDockWidget(Qt::LeftDockWidgetArea, OstivalleftDock);

    QLabel *leftContent = new QLabel("<h3>History</h3><p>No history yet.</p>", OstivalleftDock);
    leftContent->setAlignment(Qt::AlignTop | Qt::AlignHCenter);
    leftContent->setWordWrap(true);

    OstivalleftDock->setWidget(leftContent);
    OstivalleftDock->setFeatures(QDockWidget::DockWidgetClosable | QDockWidget::DockWidgetMovable);
}

QDockWidget* LeftDockBuilder::getLeftDockWidget() const {
    return OstivalleftDock;
}