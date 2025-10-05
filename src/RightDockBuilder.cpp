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
#include <QPushButton>
#include <QListWidget>
#include <QVBoxLayout>
#include "RightDockBuilder.h"

RightDockBuilder::RightDockBuilder(QMainWindow *mainWindow, QObject *parent)
    : QObject(parent), OstivalmainWindow(mainWindow)
{
    OstivalrightDock = new QDockWidget("Right Panel", OstivalmainWindow);
    OstivalmainWindow->addDockWidget(Qt::RightDockWidgetArea, OstivalrightDock);

    QWidget *container = new QWidget;
    container->setStyleSheet(R"(
    QWidget {
        background-color: #f2ffdb;
        border-radius: 12px;
        border: 1px solid #CCCCCC;
    }
    )");

    QVBoxLayout *layout = new QVBoxLayout(container);

    QLabel *header = new QLabel("Current Project Status");
    header->setAlignment(Qt::AlignCenter);
    header->setFixedHeight(40);
    header->setStyleSheet(R"(
        QLabel {
            background-color: #002b73;
            color: white;
            border-radius: 12px;
            font-size: 16px;
            font-weight: 600;
            padding-left: 10px;
            padding-right: 10px;
        }
    )");

    QListWidget *listWidget = new QListWidget;
    listWidget->addItems({"Tool: ", "Status: ", "Technology: "});

    QPushButton *refreshButton = new QPushButton("Refresh");
    refreshButton->setStyleSheet(R"(
    QPushButton {
        background-color: #196042;
        color: white;
        border-radius: 10px;
        padding: 6px 12px;
        font-size: 14px;
    }
    QPushButton:hover {
        background-color: #002b73;
    }
    QPushButton:pressed {
        background-color: #9cd304;
    }
    )");

    layout->addWidget(header);
    layout->addWidget(listWidget);
    layout->addWidget(refreshButton);

    container->setLayout(layout);
    OstivalrightDock->setWidget(container);

    OstivalrightDock->setFeatures(QDockWidget::DockWidgetClosable | QDockWidget::DockWidgetMovable);

}

QDockWidget* RightDockBuilder::getRightDockWidget() const {
    return OstivalrightDock;
}