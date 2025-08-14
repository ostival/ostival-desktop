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
    : QObject(parent), m_mainWindow(mainWindow)
{
    m_rightDock = new QDockWidget("Right Panel", m_mainWindow);
    m_mainWindow->addDockWidget(Qt::RightDockWidgetArea, m_rightDock);

    QLabel *rightContent = new QLabel("<h3>Info</h3><p>Info will display here.</p>", m_rightDock);
    rightContent->setAlignment(Qt::AlignTop | Qt::AlignHCenter);
    rightContent->setWordWrap(true);

    m_rightDock->setWidget(rightContent);
    m_rightDock->setFeatures(QDockWidget::DockWidgetClosable | QDockWidget::DockWidgetMovable);
}

void RightDockBuilder::hideDock()
{
    if (m_rightDock)
        m_rightDock->hide();
}

void RightDockBuilder::showDock()
{
    if (m_rightDock)
        m_rightDock->show();
}