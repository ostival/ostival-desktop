/*
================================
Logic to draw schematic
--------------------------------
Coded by:
Team Ostival (hello@ostival.org)
---------------------------------
*/


#ifndef DRAWSCHEMATIC_H
#define DRAWSCHEMATIC_H



#include <QWidget>
#include <QPaintEvent>
#include <QPainter>
#include <QPainterPath>
#include <QPen>
#include <QBrush>
#include <QFont>
#include <QPoint>

class DrawSchematic : public QWidget
{
    Q_OBJECT

public:
    explicit DrawSchematic(QWidget *parent = nullptr);

protected:
    void paintEvent(QPaintEvent *event) override;           // to draw custom shapes
};


#endif