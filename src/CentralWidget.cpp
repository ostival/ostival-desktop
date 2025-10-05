/*
================================
Central Widget (Currently Text Editor)
--------------------------------
Coded by:
Team Ostival (hello@ostival.org)
---------------------------------
*/

#include <QVBoxLayout>
#include <QFont>
#include "CentralWidget.h"
#include "SyntaxHighlighter.h"

CentralWidget::CentralWidget(QWidget *parent)
    : QWidget(parent) {

    OstivalTextEdit = new QTextEdit(this);
    
    OstivalTextEdit->setPlaceholderText("Ostival text editor...");

    OstivalTextEdit->setFont(QFont("Courier", 16));

    OstivalTextEdit->setStyleSheet("background-color: #282A36; color: #F8F8F2;");

    new SyntaxHighlighter(OstivalTextEdit->document());

    saveButton = new QPushButton("Save File", this);
    saveButton->setFixedHeight(36);
    saveButton->setStyleSheet(R"(
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

    auto *mainLayout = new QVBoxLayout;
    mainLayout->addWidget(OstivalTextEdit);
    mainLayout->addWidget(saveButton);


    setLayout(mainLayout);
}