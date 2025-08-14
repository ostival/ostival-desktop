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
    : QObject(parent), m_mainWindow(mainWindow)
{
    m_leftDock = new QDockWidget("Left Panel", m_mainWindow);
    m_mainWindow->addDockWidget(Qt::LeftDockWidgetArea, m_leftDock);

    QLabel *leftContent = new QLabel("<h3>History</h3><p>No history yet.</p>", m_leftDock);
    leftContent->setAlignment(Qt::AlignTop | Qt::AlignHCenter);
    leftContent->setWordWrap(true);

    m_leftDock->setWidget(leftContent);
    m_leftDock->setFeatures(QDockWidget::DockWidgetClosable | QDockWidget::DockWidgetMovable);
}