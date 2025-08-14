/*
================================
All central widget logics goes here
--------------------------------
Coded by:
Team Ostival (hello@ostival.org)
---------------------------------
*/
#include <QPushButton>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include "CentralWidget.h"


CentralWidget::CentralWidget(QWidget *parent)
    : QWidget(parent) {

    auto *addButton = new QPushButton("Button 1");
    auto *subtractButton = new QPushButton("Button 2");
    auto *multiplyButton = new QPushButton("Button 3");

    auto *buttonLayout = new QHBoxLayout;

    auto *mainLayout = new QVBoxLayout;

    setLayout(mainLayout);

}
