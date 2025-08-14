/*
================================
All central widget logics goes here
--------------------------------
Coded by:
Team Ostival (hello@ostival.org)
---------------------------------
*/
#ifndef CENTRALWIDGET_H
#define CENTRALWIDGET_H

#include <QWidget>

class InputPanel;
class ResultPanel;
class QPushButton;

class CentralWidget : public QWidget {
    Q_OBJECT

public:
    explicit CentralWidget(QWidget *parent = nullptr);

};

#endif