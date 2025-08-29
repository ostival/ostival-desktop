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

    auto *mainLayout = new QVBoxLayout;
    mainLayout->addWidget(OstivalTextEdit);

    setLayout(mainLayout);
}