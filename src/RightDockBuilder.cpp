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
#include "config.h"


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
    header->setFixedHeight(20);
    header->setStyleSheet(MODERN_TITLE_STYLE);

    QLabel *header1 = new QLabel("Constraints Files");
    header1->setAlignment(Qt::AlignCenter);
    header1->setFixedHeight(20);
    header1->setStyleSheet(MODERN_TITLE_STYLE);

    QListWidget *listWidget = new QListWidget;
    listWidget->setStyleSheet(MODERN_LIST_STYLE);
    listWidget->addItems({"Tool: ", "Status: ", "Technology: "});

    QListWidget *listWidget1 = new QListWidget;
    listWidget1->setStyleSheet(MODERN_LIST_STYLE);

    QPushButton *refreshButton = new QPushButton("Pre-Synthesis Check");
    refreshButton->setStyleSheet(MODERN_BUTTON_STYLE1);

    QPushButton *synthesisButton = new QPushButton("Run Synthesis");
    synthesisButton->setStyleSheet(MODERN_BUTTON_STYLE1);

    QPushButton *implementationButton = new QPushButton("Run PnR");
    implementationButton->setStyleSheet(MODERN_BUTTON_STYLE1);

    QPushButton *layoutButton = new QPushButton("Generate Layout/Bitstream");
    layoutButton->setStyleSheet(MODERN_BUTTON_STYLE1);

    layout->addWidget(header);
    layout->addWidget(listWidget);
    layout->addWidget(header1);
    layout->addWidget(listWidget1);
    layout->addWidget(refreshButton);
    // layout->addWidget(compileButton);
    // layout->addWidget(simulateButton);
    layout->addWidget(synthesisButton);
    layout->addWidget(implementationButton);
    layout->addWidget(layoutButton);

    container->setLayout(layout);
    OstivalrightDock->setWidget(container);

    OstivalrightDock->setFeatures(QDockWidget::DockWidgetClosable | QDockWidget::DockWidgetMovable);

}

QDockWidget* RightDockBuilder::getRightDockWidget() const {
    return OstivalrightDock;
}