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

const QString MODERN_BUTTON_STYLE = R"(
    QPushButton {
        background-color: #00A9A5;
        color: white;
        border: none;
        border-radius: 6px;
        padding: 8px 16px;
        font-size: 14px;
    }
    QPushButton:hover {
        background-color: #008F8B;
    }
    QPushButton:pressed {
        background-color: #006B68;
    }
)";

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
            background-color: #f877ff;
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
    refreshButton->setStyleSheet(MODERN_BUTTON_STYLE);

    QPushButton *compileButton = new QPushButton("Compile");
    compileButton->setStyleSheet(MODERN_BUTTON_STYLE);

    QPushButton *simulateButton = new QPushButton("Simulate");
    simulateButton->setStyleSheet(MODERN_BUTTON_STYLE);

    QPushButton *synthesisButton = new QPushButton("Synthesis");
    synthesisButton->setStyleSheet(MODERN_BUTTON_STYLE);

    QPushButton *implementationButton = new QPushButton("PnR");
    implementationButton->setStyleSheet(MODERN_BUTTON_STYLE);

    QPushButton *layoutButton = new QPushButton("Generate Layout");
    layoutButton->setStyleSheet(MODERN_BUTTON_STYLE);

    layout->addWidget(header);
    layout->addWidget(listWidget);
    layout->addWidget(refreshButton);
    layout->addWidget(compileButton);
    layout->addWidget(simulateButton);
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